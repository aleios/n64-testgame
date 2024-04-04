#include "gamemodeworld.h"
#include "../renderer/plane.h"
#include "../renderer/camera.h"
#include "../entities/player.h"
#include <GL/gl.h>
#include <libdragon.h>
#include <malloc.h>

#include "../assets/modelcache.h"
#include "../assets/matcache.h"

rdpq_font_t* fnt;

float x = 5.0f;
float y = 20.0f;

struct Plane* plane;
struct Camera cam;
struct Player player;

float camRot = 0.0f;
float camRotPitch = 0.425f;

sprite_t* playerSprite;
sprite_t* floorSprite;
GLuint playerTex;
GLuint floorTex;

struct Model* cubeModel;
struct Material* cubeMaterial;
struct Material* floorMaterial;
struct Material* playerMaterial;

void load_texture(const char* fname, sprite_t* sprite, GLuint* texid) {

    sprite = sprite_load(fname);

    if(!sprite) {
        *texid = 0;
        return;
    }

    glGenTextures(1, texid);
    glBindTexture(GL_TEXTURE_2D, *texid);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glSpriteTextureN64(GL_TEXTURE_2D, sprite, &(rdpq_texparms_t){.s.repeats = REPEAT_INFINITE, .t.repeats = REPEAT_INFINITE});
}

void gamemode_world_init()
{
    fnt = rdpq_font_load("rom:/cprime.font64");
    rdpq_font_style(fnt, 0, &(rdpq_fontstyle_t){
        .color = RGBA32(0xED, 0xAE, 0x49, 0xFF),
    });
    rdpq_text_register_font(1, fnt);

    rdpq_mode_persp(true);

    float aspectRatio = (float)display_get_width() / (float)display_get_height();
    float nearPlane = 1.0f;
    float farPlane = 50.0f;

    plane = plane_init(32.0f, 16);

    camera_init(&cam, 90.0f, aspectRatio, nearPlane, farPlane);
    cam.maxFollowDistance = 8.0f;

    // Initial camera rotation
    camera_rotate(&cam, camRotPitch, camRot);

    // Init player.
    player_init(&player);

    // Load and upload crate sprite.
    load_texture("rom:/player.sprite", playerSprite, &playerTex);
    load_texture("rom:/floor.sprite", floorSprite, &floorTex);

    cubeModel = modelcache_get("rom:/cube.aemf");
    cubeMaterial = matcache_get("rom:/cube.amtl");
    floorMaterial = matcache_get("rom:/floor.amtl");
    playerMaterial = matcache_get("rom:/player.amtl");
}

void gamemode_world_cleanup()
{
    matcache_release(cubeMaterial);
    modelcache_release(cubeModel);

    glDeleteTextures(1, &floorTex);
    glDeleteTextures(1, &playerTex);

    sprite_free(floorSprite);
    sprite_free(playerSprite);
}

void gamemode_world_step()
{
    joypad_inputs_t inputs = joypad_get_inputs(JOYPAD_PORT_1);
    joypad_buttons_t buttons = joypad_get_buttons_held(JOYPAD_PORT_1);
    struct Vector3 moveDir = { 0.0f, 0.0f, 0.0f };

    moveDir.x = (float)inputs.stick_x / 128.0f;
    moveDir.z = -(float)inputs.stick_y / 128.0f;

    float moveY = 0.0f;
    if(buttons.c_up) {
        moveY = 0.2f;
    } else if(buttons.c_down) {
        moveY = -0.2f;
    }

    float mag = vector3_lengthsqr(&moveDir);

    if(buttons.l) {
        if(buttons.a) {
            camRotPitch += 0.05f;
        } else {
            camRot += 0.05f;
        }
        camera_rotate(&cam, camRotPitch, camRot);
    } else if(buttons.r) {
        if(buttons.a) {
            camRotPitch -= 0.05f;
        } else {
            camRot -= 0.05f;
        }
        camera_rotate(&cam, camRotPitch, camRot);
    }

    if(fabsf(mag) > 0.01f || fabsf(moveY) > 0.01f) {

        struct Quat qx;
        quat_conj(&qx, &cam.transform.rot);
        quat_mul_vec(&moveDir, &qx, &moveDir);

        const float inputScale = 0.1f;
        player.position.x += moveDir.x * inputScale;
        player.position.z += moveDir.z * inputScale;
        player.position.y += moveY * inputScale;
    }
    vector3_lerp(&cam.target, &cam.target, &player.position, 0.1f);
}

void gamemode_world_render(surface_t* zbuffer)
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);

    camera_update(&cam);

    material_apply(floorMaterial);
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, 0.0f);
    plane_render(plane);
    glPopMatrix();

    material_apply(playerMaterial);
    player_render(&player);

    material_apply(cubeMaterial);
    for(int i = 0; i < 4; ++i)
    {
        for(int j = 0; j < 4; ++j)
        {
            glPushMatrix();
            glTranslatef((float)i * 4.0f, 1.0f, (float)j * 4.0f);
            model_render(cubeModel);
            glPopMatrix();
        }
    }

    struct mallinfo mallocInfo = mallinfo();
    float fps = display_get_fps();
    unsigned int memTotal = get_memory_size() / 1024;
    unsigned int memUsed = (mallocInfo.uordblks - (size_t) (((unsigned int) HEAP_START_ADDR - 0x80000000) - 0x10000)) / 1024;

    rdpq_text_printf(&(rdpq_textparms_t){
        .align = ALIGN_LEFT,
        .valign = VALIGN_TOP,
        .width = 0,
        .height = 0,
        .wrap = WRAP_NONE
        }, 1, x, y, "FPS: %f\nMem: %u/%u", fps, memUsed, memTotal);
}