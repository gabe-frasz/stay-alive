#ifndef HELPERS_H
#define HELPERS_H

#include "types.h"

void must_init(bool test, char* description);
bool check_collision(Coordinate* c, float x1, float x2, float y1, float y2);
void load_images(Images* imgs);
void load_sounds(Sounds* sounds);
void move_animal(Animal* self);
void sort_destination(Animal* self);
int get_event_index(ALLEGRO_EVENT_TYPE event_type);
int get_quarter_from_timer(ALLEGRO_TIMER* timer);
bool check_collision(Coordinate* c, float x1, float x2, float y1, float y2);
void generate_random_falling_object(Falling_Object* obj);

#endif
