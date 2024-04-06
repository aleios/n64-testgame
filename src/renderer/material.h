#pragma once
#ifndef MATERIAL_H
#define MATERIAL_H

#include <GL/gl.h>

struct Material {
    uint8_t depthTestEnable;
    uint8_t depthWriteEnable;
    uint8_t cullFaceEnable;
    GLuint texture;
};

struct Material* material_default();

struct Material* material_init();
void material_destroy(struct Material* mat);
void material_apply(struct Material* mat);

#endif //MATERIAL_H
