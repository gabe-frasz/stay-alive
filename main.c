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
const int MAP_SIZE = 2250;
const int PLAYER_WIDTH = 100;
const int PLAYER_HEIGHT = 125;
const int PLAYER_SPEED = 5;
const int BUTTON_WIDTH = 200;
const int BUTTON_HEIGHT = 50;

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
    float x, y;
} Coordinate;

enum Game_State {
    MENU,
    OPEN_MAP,
    CHALLENGE
};

typedef struct {
    ALLEGRO_TIMER* timer;
    ALLEGRO_EVENT_QUEUE* queue;
    ALLEGRO_DISPLAY* disp;
    ALLEGRO_FONT* font;
    ALLEGRO_EVENT event;
    Images imgs;
    Coordinate player, map;
    float challenges_area[5][2];
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

int main() {
    Context ctx;
    init_context(&ctx);

    al_start_timer(ctx.timer);
    while (1) {
        al_wait_for_event(ctx.queue, &ctx.event);

        switch (ctx.event.type) {
        case ALLEGRO_EVENT_DISPLAY_CLOSE:
            ctx.done = true;
            break;
        case ALLEGRO_EVENT_TIMER:
            if (ctx.state == OPEN_MAP) {
                if (ctx.player.y <= 0) {
                    if (ctx.player.x >= ctx.challenges_area[ctx.challenge_index][0] &&
                        ctx.player.x <= ctx.challenges_area[ctx.challenge_index][1])
                        ctx.state = CHALLENGE;
                }
            }
            ctx.redraw = true;
            break;
        case ALLEGRO_EVENT_KEY_CHAR:
            handle_movement(&ctx);
            break;
        case ALLEGRO_EVENT_KEY_UP:
            change_character_sprite(&ctx);
            break;
        case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
            if (ctx.state == MENU) {
                if (ctx.event.mouse.x > 500 && ctx.event.mouse.y > 500 &&
                    ctx.event.mouse.x < 500 + BUTTON_WIDTH && ctx.event.mouse.y < 500 + BUTTON_HEIGHT)
                    ctx.state = OPEN_MAP;
            }
            break;
        case ALLEGRO_EVENT_KEY_DOWN:
            if (ctx.state == CHALLENGE) {
                if (ctx.event.keyboard.keycode == ALLEGRO_KEY_0) {
                    ctx.life_counter--;
                    ctx.hunger_counter--;
                    
                    ctx.imgs.char_sprites.current = ctx.imgs.char_sprites.front[0];
                    ctx.player.y += 50;

                    ctx.challenge_index++;
                    ctx.state = OPEN_MAP;
                }
                if (ctx.event.keyboard.keycode == ALLEGRO_KEY_1) {
                    ctx.challenge_index++;
                    ctx.state = OPEN_MAP;
                }
            }
            if (ctx.event.keyboard.keycode == ALLEGRO_KEY_N)
                ctx.state = CHALLENGE;
            break;
        }
        // if (actions[ctx.state][event]) actions[ctx.state][event](&ctx);

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
                break;
            case CHALLENGE:
                if (ctx.challenge_index == 0)
                    al_clear_to_color(al_map_rgb(0, 0, 0));
                if (ctx.challenge_index == 1)
                    al_clear_to_color(al_map_rgb(255, 0, 0));
                if (ctx.challenge_index == 2)
                    al_clear_to_color(al_map_rgb(0, 255, 0));
                if (ctx.challenge_index == 3)
                    al_clear_to_color(al_map_rgb(0, 0, 255));
                if (ctx.challenge_index == 4)
                    al_clear_to_color(al_map_rgb(100, 100, 100));
                
                char msg[10];
                sprintf(msg, "Desafio %d", ctx.challenge_index + 1);
                al_draw_text(ctx.font, al_map_rgb(255, 255, 255), 0, 0, 0, msg);
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
    imgs->map = al_load_bitmap("images/map.jpg");
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
    ctx->map.x = -850;
    ctx->map.y = -1225;

    for (int i = 0; i < 5; i++) {
        ctx->challenges_area[i][0] = DISPLAY_WIDTH/5.0 * i;
        ctx->challenges_area[i][1] = ctx->challenges_area[i][0] + DISPLAY_WIDTH/5.0;
    }

    ctx->challenge_index = 0; // 0 até 4
    ctx->life_counter = 3; // 3 até 0
    ctx->hunger_counter = 3; // 3 até 0
    ctx->state = MENU;

    ctx->redraw = true;
    ctx->done = false;
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
