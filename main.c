#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <stdbool.h>
#include <stdio.h>

#define CHAR_SPRITES_LENGTH 3

const int FPS = 30;
const int DISPLAY_WIDTH = 1280;
const int DISPLAY_HEIGHT = 720;
const int MAP_SIZE = 2336;
const int INITIAL_MAP_X = -320;
const int INITIAL_MAP_Y = -90;
const int PLAYER_WIDTH = 100;
const int PLAYER_HEIGHT = 125;
const int PLAYER_SPEED = 5;
const int BUTTON_WIDTH = 200;
const int BUTTON_HEIGHT = 50;
const int HEART_WIDTH = 220;

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
    ALLEGRO_BITMAP* hearts[2];
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

void init_context(Context* ctx);
void free_context(Context* ctx);
void move_camera(Context* ctx);
void change_character_sprite(Context* ctx);
void handle_movement(Context* ctx) {
    move_camera(ctx);
    change_character_sprite(ctx);
}
void finish_challenge(bool success, Context* ctx);
int get_event_index(ALLEGRO_EVENT_TYPE event_type);

int main() {
    Context ctx;
    init_context(&ctx);
    void (*actions[4][5])(Context*) = {
        {NULL, NULL, NULL, NULL, NULL}, // MENU
        {NULL, handle_movement, change_character_sprite, NULL, NULL}, // OPEN_MAP
        {NULL, NULL, NULL, NULL, NULL}, // CHALLENGE
        {NULL, NULL, NULL, NULL, NULL}  // GAME_OVER
    };

    al_start_timer(ctx.timer);
    while (1) {
        al_wait_for_event(ctx.queue, &ctx.event);

        if (ctx.event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) ctx.done = true;
        if (ctx.event.type == ALLEGRO_EVENT_TIMER) ctx.redraw = true;

        if (ctx.event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {
            if (ctx.state == MENU && ctx.event.mouse.x > 500 && ctx.event.mouse.y > 500 &&
                ctx.event.mouse.x < 500 + BUTTON_WIDTH && ctx.event.mouse.y < 500 + BUTTON_HEIGHT)
                ctx.state = OPEN_MAP;
        }
        if (ctx.event.type == ALLEGRO_EVENT_KEY_DOWN) {
            if (ctx.state == CHALLENGE && ctx.challenge_index <= 4) {
                if (ctx.event.keyboard.keycode == ALLEGRO_KEY_0) finish_challenge(false, &ctx);
                if (ctx.event.keyboard.keycode == ALLEGRO_KEY_1) finish_challenge(true, &ctx);
            }
            if (ctx.state == OPEN_MAP && ctx.event.keyboard.keycode == ALLEGRO_KEY_N) ctx.state = CHALLENGE;
        }

        int event_index = get_event_index(ctx.event.type);
        if (actions[ctx.state][event_index]) actions[ctx.state][event_index](&ctx);

        if (ctx.done) break;

        if (ctx.redraw && al_is_event_queue_empty(ctx.queue)) {
            switch (ctx.state) {
            case MENU:
                al_clear_to_color(al_map_rgb(0, 0, 0));
                al_draw_text(ctx.font, al_map_rgb(255, 255, 255), 500, 200, 0, "Stay Alive");
                al_draw_filled_rectangle(500, 500, 500 + BUTTON_WIDTH, 500 + BUTTON_HEIGHT, al_map_rgb(255, 0, 0));
                al_draw_text(ctx.font, al_map_rgb(255, 255, 255), 500, 500, 0, "Jogar");
                break;
            case OPEN_MAP:
                al_clear_to_color(al_map_rgb(0, 0, 0));
                al_draw_bitmap(ctx.imgs.map, ctx.map.x, ctx.map.y, 0);
                al_draw_bitmap(ctx.imgs.char_sprites.current, ctx.player.x, ctx.player.y, 0);
                for (int i = 2; i >= 0; i--) {
                    if (ctx.life_counter <= i) continue;
                    al_draw_bitmap(ctx.imgs.hearts[0], 5 + i * HEART_WIDTH, 5, 0);
                }
                break;
            case CHALLENGE:
                if (ctx.challenge_index == 0) {
                    al_clear_to_color(al_map_rgb(0, 0, 0));
                    al_draw_text(ctx.font, al_map_rgb(255, 255, 255), 0, 0, 0, "Desafio 1");
                }
                if (ctx.challenge_index == 1) {
                    al_clear_to_color(al_map_rgb(255, 0, 0));
                    al_draw_text(ctx.font, al_map_rgb(255, 255, 255), 0, 0, 0, "Desafio 2");
                }
                if (ctx.challenge_index == 2) {
                    al_clear_to_color(al_map_rgb(0, 255, 0));
                    al_draw_text(ctx.font, al_map_rgb(255, 255, 255), 0, 0, 0, "Desafio 3");
                }
                if (ctx.challenge_index == 3) {
                    al_clear_to_color(al_map_rgb(0, 0, 255));
                    al_draw_text(ctx.font, al_map_rgb(255, 255, 255), 0, 0, 0, "Desafio 4");
                }
                if (ctx.challenge_index == 4) {
                    al_clear_to_color(al_map_rgb(100, 100, 100));
                    al_draw_text(ctx.font, al_map_rgb(255, 255, 255), 0, 0, 0, "Desafio 5");
                }
                char msg[10] = "";
                //sprintf(msg, "Desafio %d", ctx.challenge_index + 1);
                //al_draw_text(ctx.font, al_map_rgb(255, 255, 255), 0, 0, 0, msg);
                break;
            case GAME_OVER:
                al_clear_to_color(al_map_rgb(0, 0, 0));
                al_draw_text(ctx.font, al_map_rgb(255, 255, 255), 0, 0, 0, "Fim de jogo");
                break;
            }

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
    imgs->map = al_load_bitmap("images/map.png");
    must_init(imgs->map, "map image");
    imgs->char_sprites.front[0] = al_load_bitmap("images/parado_frente.png");
    must_init(imgs->char_sprites.front[0], "char front image");
    imgs->char_sprites.front[1] = al_load_bitmap("images/andando_frente1.png");
    must_init(imgs->char_sprites.front[1], "char walking 1 front image");
    imgs->char_sprites.front[2] = al_load_bitmap("images/andando_frente2.png");
    must_init(imgs->char_sprites.front[2], "char walking 2 front image");
    imgs->char_sprites.back[0] = al_load_bitmap("images/parado_tras.png");
    must_init(imgs->char_sprites.back[0], "char back image");
    imgs->char_sprites.back[1] = al_load_bitmap("images/andando_tras1.png");
    must_init(imgs->char_sprites.back[1], "char walking 1 back image");
    imgs->char_sprites.back[2] = al_load_bitmap("images/andando_tras2.png");
    must_init(imgs->char_sprites.back[2], "char walking 2 back image");
    imgs->char_sprites.left[0] = al_load_bitmap("images/parado_esquerda.png");
    must_init(imgs->char_sprites.left[0], "char left image");
    imgs->char_sprites.left[1] = al_load_bitmap("images/andando_esquerda1.png");
    must_init(imgs->char_sprites.left[1], "char walking 1 left image");
    imgs->char_sprites.left[2] = al_load_bitmap("images/andando_esquerda2.png");
    must_init(imgs->char_sprites.left[2], "char walking 2 left image");
    imgs->char_sprites.right[0] = al_load_bitmap("images/parado_direita.png");
    must_init(imgs->char_sprites.right[0], "char right image");
    imgs->char_sprites.right[1] = al_load_bitmap("images/andando_direita1.png");
    must_init(imgs->char_sprites.right[1], "char walking 1 right image");
    imgs->char_sprites.right[2] = al_load_bitmap("images/andando_direita2.png");
    must_init(imgs->char_sprites.right[2], "char walking 2 right image");
    imgs->hearts[0] = al_load_bitmap("images/heart.png");
    must_init(imgs->hearts[0], "heart image");
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

    ctx->player.x = DISPLAY_WIDTH/2.0 - PLAYER_WIDTH/2;
    ctx->player.y = DISPLAY_HEIGHT/2.0 - PLAYER_HEIGHT/2;
    ctx->map.x = INITIAL_MAP_X;
    ctx->map.y = INITIAL_MAP_Y;

    ctx->challenge_index = 0; // 0 até 4
    ctx->life_counter = 3; // 3 até 0
    ctx->hunger_counter = 3; // 3 até 0
    ctx->state = MENU;

    ctx->redraw = true;
    ctx->done = false;
}

void free_context(Context* ctx) {
    al_destroy_bitmap(ctx->imgs.map);
    al_destroy_bitmap(ctx->imgs.hearts[0]);
    al_destroy_bitmap(ctx->imgs.hearts[1]);

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

void move_camera(Context* ctx) {
    bool is_player_y_centered = ctx->player.y == (DISPLAY_HEIGHT/2.0 - PLAYER_HEIGHT/2);
    bool is_player_x_centered = ctx->player.x == (DISPLAY_WIDTH/2.0 - PLAYER_WIDTH/2);

    switch (ctx->event.keyboard.keycode) {
    case ALLEGRO_KEY_UP:
    case ALLEGRO_KEY_W:
        if (ctx->map.y < 0 && is_player_y_centered) ctx->map.y += PLAYER_SPEED;
        else if (ctx->player.y >= ctx->map.y) ctx->player.y -= PLAYER_SPEED;
        break;
    case ALLEGRO_KEY_DOWN:
    case ALLEGRO_KEY_S:
        if (ctx->map.y + MAP_SIZE > DISPLAY_HEIGHT && is_player_y_centered) ctx->map.y -= PLAYER_SPEED;
        else if (ctx->player.y + PLAYER_HEIGHT <= ctx->map.y + MAP_SIZE) ctx->player.y += PLAYER_SPEED;
        break;
    case ALLEGRO_KEY_LEFT:
    case ALLEGRO_KEY_A:
        if (ctx->map.x < 0 && is_player_x_centered) ctx->map.x += PLAYER_SPEED;
        else if (ctx->player.x >= ctx->map.x) ctx->player.x -= PLAYER_SPEED;
        break;
    case ALLEGRO_KEY_RIGHT:
    case ALLEGRO_KEY_D:
        if (ctx->map.x + MAP_SIZE > DISPLAY_WIDTH && is_player_x_centered) ctx->map.x -= PLAYER_SPEED;
        else if (ctx->player.x + PLAYER_WIDTH <= ctx->map.x + MAP_SIZE) ctx->player.x += PLAYER_SPEED;
        break;
    }
}

void change_character_sprite(Context* ctx) {
    // Calcula o frame atual do jogo (0-29)
    float cyclic_timer = al_get_timer_count(ctx->timer) % FPS;

    // Divide o timer em quatro partes
    bool is_one_quarter = cyclic_timer >= 0 && cyclic_timer <= 7.5;
    bool is_two_quarters = cyclic_timer > 7.5 && cyclic_timer <= 15;
    bool is_three_quarters = cyclic_timer > 15 && cyclic_timer <= 22.5;
    bool is_four_quarters = cyclic_timer > 22.5 && cyclic_timer <= 30;

    bool is_player_standing = ctx->event.type == ALLEGRO_EVENT_KEY_UP;

    ALLEGRO_BITMAP* current = ctx->imgs.char_sprites.current;
    switch (ctx->event.keyboard.keycode) {
    case ALLEGRO_KEY_UP:
    case ALLEGRO_KEY_W:
        if (is_two_quarters) current = ctx->imgs.char_sprites.back[1];
        if (is_four_quarters) current = ctx->imgs.char_sprites.back[2];
        if (is_one_quarter || is_three_quarters || is_player_standing) current = ctx->imgs.char_sprites.back[0];
        break;
    case ALLEGRO_KEY_DOWN:
    case ALLEGRO_KEY_S:
        if (is_two_quarters) current = ctx->imgs.char_sprites.front[1];
        if (is_four_quarters) current = ctx->imgs.char_sprites.front[2];
        if (is_one_quarter || is_three_quarters || is_player_standing) current = ctx->imgs.char_sprites.front[0];
        break;
    case ALLEGRO_KEY_LEFT:
    case ALLEGRO_KEY_A:
        if (is_two_quarters) current = ctx->imgs.char_sprites.left[1];
        if (is_four_quarters) current = ctx->imgs.char_sprites.left[2];
        if (is_one_quarter || is_three_quarters || is_player_standing) current = ctx->imgs.char_sprites.left[0];
        break;
    case ALLEGRO_KEY_RIGHT:
    case ALLEGRO_KEY_D:
        if (is_two_quarters) current = ctx->imgs.char_sprites.right[1];
        if (is_four_quarters) current = ctx->imgs.char_sprites.right[2];
        if (is_one_quarter || is_three_quarters || is_player_standing) current = ctx->imgs.char_sprites.right[0];
        break;
    } 
    ctx->imgs.char_sprites.current = current;
}

void finish_challenge(bool success, Context* ctx) {
    if (!success) {
        ctx->life_counter--;
    }

    if (ctx->hunger_counter == 0) {
        ctx->life_counter--;
    }

    if (ctx->life_counter <= 0) {
        ctx->state = GAME_OVER;
        return;
    }

    bool player_got_food = success && (ctx->challenge_index == 0 || ctx->challenge_index == 2);
    if (player_got_food) {
      ctx->hunger_counter = 3;
    } else if (ctx->hunger_counter > 0) {
        ctx->hunger_counter--;
    }

    if (ctx->challenge_index <= 3) {
        ctx->challenge_index++;
    }

    ctx->state = OPEN_MAP;
    printf("life: %d; hunger: %d; c index: %d\n", ctx->life_counter, ctx->hunger_counter, ctx->challenge_index);
}

int get_event_index(ALLEGRO_EVENT_TYPE event_type) {
    int index = 0;

    switch (event_type) {
    case ALLEGRO_EVENT_TIMER:
        index = 0;
        break;
    case ALLEGRO_EVENT_KEY_CHAR:
        index = 1;
        break;
    case ALLEGRO_EVENT_KEY_UP:
        index = 2;
        break;
    case ALLEGRO_EVENT_KEY_DOWN:
        index = 3;
        break;
    case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
        index = 4;
        break;
    }
    
    return index;
}
