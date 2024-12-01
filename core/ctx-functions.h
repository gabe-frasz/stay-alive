#ifndef CTX_FUNCTIONS_H
#define CTX_FUNCTIONS_H

#include "types.h"
#include "consts.h"

void set_context_to_default(Context* ctx);
void init_context(Context* ctx);
void reset_context(Context* ctx);
void free_context(Context* ctx);
void draw_context(Context* ctx);
bool check_obstacles_collision(Context* ctx);
void move_camera(Context* ctx);
void check_player_position(Context* ctx);
void change_character_sprite(Context* ctx);
void change_animals_sprite(Context* ctx);
void play_animal_sounds(Context* ctx);
void finish_challenge(bool success, Context* ctx);
void play_tutorial(Context* ctx);
void change_hallucination_angle(Context* ctx);
void handle_challenge_1(Context* ctx, Coordinate* mouse);
void handle_challenge_2(Context* ctx, Coordinate* mouse);
void handle_challenge_3(Context* ctx);
void move_character_sideways(Context* ctx);
void handle_challenge_4(Context* ctx, Coordinate* mouse);
void verify_challenge_4(Context* ctx);
void handle_challenge_5(Context* ctx, Coordinate* mouse);
void rub_bonfire(Context* ctx);
void verify_challenge_5(Context* ctx);

#endif
