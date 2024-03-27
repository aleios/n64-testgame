#pragma once
#ifndef GAMEMODE_H
#define GAMEMODE_H

#include <stdint.h>
#include <display.h>

enum GameModeIds {
    GameModeIntro,
    GameModeMenu,
    GameModeWorld
};

struct GameMode {
    uint8_t isInit;
    void (*init)();
    void (*cleanup)();
    void (*step)();
    void (*render)(surface_t* zbuffer);
};

void gamemode_set(uint16_t id);
void gamemode_clear();
uint16_t gamemode_current();

void gamemode_step();
void gamemode_render(surface_t* zbuffer);

#endif //GAMEMODE_H
