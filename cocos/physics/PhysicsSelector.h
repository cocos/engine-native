
#pragma once

#if defined(USE_PHYSICS_BULLET)
    #include "physics/bullet/Bullet.h"
#else
    #include "physics/physx/PhysX.h"
    #define WrappedWorld PhysXWorld
    #define WrappedRigidBody PhysXRigidBody
    #define WrappedSphereShape PhysXSphere
	#define WrappedBoxShape PhysXBox
	#define WrappedPlaneShape PhysXPlane
	#define WrappedCapsuleShape PhysXCapsule
    #define WrappedTrimeshShape PhysXTrimesh
    #define WrappedTerrainShape PhysXTerrain
    #define WrappedConeShape PhysXCone
    #define WrappedCylinderShape PhysXCylinder
    #define WrappedRevoluteJoint PhysXRevolute
    #define WrappedDistanceJoint PhysXDistance
#endif
