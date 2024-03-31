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

void mat_look_at(Mat4 mat, struct Vector3* eye, struct Vector3* target, struct Vector3* up) {
    struct Vector3 right, y, forward;
    vector3_sub(&forward, eye, target);
    vector3_normalize(&forward);
    vector3_cross(&right, up, &forward);
    vector3_normalize(&right);
    vector3_cross(&y, &forward, &right);

    // Construct matrix.
    mat[0][0] = right.x;
    mat[0][1] = right.y;
    mat[0][2] = right.z;
    mat[0][3] = 0.0f;

    mat[1][0] = y.x;
    mat[1][1] = y.y;
    mat[1][2] = y.z;
    mat[1][3] = 0.0f;

    mat[2][0] = forward.x;
    mat[2][1] = forward.y;
    mat[2][2] = forward.z;
    mat[2][3] = 0.0f;

    mat[3][0] = eye->x;
    mat[3][1] = eye->y;
    mat[3][2] = eye->z;
    mat[3][3] = 1.0f;
}