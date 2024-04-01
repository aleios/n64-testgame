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
    mat[0] *= t->scale.x;
    mat[1] *= t->scale.x;
    mat[2] *= t->scale.x;

    mat[4] *= t->scale.y;
    mat[5] *= t->scale.y;
    mat[6] *= t->scale.y;

    mat[8] *= t->scale.z;
    mat[9] *= t->scale.z;
    mat[10] *= t->scale.z;

    // Translation
    mat[12] = t->pos.x;
    mat[13] = t->pos.y;
    mat[14] = t->pos.z;
}