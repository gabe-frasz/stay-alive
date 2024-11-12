#ifndef TYPES_H
#define TYPES_H

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_audio.h>
#include <stdbool.h>

#define SPRITES_LENGTH 3
#define PLACEABLE_OBJECTS_LENGTH 5
#define PLACEABLE_POSITIONS_LENGTH 10
#define SELECTABLE_OBJECTS_LENGTH_C2 7
#define SELECTABLE_OBJECTS_LENGTH_C5 10
#define FALLING_OBJECTS_LENGTH 16
#define WANTED_OBJECTS_LENGTH 4
#define OBSTACLES_LENGTH 98
#define ANIMALS_LENGTH 8 // 2 grupos de aves, 2 coelhos, 1 ovelha, bode, gato, cobra

typedef struct {
    ALLEGRO_BITMAP* front[SPRITES_LENGTH];
    ALLEGRO_BITMAP* back[SPRITES_LENGTH];
    ALLEGRO_BITMAP* left[SPRITES_LENGTH];
    ALLEGRO_BITMAP* right[SPRITES_LENGTH];
    ALLEGRO_BITMAP* current;
} Sprites;

typedef struct {
    ALLEGRO_BITMAP* map;
    ALLEGRO_BITMAP* menu;
    ALLEGRO_BITMAP* end_game;
    ALLEGRO_BITMAP* game_over;
    ALLEGRO_BITMAP* challenges[5];
    ALLEGRO_BITMAP* play_btn;
    ALLEGRO_BITMAP* menu_btn;
    Sprites char_sprites;
    ALLEGRO_BITMAP* char_with_basket;
    Sprites bird_sprites;
    Sprites rabbit_sprites;
    Sprites goat_sprites;
    Sprites sheep_sprites;
    Sprites cat_sprites;
    Sprites snake_sprites;
    ALLEGRO_BITMAP* heart_empty;
    ALLEGRO_BITMAP* heart_filled;
    ALLEGRO_BITMAP* hunger_empty;
    ALLEGRO_BITMAP* hunger_filled;
} Images;

typedef struct {
    ALLEGRO_SAMPLE* footstep[2];
} Sounds;

enum Game_State {
    MENU,
    OPEN_MAP,
    CHALLENGE,
    GAME_OVER
};

enum Animal_Type {
    BIRD,
    CAT,
    SHEEP,
    SNAKE,
    RABBIT,
    GOAT
};

typedef struct {
    float x, y;
} Coordinate;

typedef struct {
  float x1, x2, y1, y2;
} Rectangle;

typedef struct Animal {
    enum Animal_Type type;
    Coordinate position, destination;
    Rectangle bounds;
    int width, height, speed, birds_count;
    bool is_moving;
    void (*move)(struct Animal* self);
    void (*sort_destination)(struct Animal* self);
} Animal;

typedef struct {
    Coordinate position;
    int width, height;
} Obstacle;

typedef struct {
    int width, height, position_index, correct_position_index;
} Placeable_Object;

typedef struct {
    Placeable_Object placeable_objects[PLACEABLE_OBJECTS_LENGTH];
    Coordinate placeable_positions[PLACEABLE_POSITIONS_LENGTH];
    int selected_object_index;
} Challenge_1;

typedef struct {
    Coordinate position;
    bool selected, correct;
} Selectable_Object;

typedef struct {
    Selectable_Object selectable_objects[SELECTABLE_OBJECTS_LENGTH_C2];
} Challenge_2;

typedef struct {
    Coordinate position;
    int id; // 0 = maçã, 1 = cogumelo
    float speed;
} Falling_Object;

typedef struct {
    Coordinate player_position;
    Falling_Object falling_objects[FALLING_OBJECTS_LENGTH];
    int apples_counter, mushrooms_counter;
} Challenge_3;

typedef struct {
    Coordinate position;
    bool selected;
} Wanted_Object;

typedef struct {
    Wanted_Object wanted_objects[WANTED_OBJECTS_LENGTH];
    Wanted_Object fake_wanted_objects[WANTED_OBJECTS_LENGTH];
    time_t start_time;
    int duration_in_seconds;
} Challenge_4;

typedef struct {
    Selectable_Object selectable_objects[SELECTABLE_OBJECTS_LENGTH_C5];
    time_t start_time;
    int duration_in_seconds;
} Challenge_5;

typedef struct {
    ALLEGRO_TIMER* timer;
    ALLEGRO_EVENT_QUEUE* queue;
    ALLEGRO_DISPLAY* disp;
    ALLEGRO_FONT* font;
    ALLEGRO_EVENT event;
    Images imgs;
    Sounds sounds;
    Coordinate player, map;
    Challenge_1 c1;
    Challenge_2 c2;
    Challenge_3 c3;
    Challenge_4 c4;
    Challenge_5 c5;
    Rectangle challenges_areas[5];
    Obstacle obstacles[OBSTACLES_LENGTH];
    Animal animals[ANIMALS_LENGTH];
    int challenge_index, life_counter, hunger_counter;
    enum Game_State state;
    bool redraw, done, has_user_lost, is_user_hallucinated;
} Context;

#endif
