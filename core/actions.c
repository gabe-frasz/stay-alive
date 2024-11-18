#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "types.h"
#include "consts.h"
#include "ctx-functions.h"
#include "helpers.h"

static void mouseup_menu(Context* ctx) {
    Coordinate mouse = { ctx->event.mouse.x, ctx->event.mouse.y };
    float x = PLAY_BTN_X,
          y = PLAY_BTN_Y,
          w = BUTTON_WIDTH,
          h = BUTTON_HEIGHT;
    bool play = check_collision(&mouse, x, x + w, y, y + h);
    if (play) ctx->state = OPEN_MAP;
}
static void timer_map(Context* ctx) {
    check_player_position(ctx);
    change_animals_sprite(ctx);
}
static void keychar_map(Context* ctx) {
    move_camera(ctx);
    change_character_sprite(ctx);
}
static void keyup_map(Context* ctx) {
    change_character_sprite(ctx);
}
static void timer_challenge(Context* ctx) {
    if (!ctx->tutorials[ctx->challenge_index].is_completed) {
        play_tutorial(ctx);
        return;
    }

    if (ctx->challenge_index == 1 && ctx->c2.is_distillation_playing) {
        play_video(ctx, ctx->videos.c2_distillation);
        return;
    }

    switch (ctx->challenge_index) {
    case 2:
        handle_challenge_3(ctx);
        break;
    case 3:
        if (ctx->c4.start_time == -1) ctx->c4.start_time = time(0);
        verify_challenge_4(ctx);
        break;
    case 4:
        verify_challenge_5(ctx);
        break;
    }
}
static void keydown_challenge(Context* ctx) {
    if (!ctx->tutorials[ctx->challenge_index].is_completed) {
        return;
    }

    switch (ctx->challenge_index) {
    case 2:
        move_character_sideways(ctx);
        break;
    case 4:
        rub_bonfire(ctx);
    }
}
static void mouseup_challenge(Context* ctx) {
    Coordinate mouse = { ctx->event.mouse.x, ctx->event.mouse.y };

    if (!ctx->tutorials[ctx->challenge_index].is_completed) {
        ALLEGRO_VIDEO* current_video = ctx->videos.tutorials[ctx->tutorial_index];
        ALLEGRO_VIDEO* next_video = ctx->videos.tutorials[ctx->tutorial_index + 1];
        if (!al_is_video_playing(current_video) && check_collision(&mouse, 1130, 1232, 630, 677)) {
            ctx->tutorial_index++;
            if (ctx->tutorial_index <= ctx->tutorials[ctx->challenge_index].last_step_index) {
                al_start_video(next_video, al_get_default_mixer());
            } else {
                ctx->tutorials[ctx->challenge_index].is_completed = true;
            }
        }
        return;
    }

    switch (ctx->challenge_index) {
    case 0:
        handle_challenge_1(ctx, &mouse);
        break;
    case 1:
        handle_challenge_2(ctx, &mouse);
        break;
    case 3:
        handle_challenge_4(ctx, &mouse);
        break;
    case 4:
        handle_challenge_5(ctx, &mouse);
        break;
    }
}
static void mouseup_gameover(Context* ctx) {
    Coordinate mouse = { ctx->event.mouse.x, ctx->event.mouse.y };
    float x = RETURN_TO_MENU_BTN_X,
          y = RETURN_TO_MENU_BTN_Y,
          w = BUTTON_WIDTH,
          h = BUTTON_HEIGHT;
    bool return_to_menu = check_collision(&mouse, x, x + w, y, y + h);
    if (return_to_menu) set_context_to_default(ctx);
}

/*
    [0][n] MENU
    [1][n] OPEN_MAP
    [2][n] CHALLENGE
    [3][n] GAME_OVER

    [n][0] timer
    [n][1] keychar
    [n][2] keyup
    [n][3] keydown
    [n][4] mouseup
*/
void (*actions[4][5])(Context*) = {
    {NULL, NULL, NULL, NULL, mouseup_menu}, // MENU
    {timer_map, keychar_map, keyup_map, NULL, NULL}, // OPEN_MAP
    {timer_challenge, NULL, NULL, keydown_challenge, mouseup_challenge}, // CHALLENGE
    {NULL, NULL, NULL, NULL, mouseup_gameover}  // GAME_OVER
};
