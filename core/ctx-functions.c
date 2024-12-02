#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_video.h>
#include <allegro5/bitmap_draw.h>
#include <allegro5/keycodes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "types.h"
#include "consts.h"
#include "helpers.h"

void set_context_to_default(Context* ctx) {
    ctx->imgs.char_sprites.current = ctx->imgs.char_sprites.front[0];
    ctx->player.x = DISPLAY_WIDTH/2.0 - PLAYER_WIDTH/2;
    ctx->player.y = DISPLAY_HEIGHT/2.0 - PLAYER_HEIGHT/2;
    ctx->map.x = INITIAL_MAP_X;
    ctx->map.y = INITIAL_MAP_Y;
    ctx->hallucination_angle = 0;
    ctx->animal_sound_interval = 7;

    ctx->imgs.current_video_frame = ctx->imgs.challenges[0];

    ctx->tutorials[0].last_step_index = 3;
    ctx->tutorials[1].last_step_index = 7;
    ctx->tutorials[2].last_step_index = 9;
    ctx->tutorials[3].last_step_index = 15;
    ctx->tutorials[4].last_step_index = 17;
    for (int i = 0; i < 5; i++) {
        ctx->tutorials[i].is_completed = false;
    }

    ctx->c1.selected_object_index = -1;
    for (int i = 0; i < PLACEABLE_OBJECTS_LENGTH; i++) {
        ctx->c1.placeable_objects[i].position_index = i * 2;
        ctx->c1.placeable_objects[i].correct_position_index = i * 2 + 1;
        ctx->c1.placeable_objects[i].img = ctx->imgs.c1_placeable_objects[i];
    }

    ctx->c2.is_distillation_playing = false;
    for (int i = 0; i < SELECTABLE_OBJECTS_LENGTH_C2; i++) {
        ctx->c2.selectable_objects[i].selected = false;
        ctx->c2.selectable_objects[i].correct = false;
        if (i < 5) ctx->c2.selectable_objects[i].correct = true;
    }

    ctx->c3.player_position.x = 490;
    ctx->c3.player_position.y = 600;
    ctx->c3.apples_counter = 0;
    ctx->c3.mushrooms_counter = 0;
    for (int i = 0; i < FALLING_OBJECTS_LENGTH; i++) {
        Falling_Object* obj = &ctx->c3.falling_objects[i];
        generate_random_falling_object(obj);
        int index = i;
        if (i >= 8) {
            index = i - 8;
            obj->position.y -= 600;
        }
        obj->position.x = (DISPLAY_WIDTH - 80.0) / 8 * index + 40;
    }

    ctx->c4.start_time = -1;
    for (int i = 0; i < WANTED_OBJECTS_LENGTH; i++) {
        ctx->c4.wanted_objects[i].selected = false;
        ctx->c4.fake_wanted_objects[i].selected = false;
    }

    ctx->c5.bonfire_scene = false;
    ctx->c5.correct_objects = false;
    ctx->c5.action_bar = DISPLAY_WIDTH;
    ctx->c5.rub_sprite_index = 0;
    ctx->c5.start_time = -1;
    for (int i = 0; i < SELECTABLE_OBJECTS_LENGTH_C5; i++) {
        ctx->c5.selectable_objects[i].selected = false;
    }

    ctx->has_user_lost = false;
    ctx->is_user_hallucinated = false;
    ctx->is_snake_idle = false;
    ctx->is_snake_hunting = false;
    ctx->is_half_water = false;
    ctx->is_underwater = false;
    ctx->sounds_muted = false;
    ctx->challenge_index = 0;
    ctx->tutorial_index = 0; 
    ctx->life_counter = 3;
    ctx->hunger_counter = 3;
    ctx->oxygen_counter = 3;
    ctx->oxygen_start_time = -1;
    ctx->state = MENU;
    ctx->redraw = true;
    ctx->done = false;

    ctx->animals[0].type = BIRD;
    ctx->animals[1].type = BIRD;
    ctx->animals[2].type = RABBIT;
    ctx->animals[3].type = RABBIT;
    ctx->animals[4].type = GOAT;
    ctx->animals[5].type = SHEEP;
    ctx->animals[6].type = CAT;
    ctx->animals[7].type = SNAKE;
    for (int i = 0; i < ANIMALS_LENGTH; i++) {
        Animal* a = &ctx->animals[i];
        Rectangle bounds;

        switch (a->type) {
        case BIRD:
            set_rectangle(&bounds, -MAP_SIZE, MAP_SIZE, -MAP_SIZE, MAP_SIZE);
            set_animal(a, -MAP_SIZE, rand() % MAP_SIZE, 25, 25, 20, bounds);
            break;
        case RABBIT:
            set_rectangle(&bounds, 800, 1400, 1000, 1600);
            set_animal(a, 1100, 1300, 25, 25, 6, bounds);
            break;
        case GOAT:
            set_rectangle(&bounds, 1000, 1100, -200, 300);
            set_animal(a, 1000, -150, 50, 50, 7, bounds);
            break;
        case SHEEP:
            set_rectangle(&bounds, 1000, 1100, -200, 300);
            set_animal(a, 1000, -200, 50, 50, 3, bounds);
            break;
        case CAT:
            set_rectangle(&bounds, 800, 1400, 1000, 1600);
            set_animal(a, 1100, 1300, 25, 25, 3, bounds);
            break;
        case SNAKE:
            set_rectangle(&bounds, -500, 500, 1500, 2400);
            set_animal(a, 0, 1600, 50, 30, 3, bounds);
            break;
        default:
            break;
        }
    }

    ctx->sounds.footstep[0].is_playing = false;
    ctx->sounds.footstep[1].is_playing = false;
    ctx->sounds.water_footstep[0].is_playing = false;
    ctx->sounds.water_footstep[1].is_playing = false;
    ctx->sounds.typing.is_playing = false;
    ctx->sounds.hurting.is_playing = false;
    ctx->sounds.challenges[0].is_playing = false;
    ctx->sounds.challenges[1].is_playing = false;
    ctx->sounds.challenges[2].is_playing = false;
    ctx->sounds.challenges[3].is_playing = false;
    ctx->sounds.challenges[4].is_playing = false;
    ctx->sounds.panting.is_playing = false;
    ctx->sounds.water_bubbles.is_playing = false;
    for (int i = 0; i < ANIMAL_TYPE_LENGTH; i++) {
        for (int j = 0; j < ANIMAL_SOUNDS_LENGTH; j++) {
            ctx->sounds.animals[i][j].is_playing = false;
        }
    }

    al_close_video(ctx->videos.c2_distillation);
    al_close_video(ctx->videos.rescue);
    al_close_video(ctx->videos.island);
    for (int i = 0; i < 5; i++) {
        al_close_video(ctx->videos.tutorials[i]);
    }
    load_videos(&ctx->videos);

    set_obstacle(&ctx->obstacles[0], 1000, 1175, 100, 200);
    set_obstacle(&ctx->obstacles[1], 1070, 1190, 100, 100);
    set_obstacle(&ctx->obstacles[2], 1100, 1225, 125, 150);
    set_obstacle(&ctx->obstacles[3], 1800, 1740, 200, 150);
    set_obstacle(&ctx->obstacles[4], 1700, 1680, 100, 150);
    set_obstacle(&ctx->obstacles[5], 1600, 1660, 100, 150);
    set_obstacle(&ctx->obstacles[6], 1550, 1590, 100, 150);
    set_obstacle(&ctx->obstacles[7], 1500, 1700, 100, 100);
    set_obstacle(&ctx->obstacles[8], 1570, 1410, 70, 90);
    set_obstacle(&ctx->obstacles[9], 1380, 1735, 100, 150);
    set_obstacle(&ctx->obstacles[10], 1310, 1760, 70, 90);
    set_obstacle(&ctx->obstacles[11], 1450, 1885, 100, 150);
    set_obstacle(&ctx->obstacles[12], 1550, 2035, 100, 100);
    set_obstacle(&ctx->obstacles[13], 1610, 2135, 100, 150);
    set_obstacle(&ctx->obstacles[14], 1950, -100, 100, 130);
    set_obstacle(&ctx->obstacles[15], 1870, -30, 80, 130);
    set_obstacle(&ctx->obstacles[16], 1750, 100, 130, 130);
    set_obstacle(&ctx->obstacles[17], 1610, -100, 100, 90);
    set_obstacle(&ctx->obstacles[18], 1490, -50, 120, 90);
    set_obstacle(&ctx->obstacles[19], 1390, 30, 100, 90);
    set_obstacle(&ctx->obstacles[20], 1290, 90, 100, 80);
    set_obstacle(&ctx->obstacles[21], 1220, -100, 70, 300);
    set_obstacle(&ctx->obstacles[22], 1200, 245, 70, 90);
    set_obstacle(&ctx->obstacles[23], 1660, 220, 90, 100);
    set_obstacle(&ctx->obstacles[24], 1570, 245, 90, 100);
    set_obstacle(&ctx->obstacles[25], 1370, 300, 200, 100);
    set_obstacle(&ctx->obstacles[26], 1340, 340, 30, 120);
    set_obstacle(&ctx->obstacles[27], 1370, 460, 60, 60);
    set_obstacle(&ctx->obstacles[28], 1430, 520, 120, 200);
    set_obstacle(&ctx->obstacles[29], 1530, 720, 500, 70);
    set_obstacle(&ctx->obstacles[30], 1670, 790, 50, 30);
    set_obstacle(&ctx->obstacles[31], 1890, 790, 200, 30);
    set_obstacle(&ctx->obstacles[32], 1455, 810, 70, 90);
    set_obstacle(&ctx->obstacles[33], 1950, 990, 70, 90);
    set_obstacle(&ctx->obstacles[34], 1850, 970, 100, 90);
    set_obstacle(&ctx->obstacles[35], 1800, 1000, 50, 60);
    set_obstacle(&ctx->obstacles[36], 1700, 970, 100, 90);
    set_obstacle(&ctx->obstacles[37], 1600, 970, 100, 150);
    set_obstacle(&ctx->obstacles[38], 1600, 1170, 100, 100);
    set_obstacle(&ctx->obstacles[39], 1670, 1120, 30, 50);
    set_obstacle(&ctx->obstacles[40], 1640, 1270, 150, 170);
    set_obstacle(&ctx->obstacles[41], 1790, 1440, 90, 70);
    set_obstacle(&ctx->obstacles[42], 1880, 1510, 150, 70);
    set_obstacle(&ctx->obstacles[43], 1190, 2170, 100, 100);
    set_obstacle(&ctx->obstacles[44], 1240, 2070, 100, 100);
    set_obstacle(&ctx->obstacles[45], 1190, 2000, 50, 100);
    set_obstacle(&ctx->obstacles[46], 1140, 1950, 50, 50);
    set_obstacle(&ctx->obstacles[47], 1090, 1900, 120, 50);
    set_obstacle(&ctx->obstacles[48], 1100, 1830, 100, 70);
    set_obstacle(&ctx->obstacles[49], 970, 1870, 80, 70);
    set_obstacle(&ctx->obstacles[50], 1030, 1940, 60, 50);
    set_obstacle(&ctx->obstacles[51], 880, 1890, 90, 70);
    set_obstacle(&ctx->obstacles[52], 850, 1920, 30, 150);
    set_obstacle(&ctx->obstacles[53], 800, 2070, 50, 50);
    set_obstacle(&ctx->obstacles[54], 700, 2010, 100, 60);
    set_obstacle(&ctx->obstacles[55], 630, 1910, 100, 100);
    set_obstacle(&ctx->obstacles[56], 560, 1930, 70, 100);
    set_obstacle(&ctx->obstacles[57], 480, 1930, 80, 100);
    set_obstacle(&ctx->obstacles[58], 520, 2030, 100, 100);
    set_obstacle(&ctx->obstacles[59], 540, 2130, 100, 150);
    set_obstacle(&ctx->obstacles[60], 240, 2110, 100, 150);
    set_obstacle(&ctx->obstacles[61], 240, 1930, 120, 150);
    set_obstacle(&ctx->obstacles[62], 190, 2080, 50, 30);
    set_obstacle(&ctx->obstacles[63], 120, 1880, 200, 50);
    set_obstacle(&ctx->obstacles[64], 190, 2170, 50, 30);
    set_obstacle(&ctx->obstacles[65], 40, 1930, 80, 50);
    set_obstacle(&ctx->obstacles[66], -20, 1960, 60, 30);
    set_obstacle(&ctx->obstacles[67], -260, 1880, 240, 80);
    set_obstacle(&ctx->obstacles[68], -360, 1960, 100, 50);
    set_obstacle(&ctx->obstacles[69], -180, 1840, 100, 40);
    set_obstacle(&ctx->obstacles[70], 20, 1700, 90, 110);

    set_rectangle(&ctx->shallow_water_areas[0], INITIAL_MAP_X, INITIAL_MAP_X + 750, INITIAL_MAP_Y, INITIAL_MAP_Y + 500);
    set_rectangle(&ctx->shallow_water_areas[1], INITIAL_MAP_X + 750, INITIAL_MAP_X + 1125, INITIAL_MAP_Y, INITIAL_MAP_Y + 180);
    set_rectangle(&ctx->shallow_water_areas[2], INITIAL_MAP_X, INITIAL_MAP_X + 100, INITIAL_MAP_Y + 500, INITIAL_MAP_Y + 1270);
    set_rectangle(&ctx->shallow_water_areas[3], INITIAL_MAP_X + 750, INITIAL_MAP_X + 900, INITIAL_MAP_Y + 180, INITIAL_MAP_Y + 330);
    set_rectangle(&ctx->shallow_water_areas[4], INITIAL_MAP_X + 100, INITIAL_MAP_X + 500, INITIAL_MAP_Y + 500, INITIAL_MAP_Y + 600);
    set_rectangle(&ctx->shallow_water_areas[5], INITIAL_MAP_X + 100, INITIAL_MAP_X + 270, INITIAL_MAP_Y + 1150, INITIAL_MAP_Y + 1270);

    set_rectangle(&ctx->deep_water_area, INITIAL_MAP_X, INITIAL_MAP_X + 550, INITIAL_MAP_Y, INITIAL_MAP_Y + 300);
}

void init_context(Context* ctx) {
    must_init(al_init(), "allegro");
    must_init(al_init_primitives_addon(), "primitives");
    must_init(al_install_keyboard(), "keyboard");
    must_init(al_install_mouse(), "mouse");
    must_init(al_init_image_addon(), "image");
    must_init(al_install_audio(), "audio");
    must_init(al_init_acodec_addon(), "acodec");
    must_init(al_reserve_samples(13), "samples");
    must_init(al_init_video_addon(), "video");

    srand(time(NULL));
    
    ctx->timer = al_create_timer(1.0 / FPS);
    must_init(ctx->timer, "timer");
    ctx->queue = al_create_event_queue();
    must_init(ctx->queue, "event queue");
    ctx->disp = al_create_display(DISPLAY_WIDTH, DISPLAY_HEIGHT);
    must_init(ctx->disp, "display");
    ctx->font = al_create_builtin_font();
    must_init(ctx->font, "font");

    al_set_window_title(ctx->disp, "Stay Alive");

    al_register_event_source(ctx->queue, al_get_display_event_source(ctx->disp));
    al_register_event_source(ctx->queue, al_get_timer_event_source(ctx->timer));
    al_register_event_source(ctx->queue, al_get_keyboard_event_source());
    al_register_event_source(ctx->queue, al_get_mouse_event_source());

    load_images(&ctx->imgs);
    load_sounds(&ctx->sounds);
    load_videos(&ctx->videos);
    set_context_to_default(ctx);

    set_rectangle(&ctx->challenges_areas[0], DISPLAY_WIDTH - 280, DISPLAY_WIDTH - 80, 0, 15);
    set_rectangle(&ctx->challenges_areas[1], DISPLAY_WIDTH - 15, DISPLAY_WIDTH, DISPLAY_HEIGHT/2.0 - 100, DISPLAY_HEIGHT/2.0 + 100);
    set_rectangle(&ctx->challenges_areas[2], DISPLAY_WIDTH - 15, DISPLAY_WIDTH, DISPLAY_HEIGHT/2.0 - 100, DISPLAY_HEIGHT/2.0 + 100);
    set_rectangle(&ctx->challenges_areas[3], DISPLAY_WIDTH - 680, DISPLAY_WIDTH - 410, DISPLAY_HEIGHT - 15, DISPLAY_HEIGHT);
    set_rectangle(&ctx->challenges_areas[4], DISPLAY_WIDTH - 680, DISPLAY_WIDTH - 410, DISPLAY_HEIGHT - 15, DISPLAY_HEIGHT);

    ctx->c1.placeable_positions[0].x = 250;
    ctx->c1.placeable_positions[0].y = 50;
    ctx->c1.placeable_positions[1].x = 100;
    ctx->c1.placeable_positions[1].y = 490;
    ctx->c1.placeable_positions[2].x = 675;
    ctx->c1.placeable_positions[2].y = 50;
    ctx->c1.placeable_positions[3].x = 380;
    ctx->c1.placeable_positions[3].y = 370;
    ctx->c1.placeable_positions[4].x = 50;
    ctx->c1.placeable_positions[4].y = 50;
    ctx->c1.placeable_positions[5].x = 650;
    ctx->c1.placeable_positions[5].y = 250;
    ctx->c1.placeable_positions[6].x = 430;
    ctx->c1.placeable_positions[6].y = 50;
    ctx->c1.placeable_positions[7].x = 1050;
    ctx->c1.placeable_positions[7].y = 390;
    ctx->c1.placeable_objects[0].width = 98;
    ctx->c1.placeable_objects[0].height = 100;
    ctx->c1.placeable_objects[1].width = 59;
    ctx->c1.placeable_objects[1].height = 100;
    ctx->c1.placeable_objects[2].width = 101;
    ctx->c1.placeable_objects[2].height = 100;
    ctx->c1.placeable_objects[3].width = 130;
    ctx->c1.placeable_objects[3].height = 100;

    set_selectable_object(&ctx->c2.selectable_objects[0], 640, 340, 101, 180, true);
    set_selectable_object(&ctx->c2.selectable_objects[1], 475, 350, 118, 99, true);
    set_selectable_object(&ctx->c2.selectable_objects[2], 690, 570, 100, 144, true);
    set_selectable_object(&ctx->c2.selectable_objects[3], 745, 380, 101, 180, true);
    set_selectable_object(&ctx->c2.selectable_objects[4], 890, 400, 145, 99, true);
    set_selectable_object(&ctx->c2.selectable_objects[5], 550, 570, 120, 99, false);
    set_selectable_object(&ctx->c2.selectable_objects[6], 900, 540, 102, 80, false);
    
    ctx->c4.duration_in_seconds = 15;
    set_wanted_object(&ctx->c4.wanted_objects[0], 100, 100, 125, 100);
    set_wanted_object(&ctx->c4.wanted_objects[1], 410, 300, 125, 145);
    set_wanted_object(&ctx->c4.wanted_objects[2], 590, 490, 125, 145);
    set_wanted_object(&ctx->c4.wanted_objects[3], 900, 270, 125, 100);
    set_wanted_object(&ctx->c4.wanted_objects[4], 1150, 570, 125, 102);
    set_wanted_object(&ctx->c4.fake_wanted_objects[0], 260, 600, 125, 100);
    set_wanted_object(&ctx->c4.fake_wanted_objects[1], 1160, 100, 125, 145);
    set_wanted_object(&ctx->c4.fake_wanted_objects[2], 630, 330, 125, 145);
    set_wanted_object(&ctx->c4.fake_wanted_objects[3], 0, 480, 125, 100);
    set_wanted_object(&ctx->c4.fake_wanted_objects[4], 770, 130, 125, 102);

    ctx->c5.duration_in_seconds = 10;
    set_selectable_object(&ctx->c5.selectable_objects[0], 670, 450, 100, 100, true);
    set_selectable_object(&ctx->c5.selectable_objects[1], 420, 450, 100, 100, true);
    set_selectable_object(&ctx->c5.selectable_objects[2], 690, 570, 100, 100, false);
    set_selectable_object(&ctx->c5.selectable_objects[3], 550, 400, 100, 100, false);
    set_selectable_object(&ctx->c5.selectable_objects[4], 850, 400, 100, 100, false);
    set_selectable_object(&ctx->c5.selectable_objects[5], 550, 570, 100, 100, false);
    set_selectable_object(&ctx->c5.selectable_objects[6], 300, 540, 100, 100, false);
    set_selectable_object(&ctx->c5.selectable_objects[7], 190, 500, 100, 100, false);

    set_audio(&ctx->sounds.footstep[0], 0.7, 0.5, 1.5);
    set_audio(&ctx->sounds.footstep[1], 0.7, -0.5, 1.5);
    set_audio(&ctx->sounds.water_footstep[0], 0.7, 0.5, 1.1);
    set_audio(&ctx->sounds.water_footstep[1], 0.7, -0.5, 1.1);
    set_audio(&ctx->sounds.typing, 1, 0, 1);
    set_audio(&ctx->sounds.hurting, 1, 0, 1);
    set_audio(&ctx->sounds.panting, 2, 0, 1.1);
    set_audio(&ctx->sounds.water_bubbles, 1, 0, 1);
    for (int i = 0; i < 5; i++) {
        set_audio(&ctx->sounds.challenges[i], 1, 0, 1);
    }
    for (int i = 0; i < ANIMAL_TYPE_LENGTH; i++) {
        for (int j = 0; j < ANIMAL_SOUNDS_LENGTH; j++) {
            set_audio(&ctx->sounds.animals[i][j], 1, 0, 1);
        }
    }
}

void free_context(Context* ctx) {
    al_destroy_bitmap(ctx->imgs.map);
    al_destroy_bitmap(ctx->imgs.menu);
    al_destroy_bitmap(ctx->imgs.end_game);
    al_destroy_bitmap(ctx->imgs.game_over);
    al_destroy_bitmap(ctx->imgs.c5_bonfire);
    al_destroy_bitmap(ctx->imgs.play_btn);
    al_destroy_bitmap(ctx->imgs.menu_btn);
    al_destroy_bitmap(ctx->imgs.next_btn);
    al_destroy_bitmap(ctx->imgs.mute_btn);
    al_destroy_bitmap(ctx->imgs.unmute_btn);
    al_destroy_bitmap(ctx->imgs.heart_empty);
    al_destroy_bitmap(ctx->imgs.heart_filled);
    al_destroy_bitmap(ctx->imgs.hunger_empty);
    al_destroy_bitmap(ctx->imgs.hunger_filled);
    al_destroy_bitmap(ctx->imgs.water_bubble);
    al_destroy_bitmap(ctx->imgs.apple);
    al_destroy_bitmap(ctx->imgs.mushroom);
    al_destroy_bitmap(ctx->imgs.char_with_basket);
    al_destroy_bitmap(ctx->imgs.snake_alert);

    al_destroy_sample(ctx->sounds.typing.sample);
    al_destroy_sample(ctx->sounds.hurting.sample);
    al_destroy_sample(ctx->sounds.panting.sample);
    al_destroy_sample(ctx->sounds.water_bubbles.sample);

    al_close_video(ctx->videos.c2_distillation);
    al_close_video(ctx->videos.rescue);
    al_close_video(ctx->videos.island);

    int i = 0;
    while (true) {
        bool done = true;

        if (i < SPRITES_LENGTH) {
            al_destroy_bitmap(ctx->imgs.char_sprites.front[i]);
            al_destroy_bitmap(ctx->imgs.char_sprites.back[i]);
            al_destroy_bitmap(ctx->imgs.char_sprites.left[i]);
            al_destroy_bitmap(ctx->imgs.char_sprites.right[i]);
            
            for (int j = 0; j < ANIMAL_TYPE_LENGTH; j++) {
                al_destroy_bitmap(ctx->imgs.animals[j].front[i]);
                al_destroy_bitmap(ctx->imgs.animals[j].back[i]);
                al_destroy_bitmap(ctx->imgs.animals[j].left[i]);
                al_destroy_bitmap(ctx->imgs.animals[j].right[i]);
            }

            done = false;
        }

        if (i < SELECTABLE_OBJECTS_LENGTH_C2) {
            al_destroy_bitmap(ctx->imgs.c2_selectable_objects[i]);
            done = false;
        }

        if (i < SELECTABLE_OBJECTS_LENGTH_C5) {
            al_destroy_bitmap(ctx->imgs.c5_selectable_objects[i]);
            done = false;
        }

        if (i < WANTED_OBJECTS_LENGTH) {
            al_destroy_bitmap(ctx->imgs.medicinal_plants[i]);
            done = false;
        }

        if (i < RUB_SPRITES_LENGTH) {
            al_destroy_bitmap(ctx->imgs.rub_sprites[i]);
            done = false;
        }

        if (i < TUTORIALS_LENGTH) {
            al_close_video(ctx->videos.tutorials[i]);
            done = false;
        }

        if (i < ANIMAL_TYPE_LENGTH && i != RABBIT) {
            for (int j = 0; j < ANIMAL_SOUNDS_LENGTH; j++) {
                al_destroy_sample(ctx->sounds.animals[i][j].sample);
            }
            done = false;
        }

        if (i < 5) {
            al_destroy_bitmap(ctx->imgs.challenges[i]);
            al_destroy_sample(ctx->sounds.challenges[i].sample);
            done = false;
        }

        if (i < 2) {
            al_destroy_sample(ctx->sounds.footstep[i].sample);
            al_destroy_sample(ctx->sounds.water_footstep[i].sample);
            done = false;
        }

        if (done) break;
        i++;
    }

    al_destroy_font(ctx->font);
    al_destroy_display(ctx->disp);
    al_destroy_timer(ctx->timer);
    al_destroy_event_queue(ctx->queue);
    al_uninstall_keyboard();
    al_uninstall_mouse();
    al_uninstall_audio();
}

void draw_context(Context* ctx) {
    al_clear_to_color(al_map_rgb(0, 0, 0));

    switch (ctx->state) {
    case MENU:
        al_draw_bitmap(ctx->imgs.menu, 0, 0, 0);
        al_draw_bitmap(ctx->imgs.play_btn, PLAY_BTN_X, PLAY_BTN_Y, 0);
        if (ctx->sounds_muted) {
            al_draw_bitmap(ctx->imgs.unmute_btn, VOLUME_BTN_X, VOLUME_BTN_Y, 0);
        } else {
            al_draw_bitmap(ctx->imgs.mute_btn, VOLUME_BTN_X, VOLUME_BTN_Y, 0);
        }
        break;
    case OPEN_MAP:
        al_draw_bitmap(ctx->imgs.map, ctx->map.x, ctx->map.y, 0);
        if (ctx->is_user_hallucinated) {
            float x = ctx->map.x + ctx->hallucination_map_x,
                  y = ctx->map.y + ctx->hallucination_map_y;
            al_draw_tinted_bitmap(ctx->imgs.map, al_map_rgba_f(0.8, 0.8, 0.8, 0.5), x, y, 0);
        }

        for (int i = 2; i < ANIMALS_LENGTH; i++) {
            Animal* a = &ctx->animals[i];
            bool hide = false;

            switch (a->type) {
            case CAT:
            case RABBIT:
                hide = a->position.x >= a->bounds.x1 + 200 && a->position.x <= a->bounds.x2 - 200 && a->position.y >= a->bounds.y1 + 100 &&
                       a->position.y <= a->bounds.y2 - 250;
                break;
            case SNAKE:
                float cx1 = ctx->obstacles[70].position.x - 20,
                      cx2 = ctx->obstacles[70].position.x + ctx->obstacles[70].width - 20,
                      cy1 = ctx->obstacles[70].position.y - 20,
                      cy2 = ctx->obstacles[70].position.y + ctx->obstacles[70].height - 20;
                hide = (a->position.x <= a->bounds.x2 - 150 && a->position.y >= a->bounds.y1 + 300) ||
                       (a->position.x >= cx1 && a->position.x <= cx2 && a->position.y >= cy1 && a->position.y <= cy2);
                break;
            case GOAT:
            case SHEEP:
            case BIRD:
            default:
                break;
            }

            if (!hide) al_draw_bitmap(a->current_sprite, a->position.x, a->position.y, 0);
            if (ctx->is_user_hallucinated && !hide) {
                float x = a->position.x + ctx->hallucination_char_x,
                      y = a->position.y + ctx->hallucination_char_y;
                al_draw_tinted_bitmap(a->current_sprite, al_map_rgba_f(0.5, 0.5, 0.5, 0.5), x, y, 0);
            }
        }

        al_draw_bitmap(ctx->imgs.char_sprites.current, ctx->player.x, ctx->player.y, 0);
        if (ctx->is_user_hallucinated) {
            float x = ctx->player.x - ctx->hallucination_char_x,
                  y = ctx->player.y - ctx->hallucination_char_y;
            al_draw_tinted_bitmap(ctx->imgs.char_sprites.current, al_map_rgba_f(0.5, 0.5, 0.5, 0.5), x, y, 0);
        }

        for (int i = 0; i < 2; i++) {
            Animal* a = &ctx->animals[i];

            for (int j = 0; j < a->birds_count; j++) {
                  float x = j * 100,
                        y = j * 50;

                  if (j % 2 == 0 && j != 0) {
                      y -= 10;
                      y *= -1;
                      x -= 25;
                  }
                  if (x < a->destination.x) x *= -1;

                  x += a->position.x;
                  y += a->position.y;

                  al_draw_bitmap(a->current_sprite, x, y, 0);
                  if (ctx->is_user_hallucinated) {
                      x += ctx->hallucination_char_x;
                      y += ctx->hallucination_char_y;
                      al_draw_tinted_bitmap(a->current_sprite,al_map_rgba_f(0.5, 0.5, 0.5, 0.5), x, y, 0);
                  }
            }
        }

        for (int i = 2; i >= 0; i--) {
            if (ctx->life_counter > i) {
                al_draw_bitmap(ctx->imgs.heart_filled, 5 + i * HEART_WIDTH, 5, 0);
            }
            else {
                al_draw_bitmap(ctx->imgs.heart_empty, 5 + i * HEART_WIDTH, 5, 0);
            }
            if (ctx->hunger_counter > i) {
                al_draw_bitmap(ctx->imgs.hunger_filled, 5 + i * HUNGER_WIDTH, HEART_HEIGHT + 15, 0);
            }
            else {
                al_draw_bitmap(ctx->imgs.hunger_empty, 5 + i * HUNGER_WIDTH, HEART_HEIGHT + 15, 0);
            }
            if (ctx->oxygen_counter > i && ctx->is_underwater) {
                al_draw_bitmap(ctx->imgs.water_bubble, 5 + i * OXYGEN_WIDTH, HEART_HEIGHT + HUNGER_HEIGHT + 15, 0);
            }
        }

        if (ctx->is_snake_hunting) al_draw_bitmap(ctx->imgs.snake_alert, DISPLAY_WIDTH/2.0 - 25, 0, 0);
        break;
    case CHALLENGE:
        al_draw_bitmap(ctx->imgs.challenges[ctx->challenge_index], 0, 0, 0);

        if (!ctx->tutorials[ctx->challenge_index].is_completed) {
            al_draw_bitmap(ctx->imgs.current_video_frame, 0, 0, 0);

            ALLEGRO_VIDEO* video = ctx->videos.tutorials[ctx->tutorial_index];
            if (!al_is_video_playing(video) && ctx->tutorial_index % 2 == 0) {
                if (ctx->tutorial_index == ctx->tutorials[ctx->challenge_index].last_step_index - 1) {
                    al_draw_bitmap(ctx->imgs.play_btn, TUTORIAL_BTN_X, TUTORIAL_BTN_Y, 0);
                } else {
                    al_draw_bitmap(ctx->imgs.next_btn, TUTORIAL_BTN_X, TUTORIAL_BTN_Y, 0);
                }
            }
            break;
        }

        if (ctx->challenge_index == 1 && ctx->c2.is_distillation_playing) {
            if (ctx->imgs.current_video_frame) al_draw_bitmap(ctx->imgs.current_video_frame, 0, 0, 0); 
            break;
        }

        if (ctx->challenge_index == 0) {
            for (int i = 0; i < PLACEABLE_OBJECTS_LENGTH; i++) {
                int pos_i = ctx->c1.placeable_objects[i].position_index;
                float x = ctx->c1.placeable_positions[pos_i].x,
                      y = ctx->c1.placeable_positions[pos_i].y,
                      w = ctx->c1.placeable_objects[i].width,
                      h = ctx->c1.placeable_objects[i].height;

                al_draw_bitmap(ctx->c1.placeable_objects[i].img, x, y, 0); 
                if (ctx->c1.selected_object_index == i) {
                    al_draw_rounded_rectangle(x - 5, y - 5, x + w + 5, y + h + 5, 5, 5, al_map_rgb(255, 255, 255), 2);
                }
            }  
        }

        if (ctx->challenge_index == 1) {
            for (int i = 0; i < SELECTABLE_OBJECTS_LENGTH_C2; i++) {
                Selectable_Object* obj = &ctx->c2.selectable_objects[i];
                float x = obj->position.x,
                      y = obj->position.y,
                      w = obj->width,
                      h = obj->height;

                al_draw_bitmap(ctx->imgs.c2_selectable_objects[i], x, y, 0);
                if (obj->selected) {
                    al_draw_rounded_rectangle(x - 5, y - 5, x + w + 5, y + h + 5, 5, 5, al_map_rgb(255, 255, 255), 2);
                }
            }
        }
            
        if (ctx->challenge_index == 2) {
            al_draw_bitmap(ctx->imgs.char_with_basket, ctx->c3.player_position.x, ctx->c3.player_position.y, 0);
            al_draw_textf(ctx->font, al_map_rgb(255, 255, 255), 1180, 0, 0, "Maçãs: %d", ctx->c3.apples_counter);
            al_draw_textf(ctx->font, al_map_rgb(255, 255, 255), 1180, 20, 0, "Cogumelos: %d", ctx->c3.mushrooms_counter);

            for (int i = 0; i < FALLING_OBJECTS_LENGTH; i++) {
                Falling_Object* obj = &ctx->c3.falling_objects[i];
                ALLEGRO_BITMAP* img;

                if (obj->id == 0) {
                    img = ctx->imgs.apple;
                } else {
                    img = ctx->imgs.mushroom;
                }
            
                al_draw_bitmap(img, obj->position.x, obj->position.y, 0);
            }
        }

        if (ctx->challenge_index == 3) {
            for (int i = 0; i < WANTED_OBJECTS_LENGTH; i++) {
                Wanted_Object* obj = &ctx->c4.wanted_objects[i];
                Wanted_Object* fake_obj = &ctx->c4.fake_wanted_objects[i];
                
                if (ctx->is_user_hallucinated && !fake_obj->selected) {
                    obj = fake_obj;
                }

                float x = obj->position.x,
                      y = obj->position.y,
                      w = obj->width,
                      h = obj->height;
                    
                if (obj->selected) {
                    al_draw_rounded_rectangle(x - 5, y - 5, x + w + 5, y + h + 5, 5, 5, al_map_rgb(255, 255, 255), 2);
                }

                ALLEGRO_BITMAP* img = ctx->imgs.medicinal_plants[i];
                al_draw_bitmap(img, x, y, 0);
            }

            int seconds_left = calculate_seconds_left(ctx->c4.start_time, ctx->c4.duration_in_seconds);
            al_draw_textf(ctx->font, al_map_rgb(255, 255, 255), 20, 20, 0, "Tempo: %d segundos", seconds_left);
        }

        if (ctx->challenge_index == 4) {
            if (ctx->c5.bonfire_scene) {
                al_draw_bitmap(ctx->imgs.rub_sprites[ctx->c5.rub_sprite_index], 0, 0, 0);
                al_draw_filled_rectangle(0, 0, ctx->c5.action_bar, 50, al_map_rgb(255, 255, 255));
                int seconds_left = calculate_seconds_left(ctx->c5.start_time, ctx->c5.duration_in_seconds);
                al_draw_textf(ctx->font, al_map_rgb(0, 0, 0), 40, 20, 0, "Tempo restante: %d segundos", seconds_left);
            } else {
                for (int i = 0; i < SELECTABLE_OBJECTS_LENGTH_C5; i++) {
                    Selectable_Object* obj = &ctx->c5.selectable_objects[i];
                    float x = obj->position.x,
                          y = obj->position.y,
                          w = obj->width,
                          h = obj->height;

                    al_draw_bitmap(ctx->imgs.c5_selectable_objects[i], x, y, 0);
                    if (obj->selected) {
                        al_draw_rounded_rectangle(x - 5, y - 5, x + w + 5, y + h + 5, 5, 5, al_map_rgb(255, 255, 255), 2);
                    }
                }
            }
        }

        if (ctx->challenge_index == 0 || ctx->challenge_index == 1 || (ctx->challenge_index == 4 && !ctx->c5.bonfire_scene)) {
            al_draw_bitmap(ctx->imgs.next_btn, CHALLENGE_NEXT_BTN_X, CHALLENGE_NEXT_BTN_Y, 0);
        }
        break;
    case GAME_OVER:
        if (ctx->has_user_lost) {
            al_draw_bitmap(ctx->imgs.game_over, 0, 0, 0);
        } else {
            if (al_is_video_playing(ctx->videos.rescue)) {
                ALLEGRO_BITMAP* frame = al_get_video_frame(ctx->videos.rescue);
                if (frame) al_draw_bitmap(frame, 0, 0, 0);
                return;
            }

            al_draw_bitmap(ctx->imgs.end_game, 0, 0, 0);
        }
        al_draw_bitmap(ctx->imgs.menu_btn, RETURN_TO_MENU_BTN_X, RETURN_TO_MENU_BTN_Y, 0);
        break;
    }
}

bool check_obstacles_collision(Context* ctx) {
    bool is_colliding = false;

    for (int i = 0; i < OBSTACLES_LENGTH; i++) {
        float ox1 = ctx->obstacles[i].position.x,
              ox2 = ctx->obstacles[i].position.x + ctx->obstacles[i].width,
              oy1 = ctx->obstacles[i].position.y,
              oy2 = ctx->obstacles[i].position.y + ctx->obstacles[i].height;

        Coordinate player_bottom_left = {ctx->player.x + 25, ctx->player.y + PLAYER_HEIGHT - 10},
                   player_bottom_right = {ctx->player.x + PLAYER_WIDTH - 25, ctx->player.y + PLAYER_HEIGHT - 10};

        if (check_collision(&player_bottom_left, ox1, ox2, oy1, oy2) ||
            check_collision(&player_bottom_right, ox1, ox2, oy1, oy2)) {
            is_colliding = true;
            break;
        }
    }

    return is_colliding;
}

bool check_water_collision(Context* ctx) {
    bool is_colliding = false;

    for (int i = 0; i < SHALLOW_WATER_AREAS_LENGTH; i++) {
        Rectangle* r = &ctx->shallow_water_areas[i];

        Coordinate player_bottom_left = {ctx->player.x + 25, ctx->player.y + PLAYER_HEIGHT - 10},
                   player_bottom_right = {ctx->player.x + PLAYER_WIDTH - 25, ctx->player.y + PLAYER_HEIGHT - 10};

        if (check_collision(&player_bottom_left, r->x1, r->x2, r->y1, r->y2) ||
            check_collision(&player_bottom_right, r->x1, r->x2, r->y1, r->y2)) {
            is_colliding = true;
            break;
        }
    }

    return is_colliding;
}

void move_camera(Context* ctx) {
    bool is_player_y_centered = ctx->player.y == (DISPLAY_HEIGHT/2.0 - PLAYER_HEIGHT/2);
    bool is_player_x_centered = ctx->player.x == (DISPLAY_WIDTH/2.0 - PLAYER_WIDTH/2);

    Coordinate player = {ctx->player.x, ctx->player.y};
    Coordinate map = {ctx->map.x, ctx->map.y};
    Coordinate obstacles[OBSTACLES_LENGTH];
    Coordinate animals_positions[ANIMALS_LENGTH];
    Coordinate animals_destinations[ANIMALS_LENGTH];
    Rectangle animals_bounds[ANIMALS_LENGTH];
    Rectangle shallow_water_areas[SHALLOW_WATER_AREAS_LENGTH];
    Rectangle deep_water_area = ctx->deep_water_area;

    for (int i = 0; i < OBSTACLES_LENGTH; i++) {
        obstacles[i] = ctx->obstacles[i].position;

        if (i < ANIMALS_LENGTH) {
            Animal* a = &ctx->animals[i];
            animals_positions[i].x = a->position.x;
            animals_positions[i].y = a->position.y;
            animals_destinations[i].x = a->destination.x;
            animals_destinations[i].y = a->destination.y;
            animals_bounds[i].x1 = a->bounds.x1;
            animals_bounds[i].x2 = a->bounds.x2;
            animals_bounds[i].y1 = a->bounds.y1;
            animals_bounds[i].y2 = a->bounds.y2;
        }

        if (i < SHALLOW_WATER_AREAS_LENGTH) {
            shallow_water_areas[i].x1 = ctx->shallow_water_areas[i].x1;
            shallow_water_areas[i].x2 = ctx->shallow_water_areas[i].x2;
            shallow_water_areas[i].y1 = ctx->shallow_water_areas[i].y1;
            shallow_water_areas[i].y2 = ctx->shallow_water_areas[i].y2;
        }
    }

    int speed = PLAYER_SPEED;
    if (check_water_collision(ctx)) {
        speed *= 0.5;
        ctx->is_half_water = true;
    } else {
        ctx->is_half_water = false;
    }

    switch (ctx->event.keyboard.keycode) {
    case ALLEGRO_KEY_UP:
    case ALLEGRO_KEY_W:
        if (ctx->map.y < 0 && is_player_y_centered) {
            ctx->map.y += speed;
            ctx->deep_water_area.y1 += speed;
            ctx->deep_water_area.y2 += speed;
            for (int i = 0; i < OBSTACLES_LENGTH; i++) {
                ctx->obstacles[i].position.y += speed;
                
                if (i < ANIMALS_LENGTH) {
                    Animal* a = &ctx->animals[i];
                    a->position.y += speed;
                    a->destination.y += speed;
                    a->bounds.y1 += speed;
                    a->bounds.y2 += speed;
                }

                if (i < SHALLOW_WATER_AREAS_LENGTH) {
                    ctx->shallow_water_areas[i].y1 += speed;
                    ctx->shallow_water_areas[i].y2 += speed;
                }
            }
        } else if (ctx->player.y >= ctx->map.y) {
            ctx->player.y -= speed;
        }
        break;
    case ALLEGRO_KEY_DOWN:
    case ALLEGRO_KEY_S:
        if (ctx->map.y + MAP_SIZE > DISPLAY_HEIGHT && is_player_y_centered) {
            ctx->map.y -= speed;
            ctx->deep_water_area.y1 -= speed;
            ctx->deep_water_area.y2 -= speed;
            for (int i = 0; i < OBSTACLES_LENGTH; i++) {
                ctx->obstacles[i].position.y -= speed;
            
                if (i < ANIMALS_LENGTH) {
                    Animal* a = &ctx->animals[i];
                    a->position.y -= speed;
                    a->destination.y -= speed;
                    a->bounds.y1 -= speed;
                    a->bounds.y2 -= speed;
                }

                if (i < SHALLOW_WATER_AREAS_LENGTH) {
                    ctx->shallow_water_areas[i].y1 -= speed;
                    ctx->shallow_water_areas[i].y2 -= speed;
                }
            }
        } else if (ctx->player.y + PLAYER_HEIGHT <= ctx->map.y + MAP_SIZE) {
            ctx->player.y += speed;
        }
        break;
    case ALLEGRO_KEY_LEFT:
    case ALLEGRO_KEY_A:
        if (ctx->map.x < 0 && is_player_x_centered) {
            ctx->map.x += speed;
            ctx->deep_water_area.x1 += speed;
            ctx->deep_water_area.x2 += speed;
            for (int i = 0; i < OBSTACLES_LENGTH; i++) {
                ctx->obstacles[i].position.x += speed;

                if (i < ANIMALS_LENGTH) {
                    Animal* a = &ctx->animals[i];
                    a->position.x += speed;
                    a->destination.x += speed;
                    a->bounds.x1 += speed;
                    a->bounds.x2 += speed;
                }

                if (i < SHALLOW_WATER_AREAS_LENGTH) {
                    ctx->shallow_water_areas[i].x1 += speed;
                    ctx->shallow_water_areas[i].x2 += speed;
                }
            }
        } else if (ctx->player.x >= ctx->map.x) {
            ctx->player.x -= speed;
        }
        break;
    case ALLEGRO_KEY_RIGHT:
    case ALLEGRO_KEY_D:
        if (ctx->map.x + MAP_SIZE > DISPLAY_WIDTH && is_player_x_centered) {
            ctx->map.x -= speed;
            ctx->deep_water_area.x1 -= speed;
            ctx->deep_water_area.x2 -= speed;
            for (int i = 0; i < OBSTACLES_LENGTH; i++) {
                ctx->obstacles[i].position.x -= speed;
            
                if (i < ANIMALS_LENGTH) {
                    Animal* a = &ctx->animals[i];
                    a->position.x -= speed;
                    a->destination.x -= speed;
                    a->bounds.x1 -= speed;
                    a->bounds.x2 -= speed;
                }

                if (i < SHALLOW_WATER_AREAS_LENGTH) {
                    ctx->shallow_water_areas[i].x1 -= speed;
                    ctx->shallow_water_areas[i].x2 -= speed;
                }
            }
        } else if (ctx->player.x + PLAYER_WIDTH <= ctx->map.x + MAP_SIZE) {
            ctx->player.x += speed;
        }
        break;
    }

    if (check_obstacles_collision(ctx)) {
        ctx->player.x = player.x;
        ctx->player.y = player.y;
        ctx->map.x = map.x;
        ctx->map.y = map.y;
        ctx->deep_water_area = deep_water_area;
        for (int i = 0; i < OBSTACLES_LENGTH; i++) {
            ctx->obstacles[i].position.x = obstacles[i].x;
            ctx->obstacles[i].position.y = obstacles[i].y;

            if (i < ANIMALS_LENGTH) {
                Animal* a = &ctx->animals[i];
                a->position.x = animals_positions[i].x;
                a->position.y = animals_positions[i].y;
                a->destination.x = animals_destinations[i].x;
                a->destination.y = animals_destinations[i].y;
                a->bounds.x1 = animals_bounds[i].x1;
                a->bounds.x2 = animals_bounds[i].x2;
                a->bounds.y1 = animals_bounds[i].y1;
                a->bounds.y2 = animals_bounds[i].y2;
            }

            if (i < SHALLOW_WATER_AREAS_LENGTH) {
                ctx->shallow_water_areas[i].x1 = shallow_water_areas[i].x1;
                ctx->shallow_water_areas[i].x2 = shallow_water_areas[i].x2;
                ctx->shallow_water_areas[i].y1 = shallow_water_areas[i].y1;
                ctx->shallow_water_areas[i].y2 = shallow_water_areas[i].y2;
            }
        }
    }
}

void check_player_position(Context* ctx) {
    float cx1 = ctx->challenges_areas[ctx->challenge_index].x1;
    float cx2 = ctx->challenges_areas[ctx->challenge_index].x2;
    float cy1 = ctx->challenges_areas[ctx->challenge_index].y1;
    float cy2 = ctx->challenges_areas[ctx->challenge_index].y2;

    Coordinate player_top_left = {ctx->player.x, ctx->player.y};
    Coordinate player_top_right = {ctx->player.x + PLAYER_WIDTH, ctx->player.y};
    Coordinate player_bottom_left = {ctx->player.x, ctx->player.y + PLAYER_HEIGHT};
    Coordinate player_bottom_right = {ctx->player.x + PLAYER_WIDTH, ctx->player.y + PLAYER_HEIGHT};

    bool is_player_top_left_colliding = check_collision(&player_top_left, cx1, cx2, cy1, cy2);
    bool is_player_top_right_colliding = check_collision(&player_top_right, cx1, cx2, cy1, cy2);
    bool is_player_bottom_left_colliding = check_collision(&player_bottom_left, cx1, cx2, cy1, cy2);
    bool is_player_bottom_right_colliding = check_collision(&player_bottom_right, cx1, cx2, cy1, cy2);

    if (ctx->challenge_index == 1 && ctx->map.y * -1 > MAP_SIZE/2.0 - 300) return;
    if (ctx->challenge_index == 2 && ctx->map.y * -1 < MAP_SIZE/2.0 - 100) return;
    if (ctx->challenge_index == 3 && ctx->map.x * -1 < 500) return;
    if (ctx->challenge_index == 4 && ctx->map.x * -1 > 500) return;

    if (is_player_top_left_colliding || is_player_top_right_colliding ||
        is_player_bottom_left_colliding || is_player_bottom_right_colliding) {
        ctx->state = CHALLENGE;
        if (!ctx->sounds_muted) al_set_video_playing(ctx->videos.island, false);
        al_start_video(ctx->videos.tutorials[ctx->tutorial_index], al_get_default_mixer());
        if (!ctx->sounds_muted) play_audio(&ctx->sounds.typing, false);
    }

    if (ctx->is_underwater) {
        if (!ctx->sounds_muted) play_audio(&ctx->sounds.water_bubbles, true);
        if (ctx->oxygen_start_time == -1) ctx->oxygen_start_time = time(0);
        if (time(0) - ctx->oxygen_start_time >= OXYGEN_UNIT_DURATION) {
            ctx->oxygen_counter--;
            if (ctx->oxygen_counter <= 0) {
                ctx->oxygen_counter = 0;
                ctx->life_counter--;
                if (!ctx->sounds_muted) play_audio(&ctx->sounds.hurting, false);
                if (ctx->life_counter <= 0) {
                    ctx->has_user_lost = true;
                    ctx->state = GAME_OVER;
                    al_rest(1);
                    al_stop_samples();
                }
            }
            ctx->oxygen_start_time = -1;
        }
    } else {
        stop_audio(&ctx->sounds.water_bubbles);
        ctx->oxygen_start_time = -1;
        ctx->oxygen_counter = 3;
    }
}

void change_character_sprite(Context* ctx) {
    int quarter = get_quarter_from_timer(ctx->timer);
    if (quarter == -1) return;

    bool is_player_standing = ctx->event.type == ALLEGRO_EVENT_KEY_UP;
    Rectangle deep_water = ctx->deep_water_area;
    Coordinate player_bottom_left = {ctx->player.x + 25, ctx->player.y + PLAYER_HEIGHT - 10},
               player_bottom_right = {ctx->player.x + PLAYER_WIDTH - 25, ctx->player.y + PLAYER_HEIGHT - 10};
    if (check_collision(&player_bottom_left, deep_water.x1, deep_water.x2, deep_water.y1, deep_water.y2) ||
        check_collision(&player_bottom_right, deep_water.x1, deep_water.x2, deep_water.y1, deep_water.y2)) {
        ctx->is_underwater = true;
    } else {
        ctx->is_underwater = false;
    }

    ALLEGRO_BITMAP* current = ctx->imgs.char_sprites.current;
    switch (ctx->event.keyboard.keycode) {
    case ALLEGRO_KEY_UP:
    case ALLEGRO_KEY_W:
        if (quarter == 2 && !ctx->is_half_water) current = ctx->imgs.char_sprites.back[1];
        if (quarter == 4 && !ctx->is_half_water) current = ctx->imgs.char_sprites.back[2];
        if ((quarter == 1 || quarter == 3 || is_player_standing) && !ctx->is_half_water) current = ctx->imgs.char_sprites.back[0];
        if (quarter == 2 && ctx->is_half_water) current = ctx->imgs.char_sprites_half_water.back[1];
        if (quarter == 4 && ctx->is_half_water) current = ctx->imgs.char_sprites_half_water.back[2];
        if ((quarter == 1 || quarter == 3 || is_player_standing) && ctx->is_half_water) current = ctx->imgs.char_sprites_half_water.back[0];
        if ( ctx->is_underwater) current = ctx->imgs.char_sprites_underwater.back;
        break;
    case ALLEGRO_KEY_DOWN:
    case ALLEGRO_KEY_S:
        if (quarter == 2 && !ctx->is_half_water) current = ctx->imgs.char_sprites.front[1];
        if (quarter == 4 && !ctx->is_half_water) current = ctx->imgs.char_sprites.front[2];
        if ((quarter == 1 || quarter == 3 || is_player_standing) && !ctx->is_half_water) current = ctx->imgs.char_sprites.front[0];
        if (quarter == 2 && ctx->is_half_water) current = ctx->imgs.char_sprites_half_water.front[1];
        if (quarter == 4 && ctx->is_half_water) current = ctx->imgs.char_sprites_half_water.front[2];
        if ((quarter == 1 || quarter == 3 || is_player_standing) && ctx->is_half_water) current = ctx->imgs.char_sprites_half_water.front[0];
        if (ctx->is_underwater) current = ctx->imgs.char_sprites_underwater.front;
        break;
    case ALLEGRO_KEY_LEFT:
    case ALLEGRO_KEY_A:
        if (quarter == 2 && !ctx->is_half_water) current = ctx->imgs.char_sprites.left[1];
        if (quarter == 4 && !ctx->is_half_water) current = ctx->imgs.char_sprites.left[2];
        if ((quarter == 1 || quarter == 3 || is_player_standing) && !ctx->is_half_water) current = ctx->imgs.char_sprites.left[0];
        if (quarter == 2 && ctx->is_half_water) current = ctx->imgs.char_sprites_half_water.left[1];
        if (quarter == 4 && ctx->is_half_water) current = ctx->imgs.char_sprites_half_water.left[2];
        if ((quarter == 1 || quarter == 3 || is_player_standing) && ctx->is_half_water) current = ctx->imgs.char_sprites_half_water.left[0];
        if (ctx->is_underwater) current = ctx->imgs.char_sprites_underwater.left;
        break;
    case ALLEGRO_KEY_RIGHT:
    case ALLEGRO_KEY_D:
        if (quarter == 2 && !ctx->is_half_water) current = ctx->imgs.char_sprites.right[1];
        if (quarter == 4 && !ctx->is_half_water) current = ctx->imgs.char_sprites.right[2];
        if ((quarter == 1 || quarter == 3 || is_player_standing) && !ctx->is_half_water) current = ctx->imgs.char_sprites.right[0];
        if (quarter == 2 && ctx->is_half_water) current = ctx->imgs.char_sprites_half_water.right[1];
        if (quarter == 4 && ctx->is_half_water) current = ctx->imgs.char_sprites_half_water.right[2];
        if ((quarter == 1 || quarter == 3 || is_player_standing) && ctx->is_half_water) current = ctx->imgs.char_sprites_half_water.right[0];
        if (ctx->is_underwater) current = ctx->imgs.char_sprites_underwater.right;
        break;
    } 
    ctx->imgs.char_sprites.current = current;

    if (ctx->sounds_muted) return;

    float cyclic_timer = al_get_timer_count(ctx->timer) % FPS;
    if (cyclic_timer == 10) {
        if (ctx->is_half_water) play_audio(&ctx->sounds.water_footstep[0], false);
        else play_audio(&ctx->sounds.footstep[0], false);
    }
    if (cyclic_timer == 25) {
        if (ctx->is_half_water) play_audio(&ctx->sounds.water_footstep[1], false);
        else play_audio(&ctx->sounds.footstep[1], false);
    }
}

void change_animals_sprite(Context* ctx) {
    int quarter = get_quarter_from_timer(ctx->timer);
    quarter--;
    if (quarter == 3) quarter = 1;

    for (int i = 0; i < ANIMALS_LENGTH; i++) {
        Animal* a = &ctx->animals[i];
        int random = rand() % 150;

        if (a->is_moving) {
            a->move(a); 
        } else if (random == 0) {
            a->sort_destination(a);
            a->is_moving = true;
            if (a->type == SNAKE) stop_audio(&ctx->sounds.panting);
        }

        if (a->type == SNAKE && !ctx->is_snake_idle) {
            Coordinate player_top_left = {ctx->player.x, ctx->player.y};
            Coordinate player_top_right = {ctx->player.x + PLAYER_WIDTH, ctx->player.y};
            Coordinate player_bottom_left = {ctx->player.x, ctx->player.y + PLAYER_HEIGHT};
            Coordinate player_bottom_right = {ctx->player.x + PLAYER_WIDTH, ctx->player.y + PLAYER_HEIGHT};
            float x1 = a->position.x - 100,
                  x2 = a->position.x + 153,
                  y1 = a->position.y - 100,
                  y2 = a->position.y + 153;
        
            bool is_player_near_animal =
                 check_collision(&player_top_left, x1, x2, y1, y2) ||
                 check_collision(&player_top_right, x1, x2, y1, y2) ||
                 check_collision(&player_bottom_left, x1, x2, y1, y2) ||
                 check_collision(&player_bottom_right, x1, x2, y1, y2);
          
            if (is_player_near_animal) {
                a->destination.x = ctx->player.x;
                a->destination.y = ctx->player.y;
                a->is_moving = true;
                if (!ctx->is_snake_hunting && !ctx->sounds_muted) {
                    stop_audio(&ctx->sounds.panting);
                    play_audio(&ctx->sounds.panting, true);
                }
                ctx->is_snake_hunting = true;
            } else {
                ctx->is_snake_hunting = false;
            }

            if (a->type == SNAKE && check_collision(&ctx->player, a->position.x, a->position.x + 10, a->position.y, a->position.y + 10)) {
                ctx->life_counter--;
                if (!ctx->sounds_muted) play_audio(&ctx->sounds.hurting, false);
                ctx->is_snake_idle = true;
                ctx->is_snake_hunting = false;
            }
        }

        if (a->type == SNAKE && ctx->is_snake_idle) {
            a->destination.x = -MAP_SIZE;
            a->destination.y = MAP_SIZE;
            a->is_moving = true;
        }

        int horizontal = a->destination.x - a->position.x,
            vertical = a->destination.y - a->position.y;
        bool right = horizontal > 0, down = vertical > 0;

        if (horizontal < 0) horizontal *= -1;
        if (vertical < 0) vertical *= -1;

        if (a->type == BIRD) {
            if (right) a->current_sprite = ctx->imgs.animals[a->type].right[quarter];
            if (!right) a->current_sprite = ctx->imgs.animals[a->type].left[quarter];
        } else {
            if (horizontal < vertical && down) a->current_sprite = ctx->imgs.animals[a->type].front[quarter];
            if (horizontal < vertical && !down) a->current_sprite = ctx->imgs.animals[a->type].back[quarter];
            if (horizontal > vertical && right) a->current_sprite = ctx->imgs.animals[a->type].right[quarter];
            if (horizontal > vertical && !right) a->current_sprite = ctx->imgs.animals[a->type].left[quarter];
            if (!a->is_moving) a->current_sprite = ctx->imgs.animals[a->type].front[0];
        }
    }
}

void play_animal_sounds(Context* ctx) {
    if (ctx->sounds_muted) return;

    int frame = al_get_timer_count(ctx->timer) % (FPS * ctx->animal_sound_interval);
    if (frame != 0) return;

    ctx->animal_sound_interval = rand() % 7 + 4;
    int animal = rand() % ANIMAL_TYPE_LENGTH;
    int sound = rand() % ANIMAL_SOUNDS_LENGTH; 
    float volume, pan;
    int max_distance;

    if (animal == RABBIT) return;

    int player_x = (ctx->map.x * -1) + ctx->player.x;
    int player_y = (ctx->map.y * -1) + ctx->player.y;
    int distance_from_player_x = player_x - ctx->animals[animal].position.x;
    int distance_from_player_y = player_y - ctx->animals[animal].position.y;
    if (distance_from_player_x < 0) distance_from_player_x *= -1;
    if (distance_from_player_y < 0) distance_from_player_y *= -1;
    if (distance_from_player_x > distance_from_player_y) {
        max_distance = distance_from_player_x;
    } else {
        max_distance = distance_from_player_y;
    }

    if (max_distance == 0) max_distance = 1;
    volume = 1.0 / (max_distance / 200.0);

    if (player_x > ctx->animals[animal].position.x) {
        pan = 0.5;
    } else {
        pan = -0.5;
    }

    set_audio(&ctx->sounds.animals[animal][sound], volume, pan, 1);
    play_audio(&ctx->sounds.animals[animal][sound], false);
}

void finish_challenge(bool success, Context* ctx) {
    if (ctx->challenge_index == 1 && success && ctx->life_counter < 3) ctx->life_counter++;

    if (ctx->challenge_index == 2 && !success) ctx->is_user_hallucinated = true;
    if (ctx->challenge_index == 3 && success) ctx->is_user_hallucinated = false;

    if (ctx->challenge_index == 4) {
        if (success) {
            al_draw_bitmap(ctx->imgs.c5_bonfire, 0, 0, 0);
            al_flip_display();
            al_rest(2);
            ctx->state = GAME_OVER;
            al_stop_samples();
            al_start_video(ctx->videos.rescue, al_get_default_mixer());
        } else {
            ctx->c5.bonfire_scene = false;
            ctx->c5.start_time = time(0);
            ctx->c5.action_bar = 1200;
        }
        return;
    }

    if (!success || ctx->hunger_counter == 0) {
        ctx->life_counter--;
        if (!ctx->sounds_muted) play_audio(&ctx->sounds.hurting, false);
        al_rest(1);
    }

    if (ctx->life_counter <= 0) {
        ctx->state = GAME_OVER;
        ctx->has_user_lost = true;
        al_stop_samples();
        return;
    }

    bool player_got_food = success && (ctx->challenge_index == 0 || ctx->challenge_index == 2);
    if (player_got_food) {
      ctx->hunger_counter = 3;
    } else if (ctx->hunger_counter > 0) {
        ctx->hunger_counter--;
    }

    stop_audio(&ctx->sounds.challenges[ctx->challenge_index]);
    if (!ctx->sounds_muted) al_set_video_playing(ctx->videos.island, true);
    if (ctx->challenge_index <= 3) ctx->challenge_index++;
    ctx->state = OPEN_MAP;
}

void play_tutorial(Context* ctx) {
    Tutorial* t = &ctx->tutorials[ctx->challenge_index];
    ALLEGRO_VIDEO* current_video = ctx->videos.tutorials[ctx->tutorial_index];
    ALLEGRO_VIDEO* next_video = ctx->videos.tutorials[ctx->tutorial_index + 1];

    ALLEGRO_BITMAP* frame = al_get_video_frame(current_video);
    if (frame) ctx->imgs.current_video_frame = frame;
    
    if (!al_is_video_playing(current_video) && ctx->tutorial_index % 2 != 0) {
        if (ctx->tutorial_index == t->last_step_index) {
            t->is_completed = true;
            Audio* audio = &ctx->sounds.challenges[ctx->challenge_index];
            if (!ctx->sounds_muted) play_audio(audio, true);
        } else {
            al_start_video(next_video, al_get_default_mixer());
            if (!ctx->sounds_muted) play_audio(&ctx->sounds.typing, false);
        }
        ctx->tutorial_index++;
    }
}

void change_hallucination_angle(Context* ctx) {
    ctx->hallucination_angle += 0.1;
    if (ctx->hallucination_angle >= 360) ctx->hallucination_angle = 0;
    ctx->hallucination_map_x = (float)sin((double)ctx->hallucination_angle) * 20;
    ctx->hallucination_map_y = (float)cos((double)ctx->hallucination_angle) * 20;
    ctx->hallucination_char_x = (float)sin((double)ctx->hallucination_angle * -1) * 10;
    ctx->hallucination_char_y = (float)cos((double)ctx->hallucination_angle * -1) * 10;
}

void handle_challenge_1(Context* ctx, Coordinate* mouse) {
    Challenge_1* c1 = &ctx->c1;

    // Seleciona o objeto clicado e retorna
    for (int i = 0; i < PLACEABLE_OBJECTS_LENGTH; i++) {
        int pos_i = c1->placeable_objects[i].position_index;
        float x = c1->placeable_positions[pos_i].x,
              y = c1->placeable_positions[pos_i].y,
              w = c1->placeable_objects[i].width,
              h = c1->placeable_objects[i].height;

        if (check_collision(mouse, x, x + w, y, y + h)) {
            c1->selected_object_index = i;
            return;
        }
    }

    // Move o objeto selecionado para a posição clicada
    for (int i = 0; i < PLACEABLE_POSITIONS_LENGTH; i++) {
        float x = c1->placeable_positions[i].x,
              y = c1->placeable_positions[i].y,
              w = PLACEABLE_POSITION_WIDTH,
              h = PLACEABLE_POSITION_HEIGHT;

        if (check_collision(mouse, x, x + w, y, y + h)) {
            c1->placeable_objects[c1->selected_object_index].position_index = i;
            c1->selected_object_index = -1;
            return;
        }
    }

    if (c1->selected_object_index != -1) c1->selected_object_index = -1;

    // Verifica se o jogador conseguiu completar o desafio
    float x1 = CHALLENGE_NEXT_BTN_X,
          x2 = CHALLENGE_NEXT_BTN_X + BUTTON_WIDTH,
          y1 = CHALLENGE_NEXT_BTN_Y,
          y2 = CHALLENGE_NEXT_BTN_Y + BUTTON_HEIGHT;

    if (check_collision(mouse, x1, x2, y1, y2)) {
        bool success = true;
        for (int i = 0; i < PLACEABLE_OBJECTS_LENGTH; i++) {
            Placeable_Object* obj = &c1->placeable_objects[i];
            if (obj->position_index != obj->correct_position_index) {
                success = false;
                break;
            }
        }
        finish_challenge(success, ctx);
    }
}

void handle_challenge_2(Context* ctx, Coordinate* mouse) {
    Challenge_2* c2 = &ctx->c2;

    // Seleciona ou desmarca os objetos clicados
    for (int i = 0; i < SELECTABLE_OBJECTS_LENGTH_C2; i++) {
        Selectable_Object* obj = &c2->selectable_objects[i];
        if (check_collision(mouse, obj->position.x, obj->position.x + obj->width, obj->position.y, obj->position.y + obj->height)) {
            obj->selected = !obj->selected;
        }
    }

    // Verifica se o jogador conseguiu completar o desafio
    float x1 = CHALLENGE_NEXT_BTN_X,
          x2 = CHALLENGE_NEXT_BTN_X + BUTTON_WIDTH,
          y1 = CHALLENGE_NEXT_BTN_Y,
          y2 = CHALLENGE_NEXT_BTN_Y + BUTTON_HEIGHT;
    if (check_collision(mouse, x1, x2, y1, y2)) {
        for (int i = 0; i < 7; i++) {
            Selectable_Object* obj = &c2->selectable_objects[i];
            if ((obj->selected && !obj->correct) || (!obj->selected && obj->correct)) {
                finish_challenge(false, ctx);
                break;
            }
        }
        c2->is_distillation_playing = true;
        al_start_video(ctx->videos.c2_distillation, al_get_default_mixer());
    }
}

void handle_challenge_3(Context* ctx) {
    Challenge_3* c3 = &ctx->c3;

    // Move os objetos e verifica se o jogador pegou algum
    for (int i = 0; i < FALLING_OBJECTS_LENGTH; i++) {
        Falling_Object* obj = &c3->falling_objects[i];
        int w = FALLING_OBJECT_WIDTH,
            h = FALLING_OBJECT_HEIGHT;

        obj->position.y += obj->speed;
        obj->speed += FALLING_ACCELERATION;

        if (obj->position.y >= c3->player_position.y && 
            (obj->position.x >= c3->player_position.x && obj->position.x <= c3->player_position.x + 100 ||
            obj->position.x + w >= c3->player_position.x && obj->position.x + w <= c3->player_position.x + 100)) {
            if (obj->id == 0) {
                c3->apples_counter++;
            } else {
                c3->mushrooms_counter++;
            }
            
            generate_random_falling_object(obj);
        }

        if (obj->position.y > DISPLAY_HEIGHT) generate_random_falling_object(obj);
    }

    // Verifica se o jogador conseguiu completar o desafio
    if (c3->mushrooms_counter >= 10) {
        return finish_challenge(false, ctx);
    }
    if (c3->apples_counter >= 20) {
        return finish_challenge(true, ctx);
    }
}

void move_character_sideways(Context* ctx) {
    switch (ctx->event.keyboard.keycode) {
    case ALLEGRO_KEY_LEFT:
    case ALLEGRO_KEY_A:
        ctx->c3.player_position.x -= 150;
        if (ctx->c3.player_position.x <= 0) ctx->c3.player_position.x += 150;
        break;
    case ALLEGRO_KEY_RIGHT:
    case ALLEGRO_KEY_D:
        ctx->c3.player_position.x += 150;
        if (ctx->c3.player_position.x + 100 >= DISPLAY_WIDTH) ctx->c3.player_position.x -= 150;
        break;
    }
} 

void handle_challenge_4(Context* ctx, Coordinate* mouse) {
    Challenge_4* c4 = &ctx->c4;

    // Seleciona os objetos clicados
    for (int i = 0; i < WANTED_OBJECTS_LENGTH; i++) {
        Wanted_Object* obj = &c4->wanted_objects[i];
        Wanted_Object* fake_obj = &c4->fake_wanted_objects[i];
        int w = obj->width, h = obj->height;

        if (check_collision(mouse, obj->position.x, obj->position.x + w, obj->position.y, obj->position.y + h)) {
            obj->selected = true;
        }

        if (check_collision(mouse, fake_obj->position.x, fake_obj->position.x + w, fake_obj->position.y, fake_obj->position.y + h)) {
            fake_obj->selected = true;
        }
    }
}

void verify_challenge_4(Context* ctx) {
    Challenge_4* c4 = &ctx->c4;

    // Verifica se o jogador conseguiu completar o desafio
    bool success = true;
    for (int i = 0; i < WANTED_OBJECTS_LENGTH; i++) {
        if (!c4->wanted_objects[i].selected) {
            success = false;
            break;
        }
    }

    time_t current_time = time(NULL);
    bool time_is_up = current_time - c4->start_time >= c4->duration_in_seconds;
    
    if (time_is_up || success) finish_challenge(success, ctx);
}

void handle_challenge_5(Context* ctx, Coordinate* mouse) {
    Challenge_5* c5 = &ctx->c5;

    // Seleciona ou desmarca os objetos clicados
    for (int i = 0; i < SELECTABLE_OBJECTS_LENGTH_C5; i++) {
        Selectable_Object* obj = &c5->selectable_objects[i];

        if (check_collision(mouse, obj->position.x, obj->position.x + obj->width, obj->position.y, obj->position.y + obj->height)) {
            obj->selected = !obj->selected;
        }
    }
    
    // Verifica se o jogador conseguiu completar o desafio
    float x1 = CHALLENGE_NEXT_BTN_X,
          x2 = CHALLENGE_NEXT_BTN_X + BUTTON_WIDTH,
          y1 = CHALLENGE_NEXT_BTN_Y,
          y2 = CHALLENGE_NEXT_BTN_Y + BUTTON_HEIGHT;
    if (check_collision(mouse, x1, x2, y1, y2)) {
        ctx->c5.correct_objects = true;
        for (int i = 0; i < SELECTABLE_OBJECTS_LENGTH_C5; i++) {
            Selectable_Object* obj = &c5->selectable_objects[i];
            if ((obj->selected && !obj->correct) || (!obj->selected && obj->correct)) {
                ctx->c5.correct_objects = false;
                break;
            }
        }
        ctx->c5.bonfire_scene = true;
        ctx->c5.start_time = time(0);
    }
}

void rub_bonfire(Context* ctx) {
    Challenge_5* c5 = &ctx->c5;

    if (!c5->bonfire_scene) return;

    if (ctx->event.keyboard.keycode == ALLEGRO_KEY_SPACE) {
        c5->action_bar += 70;
        c5->rub_sprite_index++;
        if (c5->rub_sprite_index > 3) c5->rub_sprite_index = 0;
    }
}

void verify_challenge_5(Context* ctx) {
    Challenge_5* c5 = &ctx->c5;

    if (!c5->bonfire_scene) return;

    c5->action_bar -= 20;

    if (c5->action_bar <= 0) {
        finish_challenge(false, ctx);
        return;
    }

    time_t now = time(0);
    if (now - c5->start_time >= c5->duration_in_seconds) {
        finish_challenge(c5->correct_objects, ctx);
    }
}
