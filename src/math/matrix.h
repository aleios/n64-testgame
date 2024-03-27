#pragma once
#ifndef MATRIX_H
#define MATRIX_H

typedef float Mat4[4][4];

void mat_identity(Mat4 mat);
void mat_frustum(Mat4 mat, float left, float right, float bottom, float top, float near, float far);

#endif //MATRIX_H
