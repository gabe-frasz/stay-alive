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
    Character_Sprites char_sprites;
    ALLEGRO_BITMAP* heart_empty;
    ALLEGRO_BITMAP* heart_filled;
    ALLEGRO_BITMAP* hunger_empty;
    ALLEGRO_BITMAP* hunger_filled;
} Images;

typedef struct {
    float x, y;
} Coordinate;

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
    int challenge_index, life_counter, hunger_counter;
    enum Game_State state;
    bool redraw, done;
} Context;
