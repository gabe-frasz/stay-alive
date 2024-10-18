#include "functions.c"

void keychar_map(Context* ctx) {
    move_camera(ctx);
    change_character_sprite(ctx);
}
void keyup_map(Context* ctx) {
    change_character_sprite(ctx);
}

void (*actions[4][5])(Context*) = {
    {NULL, NULL, NULL, NULL, NULL}, // MENU
    {NULL, keychar_map, keyup_map, NULL, NULL}, // OPEN_MAP
    {NULL, NULL, NULL, NULL, NULL}, // CHALLENGE
    {NULL, NULL, NULL, NULL, NULL}  // GAME_OVER
};
