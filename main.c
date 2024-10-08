#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/display.h>
#include <stdbool.h>
#include <stdio.h>

#define CHAR_SPRITES_LENGTH 3

const int FPS = 30;
const int DISPLAY_WIDTH = 1280;
const int DISPLAY_HEIGHT = 720;
const int MAP_SIZE = 2250;
const int PLAYER_WIDTH = 100;
const int PLAYER_HEIGHT = 125;
const int PLAYER_SPEED = 5;

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
} Images;

typedef struct {
    ALLEGRO_TIMER* timer;
    ALLEGRO_EVENT_QUEUE* queue;
    ALLEGRO_DISPLAY* disp;
    ALLEGRO_FONT* font;
    ALLEGRO_EVENT event;
    Images imgs;
    float player_x, player_y, map_x, map_y;
    bool redraw;
    int challenge_counter, life_counter, hunger_counter;
} Context;

void init_context(Context* ctx);
void free_context(Context* ctx);
void handle_camera_movement(ALLEGRO_EVENT* event, float* player_x, float* player_y, float* map_x, float* map_y);
void handle_character_sprite_change(ALLEGRO_EVENT* event, ALLEGRO_TIMER* timer, Images* imgs);

int main() {
    Context ctx;
    init_context(&ctx);

    al_start_timer(ctx.timer);
    while (1) {
        al_wait_for_event(ctx.queue, &ctx.event);

        switch (ctx.event.type) {
        case ALLEGRO_EVENT_TIMER:
              ctx.redraw = true;
            break;
        case ALLEGRO_EVENT_KEY_CHAR:
            handle_camera_movement(&ctx.event, &ctx.player_x, &ctx.player_y, &ctx.map_x, &ctx.map_y);
            handle_character_sprite_change(&ctx.event, ctx.timer, &ctx.imgs); 
            break;
        case ALLEGRO_EVENT_KEY_UP:
            handle_character_sprite_change(&ctx.event, ctx.timer, &ctx.imgs);
            break;
        }

        if (ctx.event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) break;

        if (ctx.redraw && al_is_event_queue_empty(ctx.queue)) {
            al_clear_to_color(al_map_rgb(0, 0, 0));
            al_draw_bitmap(ctx.imgs.map, ctx.map_x, ctx.map_y, 0);
            al_draw_bitmap(ctx.imgs.char_sprites.current, ctx.player_x, ctx.player_y, 0);

            al_flip_display();
            ctx.redraw = false;
        }
    }

    free_context(&ctx);

    return 0;
}

void must_init(bool test, char* description) {
    if (!test) {
        printf("Could not initialize %s.\n", description);
        exit(1);
    }
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

void init_context(Context* ctx) {
    must_init(al_init(), "allegro");
    must_init(al_init_primitives_addon(), "primitives");
    must_init(al_install_keyboard(), "keyboard");
    must_init(al_install_mouse(), "mouse");
    must_init(al_init_image_addon(), "image");

    ctx->timer = al_create_timer(1.0 / FPS);
    must_init(ctx->timer, "timer");
    ctx->queue = al_create_event_queue();
    must_init(ctx->queue, "event queue");
    ctx->disp = al_create_display(DISPLAY_WIDTH, DISPLAY_HEIGHT);
    must_init(ctx->disp, "display");
    ctx->font = al_create_builtin_font();
    must_init(ctx->font, "font");

    al_set_window_title(ctx->disp, "Stay Alive");

    al_register_event_source(ctx->queue, al_get_keyboard_event_source());
    al_register_event_source(ctx->queue, al_get_display_event_source(ctx->disp));
    al_register_event_source(ctx->queue, al_get_timer_event_source(ctx->timer));
    al_register_event_source(ctx->queue, al_get_mouse_event_source());

    load_images(&ctx->imgs);
    ctx->imgs.char_sprites.current = ctx->imgs.char_sprites.front[0];

    ctx->player_x = DISPLAY_WIDTH/2.0 - PLAYER_WIDTH/2;
    ctx->player_y = DISPLAY_HEIGHT/2.0 - PLAYER_HEIGHT/2;
    ctx->map_x = -850;
    ctx->map_y = -1225;
    ctx->redraw = true;
    ctx->challenge_counter = 0;
    ctx->life_counter = 3;
    ctx->hunger_counter = 3;
}

void free_context(Context* ctx) {
    al_destroy_bitmap(ctx->imgs.map);

    for (int i = 0; i < CHAR_SPRITES_LENGTH; i++) {
        al_destroy_bitmap(ctx->imgs.char_sprites.front[i]);
        al_destroy_bitmap(ctx->imgs.char_sprites.back[i]);
        al_destroy_bitmap(ctx->imgs.char_sprites.left[i]);
        al_destroy_bitmap(ctx->imgs.char_sprites.right[i]);
    }

    al_destroy_font(ctx->font);
    al_destroy_display(ctx->disp);
    al_destroy_timer(ctx->timer);
    al_destroy_event_queue(ctx->queue);
    al_uninstall_keyboard();
    al_uninstall_mouse();
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
