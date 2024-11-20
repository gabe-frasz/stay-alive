#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_video.h>
#include <allegro5/keycodes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "types.h"
#include "consts.h"
#include "helpers.h"

void set_context_to_default(Context* ctx) {
    ctx->imgs.char_sprites.current = ctx->imgs.char_sprites.front[0];
    ctx->player.x = DISPLAY_WIDTH/2.0 - PLAYER_WIDTH/2;
    ctx->player.y = DISPLAY_HEIGHT/2.0 - PLAYER_HEIGHT/2;
    ctx->map.x = INITIAL_MAP_X;
    ctx->map.y = INITIAL_MAP_Y;

    ctx->tutorials[0].last_step_index = 1;
    ctx->tutorials[1].last_step_index = 5;
    ctx->tutorials[2].last_step_index = 7;
    ctx->tutorials[3].last_step_index = 13;
    ctx->tutorials[4].last_step_index = 15;

    for (int i = 0; i < 5; i++) {
        ctx->tutorials[i].is_completed = false;
    }

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

    ctx->c4.duration_in_seconds = 10;
    ctx->c4.start_time = -1;

    for (int i = 0; i < WANTED_OBJECTS_LENGTH; i++) {
        ctx->c4.wanted_objects[i].selected = false;
        ctx->c4.fake_wanted_objects[i].selected = false;
    }

    ctx->c5.bonfire_scene = false;
    ctx->c5.correct_objects = false;
    ctx->c5.action_bar = 1280;
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
    ctx->challenge_index = 0; // 0 até 4
    ctx->tutorial_index = 0; 
    ctx->life_counter = 3; // 3 até 0
    ctx->hunger_counter = 3; // 3 até 0
    ctx->oxygen_counter = 3; // 3 até 0
    ctx->oxygen_start_time = -1;
    ctx->state = MENU;
    ctx->redraw = true;
    ctx->done = false;

    // Animais
    ctx->animals[0].type = BIRD;
    ctx->animals[1].type = BIRD;
    ctx->animals[2].type = RABBIT;
    ctx->animals[3].type = RABBIT;
    ctx->animals[4].type = GOAT;
    ctx->animals[5].type = SHEEP;
    ctx->animals[6].type = CAT;
    ctx->animals[7].type = SNAKE;

    for (int i = 0; i < ANIMALS_LENGTH; i++) {
        ctx->animals[i].is_moving = false;
        ctx->animals[i].move = &move_animal;
        ctx->animals[i].sort_destination = &sort_destination;
        ctx->animals[i].birds_count = 0;
        ctx->animals[i].bounds.x1 = 0;
        ctx->animals[i].bounds.x2 = DISPLAY_WIDTH;
        ctx->animals[i].bounds.y1 = 0;
        ctx->animals[i].bounds.y2 = DISPLAY_HEIGHT;
        
        switch (ctx->animals[i].type) {
        case BIRD:
            ctx->animals[i].position.x = -MAP_SIZE;
            ctx->animals[i].position.y = rand() % MAP_SIZE;
            ctx->animals[i].speed = 20;
            ctx->animals[i].width = 25;
            ctx->animals[i].height = 25;
            break;
        case RABBIT:
            ctx->animals[i].position.x = 1100;
            ctx->animals[i].position.y = 1300;
            ctx->animals[i].speed = 6;
            ctx->animals[i].width = 25;
            ctx->animals[i].height = 25;
            ctx->animals[i].bounds.x1 = 800;
            ctx->animals[i].bounds.x2 = 1400;
            ctx->animals[i].bounds.y1 = 1000;
            ctx->animals[i].bounds.y2 = 1600;
            break;
        case GOAT:
            ctx->animals[i].position.x = 1000;
            ctx->animals[i].position.y = -150;
            ctx->animals[i].speed = 7;
            ctx->animals[i].width = 50;
            ctx->animals[i].height = 50;
            ctx->animals[i].bounds.x1 = 1000;
            ctx->animals[i].bounds.x2 = 1100;
            ctx->animals[i].bounds.y1 = -200;
            ctx->animals[i].bounds.y2 = 300;
            break;
        case SHEEP:
            ctx->animals[i].position.x = 1000;
            ctx->animals[i].position.y = -200;
            ctx->animals[i].speed = 3;
            ctx->animals[i].width = 50;
            ctx->animals[i].height = 50;
            ctx->animals[i].bounds.x1 = 1000;
            ctx->animals[i].bounds.x2 = 1100;
            ctx->animals[i].bounds.y1 = -200;
            ctx->animals[i].bounds.y2 = 300;
            break;
        case CAT:
            ctx->animals[i].position.x = 1100;
            ctx->animals[i].position.y = 1300;
            ctx->animals[i].speed = 3;
            ctx->animals[i].width = 25;
            ctx->animals[i].height = 25;
            ctx->animals[i].bounds.x1 = 800;
            ctx->animals[i].bounds.x2 = 1400;
            ctx->animals[i].bounds.y1 = 1000;
            ctx->animals[i].bounds.y2 = 1600;
            break;
        case SNAKE:
            ctx->animals[i].position.x = 0;
            ctx->animals[i].position.y = 1600;
            ctx->animals[i].speed = 3;
            ctx->animals[i].width = 25;
            ctx->animals[i].height = 25;
            ctx->animals[i].bounds.x1 = -500;
            ctx->animals[i].bounds.x2 = 500;
            ctx->animals[i].bounds.y1 = 1500;
            ctx->animals[i].bounds.y2 = 2400;
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

    // Obstaculos
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

    ctx->shallow_water_areas[0].x1 = INITIAL_MAP_X;
    ctx->shallow_water_areas[0].x2 = INITIAL_MAP_X + 750;
    ctx->shallow_water_areas[0].y1 = INITIAL_MAP_Y;
    ctx->shallow_water_areas[0].y2 = INITIAL_MAP_Y + 500;
    ctx->shallow_water_areas[1].x1 = INITIAL_MAP_X + 750;
    ctx->shallow_water_areas[1].x2 = INITIAL_MAP_X + 1125;
    ctx->shallow_water_areas[1].y1 = INITIAL_MAP_Y;
    ctx->shallow_water_areas[1].y2 = INITIAL_MAP_Y + 180;
    ctx->shallow_water_areas[2].x1 = INITIAL_MAP_X;
    ctx->shallow_water_areas[2].x2 = INITIAL_MAP_X + 100;
    ctx->shallow_water_areas[2].y1 = INITIAL_MAP_Y + 500;
    ctx->shallow_water_areas[2].y2 = INITIAL_MAP_Y + 1270;
    ctx->shallow_water_areas[3].x1 = INITIAL_MAP_X + 750;
    ctx->shallow_water_areas[3].x2 = INITIAL_MAP_X + 900;
    ctx->shallow_water_areas[3].y1 = INITIAL_MAP_Y + 180;
    ctx->shallow_water_areas[3].y2 = INITIAL_MAP_Y + 330;
    ctx->shallow_water_areas[4].x1 = INITIAL_MAP_X + 100;
    ctx->shallow_water_areas[4].x2 = INITIAL_MAP_X + 500;
    ctx->shallow_water_areas[4].y1 = INITIAL_MAP_Y + 500;
    ctx->shallow_water_areas[4].y2 = INITIAL_MAP_Y + 600;
    ctx->shallow_water_areas[5].x1 = INITIAL_MAP_X + 100;
    ctx->shallow_water_areas[5].x2 = INITIAL_MAP_X + 270;
    ctx->shallow_water_areas[5].y1 = INITIAL_MAP_Y + 1150;
    ctx->shallow_water_areas[5].y2 = INITIAL_MAP_Y + 1270;

    ctx->deep_water_area.x1 = INITIAL_MAP_X;
    ctx->deep_water_area.x2 = INITIAL_MAP_X + 550;
    ctx->deep_water_area.y1 = INITIAL_MAP_Y;
    ctx->deep_water_area.y2 = INITIAL_MAP_Y + 300;
}

void init_context(Context* ctx) {
    must_init(al_init(), "allegro");
    must_init(al_init_primitives_addon(), "primitives");
    must_init(al_install_keyboard(), "keyboard");
    must_init(al_install_mouse(), "mouse");
    must_init(al_init_image_addon(), "image");
    must_init(al_install_audio(), "audio");
    must_init(al_init_acodec_addon(), "acodec");
    must_init(al_reserve_samples(5), "samples");
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

    ctx->challenges_areas[0].x1 = DISPLAY_WIDTH - 280;
    ctx->challenges_areas[0].x2 = DISPLAY_WIDTH - 80;
    ctx->challenges_areas[0].y1 = 0;
    ctx->challenges_areas[0].y2 = 15;
    ctx->challenges_areas[1].x1 = DISPLAY_WIDTH - 15;
    ctx->challenges_areas[1].x2 = DISPLAY_WIDTH;
    ctx->challenges_areas[1].y1 = DISPLAY_HEIGHT/2.0 - 100;
    ctx->challenges_areas[1].y2 = DISPLAY_HEIGHT/2.0 + 100;
    ctx->challenges_areas[2].x1 = DISPLAY_WIDTH - 15;
    ctx->challenges_areas[2].x2 = DISPLAY_WIDTH;
    ctx->challenges_areas[2].y1 = DISPLAY_HEIGHT/2.0 - 100;
    ctx->challenges_areas[2].y2 = DISPLAY_HEIGHT/2.0 + 100;
    ctx->challenges_areas[3].x1 = DISPLAY_WIDTH - 680;
    ctx->challenges_areas[3].x2 = DISPLAY_WIDTH - 410;
    ctx->challenges_areas[3].y1 = DISPLAY_HEIGHT - 15;
    ctx->challenges_areas[3].y2 = DISPLAY_HEIGHT;
    ctx->challenges_areas[4].x1 = DISPLAY_WIDTH - 680;
    ctx->challenges_areas[4].x2 = DISPLAY_WIDTH - 410;
    ctx->challenges_areas[4].y1 = DISPLAY_HEIGHT - 15;
    ctx->challenges_areas[4].y2 = DISPLAY_HEIGHT;

    // Challenge 1
    ctx->c1.placeable_positions[0].x = 150;
    ctx->c1.placeable_positions[0].y = 0;
    ctx->c1.placeable_positions[1].x = 100;
    ctx->c1.placeable_positions[1].y = 490;
    ctx->c1.placeable_positions[2].x = 450;
    ctx->c1.placeable_positions[2].y = 0;
    ctx->c1.placeable_positions[3].x = 380;
    ctx->c1.placeable_positions[3].y = 370;
    ctx->c1.placeable_positions[4].x = 0;
    ctx->c1.placeable_positions[4].y = 0;
    ctx->c1.placeable_positions[5].x = 650;
    ctx->c1.placeable_positions[5].y = 250;
    ctx->c1.placeable_positions[6].x = 300;
    ctx->c1.placeable_positions[6].y = 0;
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
    ctx->c1.selected_object_index = -1;

    // Challenge 2
    ctx->c2.selectable_objects[0].position.x = 640;
    ctx->c2.selectable_objects[0].position.y = 340;
    ctx->c2.selectable_objects[0].width = 101;
    ctx->c2.selectable_objects[0].height = 180;
    ctx->c2.selectable_objects[1].position.x = 475;
    ctx->c2.selectable_objects[1].position.y = 350;
    ctx->c2.selectable_objects[1].width = 118;
    ctx->c2.selectable_objects[1].height = 99;
    ctx->c2.selectable_objects[2].position.x = 690;
    ctx->c2.selectable_objects[2].position.y = 570;
    ctx->c2.selectable_objects[2].width = 100;
    ctx->c2.selectable_objects[2].height = 144;
    ctx->c2.selectable_objects[3].position.x = 745;
    ctx->c2.selectable_objects[3].position.y = 380;
    ctx->c2.selectable_objects[3].width = 101;
    ctx->c2.selectable_objects[3].height = 180;
    ctx->c2.selectable_objects[4].position.x = 890;
    ctx->c2.selectable_objects[4].position.y = 400;
    ctx->c2.selectable_objects[4].width = 145;
    ctx->c2.selectable_objects[4].height = 99;
    ctx->c2.selectable_objects[5].position.x = 550;
    ctx->c2.selectable_objects[5].position.y = 570;
    ctx->c2.selectable_objects[5].width = 120;
    ctx->c2.selectable_objects[5].height = 99;
    ctx->c2.selectable_objects[6].position.x = 900;
    ctx->c2.selectable_objects[6].position.y = 540;
    ctx->c2.selectable_objects[6].width = 102;
    ctx->c2.selectable_objects[6].height = 80;
    
    // Challenge 4
    ctx->c4.wanted_objects[0].position.x = 100;
    ctx->c4.wanted_objects[0].position.y = 100;
    ctx->c4.wanted_objects[1].position.x = 410;
    ctx->c4.wanted_objects[1].position.y = 300;
    ctx->c4.wanted_objects[2].position.x = 590;
    ctx->c4.wanted_objects[2].position.y = 490;
    ctx->c4.wanted_objects[3].position.x = 900;
    ctx->c4.wanted_objects[3].position.y = 270;
    ctx->c4.wanted_objects[4].position.x = 1150;
    ctx->c4.wanted_objects[4].position.y = 570;
    ctx->c4.fake_wanted_objects[0].position.x = 260;
    ctx->c4.fake_wanted_objects[0].position.y = 600;
    ctx->c4.fake_wanted_objects[1].position.x = 1160;
    ctx->c4.fake_wanted_objects[1].position.y = 0;
    ctx->c4.fake_wanted_objects[2].position.x = 630;
    ctx->c4.fake_wanted_objects[2].position.y = 330;
    ctx->c4.fake_wanted_objects[3].position.x = 0;
    ctx->c4.fake_wanted_objects[3].position.y = 480;
    ctx->c4.fake_wanted_objects[4].position.x = 770;
    ctx->c4.fake_wanted_objects[4].position.y = 30;

    // Challenge 5
    ctx->c5.duration_in_seconds = 10;
    ctx->c5.selectable_objects[0].position.x = 640;
    ctx->c5.selectable_objects[0].position.y = 340;
    ctx->c5.selectable_objects[0].width = 101;
    ctx->c5.selectable_objects[0].height = 180;
    ctx->c5.selectable_objects[0].correct = true;
    ctx->c5.selectable_objects[1].position.x = 475;
    ctx->c5.selectable_objects[1].position.y = 350;
    ctx->c5.selectable_objects[1].width = 118;
    ctx->c5.selectable_objects[1].height = 99;
    ctx->c5.selectable_objects[1].correct = true;
    ctx->c5.selectable_objects[2].position.x = 690;
    ctx->c5.selectable_objects[2].position.y = 570;
    ctx->c5.selectable_objects[2].width = 100;
    ctx->c5.selectable_objects[2].height = 144;
    ctx->c5.selectable_objects[2].correct = false;
    ctx->c5.selectable_objects[3].position.x = 745;
    ctx->c5.selectable_objects[3].position.y = 380;
    ctx->c5.selectable_objects[3].width = 101;
    ctx->c5.selectable_objects[3].height = 180;
    ctx->c5.selectable_objects[3].correct = false;
    ctx->c5.selectable_objects[4].position.x = 890;
    ctx->c5.selectable_objects[4].position.y = 400;
    ctx->c5.selectable_objects[4].width = 145;
    ctx->c5.selectable_objects[4].height = 99;
    ctx->c5.selectable_objects[4].correct = false;
    ctx->c5.selectable_objects[5].position.x = 550;
    ctx->c5.selectable_objects[5].position.y = 570;
    ctx->c5.selectable_objects[5].width = 120;
    ctx->c5.selectable_objects[5].height = 99;
    ctx->c5.selectable_objects[5].correct = false;
    ctx->c5.selectable_objects[6].position.x = 300;
    ctx->c5.selectable_objects[6].position.y = 540;
    ctx->c5.selectable_objects[6].width = 102;
    ctx->c5.selectable_objects[6].height = 80;
    ctx->c5.selectable_objects[6].correct = false;
    ctx->c5.selectable_objects[7].position.x = 130;
    ctx->c5.selectable_objects[7].position.y = 330;
    ctx->c5.selectable_objects[7].width = 120;
    ctx->c5.selectable_objects[7].height = 99;
    ctx->c5.selectable_objects[7].correct = false;

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
                hide = a->position.x <= a->bounds.x2 - 150 && a->position.y >= a->bounds.y1 + 300;
                break;
            case GOAT:
            case SHEEP:
            case BIRD:
            default:
                break;
            }

            if (!hide) al_draw_bitmap(a->current_sprite, a->position.x, a->position.y, 0);
        }

        al_draw_bitmap(ctx->imgs.char_sprites.current, ctx->player.x, ctx->player.y, 0);

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
            ALLEGRO_VIDEO* video = ctx->videos.tutorials[ctx->tutorial_index];
            ALLEGRO_BITMAP* frame = al_get_video_frame(video);
            if (frame) al_draw_bitmap(frame, 0, 0, 0);
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
                      w = WANTED_OBJECT_WIDTH,
                      h = WANTED_OBJECT_HEIGHT;
                    
                if (obj->selected) {
                    al_draw_rounded_rectangle(x - 5, y - 5, x + w + 5, y + h + 5, 5, 5, al_map_rgb(255, 255, 255), 2);
                }

                ALLEGRO_BITMAP* img = ctx->imgs.medicinal_plants[i];
                al_draw_bitmap(img, obj->position.x, obj->position.y, 0);
            }

            int seconds_left = calculate_seconds_left(ctx->c4.start_time, ctx->c4.duration_in_seconds);
            al_draw_textf(ctx->font, al_map_rgb(255, 255, 255), 0, 20, 0, "Tempo: %d segundos", seconds_left);
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

void finish_challenge(bool success, Context* ctx) {
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

    if (ctx->challenge_index == 1 && success && ctx->life_counter < 3) ctx->life_counter++;

    if (ctx->challenge_index == 4) {
        if (success) {
            al_stop_samples();
            al_draw_bitmap(ctx->imgs.c5_bonfire, 0, 0, 0);
            al_flip_display();
            al_rest(2);
            ctx->state = GAME_OVER;
            al_start_video(ctx->videos.rescue, al_get_default_mixer());
        } else {
            ctx->c5.bonfire_scene = false;
            ctx->c5.start_time = time(0);
            ctx->c5.action_bar = 1200;
        }
        return;
    }

    bool player_got_food = success && (ctx->challenge_index == 0 || ctx->challenge_index == 2);
    if (player_got_food) {
      ctx->hunger_counter = 3;
    } else if (ctx->hunger_counter > 0) {
        ctx->hunger_counter--;
    }

    if (ctx->challenge_index == 2 && !success) ctx->is_user_hallucinated = true;

    if (ctx->challenge_index <= 3) {
        ctx->challenge_index++;
    }

    ctx->state = OPEN_MAP;
    al_stop_samples();
}

void play_tutorial(Context* ctx) {
    Tutorial* t = &ctx->tutorials[ctx->challenge_index];
    ALLEGRO_VIDEO* current_video = ctx->videos.tutorials[ctx->tutorial_index];
    ALLEGRO_VIDEO* next_video = ctx->videos.tutorials[ctx->tutorial_index + 1];

    ctx->imgs.current_video_frame = al_get_video_frame(current_video);
    
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

void play_video(Context* ctx, ALLEGRO_VIDEO* video) {
    ctx->imgs.current_video_frame = al_get_video_frame(video);
    if (!al_is_video_playing(video)) {
        ctx->c2.is_distillation_playing = false;
        al_rest(2);
        return finish_challenge(true, ctx);
    }
}

void handle_challenge_1(Context* ctx, Coordinate* mouse) {
    Challenge_1* c1 = &ctx->c1;
    int w = PLACEABLE_OBJECT_WIDTH,
        h = PLACEABLE_OBJECT_HEIGHT;

    // Seleciona o objeto clicado e retorna
    for (int i = 0; i < PLACEABLE_OBJECTS_LENGTH; i++) {
        int pos_i = c1->placeable_objects[i].position_index;
        float x = c1->placeable_positions[pos_i].x,
              y = c1->placeable_positions[pos_i].y;

        if (check_collision(mouse, x, x + w, y, y + h)) {
            c1->selected_object_index = i;
            return;
        }
    }

    // Move o objeto selecionado para a posição clicada
    for (int i = 0; i < PLACEABLE_POSITIONS_LENGTH; i++) {
        float x = c1->placeable_positions[i].x,
              y = c1->placeable_positions[i].y;

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
    if (c3->apples_counter >= 10) {
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
        int w = WANTED_OBJECT_WIDTH,
            h = WANTED_OBJECT_HEIGHT;

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
