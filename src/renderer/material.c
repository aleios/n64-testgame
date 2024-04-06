#include <malloc.h>
#include "material.h"

struct Material materialDefault;
struct Material* material_default() {
    if(materialDefault.texture == 0) {
        materialDefault.cullFaceEnable = 1;
        materialDefault.depthWriteEnable = 1;
        materialDefault.depthTestEnable = 1;

        // Make texture.
        glGenTextures(1, &materialDefault.texture);
        glBindTexture(GL_TEXTURE_2D, materialDefault.texture);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

        // Checkerboard pattern
        uint32_t pixData[32*32];
        for(int y = 0; y < 32; ++y) {
            for(int x = 0; x < 32; ++x) {
                int index = y * 32 + x;
                int isAlt = ((x / 4) + (y / 4)) % 2 == 0;
                if (isAlt) {
                    pixData[index] = 0x000000FF;
                } else {
                    pixData[index] = 0xFF00FFFF;
                }
            }
        }

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 32, 32, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixData);
    }
    return &materialDefault;
}

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