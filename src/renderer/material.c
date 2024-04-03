#include <malloc.h>
#include "material.h"

struct Material* material_init() {
    struct Material* mat = malloc(sizeof(struct Material));

    if(!mat)
        return NULL;

    mat->depthTestEnable = 0;
    mat->depthWriteEnable = 0;
    mat->cullFaceEnable = 0;
    mat->texture = 0;

    return mat;
}

void material_destroy(struct Material* mat) {
    if(mat->texture) {
        glDeleteTextures(1, &mat->texture);
    }

    free(mat);
}

void material_apply(struct Material* mat) {
    if(mat->depthTestEnable) {
        glEnable(GL_DEPTH_TEST);
    } else {
        glDisable(GL_DEPTH_TEST);
    }

    glDepthMask(mat->depthWriteEnable);

    if(mat->cullFaceEnable) {
        glEnable(GL_CULL_FACE);
    } else {
        glDisable(GL_CULL_FACE);
    }

    if(mat->texture) {
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, mat->texture);
    } else {
        glDisable(GL_TEXTURE_2D);
    }
}