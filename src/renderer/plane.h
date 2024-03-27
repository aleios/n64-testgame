#pragma once
#ifndef PLANE_H
#define PLANE_H

#include <GL/gl.h>

struct Plane {
    GLuint list;
    GLuint buffers[2];
    GLuint vao;
    uint16_t numIndices;
};

struct Plane* plane_init(float size, int segments);
void plane_destroy(struct Plane* plane);
void plane_render(struct Plane* plane);

#endif //PLANE_H
