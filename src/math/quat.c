#include "quat.h"
#include "math.h"

void quat_identity(struct Quat* quat) {
    quat->x = 0.0f;
    quat->y = 0.0f;
    quat->z = 0.0f;
    quat->w = 1.0f;
}

void quat_axis_angle(struct Quat* quat, struct Vector3* axis, float angle) {
    float s = sinf(angle * 0.5f);
    float c = cosf(angle * 0.5f);
    quat->x = axis->x * s;
    quat->y = axis->y * s;
    quat->z = axis->z * s;
    quat->w = c;
}

void quat_tomat4(struct Quat* quat, Mat4 mat) {

    float sqx = quat->x * quat->x;
    float sqy = quat->y * quat->y;
    float sqz = quat->z * quat->z;

    float xy = quat->x * quat->y;
    float yz = quat->y * quat->z;
    float xz = quat->x * quat->z;

    float xw = quat->x * quat->w;
    float yw = quat->y * quat->w;
    float zw = quat->z * quat->w;

    mat[0][0] = 1.0f - 2.0f * (sqy + sqz);
    mat[0][1] = 2.0f * (xy + zw);
    mat[0][2] = 2.0f * (xz - yw);
    mat[0][3] = 0.0f;

    mat[1][0] = 2.0f * (xy - zw);
    mat[1][1] = 1.0f - 2.0f * (sqx + sqz);
    mat[1][2] = 2.0f * (yz + xw);
    mat[1][3] = 0.0f;

    mat[2][0] = 2.0f * (xz + yw);
    mat[2][1] = 2.0f * (yz - xw);
    mat[2][2] = 1.0f - 2.0f * (sqx + sqy);
    mat[2][3] = 0.0f;

    mat[3][0] = 0.0f;
    mat[3][1] = 0.0f;
    mat[3][2] = 0.0f;
    mat[3][3] = 1.0f;
}

void quat_conj(struct Quat* dest, struct Quat* quat) {
    dest->x = -quat->x;
    dest->y = -quat->y;
    dest->z = -quat->z;
    dest->w = quat->w;
}

void quat_mul(struct Quat* dest, struct Quat* a, struct Quat* b) {
    dest->x = a->w*b->x + a->x*b->w + a->y*b->z - a->z*b->y;
    dest->y = a->w*b->y + a->y*b->w + a->z*b->x - a->x*b->z;
    dest->z = a->w*b->z + a->z*b->w + a->x*b->y - a->y*b->x;
    dest->w = a->w*b->w - a->x*b->x - a->y*b->y - a->z*b->z;
}

void quat_mul_vec(struct Vector3* dest, struct Quat* quat, struct Vector3* vec) {
    struct Quat vecQuat, tform, conj;

    // Treat vector as quaternion with w = 0.
    vecQuat.x = vec->x;
    vecQuat.y = vec->y;
    vecQuat.z = vec->z;
    vecQuat.w = 0.0f;

    // Multiply input Quat with vector
    quat_mul(&tform, quat, &vecQuat);

    // Multiply conjugate of input with transformed quat
    quat_conj(&conj, quat);
    quat_mul(&vecQuat, &tform, &conj);

    // Output transformed vector.
    dest->x = vecQuat.x;
    dest->y = vecQuat.y;
    dest->z = vecQuat.z;
}