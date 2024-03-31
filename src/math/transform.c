#include <debug.h>
#include "transform.h"

void transform_reset(struct Transform* t) {
    t->pos = (struct Vector3){ 0.0f, 0.0f, 0.0f };
    t->scale = (struct Vector3){ 1.0f, 1.0f, 1.0f };
    quat_identity(&t->rot);
}

void transform_tomat4(struct Transform* t, Mat4 mat) {
    // Rotation
    quat_tomat4(&t->rot, mat);

    // Scale
    mat[0][0] *= t->scale.x;
    mat[0][1] *= t->scale.x;
    mat[0][2] *= t->scale.x;

    mat[1][0] *= t->scale.y;
    mat[1][1] *= t->scale.y;
    mat[1][2] *= t->scale.y;

    mat[2][0] *= t->scale.z;
    mat[2][1] *= t->scale.z;
    mat[2][2] *= t->scale.z;

    // Translation
    mat[3][0] = t->pos.x;
    mat[3][1] = t->pos.y;
    mat[3][2] = t->pos.z;
}