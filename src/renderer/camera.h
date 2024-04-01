#pragma once
#ifndef CAMERA_H
#define CAMERA_H

#include "../math/transform.h"
#include "../math/matrix.h"

// Perspective camera
struct Camera {
    struct Transform transform;
    struct Vector3 target;
    float maxFollowDistance;

    Mat4 projMatrix;
};

void camera_init(struct Camera* cam, float fovy, float aspect, float near, float far);
void camera_update(struct Camera* cam);

void camera_rotate(struct Camera* cam, float pitch, float yaw);

#endif //CAMERA_H
