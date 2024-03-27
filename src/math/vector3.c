#include "vector3.h"

void vector3_add(struct Vector3* dest, struct Vector3* a) {
    dest->x += a->x;
    dest->y += a->y;
    dest->z += a->z;
}

void vector3_sub(struct Vector3* dest, struct Vector3* a) {
    dest->x -= a->x;
    dest->y -= a->y;
    dest->z -= a->z;
}

void vector3_scale(struct Vector3* dest, float scale) {
    dest->x *= scale;
    dest->y *= scale;
    dest->z *= scale;
}

float vector3_dot(struct Vector3* a, struct Vector3* b) {
    return a->x * b->x + a->y * b->y + a->z * b->z;
}

void vector3_cross(struct Vector3* dest, struct Vector3* a, struct Vector3* b) {
    dest->x = a->y * b->z - a->z * b->y;
    dest->y = a->z * b->x - a->x * b->z;
    dest->z = a->x * b->y - a->y * b->x;
}