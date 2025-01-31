//
// Created by hujianzhe
//

#ifndef	UTIL_C_CRT_GEOMETRY_AABB_H
#define	UTIL_C_CRT_GEOMETRY_AABB_H

#include "../../compiler_define.h"
#include "triangle.h"

typedef struct GeometryAABB_t {
	float o[3];
	float half[3];
} GeometryAABB_t;

#ifdef	__cplusplus
extern "C" {
#endif

extern const int Box_Edge_Indices[24];
extern const int Box_Vertice_Adjacent_Indices[8][3];
extern const int Box_Triangle_Vertices_Indices[36];
extern const float AABB_Plane_Normal[6][3];

__declspec_dll void mathAABBPlaneVertices(const float o[3], const float half[3], float v[6][3]);
__declspec_dll void mathAABBPlaneRectSizes(const float aabb_half[3], float half_w[6], float half_h[6]);
__declspec_dll GeometryRect_t* mathAABBPlaneRect(const float o[3], const float half[3], unsigned int idx, GeometryRect_t* rect);
__declspec_dll void mathAABBVertices(const float o[3], const float half[3], float v[8][3]);
__declspec_dll void mathAABBMinVertice(const float o[3], const float half[3], float v[3]);
__declspec_dll void mathAABBMaxVertice(const float o[3], const float half[3], float v[3]);

__declspec_dll int mathAABBHasPoint(const float o[3], const float half[3], const float p[3]);
__declspec_dll void mathAABBClosestPointTo(const float o[3], const float half[3], const float p[3], float closest_p[3]);
__declspec_dll void mathAABBSplit(const float o[3], const float half[3], float new_o[8][3], float new_half[3]);
__declspec_dll int mathAABBIntersectAABB(const float o1[3], const float half1[3], const float o2[3], const float half2[3]);
__declspec_dll int mathAABBContainAABB(const float o1[3], const float half1[3], const float o2[3], const float half2[3]);

#ifdef	__cplusplus
}
#endif

#endif
