#pragma once
#ifndef MODELCACHE_H
#define MODELCACHE_H

#include "../renderer/model.h"

struct Model* modelcache_get(const char* filename);
void modelcache_release(struct Model* model);

#endif //MODELCACHE_H
