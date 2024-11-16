#include <allegro5/allegro5.h>
#include <stdbool.h>
#include "core/actions.c"
#include "core/helpers.c"
#include "core/ctx-functions.c"

int main() {
    Context ctx;
    init_context(&ctx);

    al_start_timer(ctx.timer);
    while (1) {
        al_wait_for_event(ctx.queue, &ctx.event);

        if (ctx.event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) ctx.done = true;
        if (ctx.event.type == ALLEGRO_EVENT_TIMER) ctx.redraw = true;

        int event_index = get_event_index(ctx.event.type);
        if (event_index != -1 && actions[ctx.state][event_index]) actions[ctx.state][event_index](&ctx);

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
