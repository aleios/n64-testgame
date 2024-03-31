#include <math.h>
#include "vector3.h"

struct Vector3 unitVecUp = { 0.0f, 1.0f, 0.0f };
struct Vector3 unitVecForward = { 0.0f, 0.0f, 1.0f };
struct Vector3 unitVecRight = { 1.0f, 0.0f, 0.0f };

void vector3_add(struct Vector3* dest, struct Vector3* a, struct Vector3* b) {
    dest->x = a->x + b->x;
    dest->y = a->y + b->y;
    dest->z = a->z + b->z;
}

void vector3_sub(struct Vector3* dest, struct Vector3* a, struct Vector3* b) {
    dest->x = a->x - b->x;
    dest->y = a->y - b->y;
    dest->z = a->z - b->z;
}

void vector3_mul(struct Vector3* dest, struct Vector3* a, struct Vector3* b) {
    dest->x = a->x * b->x;
    dest->y = a->y * b->y;
    dest->z = a->z * b->z;
}

float vector3_length(struct Vector3* a) {
    return sqrtf(a->x * a->x + a->y * a->y + a->z * a->z);
}

void vector3_normalize(struct Vector3* a) {
    float len = vector3_length(a);

    // Avoid division by zero.
    if(len == 0.0f) {
        return;
    }
    a->x /= len;
    a->y /= len;
    a->z /= len;
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

void vector3_negate(struct Vector3* a) {
    a->x = -a->x;
    a->y = -a->y;
    a->z = -a->z;
}

void vector3_lerp(struct Vector3* dest, struct Vector3* a, struct Vector3* b, float amount) {
    float inv = 1.0f - amount;
    dest->x = a->x * inv + b->x * amount;
    dest->y = a->y * inv + b->y * amount;
    dest->z = a->z * inv + b->z * amount;
}