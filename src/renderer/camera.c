#include <GL/gl.h>
#include <math.h>
#include "camera.h"

void camera_init(struct Camera* cam, float fovy, float aspect, float near, float far) {
    transform_reset(&cam->transform);

    // Perspective projection matrix.
    const float bottom = -near * tanf(0.5f * fovy * (float)M_PI / 180.0f);
    const float top = -bottom;
    const float left = aspect * bottom;
    const float right = -left;
    mat_frustum(cam->projMatrix, left, right, bottom, top, near, far);

    glMatrixMode(GL_PROJECTION);
    glLoadMatrixf((GLfloat*)cam->projMatrix);

    // Set back to model view.
    glMatrixMode(GL_MODELVIEW);
}

void camera_update(struct Camera* cam) {

    struct Vector3 offset = { 0.0f, 0.0f, -cam->maxFollowDistance };
    // Move back to the target.
    cam->transform.pos = cam->target;

    // Calculate new view matrix.
    Mat4 viewMatrix = {};

    // Do our transforms
    quat_mul_vec(&cam->transform.pos, &cam->transform.rot, &cam->transform.pos);
    vector3_sub(&cam->transform.pos, &cam->transform.pos, &offset);
    vector3_negate(&cam->transform.pos);

    // Grab new matrix.
    transform_tomat4(&cam->transform, viewMatrix);
    glLoadMatrixf((GLfloat*)viewMatrix);

}

void camera_rotate(struct Camera* cam, float pitch, float yaw) {
    struct Quat qx;
    struct Quat qy;
    quat_axis_angle(&qy, &unitVecUp, yaw); // Rotate around Y
    quat_axis_angle(&qx, &unitVecRight, pitch); // Rotate around X
    quat_mul(&cam->transform.rot, &qx, &qy);
}