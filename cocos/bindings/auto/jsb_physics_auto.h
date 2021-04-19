#pragma once
#include "base/Config.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#include <type_traits>
#include "cocos/bindings/jswrapper/SeApi.h"
#include "cocos/bindings/manual/jsb_conversions.h"
#include "cocos/physics/PhysicsSDK.h"

extern se::Object* __jsb_cc_physics_World_proto;
extern se::Class* __jsb_cc_physics_World_class;

bool js_register_cc_physics_World(se::Object* obj);
bool register_all_physics(se::Object* obj);

JSB_REGISTER_OBJECT_TYPE(cc::physics::World);
SE_DECLARE_FUNC(js_physics_World_destroy);
SE_DECLARE_FUNC(js_physics_World_emitEvents);
SE_DECLARE_FUNC(js_physics_World_setAllowSleep);
SE_DECLARE_FUNC(js_physics_World_setDefaultMaterial);
SE_DECLARE_FUNC(js_physics_World_setGravity);
SE_DECLARE_FUNC(js_physics_World_step);
SE_DECLARE_FUNC(js_physics_World_syncSceneToPhysics);
SE_DECLARE_FUNC(js_physics_World_syncSceneWithCheck);
SE_DECLARE_FUNC(js_physics_World_World);

extern se::Object* __jsb_cc_physics_RigidBody_proto;
extern se::Class* __jsb_cc_physics_RigidBody_class;

bool js_register_cc_physics_RigidBody(se::Object* obj);
bool register_all_physics(se::Object* obj);

JSB_REGISTER_OBJECT_TYPE(cc::physics::RigidBody);
SE_DECLARE_FUNC(js_physics_RigidBody_applyForce);
SE_DECLARE_FUNC(js_physics_RigidBody_applyImpulse);
SE_DECLARE_FUNC(js_physics_RigidBody_applyLocalForce);
SE_DECLARE_FUNC(js_physics_RigidBody_applyLocalImpulse);
SE_DECLARE_FUNC(js_physics_RigidBody_applyLocalTorque);
SE_DECLARE_FUNC(js_physics_RigidBody_applyTorque);
SE_DECLARE_FUNC(js_physics_RigidBody_clearForces);
SE_DECLARE_FUNC(js_physics_RigidBody_clearState);
SE_DECLARE_FUNC(js_physics_RigidBody_clearVelocity);
SE_DECLARE_FUNC(js_physics_RigidBody_getAngularVelocity);
SE_DECLARE_FUNC(js_physics_RigidBody_getLinearVelocity);
SE_DECLARE_FUNC(js_physics_RigidBody_getSleepThreshold);
SE_DECLARE_FUNC(js_physics_RigidBody_initialize);
SE_DECLARE_FUNC(js_physics_RigidBody_isAwake);
SE_DECLARE_FUNC(js_physics_RigidBody_isSleeping);
SE_DECLARE_FUNC(js_physics_RigidBody_isSleepy);
SE_DECLARE_FUNC(js_physics_RigidBody_onDestroy);
SE_DECLARE_FUNC(js_physics_RigidBody_onDisable);
SE_DECLARE_FUNC(js_physics_RigidBody_onEnable);
SE_DECLARE_FUNC(js_physics_RigidBody_setAllowSleep);
SE_DECLARE_FUNC(js_physics_RigidBody_setAngularDamping);
SE_DECLARE_FUNC(js_physics_RigidBody_setAngularFactor);
SE_DECLARE_FUNC(js_physics_RigidBody_setAngularVelocity);
SE_DECLARE_FUNC(js_physics_RigidBody_setCollisionFilter);
SE_DECLARE_FUNC(js_physics_RigidBody_setLinearDamping);
SE_DECLARE_FUNC(js_physics_RigidBody_setLinearFactor);
SE_DECLARE_FUNC(js_physics_RigidBody_setLinearVelocity);
SE_DECLARE_FUNC(js_physics_RigidBody_setMass);
SE_DECLARE_FUNC(js_physics_RigidBody_setSleepThreshold);
SE_DECLARE_FUNC(js_physics_RigidBody_setType);
SE_DECLARE_FUNC(js_physics_RigidBody_sleep);
SE_DECLARE_FUNC(js_physics_RigidBody_useGravity);
SE_DECLARE_FUNC(js_physics_RigidBody_wakeUp);
SE_DECLARE_FUNC(js_physics_RigidBody_RigidBody);

extern se::Object* __jsb_cc_physics_SphereShape_proto;
extern se::Class* __jsb_cc_physics_SphereShape_class;

bool js_register_cc_physics_SphereShape(se::Object* obj);
bool register_all_physics(se::Object* obj);

JSB_REGISTER_OBJECT_TYPE(cc::physics::SphereShape);
SE_DECLARE_FUNC(js_physics_SphereShape_getAABB);
SE_DECLARE_FUNC(js_physics_SphereShape_getBoundingSphere);
SE_DECLARE_FUNC(js_physics_SphereShape_getImpl);
SE_DECLARE_FUNC(js_physics_SphereShape_initialize);
SE_DECLARE_FUNC(js_physics_SphereShape_onDestroy);
SE_DECLARE_FUNC(js_physics_SphereShape_onDisable);
SE_DECLARE_FUNC(js_physics_SphereShape_onEnable);
SE_DECLARE_FUNC(js_physics_SphereShape_setAsTrigger);
SE_DECLARE_FUNC(js_physics_SphereShape_setCenter);
SE_DECLARE_FUNC(js_physics_SphereShape_setCollisionFilter);
SE_DECLARE_FUNC(js_physics_SphereShape_setMaterial);
SE_DECLARE_FUNC(js_physics_SphereShape_setRadius);
SE_DECLARE_FUNC(js_physics_SphereShape_updateEventListener);
SE_DECLARE_FUNC(js_physics_SphereShape_SphereShape);

extern se::Object* __jsb_cc_physics_BoxShape_proto;
extern se::Class* __jsb_cc_physics_BoxShape_class;

bool js_register_cc_physics_BoxShape(se::Object* obj);
bool register_all_physics(se::Object* obj);

JSB_REGISTER_OBJECT_TYPE(cc::physics::BoxShape);
SE_DECLARE_FUNC(js_physics_BoxShape_getAABB);
SE_DECLARE_FUNC(js_physics_BoxShape_getBoundingSphere);
SE_DECLARE_FUNC(js_physics_BoxShape_getImpl);
SE_DECLARE_FUNC(js_physics_BoxShape_initialize);
SE_DECLARE_FUNC(js_physics_BoxShape_onDestroy);
SE_DECLARE_FUNC(js_physics_BoxShape_onDisable);
SE_DECLARE_FUNC(js_physics_BoxShape_onEnable);
SE_DECLARE_FUNC(js_physics_BoxShape_setAsTrigger);
SE_DECLARE_FUNC(js_physics_BoxShape_setCenter);
SE_DECLARE_FUNC(js_physics_BoxShape_setCollisionFilter);
SE_DECLARE_FUNC(js_physics_BoxShape_setMaterial);
SE_DECLARE_FUNC(js_physics_BoxShape_setSize);
SE_DECLARE_FUNC(js_physics_BoxShape_updateEventListener);
SE_DECLARE_FUNC(js_physics_BoxShape_BoxShape);

extern se::Object* __jsb_cc_physics_CapsuleShape_proto;
extern se::Class* __jsb_cc_physics_CapsuleShape_class;

bool js_register_cc_physics_CapsuleShape(se::Object* obj);
bool register_all_physics(se::Object* obj);

JSB_REGISTER_OBJECT_TYPE(cc::physics::CapsuleShape);
SE_DECLARE_FUNC(js_physics_CapsuleShape_getAABB);
SE_DECLARE_FUNC(js_physics_CapsuleShape_getBoundingSphere);
SE_DECLARE_FUNC(js_physics_CapsuleShape_getImpl);
SE_DECLARE_FUNC(js_physics_CapsuleShape_initialize);
SE_DECLARE_FUNC(js_physics_CapsuleShape_onDestroy);
SE_DECLARE_FUNC(js_physics_CapsuleShape_onDisable);
SE_DECLARE_FUNC(js_physics_CapsuleShape_onEnable);
SE_DECLARE_FUNC(js_physics_CapsuleShape_setAsTrigger);
SE_DECLARE_FUNC(js_physics_CapsuleShape_setCenter);
SE_DECLARE_FUNC(js_physics_CapsuleShape_setCollisionFilter);
SE_DECLARE_FUNC(js_physics_CapsuleShape_setCylinderHeight);
SE_DECLARE_FUNC(js_physics_CapsuleShape_setDirection);
SE_DECLARE_FUNC(js_physics_CapsuleShape_setMaterial);
SE_DECLARE_FUNC(js_physics_CapsuleShape_setRadius);
SE_DECLARE_FUNC(js_physics_CapsuleShape_updateEventListener);
SE_DECLARE_FUNC(js_physics_CapsuleShape_CapsuleShape);

extern se::Object* __jsb_cc_physics_PlaneShape_proto;
extern se::Class* __jsb_cc_physics_PlaneShape_class;

bool js_register_cc_physics_PlaneShape(se::Object* obj);
bool register_all_physics(se::Object* obj);

JSB_REGISTER_OBJECT_TYPE(cc::physics::PlaneShape);
SE_DECLARE_FUNC(js_physics_PlaneShape_getAABB);
SE_DECLARE_FUNC(js_physics_PlaneShape_getBoundingSphere);
SE_DECLARE_FUNC(js_physics_PlaneShape_getImpl);
SE_DECLARE_FUNC(js_physics_PlaneShape_initialize);
SE_DECLARE_FUNC(js_physics_PlaneShape_onDestroy);
SE_DECLARE_FUNC(js_physics_PlaneShape_onDisable);
SE_DECLARE_FUNC(js_physics_PlaneShape_onEnable);
SE_DECLARE_FUNC(js_physics_PlaneShape_setAsTrigger);
SE_DECLARE_FUNC(js_physics_PlaneShape_setCenter);
SE_DECLARE_FUNC(js_physics_PlaneShape_setCollisionFilter);
SE_DECLARE_FUNC(js_physics_PlaneShape_setConstant);
SE_DECLARE_FUNC(js_physics_PlaneShape_setMaterial);
SE_DECLARE_FUNC(js_physics_PlaneShape_setNormal);
SE_DECLARE_FUNC(js_physics_PlaneShape_updateEventListener);
SE_DECLARE_FUNC(js_physics_PlaneShape_PlaneShape);

extern se::Object* __jsb_cc_physics_PhysXBindings_proto;
extern se::Class* __jsb_cc_physics_PhysXBindings_class;

bool js_register_cc_physics_PhysXBindings(se::Object* obj);
bool register_all_physics(se::Object* obj);

JSB_REGISTER_OBJECT_TYPE(cc::physics::PhysXBindings);
SE_DECLARE_FUNC(js_physics_PhysXBindings_testAPI);
SE_DECLARE_FUNC(js_physics_PhysXBindings_getLength);
SE_DECLARE_FUNC(js_physics_PhysXBindings_modifyByPtr);
SE_DECLARE_FUNC(js_physics_PhysXBindings_getPtr);

#endif //#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
