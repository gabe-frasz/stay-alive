#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "types.h"
#include "consts.h"

void must_init(bool test, char* description);
void load_images(Images* imgs);
void init_context(Context* ctx);
void reset_context(Context* ctx);
void free_context(Context* ctx);
void draw_context(Context* ctx);
void move_camera(Context* ctx);
void change_character_sprite(Context* ctx);
void finish_challenge(bool success, Context* ctx);
int get_event_index(ALLEGRO_EVENT_TYPE event_type);
bool check_collision(Coordinate* c, float x1, float x2, float y1, float y2);

#endif
