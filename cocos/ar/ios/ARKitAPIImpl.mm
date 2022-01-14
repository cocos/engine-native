
#include "ARKitAPIImpl.h"
#import <ARKit/ARKit.h>
#import <CoreVideo/CVPixelBuffer.h>
#import <dispatch/dispatch.h>

static const float kCameraTexCoordData[8] = {
    0.0, 0.0,  0.0, 1.0,
    1.0, 0.0,  1.0, 1.0,
};

static const int kPlanesInfoSize = 12;

@interface SortablePlane : NSObject {
    float distance;
    @public
    ARPlaneAnchor* plane;
}
- (id) initWithDistance : (float) dis andPlane : (ARPlaneAnchor *) arPlane;
- (NSComparisonResult) compare : (id)other;
@end

@implementation SortablePlane

- (id) initWithDistance : (float) dis andPlane : (ARPlaneAnchor *) arPlane {
    distance = dis;
    plane = arPlane;
    return self;
}

- (NSComparisonResult) compare : (SortablePlane*)other {
    if (self->distance > other->distance) {
        return NSOrderedDescending;
    } else if (self->distance < other->distance) {
        return NSOrderedAscending;
    } else {
        return NSOrderedSame;
    }
}

@end

@interface ARKitAPI : NSObject<ARSessionDelegate> {
    ARSession* mARSession;
    ARFrame* mFrame;
    CVPixelBufferRef mPixelBuffer;
    simd_float4x4 mCameraTransform;
    float* mCameraProjMat;
    float* mCameraTexCoords;
    CGSize mViewportSize;
    UIInterfaceOrientation mUIOrientation;
    
    int mPlaneRefTag;
    NSMutableArray* mRecycledRefs;
    NSMutableArray* mDetectedPlanes;
    NSMutableArray* mPlanesIndices;
    NSMutableDictionary* mAnchorsRefMap;
    NSMutableArray* mAllPlanes;
    NSMutableArray* mAddedPlanes;
    NSMutableArray* mRemovedPlanes;
    NSMutableArray* mUpdatedPlanes;
}

- (id)init;
- (void)session:(ARSession *)session didUpdateFrame:(ARFrame *)frame;
- (void)session:(ARSession *)session didAddAnchors:(NSArray<__kindof ARAnchor *> *)anchors;
- (void)session:(ARSession *)session didUpdateAnchors:(NSArray<__kindof ARAnchor *> *)anchors;
- (void)session:(ARSession *)session didRemoveAnchors:(NSArray<__kindof ARAnchor *> *)anchors;
- (void)startSession;
- (void)updateSession;
- (bool)checkStart;
- (float*)getCameraPose;
- (CVPixelBufferRef)getCameraTextureRef;
- (float*)getCameraTexCoords;
- (void)updateCameraTexCoords;

- (void) addRefWithAnchor:(ARAnchor *) anchor;
- (int) recycleRefOfAnchor:(ARAnchor *) anchor;
- (int) getAddedPlanesCount;
- (int) getUpdatedPlanesCount;
- (float *) getAddedPlanesInfo;
- (float *) getUpdatedPlanesInfo;
@end

@implementation ARKitAPI

- (id) init {
    self = [super init];
    mARSession = [ARSession new];
    mARSession.delegate = self;
    
    //mSemaphore = dispatch_semaphore_create(1);
    mCameraProjMat = (float *)malloc(sizeof(float) * 16);
    mCameraTexCoords = (float *)malloc(sizeof(float) * 8);
    // the device upright and the Home button on the Right
    mUIOrientation = UIInterfaceOrientationLandscapeRight;
    
    mPlaneRefTag = 0;
    mRecycledRefs = [NSMutableArray new];
    mDetectedPlanes = [NSMutableArray new];
    mAllPlanes = [NSMutableArray new];
    mAddedPlanes = [NSMutableArray new];
    mRemovedPlanes = [NSMutableArray new];
    mUpdatedPlanes = [NSMutableArray new];
    mAnchorsRefMap = [NSMutableDictionary new];
    
    return self;
}
//*
- (void) session : (ARSession*) session didUpdateFrame : (ARFrame*)frame {
    mFrame = frame;
    
    //mViewportSize = CGSizeMake(width, height);
    mViewportSize = CGSizeMake(2532, 1170);
    
    [self updateCameraTexCoords];
    
    [self updateCameraTex];

    mCameraTransform = [frame.camera transform];
    
    matrix_float4x4 projMat = [mFrame.camera projectionMatrix];
    for(int i = 0; i < 4; ++i) {
        vector_float4 col = projMat.columns[i];
        mCameraProjMat[i * 4] = col.x;
        mCameraProjMat[i * 4 + 1] = col.y;
        mCameraProjMat[i * 4 + 2] = col.z;
        mCameraProjMat[i * 4 + 3] = col.w;
    }
    
}
//*/




- (void) startSession {
    ARWorldTrackingConfiguration* config = [ARWorldTrackingConfiguration new];
    
    config.planeDetection = ARPlaneDetectionHorizontal;
    
    [mARSession runWithConfiguration : config];
}

- (void) updateSession {
    //*
    //mFrame = mARSession.currentFrame;
    if(!mFrame) return;
    //[self updateTexture : mFrame];
    //*/

    //mFrame = frame;
    
    //mViewportSize = CGSizeMake(width, height);
    //*
    mViewportSize = CGSizeMake(2532, 1170);
    
    [self updateCameraTexCoords];
    
    [self updateCameraTex];

    mCameraTransform = [mFrame.camera transform];
    
    matrix_float4x4 projMat = [mFrame.camera projectionMatrix];
    for(int i = 0; i < 4; ++i) {
        vector_float4 col = projMat.columns[i];
        mCameraProjMat[i * 4] = col.x;
        mCameraProjMat[i * 4 + 1] = col.y;
        mCameraProjMat[i * 4 + 2] = col.z;
        mCameraProjMat[i * 4 + 3] = col.w;
    }
     //*/
}

- (bool) checkStart {
    return mARSession && mFrame;
}

#pragma mark - ar camera

- (CVPixelBufferRef) getCameraTextureRef {
    return mPixelBuffer;
}

- (float*) getCameraPose {
    float * pose = (float *)malloc(sizeof(float) * 7);
    
    vector_float4 c0 = mCameraTransform.columns[0];
    vector_float4 c1 = mCameraTransform.columns[1];
    vector_float4 c2 = mCameraTransform.columns[2];
    vector_float4 c3 = mCameraTransform.columns[3];
    float qw = sqrt(1 + c0.x + c1.y + c2.z) * 0.5f;
    float qw_4 = 4.0f * qw;
    
    pose[0] = c3.x;
    pose[1] = c3.y;
    pose[2] = c3.z;
    pose[3] = -(c2.y - c1.z) / qw_4;
    pose[4] = -(c0.z - c2.x) / qw_4;
    pose[5] = -(c1.x - c0.y) / qw_4;
    pose[6] = qw;
    
    return pose;
}

- (float*) getCameraTexCoords {
    return mCameraTexCoords;
}

- (float*) getCameraProjectionMatrix {
    return mCameraProjMat;
}

- (void) updateCameraTex {
    CVPixelBufferRef capturedBuffer = mFrame.capturedImage;
    
    if(!mPixelBuffer) {
        CGFloat width = CVPixelBufferGetWidth(capturedBuffer);
        CGFloat height = CVPixelBufferGetHeight(capturedBuffer);
        NSDictionary* cvBufferProperties = @{
            (__bridge NSString*)kCVPixelBufferOpenGLCompatibilityKey : @YES,
            (__bridge NSString*)kCVPixelBufferMetalCompatibilityKey : @YES,
        };
        CVPixelBufferCreate(kCFAllocatorDefault,
                            width,
                            height,
                            CVPixelBufferGetPixelFormatType(capturedBuffer),
                            (__bridge CFDictionaryRef)cvBufferProperties,
                            &mPixelBuffer);
    }

    CVPixelBufferLockBaseAddress(mPixelBuffer, 0);
    CVPixelBufferLockBaseAddress(capturedBuffer, kCVPixelBufferLock_ReadOnly);
    for(int i = 0; i < CVPixelBufferGetPlaneCount(capturedBuffer); ++i) {
        void* dest = CVPixelBufferGetBaseAddressOfPlane(mPixelBuffer, i);
        void* source = CVPixelBufferGetBaseAddressOfPlane(capturedBuffer, i);
        size_t height = CVPixelBufferGetHeightOfPlane(capturedBuffer, i);
        size_t bytesPerRowSrc = CVPixelBufferGetBytesPerRowOfPlane(capturedBuffer, i);
        memcpy(dest, source, height * bytesPerRowSrc);
    }
    CVPixelBufferUnlockBaseAddress(capturedBuffer, kCVPixelBufferLock_ReadOnly);
    CVPixelBufferUnlockBaseAddress(mPixelBuffer, 0);
}

- (void) updateCameraTexCoords {
    if(!mFrame)return;
    CGAffineTransform displayToCameraTransform = CGAffineTransformInvert([mFrame displayTransformForOrientation : mUIOrientation viewportSize : mViewportSize]);

    for (NSInteger index = 0; index < 4; index++) {
        NSInteger textureCoordIndex = index * 2;
        CGPoint textureCoord = CGPointMake(kCameraTexCoordData[textureCoordIndex], kCameraTexCoordData[textureCoordIndex + 1]);
        CGPoint transformedCoord = CGPointApplyAffineTransform(textureCoord, displayToCameraTransform);
        mCameraTexCoords[textureCoordIndex] = transformedCoord.x;
        mCameraTexCoords[textureCoordIndex + 1] = transformedCoord.y;
    }
}

#pragma mark - anchor contents

- (void) session : (ARSession*) session didAddAnchors : (NSArray<__kindof ARAnchor *> *)anchors {
    for (ARAnchor* anchor in anchors) {
        if([anchor isKindOfClass:[ARPlaneAnchor class]]) {
            ARPlaneAnchor* plane = (ARPlaneAnchor*)anchor;
            [mAddedPlanes addObject : plane];
            [self addRefWithAnchor:plane];
        }
    }
    /*
    [mDetectedPlanes removeAllObjects];
    for (ARAnchor* anchor in anchors) {
        if([anchor isKindOfClass:[ARPlaneAnchor class]]) {
            ARPlaneAnchor* plane = (ARPlaneAnchor*)anchor;
            [mDetectedPlanes addObject : plane];
        }
    }
    
    NSMutableArray* sortableArray = [NSMutableArray new];
    vector_float3 cameraPos = mCameraTransform.columns[3].xyz;
    for (ARPlaneAnchor* plane in mDetectedPlanes) {
        vector_float3 normal = simd_mul(plane.transform, simd_make_float4(0, 1, 0, 1)).xyz;
        normal = simd_normalize(normal);
        
        float normalDistance = simd_dot((cameraPos - plane.center), normal);
        if (normalDistance < 0) continue;
        
        SortablePlane* sortable = [[SortablePlane alloc] initWithDistance : normalDistance andPlane : plane];
        [sortableArray addObject:sortable];
    }
    
    [sortableArray sortUsingComparator:^NSComparisonResult(SortablePlane* obj1, SortablePlane* obj2) {
        return [obj1 compare: obj2];
    }];
    
    int count = 0;
    
    //[mAddedPlanes removeAllObjects];
    //[mUpdatedPlanes removeAllObjects];
    for (SortablePlane* sortedPlane in sortableArray) {
        ARPlaneAnchor* plane = sortedPlane->plane;
        
        if ([mAllPlanes containsObject : plane]) {
            //[mUpdatedPlanes addObject : plane];
        } else {
            [mAddedPlanes addObject : plane];
            [mPlanesIndices addObject: [NSNumber numberWithInt:planeRefTag]];
            ++planeRefTag;
            [mAllPlanes addObject : plane];
            [mPlanesMap setObject:plane forKey:[NSNumber numberWithUnsignedInteger:plane.identifier.hash]];
        }
        
        ++count;
    }
    //*/
}

- (void) session:(ARSession *)session didRemoveAnchors:(NSArray<__kindof ARAnchor *> *)anchors {
    for (ARAnchor* anchor in anchors) {
        if([anchor isKindOfClass:[ARPlaneAnchor class]]) {
            ARPlaneAnchor* plane = (ARPlaneAnchor*)anchor;
            [mRemovedPlanes addObject : plane];
        }
    }
}

- (void) session:(ARSession *)session didUpdateAnchors:(NSArray<__kindof ARAnchor *> *)anchors {
    for (ARAnchor* anchor in anchors) {
        if([anchor isKindOfClass:[ARPlaneAnchor class]]) {
            ARPlaneAnchor* plane = (ARPlaneAnchor*)anchor;
            [mUpdatedPlanes addObject : plane];
        }
    }
}

#pragma mark - plane detection

- (int) getAddedPlanesCount {
    return (int)mAddedPlanes.count;
}

- (int) getUpdatedPlanesCount {
    return (int)mUpdatedPlanes.count;
}

- (int) getRemovedPlanesCount {
    return (int)mRemovedPlanes.count;
}

- (float *) getAddedPlanesInfo {
    float* planesInfo = [self transferPlanesInfo : mAddedPlanes];
    [mAddedPlanes removeAllObjects];
    return planesInfo;
}

- (float *) getUpdatedPlanesInfo {
    float* planesInfo = [self transferPlanesInfo : mUpdatedPlanes];
    [mUpdatedPlanes removeAllObjects];
    return planesInfo;
}

- (unsigned long *) getRemovedPlanesInfo {
    unsigned long * planesInfo = (unsigned long *)malloc(sizeof(unsigned long) * kPlanesInfoSize * mRemovedPlanes.count);
    int n = 0;
    for (ARPlaneAnchor* plane in mRemovedPlanes) {
        planesInfo[n] = [self recycleRefOfAnchor:plane];
        ++n;
    }
    [mRemovedPlanes removeAllObjects];
    return planesInfo;
}

#pragma mark - raycast

- (bool) raycastWithX:(float) x WithY:(float) y {
    bool result = false;
    if (@available(iOS 13.0, *)) {
        NSArray<ARRaycastResult *> * raycastResults = [mARSession raycast:[mFrame raycastQueryFromPoint:CGPointMake(x, y) allowingTarget:ARRaycastTargetExistingPlaneInfinite alignment:ARRaycastTargetAlignmentHorizontal]];
        if(raycastResults.count > 0) {
            
            result = true;
        }
    } else {
        // Fallback on earlier versions
        NSArray<ARHitTestResult *> * raycastResults = [mFrame hitTest:CGPointMake(x, y) types:ARHitTestResultTypeExistingPlane];
        if(raycastResults.count > 0) {
            result = true;
        }
    }
}

#pragma mark - utils

- (void) addRefWithAnchor:(ARAnchor *) anchor {
    unsigned int ref;
    if (mRecycledRefs.count > 0) {
        ref = [mRecycledRefs[0] intValue];
        [mRecycledRefs removeObjectAtIndex:0];
    } else {
        ref = mPlaneRefTag++;
    }
    [mAnchorsRefMap setObject:[NSNumber numberWithUnsignedInteger:ref] forKey:anchor];
}

- (int) recycleRefOfAnchor:(ARAnchor *) anchor {
    int recycleRef = -1;
    NSNumber* refNumber = [mAnchorsRefMap objectForKey:anchor];
    if(refNumber) {
        recycleRef = [refNumber intValue];
        [mRecycledRefs addObject:refNumber];
        [mAnchorsRefMap removeObjectForKey:anchor];
    }
    return recycleRef;
}

- (float *) transferPlanesInfo : (NSMutableArray *) planes {
    float * planesInfo = (float *)malloc(sizeof(float) * kPlanesInfoSize * planes.count);
    //int maxSize = 5;
    int n = 0;
    for (ARPlaneAnchor* plane in planes) {
        //if (n >= maxSize) break;
        planesInfo[n * kPlanesInfoSize] = [[mAnchorsRefMap objectForKey:plane] floatValue];
        planesInfo[n * kPlanesInfoSize + 1] = plane.alignment;
        planesInfo[n * kPlanesInfoSize + 2] = 0;
        
        planesInfo[n * kPlanesInfoSize + 3] = plane.extent.x;
        planesInfo[n * kPlanesInfoSize + 4] = plane.extent.z;
        
        vector_float4 c3 = plane.transform.columns[3];
        simd_float3 center = matrix_multiply(plane.transform, simd_make_float4(plane.center, 1)).xyz;
        planesInfo[n * kPlanesInfoSize + 5] = center.x;
        planesInfo[n * kPlanesInfoSize + 6] = center.y;
        planesInfo[n * kPlanesInfoSize + 7] = center.z;
        
        simd_float4 quat = [ARKitAPI transformToQuaternion : plane.transform];
        planesInfo[n * kPlanesInfoSize + 8] = quat.x;
        planesInfo[n * kPlanesInfoSize + 9] = quat.y;
        planesInfo[n * kPlanesInfoSize + 10] = quat.z;
        planesInfo[n * kPlanesInfoSize + 11] = quat.w;
        ++n;
    }
    return planesInfo;
}

+ (simd_float4) transformToQuaternion : (simd_float4x4)transform {
    vector_float4 c0 = transform.columns[0];
    vector_float4 c1 = transform.columns[1];
    vector_float4 c2 = transform.columns[2];
    float qw = sqrt(1 + c0.x + c1.y + c2.z) * 0.5f;
    float qw_4 = 4.0f * qw;
    
    float qx = -(c2.y - c1.z) / qw_4;
    float qy = -(c0.z - c2.x) / qw_4;
    float qz = -(c1.x - c0.y) / qw_4;
    return simd_make_float4(qx, qy, qz, qw);
}
@end

#pragma mark - ARKitAPIImpl

#define TransferImpl ARKitAPI *impl = (__bridge ARKitAPI *)_impl;

namespace cc {
namespace ar {

ARKitAPIImpl::ARKitAPIImpl() : _impl(nil) {
    _impl = [ARKitAPI new];
}

ARKitAPIImpl::~ARKitAPIImpl() {
    _impl = nullptr;
}

void ARKitAPIImpl::start() {
    TransferImpl;
    [impl startSession];
}

void ARKitAPIImpl::update() {
    //TransferImpl;
    //[impl updateSession];
}

void ARKitAPIImpl::resume() {}

void ARKitAPIImpl::pause() {}

int ARKitAPIImpl::getAPIState() {
    TransferImpl;
    if([impl checkStart]) return 0;
    return -1;
}

void ARKitAPIImpl::setCameraTextureName(int id) {}

float* ARKitAPIImpl::getCameraPose() {
    TransferImpl;
    return (__bridge float*)[impl getCameraPose];
}

float* ARKitAPIImpl::getCameraViewMatrix() {}

float* ARKitAPIImpl::getCameraProjectionMatrix() {
    TransferImpl;
    return (__bridge float *)[impl getCameraProjectionMatrix];
}

float* ARKitAPIImpl::getCameraTexCoords() {
    TransferImpl;
    return (__bridge float*)[impl getCameraTexCoords];
}

void* ARKitAPIImpl::getCameraTextureRef() {
    TransferImpl;
    return (__bridge void *)[impl getCameraTextureRef];
}

int ARKitAPIImpl::getAddedPlanesCount() {
    TransferImpl;
    return [impl getAddedPlanesCount];
}
int ARKitAPIImpl::getRemovedPlanesCount() {
    return 0;
}
int ARKitAPIImpl::getUpdatedPlanesCount() {
     TransferImpl;
    return [impl getUpdatedPlanesCount];
}
void ARKitAPIImpl::updatePlanesInfo() {

}
float* ARKitAPIImpl::getAddedPlanesInfo() {
    TransferImpl;
    _infoLength = [impl getAddedPlanesCount] * 12;
    return (__bridge float *)[impl getAddedPlanesInfo];
}
unsigned long* ARKitAPIImpl::getRemovedPlanesInfo() {
    TransferImpl;
    _infoLength = [impl getRemovedPlanesCount];
    return (__bridge unsigned long *)[impl getRemovedPlanesInfo];
}
float* ARKitAPIImpl::getUpdatedPlanesInfo() {
    TransferImpl;
    _infoLength = [impl getUpdatedPlanesCount] * 12;
    return (__bridge float *)[impl getUpdatedPlanesInfo];
}
int ARKitAPIImpl::getInfoLength() {
    return _infoLength;
}

} // namespace ar
} // namespace cc
