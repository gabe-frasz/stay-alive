#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/display.h>
#include <stdbool.h>
#include <stdio.h>

const int FPS = 30;
const int DISPLAY_WIDTH = 1280;
const int DISPLAY_HEIGHT = 720;
const int MAP_SIZE = 2250;
const int PLAYER_WIDTH = 100;
const int PLAYER_HEIGHT = 125;
const int PLAYER_SPEED = 5;

typedef struct {
    ALLEGRO_BITMAP* front[3]; // o index 0 é o sprite do personagem parado, os demais são dele em movimento
    ALLEGRO_BITMAP* back[3];
    ALLEGRO_BITMAP* left[3];
    ALLEGRO_BITMAP* right[3];
    ALLEGRO_BITMAP* current;
} Character_Sprites;

typedef struct {
    ALLEGRO_BITMAP* map;
    Character_Sprites char_sprites;
} Images;

void must_init(bool test, char* description);
void init_game(ALLEGRO_TIMER** timer, ALLEGRO_EVENT_QUEUE** queue, ALLEGRO_DISPLAY** disp, ALLEGRO_FONT** font, Images* imgs);
void load_images(Images* imgs);
void handle_camera_movement(ALLEGRO_EVENT* event, float* player_x, float* player_y, float* map_x, float* map_y);
void handle_character_sprite_change(ALLEGRO_EVENT* event, ALLEGRO_TIMER* timer, Images* imgs);

int main() {
    ALLEGRO_TIMER* timer;
    ALLEGRO_EVENT_QUEUE* queue;
    ALLEGRO_DISPLAY* disp;
    ALLEGRO_FONT* font;
    Images imgs;

    init_game(&timer, &queue, &disp, &font, &imgs);

    bool redraw = true;
    ALLEGRO_EVENT event;

    float player_x = DISPLAY_WIDTH/2.0 - PLAYER_WIDTH/2, player_y = DISPLAY_HEIGHT/2.0 - PLAYER_HEIGHT/2, map_x = 0, map_y = 0;

    al_start_timer(timer);
    while (1) {
        al_wait_for_event(queue, &event);

        switch (event.type) {
        case ALLEGRO_EVENT_TIMER:
              redraw = true;
            break;
        case ALLEGRO_EVENT_KEY_CHAR:
            handle_camera_movement(&event, &player_x, &player_y, &map_x, &map_y);
            handle_character_sprite_change(&event, timer, &imgs); 
            break;
        case ALLEGRO_EVENT_KEY_UP:
            handle_character_sprite_change(&event, timer, &imgs);
            break;
        }

        if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) break;

        if (redraw && al_is_event_queue_empty(queue)) {
            al_clear_to_color(al_map_rgb(0, 0, 0));
            al_draw_bitmap(imgs.map, map_x, map_y, 0);
            al_draw_bitmap(imgs.char_sprites.current, player_x, player_y, 0);

            al_flip_display();
            redraw = false;
        }
    }

    al_destroy_bitmap(imgs.map);
    for (int i = 0; i < 3; i++) {
        al_destroy_bitmap(imgs.char_sprites.front[i]);
        al_destroy_bitmap(imgs.char_sprites.back[i]);
        al_destroy_bitmap(imgs.char_sprites.left[i]);
        al_destroy_bitmap(imgs.char_sprites.right[i]);
    }

    al_destroy_font(font);
    al_destroy_display(disp);
    al_destroy_timer(timer);
    al_destroy_event_queue(queue);
    al_uninstall_keyboard();
    al_uninstall_mouse();

    return 0;
}

void must_init(bool test, char* description) {
    if (!test) {
        printf("Could not initialize %s.\n", description);
        exit(1);
    }
}

void init_game(ALLEGRO_TIMER** timer, ALLEGRO_EVENT_QUEUE** queue, ALLEGRO_DISPLAY** disp, ALLEGRO_FONT** font, Images* imgs) {
    must_init(al_init(), "allegro");
    must_init(al_init_primitives_addon(), "primitives");
    must_init(al_install_keyboard(), "keyboard");
    must_init(al_install_mouse(), "mouse");
    must_init(al_init_image_addon(), "image");

    *timer = al_create_timer(1.0 / FPS);
    must_init(*timer, "timer");
    *queue = al_create_event_queue();
    must_init(*queue, "event queue");
    *disp = al_create_display(DISPLAY_WIDTH, DISPLAY_HEIGHT);
    must_init(*disp, "display");
    *font = al_create_builtin_font();
    must_init(*font, "font");

    al_set_window_title(*disp, "Stay Alive");

    al_register_event_source(*queue, al_get_keyboard_event_source());
    al_register_event_source(*queue, al_get_display_event_source(*disp));
    al_register_event_source(*queue, al_get_timer_event_source(*timer));
    al_register_event_source(*queue, al_get_mouse_event_source()); 

    load_images(imgs);
    imgs->char_sprites.current = imgs->char_sprites.front[0];
}

void load_images(Images* imgs) {
    imgs->map = al_load_bitmap("images/map.jpg");
    must_init(imgs->map, "map image");
    imgs->char_sprites.front[0] = al_load_bitmap("images/parado_frente.png");
    must_init(imgs->char_sprites.front[0], "imgs.char_sprites.current front image");
    imgs->char_sprites.front[1] = al_load_bitmap("images/andando_frente1.png");
    must_init(imgs->char_sprites.front[1], "imgs.char_sprites.current walking 1 front image");
    imgs->char_sprites.front[2] = al_load_bitmap("images/andando_frente2.png");
    must_init(imgs->char_sprites.front[2], "imgs.char_sprites.current walking 2 front image");
    imgs->char_sprites.back[0] = al_load_bitmap("images/parado_tras.png");
    must_init(imgs->char_sprites.back[0], "imgs.char_sprites.current back image");
    imgs->char_sprites.back[1] = al_load_bitmap("images/andando_tras1.png");
    must_init(imgs->char_sprites.back[1], "imgs.char_sprites.current walking 1 back image");
    imgs->char_sprites.back[2] = al_load_bitmap("images/andando_tras2.png");
    must_init(imgs->char_sprites.back[2], "imgs.char_sprites.current walking 2 back image");
    imgs->char_sprites.left[0] = al_load_bitmap("images/parado_esquerda.png");
    must_init(imgs->char_sprites.left[0], "imgs.char_sprites.current left image");
    imgs->char_sprites.left[1] = al_load_bitmap("images/andando_esquerda1.png");
    must_init(imgs->char_sprites.left[1], "imgs.char_sprites.current walking 1 left image");
    imgs->char_sprites.left[2] = al_load_bitmap("images/andando_esquerda2.png");
    must_init(imgs->char_sprites.left[2], "imgs.char_sprites.current walking 2 left image");
    imgs->char_sprites.right[0] = al_load_bitmap("images/parado_direita.png");
    must_init(imgs->char_sprites.right[0], "imgs.char_sprites.current right image");
    imgs->char_sprites.right[1] = al_load_bitmap("images/andando_direita1.png");
    must_init(imgs->char_sprites.right[1], "imgs.char_sprites.current walking 1 right image");
    imgs->char_sprites.right[2] = al_load_bitmap("images/andando_direita2.png");
    must_init(imgs->char_sprites.right[2], "imgs.char_sprites.current walking 2 right image");
}

void handle_camera_movement(ALLEGRO_EVENT* event, float* player_x, float* player_y, float* map_x, float* map_y) {
    bool is_player_y_centered = *player_y == (DISPLAY_HEIGHT/2.0 - PLAYER_HEIGHT/2);
    bool is_player_x_centered = *player_x == (DISPLAY_WIDTH/2.0 - PLAYER_WIDTH/2);

    switch (event->keyboard.keycode) {
    case ALLEGRO_KEY_UP:
        if (*map_y < 0 && is_player_y_centered) *map_y += PLAYER_SPEED;
        else if (*player_y >= *map_y) *player_y -= PLAYER_SPEED;
        break;
    case ALLEGRO_KEY_DOWN:
        if (*map_y + MAP_SIZE > DISPLAY_HEIGHT && is_player_y_centered) *map_y -= PLAYER_SPEED;
        else if (*player_y + PLAYER_HEIGHT <= *map_y + MAP_SIZE) *player_y += PLAYER_SPEED;
        break;
    case ALLEGRO_KEY_LEFT:
        if (*map_x < 0 && is_player_x_centered) *map_x += PLAYER_SPEED;
        else if (*player_x >= *map_x) *player_x -= PLAYER_SPEED;
        break;
    case ALLEGRO_KEY_RIGHT:
        if (*map_x + MAP_SIZE > DISPLAY_WIDTH && is_player_x_centered) *map_x -= PLAYER_SPEED;
        else if (*player_x + PLAYER_WIDTH <= *map_x + MAP_SIZE) *player_x += PLAYER_SPEED;
        break;
    }
}

void handle_character_sprite_change(ALLEGRO_EVENT* event, ALLEGRO_TIMER* timer, Images* imgs) {
    // Calcula o frame atual do jogo (0-29)
    float cyclic_timer = al_get_timer_count(timer) % FPS;

    // Divide o timer em quatro partes
    bool is_one_quarter = cyclic_timer >= 0 && cyclic_timer <= 7.5;
    bool is_two_quarters = cyclic_timer > 7.5 && cyclic_timer <= 15;
    bool is_three_quarters = cyclic_timer > 15 && cyclic_timer <= 22.5;
    bool is_four_quarters = cyclic_timer > 22.5 && cyclic_timer <= 30;

    bool is_player_standing = event->type == ALLEGRO_EVENT_KEY_UP;

    switch (event->keyboard.keycode) {
    case ALLEGRO_KEY_UP:
        if (is_two_quarters) imgs->char_sprites.current = imgs->char_sprites.back[1];
        if (is_four_quarters) imgs->char_sprites.current = imgs->char_sprites.back[2];
        if (is_one_quarter || is_three_quarters || is_player_standing) imgs->char_sprites.current = imgs->char_sprites.back[0];
        break;
    case ALLEGRO_KEY_DOWN:
        if (is_two_quarters) imgs->char_sprites.current = imgs->char_sprites.front[1];
        if (is_four_quarters) imgs->char_sprites.current = imgs->char_sprites.front[2];
        if (is_one_quarter || is_three_quarters || is_player_standing) imgs->char_sprites.current = imgs->char_sprites.front[0];
        break;
    case ALLEGRO_KEY_LEFT:
        if (is_two_quarters) imgs->char_sprites.current = imgs->char_sprites.left[1];
        if (is_four_quarters) imgs->char_sprites.current = imgs->char_sprites.left[2];
        if (is_one_quarter || is_three_quarters || is_player_standing) imgs->char_sprites.current = imgs->char_sprites.left[0];
        break;
    case ALLEGRO_KEY_RIGHT:
        if (is_two_quarters) imgs->char_sprites.current = imgs->char_sprites.right[1];
        if (is_four_quarters) imgs->char_sprites.current = imgs->char_sprites.right[2];
        if (is_one_quarter || is_three_quarters || is_player_standing) imgs->char_sprites.current = imgs->char_sprites.right[0];
        break;
    } 
}
