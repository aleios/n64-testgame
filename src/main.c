#include <libdragon.h>
#include <GL/gl.h>
#include <GL/gl_integration.h>
#include <model64.h>
#include "gamemode/gamemode.h"

volatile static int vblankTriggered = 0;
void on_vi_interrupt() {
    vblankTriggered = 1;
}

void init()
{
    display_init(RESOLUTION_320x240, DEPTH_16_BPP, 2, GAMMA_NONE, FILTERS_RESAMPLE);
    rdpq_init();
    gl_init();
    dfs_init(DFS_DEFAULT_LOCATION);
    joypad_init();

    debug_init_isviewer();
    debug_init_usblog();
    console_set_debug(true);

    register_VI_handler(on_vi_interrupt);
}

int main(void)
{
    init();
    uint32_t displayWidth = display_get_width();
    uint32_t displayHeight = display_get_height();
    surface_t zbuffer = surface_alloc(FMT_RGBA16, displayWidth, displayHeight);

    gamemode_set(GameModeWorld);

    while(1)
    {
        // Spin for vblank.
        while(!vblankTriggered) {
        }
        vblankTriggered = 0;

        // Poll joysticks and call gamemode step.
        joypad_poll();
        gamemode_step();

        // Grab the framebuffer and call gamemode render.
        surface_t* fb = display_try_get();
        if(!fb)
            continue;

        rdpq_attach(fb, &zbuffer);
        gl_context_begin();

        gamemode_render(&zbuffer);

        gl_context_end();
        rdpq_detach_show();
    }
}
