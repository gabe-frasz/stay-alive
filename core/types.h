#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <stdbool.h>

#define CHAR_SPRITES_LENGTH 3

typedef struct {
    ALLEGRO_BITMAP* front[CHAR_SPRITES_LENGTH]; // o index 0 é o sprite do personagem parado,
    ALLEGRO_BITMAP* back[CHAR_SPRITES_LENGTH];  // os demais são dele em movimento
    ALLEGRO_BITMAP* left[CHAR_SPRITES_LENGTH];
    ALLEGRO_BITMAP* right[CHAR_SPRITES_LENGTH];
    ALLEGRO_BITMAP* current;
} Character_Sprites;

typedef struct {
    ALLEGRO_BITMAP* map;
    ALLEGRO_BITMAP* menu;
    ALLEGRO_BITMAP* end_game;
    ALLEGRO_BITMAP* game_over;
    ALLEGRO_BITMAP* play_btn;
    ALLEGRO_BITMAP* menu_btn;
    Character_Sprites char_sprites;
    ALLEGRO_BITMAP* heart_empty;
    ALLEGRO_BITMAP* heart_filled;
    ALLEGRO_BITMAP* hunger_empty;
    ALLEGRO_BITMAP* hunger_filled;
} Images;

typedef struct {
    float x, y;
} Coordinate;

typedef struct {
    float x1, x2, y1, y2;
} Challenge_Area;

enum Game_State {
    MENU,
    OPEN_MAP,
    CHALLENGE,
    GAME_OVER
};

typedef struct {
    ALLEGRO_TIMER* timer;
    ALLEGRO_EVENT_QUEUE* queue;
    ALLEGRO_DISPLAY* disp;
    ALLEGRO_FONT* font;
    ALLEGRO_EVENT event;
    Images imgs;
    Coordinate player, map;
    Challenge_Area challenges_areas[5];
    int challenge_index, life_counter, hunger_counter;
    enum Game_State state;
    bool redraw, done, has_user_lost;
} Context;
