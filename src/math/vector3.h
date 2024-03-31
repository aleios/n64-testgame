#pragma once
#ifndef VECTOR3_H
#define VECTOR3_H

struct Vector3 {
    float x, y, z;
};

void vector3_add(struct Vector3* dest, struct Vector3* a, struct Vector3* b);
void vector3_sub(struct Vector3* dest, struct Vector3* a, struct Vector3* b);
void vector3_mul(struct Vector3* dest, struct Vector3* a, struct Vector3* b);
float vector3_length(struct Vector3* a);
void vector3_normalize(struct Vector3* a);
void vector3_scale(struct Vector3* dest, float scale);
float vector3_dot(struct Vector3* a, struct Vector3* b);
void vector3_cross(struct Vector3* dest, struct Vector3* a, struct Vector3* b);
void vector3_negate(struct Vector3* a);

#endif //VECTOR3_H
