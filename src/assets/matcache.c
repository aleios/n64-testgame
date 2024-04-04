#include <libdragon.h>
#include "matcache.h"
#include "sprcache.h"

struct Material* matcache_load(const char* filename) {
    FILE* f = asset_fopen(filename, NULL);

    if(!f) {
        return NULL;
    }

    int magicNum;
    fread(&magicNum, 1, 4, f);
    if(magicNum != 0x414D544C) { // AMTL
        fclose(f);
        return NULL;
    }

    uint8_t version;
    fread(&version, sizeof(uint8_t), 1, f);

    struct Material* mat = material_init();
    if(!mat) {
        fclose(f);
        return NULL;
    }

    // Read render opts
    fread(&mat->depthTestEnable, sizeof(uint8_t), 1, f);
    fread(&mat->depthWriteEnable, sizeof(uint8_t), 1, f);
    fread(&mat->cullFaceEnable, sizeof(uint8_t), 1, f);

    // Read texture path.
    uint16_t pathLen;
    fread(&pathLen, sizeof(uint16_t), 1, f);

    if(pathLen) {
        char texFilename[pathLen];
        fread(texFilename, sizeof(char), pathLen, f);

        // Generate and upload texture.
        sprite_t* sprite = sprcache_get(texFilename);

        glGenTextures(1, &mat->texture);
        glBindTexture(GL_TEXTURE_2D, mat->texture);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glSpriteTextureN64(GL_TEXTURE_2D, sprite, &(rdpq_texparms_t){.s.repeats = REPEAT_INFINITE, .t.repeats = REPEAT_INFINITE});
    }

    return mat;
}

struct Material* matcache_get(const char* filename) {
    return matcache_load(filename);
}

void matcache_release(struct Material* mat) {
    material_destroy(mat);
}