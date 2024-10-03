#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <stdbool.h>
#include <stdio.h>

const int FPS = 30;
const int DISPLAY_WIDTH = 1280;
const int DISPLAY_HEIGHT = 720;

void must_init(bool test, char* description);

int main() {
    must_init(al_init(), "allegro");
    must_init(al_init_primitives_addon(), "primitives");
    must_init(al_install_keyboard(), "keyboard");
    must_init(al_install_mouse(), "mouse");
    must_init(al_init_image_addon(), "image");

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

    ALLEGRO_BITMAP* map_img = al_load_bitmap("images/map.jpg");
    must_init(map_img, "map image");
    ALLEGRO_BITMAP* char_front_img = al_load_bitmap("images/parado_frente.png");
    must_init(char_front_img, "character front image");
    ALLEGRO_BITMAP* char_walk1_front_img = al_load_bitmap("images/andando_frente1.png");
    must_init(char_walk1_front_img, "character walking 1 front image");
    ALLEGRO_BITMAP* char_walk2_front_img = al_load_bitmap("images/andando_frente2.png");
    must_init(char_walk2_front_img, "character walking 2 front image");
    ALLEGRO_BITMAP* char_back_img = al_load_bitmap("images/parado_tras.png");
    must_init(char_back_img, "character back image");
    ALLEGRO_BITMAP* char_walk1_back_img = al_load_bitmap("images/andando_tras1.png");
    must_init(char_walk1_back_img, "character walking 1 back image");
    ALLEGRO_BITMAP* char_walk2_back_img = al_load_bitmap("images/andando_tras2.png");
    must_init(char_walk2_back_img, "character walking 2 back image");
    ALLEGRO_BITMAP* char_left_img = al_load_bitmap("images/parado_esquerda.png");
    must_init(char_left_img, "character left image");
    ALLEGRO_BITMAP* char_walk1_left_img = al_load_bitmap("images/andando_esquerda1.png");
    must_init(char_walk1_left_img, "character walking 1 left image");
    ALLEGRO_BITMAP* char_walk2_left_img = al_load_bitmap("images/andando_esquerda2.png");
    must_init(char_walk2_left_img, "character walking 2 left image");
    ALLEGRO_BITMAP* char_right_img = al_load_bitmap("images/parado_direita.png");
    must_init(char_right_img, "character right image");
    ALLEGRO_BITMAP* char_walk1_right_img = al_load_bitmap("images/andando_direita1.png");
    must_init(char_walk1_right_img, "character walking 1 right image");
    ALLEGRO_BITMAP* char_walk2_right_img = al_load_bitmap("images/andando_direita2.png");
    must_init(char_walk2_right_img, "character walking 2 right image");
    ALLEGRO_BITMAP* character = char_front_img;

    bool done = false;
    bool redraw = true;
    ALLEGRO_EVENT event;

    float player_x = DISPLAY_WIDTH/2.0, player_y = DISPLAY_HEIGHT/2.0, map_x = 0, map_y = 0;
    float cycle_timer;

    al_start_timer(timer);
    while (1) {
        al_wait_for_event(queue, &event);

        switch (event.type) {
        case ALLEGRO_EVENT_TIMER:
              redraw = true;
            break;
        case ALLEGRO_EVENT_KEY_CHAR:
            cycle_timer = ((float)al_get_timer_count(timer)/FPS - al_get_timer_count(timer)/FPS) * FPS;
            
            switch (event.keyboard.keycode) {
            case ALLEGRO_KEY_UP:
                map_y += 5;
                if (cycle_timer >= 0 && cycle_timer <= 7.5 || cycle_timer >= 15 && cycle_timer <= 22.5) {
                    character = char_back_img;
                }
                if (cycle_timer > 7.5 && cycle_timer <= 15) {
                    character = char_walk1_back_img;
                }
                if (cycle_timer > 22.5 && cycle_timer <= 30) {
                    character = char_walk2_back_img;
                }
                break;
            case ALLEGRO_KEY_DOWN:
                map_y -= 5;
                if (cycle_timer >= 0 && cycle_timer <= 7.5 || cycle_timer >= 15 && cycle_timer <= 22.5) {
                    character = char_front_img;
                }
                if (cycle_timer > 7.5 && cycle_timer <= 15) {
                    character = char_walk1_front_img;
                }
                if (cycle_timer > 22.5 && cycle_timer <= 30) {
                    character = char_walk2_front_img;
                }
                break;
            case ALLEGRO_KEY_LEFT:
                map_x += 5;
                if (cycle_timer >= 0 && cycle_timer <= 7.5 || cycle_timer >= 15 && cycle_timer <= 22.5) {
                    character = char_left_img;
                }
                if (cycle_timer > 7.5 && cycle_timer <= 15) {
                    character = char_walk1_left_img;
                }
                if (cycle_timer > 22.5 && cycle_timer <= 30) {
                    character = char_walk2_left_img;
                }
                break;
            case ALLEGRO_KEY_RIGHT:
                map_x -= 5;
                if (cycle_timer >= 0 && cycle_timer <= 7.5 || cycle_timer >= 15 && cycle_timer <= 22.5) {
                    character = char_right_img;
                }
                if (cycle_timer > 7.5 && cycle_timer <= 15) {
                    character = char_walk1_right_img;
                }
                if (cycle_timer > 22.5 && cycle_timer <= 30) {
                    character = char_walk2_right_img;
                }
                break;
            }
            break;
        case ALLEGRO_EVENT_KEY_UP:
            switch (event.keyboard.keycode) {
            case ALLEGRO_KEY_UP:
                character = char_back_img;
                break;
            case ALLEGRO_KEY_DOWN:
                character = char_front_img;
                break;
            case ALLEGRO_KEY_LEFT:
                character = char_left_img;
                break;
            case ALLEGRO_KEY_RIGHT:
                character = char_right_img;
                break;
            }
            break;
        case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
            break;
        case ALLEGRO_EVENT_DISPLAY_CLOSE:
            done = true;
            break;
        }

        if (done)
            break;

        if (redraw && al_is_event_queue_empty(queue)) {
            al_clear_to_color(al_map_rgb(0, 0, 0));
            al_draw_bitmap(map_img, map_x, map_y, 0);
            al_draw_bitmap(character, player_x, player_y, 0);

            al_flip_display();
            redraw = false;
        }
    }
    al_destroy_bitmap(map_img);
    al_destroy_bitmap(char_front_img);
    al_destroy_bitmap(char_walk1_front_img);
    al_destroy_bitmap(char_walk2_front_img);
    al_destroy_bitmap(char_back_img);
    al_destroy_bitmap(char_walk1_back_img);
    al_destroy_bitmap(char_walk2_back_img);
    al_destroy_bitmap(char_left_img);
    al_destroy_bitmap(char_walk1_left_img);
    al_destroy_bitmap(char_walk2_left_img);
    al_destroy_bitmap(char_right_img);
    al_destroy_bitmap(char_walk1_right_img);
    al_destroy_bitmap(char_walk2_right_img);

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
