#ifndef HELPERS_H
#define HELPERS_H

#include "types.h"

void must_init(bool test, char* description);
bool check_collision(Coordinate* c, float x1, float x2, float y1, float y2);
void load_images(Images* imgs);
void load_sounds(Sounds* sounds);
void load_videos(Videos* videos);
void move_animal(Animal* self);
void sort_destination(Animal* self);
int get_event_index(ALLEGRO_EVENT_TYPE event_type);
int get_quarter_from_timer(ALLEGRO_TIMER* timer);
bool check_collision(Coordinate* c, float x1, float x2, float y1, float y2);
void generate_random_falling_object(Falling_Object* obj);
void play_audio(Audio* audio, bool loop);
void stop_audio(Audio* audio);
void set_audio(Audio* audio, float volume, float pan, float speed);
int calculate_seconds_left(time_t start_time, int duration_in_seconds);
void set_rectangle(Rectangle* r, float x1, float x2, float y1, float y2);
void set_obstacle(Obstacle* obstacle, float x, float y, int width, int height);
void set_animal(Animal* a, float initial_x, float initial_y, int width, int height, int speed, Rectangle bounds);
void set_selectable_object(Selectable_Object* obj, float x, float y, int width, int height, bool correct);
void set_wanted_object(Wanted_Object* w, float x, float y, int width, int height);

#endif
