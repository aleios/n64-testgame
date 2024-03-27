#pragma once
#ifndef GAMEMODEMENU_H
#define GAMEMODEMENU_H

#include <display.h>

void gamemode_menu_init();
void gamemode_menu_cleanup();
void gamemode_menu_step();
void gamemode_menu_render(surface_t* zbuffer);

#endif //GAMEMODEMENU_H
