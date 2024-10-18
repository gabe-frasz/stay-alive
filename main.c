#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include <stdbool.h>
#include "core/actions.c"

int main() {
    Context ctx;
    init_context(&ctx);

    al_start_timer(ctx.timer);
    while (1) {
        al_wait_for_event(ctx.queue, &ctx.event);

        if (ctx.event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) ctx.done = true;
        if (ctx.event.type == ALLEGRO_EVENT_TIMER) ctx.redraw = true;

        if (ctx.event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {
            Coordinate mouse = {ctx.event.mouse.x, ctx.event.mouse.y};
            bool is_collision = check_collision(&mouse, 500, 500 + BUTTON_WIDTH, 500, 500 + BUTTON_HEIGHT);
            if (ctx.state == MENU && is_collision) ctx.state = OPEN_MAP;
            if (ctx.state == GAME_OVER && is_collision) reset_context(&ctx);
        }
        if (ctx.event.type == ALLEGRO_EVENT_KEY_DOWN) {
            if (ctx.state == CHALLENGE) {
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
                    if (ctx.life_counter > i) al_draw_bitmap(ctx.imgs.heart_filled, 5 + i * HEART_WIDTH, 5, 0);
                    if (ctx.hunger_counter > i) al_draw_bitmap(ctx.imgs.hunger_filled, 5 + i * HUNGER_WIDTH, 300, 0);
                }
                break;
            case CHALLENGE:
                if (ctx.challenge_index == 0) al_clear_to_color(al_map_rgb(0, 0, 0));
                if (ctx.challenge_index == 1) al_clear_to_color(al_map_rgb(255, 0, 0));
                if (ctx.challenge_index == 2) al_clear_to_color(al_map_rgb(0, 255, 0));
                if (ctx.challenge_index == 3) al_clear_to_color(al_map_rgb(0, 0, 255));
                if (ctx.challenge_index == 4) al_clear_to_color(al_map_rgb(100, 100, 100));
                al_draw_textf(ctx.font, al_map_rgb(255, 255, 255), 0, 0, 0, "Desafio %d", ctx.challenge_index + 1);
                break;
            case GAME_OVER:
                al_clear_to_color(al_map_rgb(0, 0, 0));
                al_draw_text(ctx.font, al_map_rgb(255, 255, 255), 0, 0, 0, "Fim de jogo");
                al_draw_filled_rectangle(500, 500, 500 + BUTTON_WIDTH, 500 + BUTTON_HEIGHT, al_map_rgb(255, 0, 0));
                al_draw_text(ctx.font, al_map_rgb(255, 255, 255), 500, 500, 0, "Retornar ao menu");
                break;
            }

            al_flip_display();
            ctx.redraw = false;
        }
    }

    free_context(&ctx);

    return 0;
}
