#include "functions.c"

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

/*
    [0][n] MENU
    [1][n] OPEN_MAP
    [2][n] CHALLENGE
    [3][n] GAME_OVER

    [n][0] timer
    [n][1] keychar
    [n][2] keyup
    [n][3] keydown
    [n][4] mousedown
*/
void (*actions[4][5])(Context*) = {
    {NULL, NULL, NULL, NULL, NULL}, // MENU
    {timer_map, keychar_map, keyup_map, NULL, NULL}, // OPEN_MAP
    {NULL, NULL, NULL, NULL, NULL}, // CHALLENGE
    {NULL, NULL, NULL, NULL, NULL}  // GAME_OVER
};
