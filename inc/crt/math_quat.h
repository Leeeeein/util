//
// Created by hujianzhe
//

#ifndef	UTIL_C_CRT_MATH_QUAT_H
#define UTIL_C_CRT_MATH_QUAT_H

#include "../compiler_define.h"

#ifdef	__cplusplus
extern "C" {
#endif

__declspec_dll float* mathQuatNormalized(float r[4], const float q[4]);
__declspec_dll float* mathQuatFromEuler(float q[4], const float e[3], const char order[3]);
__declspec_dll float* mathQuatFromUnitVec3(float q[4], const float from[3], const float to[3]);
__declspec_dll float* mathQuatFromAxisRadian(float q[4], const float axis[3], float radian);
__declspec_dll void mathQuatToAxisRadian(const float q[4], float axis[3], float* radian);
__declspec_dll float* mathQuatIdentity(float q[4]);
__declspec_dll float* mathQuatConjugate(float r[4], const float q[4]);
__declspec_dll float* mathQuatMulQuat(float r[4], const float q1[4], const float q2[4]);
__declspec_dll float* mathQuatMulVec3(float r[3], const float q[4], const float v[3]);

#ifdef	__cplusplus
}
#endif

#endif
