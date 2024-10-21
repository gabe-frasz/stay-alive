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
            draw_context(&ctx);
            al_flip_display();
            ctx.redraw = false;
        }
    }

    free_context(&ctx);

    return 0;
}
