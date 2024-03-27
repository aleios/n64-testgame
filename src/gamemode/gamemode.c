#include "gamemode.h"

#include "gamemodeintro.h"
#include "gamemodemenu.h"
#include "gamemodeworld.h"

void gamemode_noop() {}
struct GameMode gameModeIntro = {
    .isInit  = 0,
    .init    = gamemode_intro_init,
    .cleanup = gamemode_intro_cleanup,
    .step    = gamemode_intro_step,
    .render  = gamemode_intro_render
};

struct GameMode gameModeMenu = {
    .isInit  = 0,
    .init    = gamemode_menu_init,
    .cleanup = gamemode_menu_cleanup,
    .step    = gamemode_menu_step,
    .render  = gamemode_menu_render,
};

struct GameMode gameModeWorld = {
    .isInit  = 0,
    .init    = gamemode_world_init,
    .cleanup = gamemode_world_cleanup,
    .step    = gamemode_world_step,
    .render  = gamemode_world_render,
};

struct GameMode* gameModes[] = {
    [GameModeIntro] = &gameModeIntro,
    [GameModeMenu]  = &gameModeMenu,
    [GameModeWorld] = &gameModeWorld,
};

uint16_t currentGameModeId;
struct GameMode currentGameMode;

struct GameMode* gamemode_init(struct GameMode* mode) {
    struct GameMode* m = &currentGameMode;

    m->init = (mode->init) ? mode->init : gamemode_noop;
    m->cleanup = (mode->cleanup) ? mode->cleanup : gamemode_noop;
    m->step = (mode->step) ? mode->step : gamemode_noop;
    m->render = (mode->render) ? mode->render : gamemode_noop;

    m->init();
    m->isInit = 1;
    return m;
}

void gamemode_set(uint16_t id) {
    currentGameModeId = id;
    gamemode_init(gameModes[id]);
}

void gamemode_clear() {
    currentGameMode.cleanup();
    currentGameMode.isInit = 0;
}

uint16_t gamemode_current() {
    return currentGameModeId;
}

void gamemode_step() {
    currentGameMode.step();
}

void gamemode_render(surface_t* zbuffer) {
    currentGameMode.render(zbuffer);
}