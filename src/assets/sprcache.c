#include "sprcache.h"

sprite_t* sprcache_get(const char* filename) {
    return sprite_load(filename);
}

void sprcache_release(sprite_t* sprite) {
    sprite_free(sprite);
}