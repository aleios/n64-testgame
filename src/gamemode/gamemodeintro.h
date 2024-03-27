#pragma once
#ifndef GAMEMODEINTRO_H
#define GAMEMODEINTRO_H

#include <display.h>

void gamemode_intro_init();
void gamemode_intro_cleanup();
void gamemode_intro_step();
void gamemode_intro_render(surface_t* zbuffer);

#endif //GAMEMODEINTRO_H
