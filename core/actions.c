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
static void mouseup_challenge(Context* ctx) {
    Coordinate mouse = { ctx->event.mouse.x, ctx->event.mouse.y };

    if (ctx->challenge_index == 0) {
        for (int i = 0; i < 5; i++) {
            int pos_i = ctx->c1.placeable_objects[i].position_index,
                cpos_i = ctx->c1.placeable_objects[i].correct_position_index;
            float x = ctx->c1.placeable_positions[pos_i].x,
                  y = ctx->c1.placeable_positions[pos_i].y,
                  w = ctx->c1.placeable_objects[i].width,
                  h = ctx->c1.placeable_objects[i].height;

            if (check_collision(&mouse, x, x + w, y, y + h)) {
                ctx->c1.selected_object_index = i;
            }
        }
        for (int i = 0; i < 10; i++) {
            Placeable_Object* selected = &ctx->c1.placeable_objects[ctx->c1.selected_object_index];
            float x = ctx->c1.placeable_positions[i].x,
                  y = ctx->c1.placeable_positions[i].y;
            if (check_collision(&mouse, x, x + 100, y, y + 100)) {
               selected->position_index = i;
            }
        }

        if (check_collision(&mouse, 1000, 1200, 600, 700)) {
            bool success = true;
            for (int i = 0; i < 5; i++) {
                Placeable_Object* obj = &ctx->c1.placeable_objects[i];
                if (obj->position_index != obj->correct_position_index) success = false;
            }
            finish_challenge(success, ctx);
        }
        return;
    }

    if (ctx->challenge_index == 1) {
        for (int i = 0; i < 7; i++) {
            Selectable_Object* obj = &ctx->c2.selectable_objects[i];
            if (check_collision(&mouse, obj->position.x, obj->position.x + 100, obj->position.y, obj->position.y + 100)) {
                obj->selected = !obj->selected;
            }
        }

        if (check_collision(&mouse, 1000, 1200, 600, 700)) {
            bool success = true;
            for (int i = 0; i < 7; i++) {
                if ((ctx->c2.selectable_objects[i].selected && !ctx->c2.selectable_objects[i].correct) || 
                    (!ctx->c2.selectable_objects[i].selected && ctx->c2.selectable_objects[i].correct)) {
                    success = false;
                }
            }
            finish_challenge(success, ctx);
        }
        return;
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
    {NULL, NULL, NULL, NULL, mouseup_challenge}, // CHALLENGE
    {NULL, NULL, NULL, NULL, mouseup_gameover}  // GAME_OVER
};
