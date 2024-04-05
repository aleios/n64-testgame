#pragma once
#ifndef MODEL_H
#define MODEL_H

#include <GL/gl.h>
#include "material.h"

struct Model {
    GLuint listIds;
    struct Material** materials;
    uint16_t numMeshes;

// TODO: Need dynarray to track these...
//    GLuint buffers;
//    GLuint vaos;
};

struct Model* model_init(uint32_t numMeshes);
void model_destroy(struct Model* model);

void model_render(struct Model* model);

#endif //MODEL_H
