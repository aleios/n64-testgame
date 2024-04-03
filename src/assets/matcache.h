#pragma once
#ifndef MATCACHE_H
#define MATCACHE_H

#include "../renderer/material.h"

struct Material* matcache_get(const char* filename);
void matcache_release(struct Material* mat);

#endif //MATCACHE_H
