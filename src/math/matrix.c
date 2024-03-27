#include "matrix.h"

void mat_identity(Mat4 mat) {
    mat[0][0] = 1.0f;
    mat[0][1] = 0.0f;
    mat[0][2] = 0.0f;
    mat[0][3] = 0.0f;

    mat[1][0] = 0.0f;
    mat[1][1] = 1.0f;
    mat[1][2] = 0.0f;
    mat[1][3] = 0.0f;

    mat[2][0] = 0.0f;
    mat[2][1] = 0.0f;
    mat[2][2] = 1.0f;
    mat[2][3] = 0.0f;

    mat[3][0] = 0.0f;
    mat[3][1] = 0.0f;
    mat[3][2] = 0.0f;
    mat[3][3] = 1.0f;
}

void mat_frustum(Mat4 mat, float left, float right, float bottom, float top, float near, float far) {
    mat[0][0] = (2.0f * near) / (right - left);
    mat[0][1] = 0.0f;
    mat[0][2] = 0.0f;
    mat[0][3] = 0.0f;

    mat[1][0] = 0.0f;
    mat[1][1] = (2.0f * near) / (top - bottom);
    mat[1][2] = 0.0f;
    mat[1][3] = 0.0f;

    mat[2][0] = (right + left) / (right - left);
    mat[2][1] = (top + bottom) / (top - bottom);
    mat[2][2] = -(far + near) / (far - near);
    mat[2][3] = -1.0f;

    mat[3][0] = 0.0f;
    mat[3][1] = 0.0f;
    mat[3][2] = -(2 * far * near) / (far - near);
    mat[3][3] = 0.0f;
}