#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <stdbool.h>
#include <stdio.h>

const int FPS = 30;
const int DISPLAY_WIDTH = 1280;
const int DISPLAY_HEIGHT = 720;

void must_init(bool test, char* description);

typedef struct {
    float x, y, size, correct_x, correct_y, id;
    bool is_correct;
} item;

int main() {
    must_init(al_init(), "allegro");
    must_init(al_init_primitives_addon(), "primitives");
    must_init(al_install_keyboard(), "keyboard");
    must_init(al_install_mouse(), "mouse");

    ALLEGRO_TIMER* timer = al_create_timer(1.0 / FPS);
    must_init(timer, "timer");
    ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
    must_init(queue, "event queue");
    ALLEGRO_DISPLAY* disp = al_create_display(DISPLAY_WIDTH, DISPLAY_HEIGHT);
    must_init(disp, "display");
    ALLEGRO_FONT* font = al_create_builtin_font();
    must_init(font, "font");

    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_display_event_source(disp));
    al_register_event_source(queue, al_get_timer_event_source(timer));
    al_register_event_source(queue, al_get_mouse_event_source());

    bool done = false;
    bool redraw = true;
    ALLEGRO_EVENT event;

    float player_x = 100, player_y = 100, objective_x = 1100, objective_y = 600;
    bool is_inside_objective = false;
    char* msg = "";
    int bg_color[3] = { 0, 0, 0 }, text_color[3] = { 255, 255, 255 },
        game_challenge = 0;
    item items[4] = { {.x = 20,
                      .y = 650,
                      .size = 40,
                      .correct_x = 140,
                      .correct_y = 200,
                      .id = 1},
                     {.x = 100,
                      .y = 590,
                      .size = 90,
                      .correct_x = 20,
                      .correct_y = 150,
                      .id = 2},
                     {.x = 400,
                      .y = 570,
                      .size = 75,
                      .correct_x = 500,
                      .correct_y = 290,
                      .id = 3},
                     {.x = 600,
                      .y = 595,
                      .size = 120,
                      .correct_x = 800,
                      .correct_y = 150,
                      .id = 4} };
    int selected_item = 0;

    al_start_timer(timer);
    while (1) {
        al_wait_for_event(queue, &event);

        switch (event.type) {
        case ALLEGRO_EVENT_TIMER:
            if (game_challenge == 0) {
                if (player_x == objective_x && player_y == objective_y) {
                    is_inside_objective = true;
                    msg = "Aperte ENTER para continuar";
                }
                else {
                    is_inside_objective = false;
                    msg = "Mova o jogador para a área branca usando as setas";
                }
            }
            if (game_challenge == 1) {
                bg_color[0] = 255;
                bg_color[1] = 255;
                bg_color[2] = 255;
                text_color[0] = 0;
                text_color[1] = 0;
                text_color[2] = 0;

                msg = "Agora use o mouse para clicar nos objetos e posicioná-los "
                    "corretamente";

                for (int i = 0; i < 4; i++) {
                    if (!items[i].is_correct) {
                        break;
                    }

                    msg = "Parabéns! Você concluiu o desafio!";
                }
            }

            redraw = true;
            break;
        case ALLEGRO_EVENT_KEY_CHAR:
            if (event.keyboard.keycode == ALLEGRO_KEY_UP) {
                player_y -= 20;
            }
            if (event.keyboard.keycode == ALLEGRO_KEY_DOWN) {
                player_y += 20;
            }
            if (event.keyboard.keycode == ALLEGRO_KEY_LEFT) {
                player_x -= 20;
            }
            if (event.keyboard.keycode == ALLEGRO_KEY_RIGHT) {
                player_x += 20;
            }

            if (event.keyboard.keycode == ALLEGRO_KEY_ENTER) {
                if (is_inside_objective)
                    game_challenge = 1;
            }
            break;
        case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
            for (int i = 0; i < 4; i++) {
                if (event.mouse.x >= items[i].x &&
                    event.mouse.x <= items[i].x + items[i].size &&
                    event.mouse.y >= items[i].y &&
                    event.mouse.y <= items[i].y + items[i].size) {
                    selected_item = items[i].id;
                }

                if (event.mouse.x >= items[i].correct_x &&
                    event.mouse.x <= items[i].correct_x + items[i].size &&
                    event.mouse.y >= items[i].correct_y &&
                    event.mouse.y <= items[i].correct_y + items[i].size) {
                    if (selected_item == items[i].id) {
                        items[i].is_correct = true;
                    }
                }
            }
            break;
        case ALLEGRO_EVENT_DISPLAY_CLOSE:
            done = true;
            break;
        }

        if (done)
            break;

        if (redraw && al_is_event_queue_empty(queue)) {
            al_clear_to_color(al_map_rgb(bg_color[0], bg_color[1], bg_color[2]));
            al_draw_text(font,
                al_map_rgb(text_color[0], text_color[1], text_color[2]), 0,
                0, 0, msg);

            switch (game_challenge) {
            case 0:
                al_draw_filled_rectangle(objective_x, objective_y, objective_x + 100,
                    objective_y + 100,
                    al_map_rgb(255, 255, 255)); // objective
                al_draw_filled_rectangle(player_x, player_y, player_x + 100,
                    player_y + 100,
                    al_map_rgb(255, 0, 0)); // player
                break;
            case 1:
                for (int i = 0; i < 4; i++) {
                    if (items[i].is_correct) {
                        al_draw_filled_rectangle(items[i].correct_x, items[i].correct_y,
                            items[i].correct_x + items[i].size,
                            items[i].correct_y + items[i].size,
                            al_map_rgb(0, 0, 0));
                    }
                    else {
                        al_draw_filled_rectangle(items[i].correct_x, items[i].correct_y,
                            items[i].correct_x + items[i].size,
                            items[i].correct_y + items[i].size,
                            al_map_rgb(220, 220, 220));
                        al_draw_filled_rectangle(
                            items[i].x, items[i].y, items[i].x + items[i].size,
                            items[i].y + items[i].size, al_map_rgb(0, 0, 0));
                    }
                }
                break;
            }

            al_flip_display();

            redraw = false;
        }
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