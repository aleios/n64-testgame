#pragma once
#ifndef GAMEMODEWORLD_H
#define GAMEMODEWORLD_H

#include <display.h>

void gamemode_world_init();
void gamemode_world_cleanup();
void gamemode_world_step();
void gamemode_world_render(surface_t* zbuffer);

#endif //GAMEMODEWORLD_H
