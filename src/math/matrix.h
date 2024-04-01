#pragma once
#ifndef MATRIX_H
#define MATRIX_H

#include "vector3.h"

// TODO: Convert to 1D array.
typedef float Mat4[16];

void mat_identity(Mat4 mat);
void mat_frustum(Mat4 mat, float left, float right, float bottom, float top, float near, float far);
void mat_look_at(Mat4 mat, struct Vector3* eye, struct Vector3* target, struct Vector3* up);

#endif //MATRIX_H
