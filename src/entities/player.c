#include "player.h"
#include "../renderer/cube.h"

void player_init(struct Player* p) {
    p->position.x = 0.0f;
    p->position.y = 0.0f;
    p->position.z = 0.0f;
}

void player_cleanup(struct Player* p) {

}

void player_render(struct Player* p) {
    cube_render(p->position.x, p->position.y + 0.5f, p->position.z, 0.5f);
}