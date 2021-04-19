
#if defined(CC_PHYSICS_BULLET)
    #include "bullet/Bullet.h"
#else
    #include "physx/PhysX.h"
    #define WrappedWorld PhysXWorld
    #define WrappedRigidBody PhysXRigidBody
    #define WrappedSphereShape PhysXSphere
	#define WrappedBoxShape PhysXBox
#endif
