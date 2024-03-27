#include "bbox3d.h"

int bbox3d_contains(struct BBox3D* a, struct BBox3D* b) {
    return a->min.x <= b->max.x && a->max.x >= b->min.x &&
           a->min.y <= b->max.y && a->max.y >= b->min.y &&
           a->min.z <= b->max.z && a->max.z >= b->min.z;
}

int bbox3d_contains_point(struct BBox3D* bbox, struct Vector3* point) {
    return bbox->min.x < point->x && bbox->min.y < point->y &&
           bbox->min.z < point->z && bbox->max.x > point->x &&
           bbox->max.y > point->y && bbox->max.z > point->z;
}