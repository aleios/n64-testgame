#pragma once
#ifndef PLAYER_H
#define PLAYER_H

#include "../math/vector3.h"

struct Player {
    struct Vector3 position;
};

void player_init(struct Player* p);
void player_cleanup(struct Player* p);

void player_render(struct Player* p);

#endif //PLAYER_H
