#include "matrix.h"

void mat_identity(Mat4 mat) {
    mat[0] = 1.0f;
    mat[1] = 0.0f;
    mat[2] = 0.0f;
    mat[3] = 0.0f;

    mat[4] = 0.0f;
    mat[5] = 1.0f;
    mat[6] = 0.0f;
    mat[7] = 0.0f;

    mat[8] = 0.0f;
    mat[9] = 0.0f;
    mat[10] = 1.0f;
    mat[11] = 0.0f;

    mat[12] = 0.0f;
    mat[13] = 0.0f;
    mat[14] = 0.0f;
    mat[15] = 1.0f;
}

void mat_frustum(Mat4 mat, float left, float right, float bottom, float top, float near, float far) {
    mat[0] = (2.0f * near) / (right - left);
    mat[1] = 0.0f;
    mat[2] = 0.0f;
    mat[3] = 0.0f;

    mat[4] = 0.0f;
    mat[5] = (2.0f * near) / (top - bottom);
    mat[6] = 0.0f;
    mat[7] = 0.0f;

    mat[8] = (right + left) / (right - left);
    mat[9] = (top + bottom) / (top - bottom);
    mat[10] = -(far + near) / (far - near);
    mat[11] = -1.0f;

    mat[12] = 0.0f;
    mat[13] = 0.0f;
    mat[14] = -(2 * far * near) / (far - near);
    mat[15] = 0.0f;
}

void mat_look_at(Mat4 mat, struct Vector3* eye, struct Vector3* target, struct Vector3* up) {
    struct Vector3 right, y, forward;
    vector3_sub(&forward, eye, target);
    vector3_normalize(&forward);
    vector3_cross(&right, up, &forward);
    vector3_normalize(&right);
    vector3_cross(&y, &forward, &right);

    // Construct matrix.
    mat[0] = right.x;
    mat[1] = right.y;
    mat[2] = right.z;
    mat[3] = 0.0f;

    mat[4] = y.x;
    mat[5] = y.y;
    mat[6] = y.z;
    mat[7] = 0.0f;

    mat[8] = forward.x;
    mat[9] = forward.y;
    mat[10] = forward.z;
    mat[11] = 0.0f;

    mat[12] = eye->x;
    mat[13] = eye->y;
    mat[14] = eye->z;
    mat[15] = 1.0f;
}