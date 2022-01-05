//
// Created by hujianzhe
//

#ifndef UTIL_C_CRT_COLLISION_DETECTION_H
#define	UTIL_C_CRT_COLLISION_DETECTION_H

#include "../compiler_define.h"

typedef struct CCTResult_t {
	float distance;
	int hit_point_cnt;
	float hit_point[3];
	float hit_normal[3];
} CCTResult_t;

enum {
	COLLISION_BODY_RAY,
	COLLISION_BODY_AABB,
	COLLISION_BODY_SPHERE,
	COLLISION_BODY_CAPSULE,
	COLLISION_BODY_PLANE,
	COLLISION_BODY_TRIANGLES_PLANE
};

typedef struct CollisionBodyRay_t {
	int type;
	float pos[3];
} CollisionBodyRay_t;

typedef struct CollisionBodySphere_t {
	int type;
	float pos[3];
	float radius;
} CollisionBodySphere_t;

typedef struct CollisionBodyCapsule_t {
	int type;
	float pos[3];
	float axis[3];
	float radius;
	float half_height;
} CollisionBodyCapsule_t;

typedef struct CollisionBodyAABB_t {
	int type;
	float pos[3];
	float half[3];
} CollisionBodyAABB_t;

typedef struct CollisionBodyPlane_t {
	int type;
	float normal[3];
	float vertice[3];
} CollisionBodyPlane_t;

typedef struct CollisionBodyTrianglesPlane_t {
	int type;
	float normal[3];
	float(*vertices)[3];
	int verticescnt;
	int* indices;
	int indicescnt;
} CollisionBodyTrianglesPlane_t;

typedef union CollisionBody_t {
	int type;
	CollisionBodySphere_t sphere;
	CollisionBodyCapsule_t capsule;
	CollisionBodyAABB_t aabb;
	CollisionBodyPlane_t plane;
	CollisionBodyTrianglesPlane_t triangles_plane;
} CollisionBody_t;

#ifdef __cplusplus
extern "C" {
#endif

__declspec_dll void mathAABBSplit(const float o[3], const float half[3], float new_o[8][3], float new_half[3]);
__declspec_dll int mathAABBIntersectAABB(const float o1[3], const float half1[3], const float o2[3], const float half2[3]);
__declspec_dll int mathAABBContainAABB(const float o1[3], const float half1[3], const float o2[3], const float half2[3]);

__declspec_dll CollisionBody_t* mathCollisionBodyBoundingBox(const CollisionBody_t* b, const float delta_half_v[3], CollisionBodyAABB_t* aabb);
__declspec_dll int mathCollisionBodyIntersect(const CollisionBody_t* b1, const CollisionBody_t* b2);
__declspec_dll CCTResult_t* mathCollisionBodyCast(const CollisionBody_t* b1, const float dir[3], const CollisionBody_t* b2, CCTResult_t* result);

#ifdef	__cplusplus
}
#endif

#endif // !UTIL_C_CRT_COLLISION_DETECTION_H
