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

    struct Vector3 offset = { 0.0f, 0.0f, -4.0f };
    // Translate to object coords.
    cam->transform.pos = cam->target;
    // Rotate around object.
    quat_mul_vec(&cam->transform.pos, &cam->transform.rot,&cam->transform.pos);
    // Translate back.
    vector3_sub(&cam->transform.pos, &cam->transform.pos, &offset);
    vector3_negate(&cam->transform.pos);

    // Calculate new view matrix.
    Mat4 viewMatrix = {};
    transform_tomat4(&cam->transform, viewMatrix);

    glLoadMatrixf((GLfloat*)viewMatrix);
}

void camera_rotate(struct Camera* cam, float pitch, float yaw, float roll) {
    // TODO: Implement instead of relying on outside transforms.
}