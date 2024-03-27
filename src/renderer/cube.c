#include <malloc.h>
#include <GL/gl.h>
#include "cube.h"

struct CubeVertex {
    float position[3];
    float normal[3];
    uint32_t color;
};

const float cubeSize = 1.0f;
const struct CubeVertex cubeVertices[] = {
    // +X
    { .position = { cubeSize, -cubeSize, -cubeSize}, .normal = { 1.f,  0.f,  0.f}, .color = 0xFF0000FF },
    { .position = { cubeSize,  cubeSize, -cubeSize}, .normal = { 1.f,  0.f,  0.f}, .color = 0xFF0000FF },
    { .position = { cubeSize,  cubeSize,  cubeSize}, .normal = { 1.f,  0.f,  0.f}, .color = 0xFF0000FF },
    { .position = { cubeSize, -cubeSize,  cubeSize}, .normal = { 1.f,  0.f,  0.f}, .color = 0xFF0000FF },

    // -X
    { .position = {-cubeSize, -cubeSize, -cubeSize}, .normal = {-1.f,  0.f,  0.f}, .color = 0x00FFFFFF },
    { .position = {-cubeSize, -cubeSize,  cubeSize}, .normal = {-1.f,  0.f,  0.f}, .color = 0x00FFFFFF },
    { .position = {-cubeSize,  cubeSize,  cubeSize}, .normal = {-1.f,  0.f,  0.f}, .color = 0x00FFFFFF },
    { .position = {-cubeSize,  cubeSize, -cubeSize}, .normal = {-1.f,  0.f,  0.f}, .color = 0x00FFFFFF },

    // +Y
    { .position = {-cubeSize,  cubeSize, -cubeSize}, .normal = { 0.f,  1.f,  0.f}, .color = 0x00FF00FF },
    { .position = {-cubeSize,  cubeSize,  cubeSize}, .normal = { 0.f,  1.f,  0.f}, .color = 0x00FF00FF },
    { .position = { cubeSize,  cubeSize,  cubeSize}, .normal = { 0.f,  1.f,  0.f}, .color = 0x00FF00FF },
    { .position = { cubeSize,  cubeSize, -cubeSize}, .normal = { 0.f,  1.f,  0.f}, .color = 0x00FF00FF },

    // -Y
    { .position = {-cubeSize, -cubeSize, -cubeSize}, .normal = { 0.f, -1.f,  0.f}, .color = 0xFF00FFFF },
    { .position = { cubeSize, -cubeSize, -cubeSize}, .normal = { 0.f, -1.f,  0.f}, .color = 0xFF00FFFF },
    { .position = { cubeSize, -cubeSize,  cubeSize}, .normal = { 0.f, -1.f,  0.f}, .color = 0xFF00FFFF },
    { .position = {-cubeSize, -cubeSize,  cubeSize}, .normal = { 0.f, -1.f,  0.f}, .color = 0xFF00FFFF },

    // +Z
    { .position = {-cubeSize, -cubeSize,  cubeSize}, .normal = { 0.f,  0.f,  1.f}, .color = 0x0000FFFF },
    { .position = { cubeSize, -cubeSize,  cubeSize}, .normal = { 0.f,  0.f,  1.f}, .color = 0x0000FFFF },
    { .position = { cubeSize,  cubeSize,  cubeSize}, .normal = { 0.f,  0.f,  1.f}, .color = 0x0000FFFF },
    { .position = {-cubeSize,  cubeSize,  cubeSize}, .normal = { 0.f,  0.f,  1.f}, .color = 0x0000FFFF },

    // -Z
    { .position = {-cubeSize, -cubeSize, -cubeSize}, .normal = { 0.f,  0.f, -1.f}, .color = 0xFFFF00FF },
    { .position = {-cubeSize,  cubeSize, -cubeSize}, .normal = { 0.f,  0.f, -1.f}, .color = 0xFFFF00FF },
    { .position = { cubeSize,  cubeSize, -cubeSize}, .normal = { 0.f,  0.f, -1.f}, .color = 0xFFFF00FF },
    { .position = { cubeSize, -cubeSize, -cubeSize}, .normal = { 0.f,  0.f, -1.f}, .color = 0xFFFF00FF },
};

static const uint16_t cubeIndices[] = {
    0,  1,  2,  0,  2,  3,
    4,  5,  6,  4,  6,  7,
    8,  9, 10,  8, 10, 11,
    12, 13, 14, 12, 14, 15,
    16, 17, 18, 16, 18, 19,
    20, 21, 22, 20, 22, 23,
};

void cube_render(float x, float y, float z, float size)
{
    glPushMatrix();
    glTranslatef(x, y, z);
    glScalef(size, size, size);

    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);

    glVertexPointer(3, GL_FLOAT, sizeof(struct CubeVertex), (void*)(0*sizeof(float) + (void*)cubeVertices));
    glNormalPointer(GL_FLOAT, sizeof(struct CubeVertex), (void*)(3*sizeof(float) + (void*)cubeVertices));
    glColorPointer(4, GL_UNSIGNED_BYTE, sizeof(struct CubeVertex), (void*)(6*sizeof(float) + (void*)cubeVertices));

    glDrawElements(GL_TRIANGLES, sizeof(cubeIndices) / sizeof(uint16_t), GL_UNSIGNED_SHORT, cubeIndices);

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);

    glDisable(GL_COLOR_MATERIAL);
    glPopMatrix();
}