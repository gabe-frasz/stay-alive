#include <stdlib.h>
#include "types.h"
#include "consts.h"
#include "functions.h"

static void mouseup_menu(Context* ctx) {
    Coordinate mouse = { ctx->event.mouse.x, ctx->event.mouse.y };
    float btn_x = DISPLAY_WIDTH / 2.0 - BUTTON_WIDTH / 2.0;
    float btn_y = DISPLAY_HEIGHT / 2.0 - BUTTON_HEIGHT / 2.0;
    bool is_collision = check_collision(&mouse, btn_x, btn_x + BUTTON_WIDTH, btn_y, btn_y + BUTTON_HEIGHT);
    if (is_collision) ctx->state = OPEN_MAP;
}
static void timer_map(Context* ctx) {
    float cx1 = ctx->challenges_areas[ctx->challenge_index].x1;
    float cx2 = ctx->challenges_areas[ctx->challenge_index].x2;
    float cy1 = ctx->challenges_areas[ctx->challenge_index].y1;
    float cy2 = ctx->challenges_areas[ctx->challenge_index].y2;

    Coordinate player_top_left = {ctx->player.x, ctx->player.y};
    Coordinate player_top_right = {ctx->player.x + PLAYER_WIDTH, ctx->player.y};
    Coordinate player_bottom_left = {ctx->player.x, ctx->player.y + PLAYER_HEIGHT};
    Coordinate player_bottom_right = {ctx->player.x + PLAYER_WIDTH, ctx->player.y + PLAYER_HEIGHT};

    bool is_player_top_left_colliding = check_collision(&player_top_left, cx1, cx2, cy1, cy2);
    bool is_player_top_right_colliding = check_collision(&player_top_right, cx1, cx2, cy1, cy2);
    bool is_player_bottom_left_colliding = check_collision(&player_bottom_left, cx1, cx2, cy1, cy2);
    bool is_player_bottom_right_colliding = check_collision(&player_bottom_right, cx1, cx2, cy1, cy2);

    if (ctx->challenge_index == 1 && ctx->map.y * -1 > MAP_SIZE/2.0 - 300) return;
    if (ctx->challenge_index == 2 && ctx->map.y * -1 < MAP_SIZE/2.0 - 100) return;
    if (ctx->challenge_index == 3 && ctx->map.x * -1 < 500) return;
    if (ctx->challenge_index == 4 && ctx->map.x * -1 > 500) return;

    if (is_player_top_left_colliding || is_player_top_right_colliding ||
        is_player_bottom_left_colliding || is_player_bottom_right_colliding) {
        ctx->state = CHALLENGE;
    }
}
static void keychar_map(Context* ctx) {
    move_camera(ctx);
    change_character_sprite(ctx);
}
static void keyup_map(Context* ctx) {
    change_character_sprite(ctx);
}
static void timer_challenge(Context* ctx) {
    if (ctx->challenge_index != 2) return;
    
    Challenge_3* c3 = &ctx->c3;

    for (int i = 0; i < 16; i++) {
        Falling_Object* obj = &c3->falling_objects[i];

        obj->position.y += FALLING_SPEED;

        if (obj->position.y >= c3->player_position.y && 
            (obj->position.x >= c3->player_position.x && obj->position.x <= c3->player_position.x + 100 ||
            obj->position.x + 50 >= c3->player_position.x && obj->position.x + 50 <= c3->player_position.x + 100)) {
            if (obj->id == 0) {
                c3->apples_counter++;
            } else {
                c3->mushrooms_counter++;
            }
            
            generate_random_falling_object(obj);
        }

        if (obj->position.y > DISPLAY_HEIGHT) generate_random_falling_object(obj);
    }

    if (c3->apples_counter >= 10) finish_challenge(true, ctx);
    if (c3->mushrooms_counter >= 10) finish_challenge(false, ctx);
}
static void keydown_challenge(Context* ctx) {
    move_character_sideways(ctx);
}
static void mouseup_challenge(Context* ctx) {
    Coordinate mouse = { ctx->event.mouse.x, ctx->event.mouse.y };

    switch (ctx->challenge_index) {
    case 0:
        handle_challenge_1(ctx, &mouse);
        break;
    case 1:
        handle_challenge_2(ctx, &mouse);
        break;
    }
}
static void mouseup_gameover(Context* ctx) {
    Coordinate mouse = { ctx->event.mouse.x, ctx->event.mouse.y };
    float btn_x = DISPLAY_WIDTH / 2.0 - BUTTON_WIDTH / 2.0;
    float btn_y = DISPLAY_HEIGHT / 2.0 - BUTTON_HEIGHT / 2.0;
    bool is_collision = check_collision(&mouse, btn_x, btn_x + BUTTON_WIDTH, btn_y, btn_y + BUTTON_HEIGHT);
    if (is_collision) reset_context(ctx);
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
