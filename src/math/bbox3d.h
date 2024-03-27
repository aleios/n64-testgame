#pragma once
#ifndef BBOX3D_H
#define BBOX3D_H

#include "vector3.h"

struct BBox3D {
    struct Vector3 min;
    struct Vector3 max;
};

int bbox3d_contains(struct BBox3D* a, struct BBox3D* b);
int bbox3d_contains_point(struct BBox3D* bbox, struct Vector3* point);

#endif //BBOX3D_H
