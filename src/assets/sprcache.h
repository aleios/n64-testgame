#pragma once
#ifndef SPRCACHE_H
#define SPRCACHE_H

#include <libdragon.h>

sprite_t* sprcache_get(const char* filename);
void sprcache_release(sprite_t* sprite);

#endif //SPRCACHE_H
