#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "types.h"
#include "consts.h"

void must_init(bool test, char* description);
void generate_random_falling_object(Falling_Object* obj);
void load_images(Images* imgs);
void load_sounds(Sounds* sounds);
void set_context_to_default(Context* ctx);
void init_context(Context* ctx);
void reset_context(Context* ctx);
void free_context(Context* ctx);
void draw_context(Context* ctx);
void move_animal(Animal* self);
bool check_obstacles_collision(Context* ctx);
void move_camera(Context* ctx);
int get_quarter_from_timer(ALLEGRO_TIMER* timer);
void change_character_sprite(Context* ctx);
void finish_challenge(bool success, Context* ctx);
int get_event_index(ALLEGRO_EVENT_TYPE event_type);
bool check_collision(Coordinate* c, float x1, float x2, float y1, float y2);
void handle_challenge_1(Context* ctx, Coordinate* mouse);
void handle_challenge_2(Context* ctx, Coordinate* mouse);
void handle_challenge_3(Context* ctx);
void move_character_sideways(Context* ctx);
void handle_challenge_4(Context* ctx, Coordinate* mouse);
void verify_challenge_4(Context* ctx);

#endif
