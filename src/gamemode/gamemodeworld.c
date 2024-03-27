#include "gamemodeworld.h"
#include "gamemode.h"
#include "../renderer/cube.h"
#include "../renderer/plane.h"
#include <GL/gl.h>
#include <libdragon.h>

rdpq_font_t* fnt;

float x = 5.0f;
float y = 20.0f;

struct Plane* plane;

void gamemode_world_init()
{
    fnt = rdpq_font_load("rom:/cprime.font64");
    rdpq_font_style(fnt, 0, &(rdpq_fontstyle_t){
        .color = RGBA32(0xED, 0xAE, 0x49, 0xFF),
    });
    rdpq_text_register_font(1, fnt);

    rdpq_mode_persp(true);

    float aspect_ratio = (float)display_get_width() / (float)display_get_height();
    float near_plane = 1.0f;
    float far_plane = 50.0f;

    plane = plane_init(32.0f, 1);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-near_plane*aspect_ratio, near_plane*aspect_ratio, -near_plane, near_plane, near_plane, far_plane);
}

void gamemode_world_cleanup()
{

}

void gamemode_world_step()
{
    joypad_inputs_t inputs = joypad_get_inputs(JOYPAD_PORT_1);
    joypad_buttons_t buttons = joypad_get_buttons_held(JOYPAD_PORT_1);

    float sx = (float)inputs.stick_x / 128.0f;
    float sy = (float)inputs.stick_y / 128.0f;
    float mag = sx*sx + sy*sy;

    float sz = 0.0f;
    if(buttons.c_up) {
        sz = -0.1f;
    } else if(buttons.c_down) {
        sz = 0.1f;
    }

    float rot = 0.0f;
    if(buttons.l) {
        rot = -0.1f;
    } else if(buttons.r) {
        rot = 0.1f;
    }

    if(fabsf(mag) > 0.01f || sz != 0.0f || rot != 0.0f) {
        glMatrixMode(GL_MODELVIEW);
        glTranslatef(-sx, sz, sy);
    }
}

void gamemode_world_render(surface_t* zbuffer)
{
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);


    glDisable(GL_CULL_FACE);
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, 0.0f);
    plane_render(plane);
    glPopMatrix();

    glEnable(GL_CULL_FACE);
    for(int i = 0; i < 5; ++i)
    {
        for(int j = 0; j < 5; ++j)
        {
            cube_render((float)i * 4.0f, 2.0f, (float)j * 4.0f, 1.0f);
        }
    }

    float fps = display_get_fps();
    rdpq_text_printf(&(rdpq_textparms_t){
        .align = ALIGN_LEFT,
        .valign = VALIGN_TOP,
        .width = 0,
        .height = 0,
        .wrap = WRAP_NONE
        }, 1, x, y, "FPS: %f", fps);
}