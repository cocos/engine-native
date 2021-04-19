#include "PhysXWorld.h"
#include "../spec/IWorld.h"
#include "PhysXInc.h"
#include "PhysXUtils.h"

using namespace physx;

namespace cc {
namespace physics {

PhysXWorld *PhysXWorld::instance = nullptr;
PhysXWorld &PhysXWorld::getInstance() {
    return *instance;
}

PxFoundation &PhysXWorld::getFundation() {
    return *getInstance().mFoundation;
}

PxCooking &PhysXWorld::getCooking() {
    return *getInstance().mCooking;
}

PxPhysics &PhysXWorld::getPhysics() {
    return *getInstance().mPhysics;
}

PhysXWorld::PhysXWorld() {
    instance = this; // TODO
    static PxDefaultAllocator gAllocator;
    static PxDefaultErrorCallback gErrorCallback;
    mFoundation = PxCreateFoundation(PX_PHYSICS_VERSION, gAllocator, gErrorCallback);
    PxTolerancesScale scale{};
    mCooking = PxCreateCooking(PX_PHYSICS_VERSION, *mFoundation, PxCookingParams(scale));

    PxPvd *pvd = nullptr;
#ifdef CC_DEBUG
    pvd = mPvd = PxCreatePvd(*mFoundation);
    PxPvdTransport *transport = PxDefaultPvdSocketTransportCreate("127.0.0.1", 5425, 10);
    mPvd->connect(*transport, PxPvdInstrumentationFlag::eALL);
#endif
    mPhysics = PxCreatePhysics(PX_PHYSICS_VERSION, *mFoundation, scale, true, pvd);
    PxInitExtensions(*mPhysics, pvd);
    mDispatcher = PxDefaultCpuDispatcherCreate(0);

    mEventMgr = new PhysXEventManager();

    PxSceneDesc sceneDesc(mPhysics->getTolerancesScale());
    sceneDesc.gravity = PxVec3(0.0f, -10.0f, 0.0f);
    sceneDesc.cpuDispatcher = mDispatcher;
    sceneDesc.kineKineFilteringMode = PxPairFilteringMode::eKEEP;
    sceneDesc.staticKineFilteringMode = PxPairFilteringMode::eKEEP;
    sceneDesc.flags |= PxSceneFlag::eENABLE_CCD;
    sceneDesc.filterShader = SimpleFilterShader;
    sceneDesc.simulationEventCallback = &mEventMgr->getEventCallback();
    mScene = mPhysics->createScene(sceneDesc);

    mCollisionMatrix[0] = 1;

    createMaterial(0, 0.6f, 0.6f, 0.1f, 2, 2);
}

PhysXWorld::~PhysXWorld() {
    delete mEventMgr;
    PX_RELEASE(mScene);
    PX_RELEASE(mDispatcher);
    PX_RELEASE(mPhysics);
#ifdef CC_DEBUG
    PxPvdTransport *transport = mPvd->getTransport();
    PX_RELEASE(mPvd);
    PX_RELEASE(transport);
#endif
    PxCloseExtensions();
    PX_RELEASE(mFoundation);
}

void PhysXWorld::step(float fixedTimeStep) {
    mScene->simulate(fixedTimeStep);
    mScene->fetchResults(true);
    syncPhysicsToScene();
}

void PhysXWorld::setGravity(float x, float y, float z) {
    mScene->setGravity(PxVec3(x, y, z));
}

void PhysXWorld::destroy() {
}

void PhysXWorld::setCollisionMatrix(uint32_t index, uint32_t mask) {
    if (index < 0 || index > 31) return;
    mCollisionMatrix[index] = mask;
}

intptr_t PhysXWorld::createConvex(ConvexDesc &desc) {
    PxConvexMeshDesc convexDesc;
    convexDesc.points.count = desc.positionLength;
    convexDesc.points.stride = sizeof(PxVec3);
    convexDesc.points.data = (PxVec3 *)desc.positions;
    convexDesc.flags = PxConvexFlag::eCOMPUTE_CONVEX;
    PxConvexMesh *convexMesh = getCooking().createConvexMesh(convexDesc, PxGetPhysics().getPhysicsInsertionCallback());
    return (intptr_t)convexMesh;
}

intptr_t PhysXWorld::createTrimesh(TrimeshDesc &desc) {
    PxTriangleMeshDesc meshDesc;
    meshDesc.points.count = desc.positionLength;
    meshDesc.points.stride = sizeof(PxVec3);
    meshDesc.points.data = (PxVec3 *)desc.positions;
    meshDesc.triangles.count = desc.triangleLength;
    if (desc.isU16) {
        meshDesc.triangles.stride = 3 * sizeof(PxU16);
        meshDesc.triangles.data = (PxU16 *)desc.triangles;
        meshDesc.flags = PxMeshFlag::e16_BIT_INDICES;
    } else {
        meshDesc.triangles.stride = 3 * sizeof(PxU32);
        meshDesc.triangles.data = (PxU32 *)desc.triangles;
    }
    PxTriangleMesh *triangleMesh = getCooking().createTriangleMesh(meshDesc, PxGetPhysics().getPhysicsInsertionCallback());
    return (intptr_t)triangleMesh;
}

intptr_t PhysXWorld::createHeightField(HeightFieldDesc &desc) {
    const auto rows = desc.rows;
    const auto columns = desc.columns;
    const PxU32 counts = rows * columns;
    auto samples = new PxHeightFieldSample[counts];
    for (PxU32 r = 0; r < rows; r++) {
        for (PxU32 c = 0; c < columns; c++) {
            const auto index = c + r * columns;
            auto v = ((int16_t *)desc.samples)[index];
            samples[index].height = v;
        }
    }
    PxHeightFieldDesc hfDesc;
    hfDesc.nbRows = rows;
    hfDesc.nbColumns = columns;
    hfDesc.samples.data = samples;
    hfDesc.samples.stride = sizeof(PxHeightFieldSample);
    PxHeightField *hf = getCooking().createHeightField(hfDesc, PxGetPhysics().getPhysicsInsertionCallback());
    delete[] samples;
    return (intptr_t)hf;
}

intptr_t PhysXWorld::createMaterial(const uint16_t ID, float f, float df, float r,
                                    uint8_t m0, uint8_t m1) {
    PxMaterial *mat;
    auto &m = getPxMaterialMap();
    if (m.find(ID) == m.end()) {
        mat = PxGetPhysics().createMaterial(f, df, r);
        m[ID] = (intptr_t)mat;
        mat->setFrictionCombineMode(PxCombineMode::Enum(m0));
        mat->setRestitutionCombineMode(PxCombineMode::Enum(m1));
    } else {
        mat = (PxMaterial *)m[ID];
        mat->setStaticFriction(f);
        mat->setDynamicFriction(df);
        mat->setRestitution(r);
        mat->setFrictionCombineMode(PxCombineMode::Enum(m0));
        mat->setRestitutionCombineMode(PxCombineMode::Enum(m1));
    }
    return intptr_t(mat);
}

void PhysXWorld::emitEvents() {
    mEventMgr->refreshPairs();
}

void PhysXWorld::syncSceneToPhysics() {
    for (auto const &sb : mSharedBodies) {
        sb->syncSceneToPhysics();
    }
}

int PhysXWorld::getMaskByIndex(uint32_t i) {
    if (i < 0 || i > 31) i = 0;
    return mCollisionMatrix[i];
}

void PhysXWorld::syncPhysicsToScene() {
    for (auto const &sb : mSharedBodies) {
        sb->syncPhysicsToScene();
    }
}

void PhysXWorld::syncSceneWithCheck() {
    for (auto const &sb : mSharedBodies) {
        sb->syncSceneWithCheck();
    }
}

void PhysXWorld::setAllowSleep(bool val) {
}

void PhysXWorld::addActor(PhysXSharedBody &sb) {
    auto beg = mSharedBodies.begin();
    auto end = mSharedBodies.end();
    auto iter = find(beg, end, &sb);
    if (iter == end) {
        mScene->addActor(*sb.getImpl().rigidActor);
        mSharedBodies.push_back(&sb);
    }
}

void PhysXWorld::removeActor(PhysXSharedBody &sb) {
    auto beg = mSharedBodies.begin();
    auto end = mSharedBodies.end();
    auto iter = find(beg, end, &sb);
    if (iter != end) {
        mScene->removeActor(*sb.getImpl().rigidActor, true);
        mSharedBodies.erase(iter);
    }
}

bool PhysXWorld::raycast(RaycastOptions &opt) {
    PxQueryCache *cache = nullptr;
    const auto o = opt.origin;
    const auto ud = opt.unitDir;
    PxVec3 origin{o.x, o.y, o.z};
    PxVec3 unitDir{ud.x, ud.y, ud.z};
    unitDir.normalize();
    PxHitFlags flags = PxHitFlag::ePOSITION | PxHitFlag::eNORMAL;
    PxSceneQueryFilterData filterData;
    filterData.data.word0 = opt.mask;
    filterData.data.word3 = QUERY_FILTER | (opt.queryTrigger ? 0 : QUERY_CHECK_TRIGGER);
    filterData.flags = PxQueryFlag::eSTATIC | PxQueryFlag::eDYNAMIC | PxQueryFlag::ePREFILTER;
    auto &hitBuffer = getPxRaycastHitBuffer();
    bool result = false;
    const auto nbTouches = PxSceneQueryExt::raycastMultiple(
        getScene(), origin, unitDir, opt.distance, flags, hitBuffer.data(),
        hitBuffer.size(), result, filterData, &getQueryFilterShader(), cache);
    if (nbTouches == 0 || nbTouches == -1) return false;
    auto &r = raycastResult();
    r.resize(nbTouches);
    for (PxI32 i = 0; i < nbTouches; i++) {
        const auto &shapeIter = getPxShapeMap().find((intptr_t)hitBuffer[i].shape);
        if (shapeIter == getPxShapeMap().end()) return false;
        r[i].shape = shapeIter->second;
        r[i].distance = hitBuffer[i].distance;
        PxSetVec3Ext(r[i].hitNormal, hitBuffer[i].normal);
        PxSetVec3Ext(r[i].hitPoint, hitBuffer[i].position);
    }
    return true;
}

std::vector<RaycastResult> &PhysXWorld::raycastResult() {
    static std::vector<RaycastResult> hits;
    return hits;
}

bool PhysXWorld::raycastClosest(RaycastOptions &opt) {
    PxRaycastHit hit;
    PxQueryCache *cache = nullptr;
    const auto o = opt.origin;
    const auto ud = opt.unitDir;
    PxVec3 origin{o.x, o.y, o.z};
    PxVec3 unitDir{ud.x, ud.y, ud.z};
    unitDir.normalize();
    PxHitFlags flags = PxHitFlag::ePOSITION | PxHitFlag::eNORMAL;
    PxSceneQueryFilterData filterData;
    filterData.data.word0 = opt.mask;
    filterData.data.word3 = QUERY_FILTER | (opt.queryTrigger ? 0 : QUERY_CHECK_TRIGGER) | QUERY_SINGLE_HIT;
    filterData.flags = PxQueryFlag::eSTATIC | PxQueryFlag::eDYNAMIC | PxQueryFlag::ePREFILTER;
    const auto result = PxSceneQueryExt::raycastSingle(
        getScene(), origin, unitDir, opt.distance, flags,
        hit, filterData, &getQueryFilterShader(), cache);
    if (result) {
        auto &r = raycastClosestResult();
        const auto &shapeIter = getPxShapeMap().find((intptr_t)hit.shape);
        if (shapeIter == getPxShapeMap().end()) return false;
        r.shape = shapeIter->second;
        r.distance = hit.distance;
        PxSetVec3Ext(r.hitPoint, hit.position);
        PxSetVec3Ext(r.hitNormal, hit.normal);
    }
    return result;
}

RaycastResult &PhysXWorld::raycastClosestResult() {
    static RaycastResult hit;
    return hit;
}

} // namespace physics
} // namespace cc
