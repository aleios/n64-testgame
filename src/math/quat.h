#pragma once
#ifndef QUAT_H
#define QUAT_H

#include "matrix.h"
#include "vector3.h"

struct Quat {
    float x, y, z, w;
};

void quat_identity(struct Quat* quat);
void quat_axis_angle(struct Quat* quat, struct Vector3* axis, float angle);
void quat_tomat4(struct Quat* quat, Mat4 mat);
void quat_conj(struct Quat* dest, struct Quat* quat);

void quat_mul(struct Quat* dest, struct Quat* a, struct Quat* b);
void quat_mul_vec(struct Vector3* dest, struct Quat* quat, struct Vector3* vec);

#endif //QUAT_H
