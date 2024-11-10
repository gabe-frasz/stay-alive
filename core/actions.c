#include <stdlib.h>
#include <time.h>
#include "types.h"
#include "consts.h"
#include "functions.h"

static void mouseup_menu(Context* ctx) {
    Coordinate mouse = { ctx->event.mouse.x, ctx->event.mouse.y };
    float x1 = PLAY_BTN_X,
        x2 = PLAY_BTN_X + BUTTON_WIDTH,
        y1 = PLAY_BTN_Y,
        y2 = PLAY_BTN_Y + BUTTON_HEIGHT;
    bool is_collision = check_collision(&mouse, x1, x2, y1, y2);
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
        if (ctx->challenge_index == 3) ctx->c4.start_time = time(0);
        ctx->state = CHALLENGE;
    }

    int quarter = get_quarter_from_timer(ctx->timer);
    quarter--;
    if (quarter == 3) quarter = 1;

    for (int i = 0; i < ANIMALS_LENGTH; i++) {
        Animal* a = &ctx->animals[i];
        int random = rand() % 100;

        if (a->is_moving) {
            a->move(a);
        } else if (random == 0) {
            a->sort_destination(a);
            a->is_moving = true;
        }

        int horizontal = a->destination.x - a->position.x,
            vertical = a->destination.y - a->position.y;
        bool right = horizontal > 0, down = vertical > 0;

        if (horizontal < 0) horizontal *= -1;
        if (vertical < 0) vertical *= -1;

        switch (a->type) {
        case BIRD:
              if (horizontal < vertical && down) ctx->imgs.bird_sprites.current = ctx->imgs.bird_sprites.front[quarter];
              if (horizontal < vertical && !down) ctx->imgs.bird_sprites.current = ctx->imgs.bird_sprites.back[quarter];
              if (horizontal > vertical && right) ctx->imgs.bird_sprites.current = ctx->imgs.bird_sprites.right[quarter];
              if (horizontal > vertical && !right) ctx->imgs.bird_sprites.current = ctx->imgs.bird_sprites.left[quarter];
              if (!a->is_moving) ctx->imgs.bird_sprites.current = ctx->imgs.bird_sprites.front[0];
            break;
        case RABBIT:
            if (horizontal < vertical && down) ctx->imgs.rabbit_sprites.current = ctx->imgs.rabbit_sprites.front[quarter];
            if (horizontal < vertical && !down) ctx->imgs.rabbit_sprites.current = ctx->imgs.rabbit_sprites.back[quarter];
            if (horizontal > vertical && right) ctx->imgs.rabbit_sprites.current = ctx->imgs.rabbit_sprites.right[quarter];
            if (horizontal > vertical && !right) ctx->imgs.rabbit_sprites.current = ctx->imgs.rabbit_sprites.left[quarter];
            if (!a->is_moving) ctx->imgs.rabbit_sprites.current = ctx->imgs.rabbit_sprites.front[0];
            break;
        case GOAT:
            if (horizontal < vertical && down) ctx->imgs.goat_sprites.current = ctx->imgs.goat_sprites.front[quarter];
            if (horizontal < vertical && !down) ctx->imgs.goat_sprites.current = ctx->imgs.goat_sprites.back[quarter];
            if (horizontal > vertical && right) ctx->imgs.goat_sprites.current = ctx->imgs.goat_sprites.right[quarter];
            if (horizontal > vertical && !right) ctx->imgs.goat_sprites.current = ctx->imgs.goat_sprites.left[quarter];
            if (!a->is_moving) ctx->imgs.goat_sprites.current = ctx->imgs.goat_sprites.front[0];
            break;
        case SHEEP:
            if (horizontal < vertical && down) ctx->imgs.sheep_sprites.current = ctx->imgs.sheep_sprites.front[quarter];
            if (horizontal < vertical && !down) ctx->imgs.sheep_sprites.current = ctx->imgs.sheep_sprites.back[quarter];
            if (horizontal > vertical && right) ctx->imgs.sheep_sprites.current = ctx->imgs.sheep_sprites.right[quarter];
            if (horizontal > vertical && !right) ctx->imgs.sheep_sprites.current = ctx->imgs.sheep_sprites.left[quarter];
            if (!a->is_moving) ctx->imgs.sheep_sprites.current = ctx->imgs.sheep_sprites.front[0];
            break;
        case CAT:
            if (horizontal < vertical && down) ctx->imgs.cat_sprites.current = ctx->imgs.cat_sprites.front[quarter];
            if (horizontal < vertical && !down) ctx->imgs.cat_sprites.current = ctx->imgs.cat_sprites.back[quarter];
            if (horizontal > vertical && right) ctx->imgs.cat_sprites.current = ctx->imgs.cat_sprites.right[quarter];
            if (horizontal > vertical && !right) ctx->imgs.cat_sprites.current = ctx->imgs.cat_sprites.left[quarter];
            if (!a->is_moving) ctx->imgs.cat_sprites.current = ctx->imgs.cat_sprites.front[0];
            break;
        case SNAKE:
            if (horizontal < vertical && down) ctx->imgs.snake_sprites.current = ctx->imgs.snake_sprites.front[quarter];
            if (horizontal < vertical && !down) ctx->imgs.snake_sprites.current = ctx->imgs.snake_sprites.back[quarter];
            if (horizontal > vertical && right) ctx->imgs.snake_sprites.current = ctx->imgs.snake_sprites.right[quarter];
            if (horizontal > vertical && !right) ctx->imgs.snake_sprites.current = ctx->imgs.snake_sprites.left[quarter];
            if (!a->is_moving) ctx->imgs.snake_sprites.current = ctx->imgs.snake_sprites.front[0];
            break;
        }

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
    switch (ctx->challenge_index) {
    case 2:
        handle_challenge_3(ctx);
        break;
    case 3:
        verify_challenge_4(ctx);
        break;
    }
    
}
static void keydown_challenge(Context* ctx) {
    switch (ctx->challenge_index) {
    case 2:
        move_character_sideways(ctx);
        break;
    }
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
    case 3:
        handle_challenge_4(ctx, &mouse);
        break;
    }
}
static void mouseup_gameover(Context* ctx) {
    Coordinate mouse = { ctx->event.mouse.x, ctx->event.mouse.y };
    float x1 = RETURN_TO_MENU_BTN_X,
        x2 = RETURN_TO_MENU_BTN_X + BUTTON_WIDTH,
        y1 = RETURN_TO_MENU_BTN_Y,
        y2 = RETURN_TO_MENU_BTN_Y + BUTTON_HEIGHT;
    bool is_collision = check_collision(&mouse, x1, x2, y1, y2);
    if (is_collision) set_context_to_default(ctx);
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
