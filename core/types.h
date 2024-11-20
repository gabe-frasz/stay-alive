#ifndef TYPES_H
#define TYPES_H

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_video.h>
#include <stdbool.h>

#define SPRITES_LENGTH 3
#define PLACEABLE_OBJECTS_LENGTH 4
#define PLACEABLE_POSITIONS_LENGTH 8
#define SELECTABLE_OBJECTS_LENGTH_C2 7
#define SELECTABLE_OBJECTS_LENGTH_C5 8
#define FALLING_OBJECTS_LENGTH 16
#define WANTED_OBJECTS_LENGTH 5
#define OBSTACLES_LENGTH 70
#define SHALLOW_WATER_AREAS_LENGTH 6
#define ANIMALS_LENGTH 8 // 2 grupos de aves, 2 coelhos, 1 ovelha, bode, gato, cobra
#define TUTORIALS_LENGTH 16
#define RUB_SPRITES_LENGTH 4

enum Animal_Type {
    BIRD,
    CAT,
    SHEEP,
    SNAKE,
    RABBIT,
    GOAT,
    ANIMAL_TYPE_LENGTH
};

typedef struct {
    ALLEGRO_BITMAP* front[SPRITES_LENGTH];
    ALLEGRO_BITMAP* back[SPRITES_LENGTH];
    ALLEGRO_BITMAP* left[SPRITES_LENGTH];
    ALLEGRO_BITMAP* right[SPRITES_LENGTH];
    ALLEGRO_BITMAP* current;
} Sprites;

typedef struct {
    ALLEGRO_BITMAP* front;
    ALLEGRO_BITMAP* back;
    ALLEGRO_BITMAP* left;
    ALLEGRO_BITMAP* right;
} Simple_Sprites;

typedef struct {
    ALLEGRO_BITMAP* map;
    ALLEGRO_BITMAP* menu;
    ALLEGRO_BITMAP* end_game;
    ALLEGRO_BITMAP* game_over;
    ALLEGRO_BITMAP* challenges[5];
    ALLEGRO_BITMAP* c5_bonfire;
    ALLEGRO_BITMAP* play_btn;
    ALLEGRO_BITMAP* next_btn;
    ALLEGRO_BITMAP* menu_btn;
    ALLEGRO_BITMAP* mute_btn;
    ALLEGRO_BITMAP* unmute_btn;
    Sprites char_sprites;
    ALLEGRO_BITMAP* char_with_basket;
    Sprites char_sprites_half_water;
    Simple_Sprites char_sprites_underwater;
    Sprites animals[ANIMAL_TYPE_LENGTH];
    ALLEGRO_BITMAP* medicinal_plants[WANTED_OBJECTS_LENGTH];
    ALLEGRO_BITMAP* heart_empty;
    ALLEGRO_BITMAP* heart_filled;
    ALLEGRO_BITMAP* hunger_empty;
    ALLEGRO_BITMAP* hunger_filled;
    ALLEGRO_BITMAP* water_bubble;
    ALLEGRO_BITMAP* snake_alert;
    ALLEGRO_BITMAP* c1_placeable_objects[PLACEABLE_OBJECTS_LENGTH];
    ALLEGRO_BITMAP* c2_selectable_objects[SELECTABLE_OBJECTS_LENGTH_C2];
    ALLEGRO_BITMAP* c5_selectable_objects[SELECTABLE_OBJECTS_LENGTH_C5];
    ALLEGRO_BITMAP* apple;
    ALLEGRO_BITMAP* mushroom;
    ALLEGRO_BITMAP* rub_sprites[RUB_SPRITES_LENGTH];
    ALLEGRO_BITMAP* current_video_frame;
} Images;

typedef struct {
    ALLEGRO_SAMPLE* sample;
    ALLEGRO_SAMPLE_ID id;
    float volume, pan, speed;
    bool is_playing;
} Audio;

typedef struct {
    Audio footstep[2], water_footstep[2];
    Audio typing, challenges[5];
    Audio hurting, panting, water_bubbles;
} Sounds;

typedef struct {
    ALLEGRO_VIDEO* tutorials[TUTORIALS_LENGTH];
    ALLEGRO_VIDEO* c2_distillation;
    ALLEGRO_VIDEO* rescue;
} Videos;

enum Game_State {
    MENU,
    OPEN_MAP,
    CHALLENGE,
    GAME_OVER
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
    ALLEGRO_BITMAP* current_sprite;
    void (*move)(struct Animal* self);
    void (*sort_destination)(struct Animal* self);
} Animal;

typedef struct {
    Coordinate position;
    int width, height;
} Obstacle;

typedef struct {
    int position_index, correct_position_index, width, height;
    ALLEGRO_BITMAP* img;
} Placeable_Object;

typedef struct {
    Placeable_Object placeable_objects[PLACEABLE_OBJECTS_LENGTH];
    Coordinate placeable_positions[PLACEABLE_POSITIONS_LENGTH];
    int selected_object_index;
} Challenge_1;

typedef struct {
    Coordinate position;
    int width, height;
    bool selected, correct;
} Selectable_Object;

typedef struct {
    Selectable_Object selectable_objects[SELECTABLE_OBJECTS_LENGTH_C2];
    bool is_distillation_playing;
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
    int width, height;
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
    int duration_in_seconds, action_bar, rub_sprite_index;
    bool bonfire_scene, correct_objects;
} Challenge_5;

typedef struct {
    int last_step_index;
    bool is_completed;
} Tutorial;

typedef struct {
    ALLEGRO_TIMER* timer;
    ALLEGRO_EVENT_QUEUE* queue;
    ALLEGRO_DISPLAY* disp;
    ALLEGRO_FONT* font;
    ALLEGRO_EVENT event;
    Images imgs;
    Sounds sounds;
    Videos videos;
    Coordinate player, map;
    Tutorial tutorials[5];
    Challenge_1 c1;
    Challenge_2 c2;
    Challenge_3 c3;
    Challenge_4 c4;
    Challenge_5 c5;
    Rectangle challenges_areas[5];
    Obstacle obstacles[OBSTACLES_LENGTH];
    Rectangle shallow_water_areas[SHALLOW_WATER_AREAS_LENGTH];
    Rectangle deep_water_area;
    Animal animals[ANIMALS_LENGTH];
    int challenge_index, tutorial_index, life_counter, hunger_counter, oxygen_counter;
    time_t oxygen_start_time;
    enum Game_State state;
    bool has_user_lost, is_user_hallucinated, is_snake_idle, is_snake_hunting, is_half_water, is_underwater; 
    bool redraw, done, sounds_muted;
} Context;

#endif
