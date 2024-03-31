#pragma once
#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "vector3.h"
#include "quat.h"
#include "matrix.h"

struct Transform {
    struct Vector3 pos;
    struct Vector3 scale;
    struct Quat rot;
};

void transform_reset(struct Transform* t);
void transform_tomat4(struct Transform* t, Mat4 mat);

#endif //TRANSFORM_H
