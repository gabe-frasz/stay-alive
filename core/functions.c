#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "types.h"
#include "consts.h"

void must_init(bool test, char* description) {
    if (!test) {
        printf("Could not initialize %s.\n", description);
        exit(1);
    }
}

bool check_collision(Coordinate* c, float x1, float x2, float y1, float y2) {
    return c->x >= x1 && c->x <= x2 && c->y >= y1 && c->y <= y2;
}

void generate_random_falling_object(Falling_Object* obj) {
    obj->speed = 0;
    obj->position.y = (rand() % 150 + 50) * -1;
    obj->id = rand() % 2;

    if (obj->id == 0) {
        obj->position.x += rand() % 25;
    } else {
        obj->position.x -= rand() % 25;
    }
}

void load_images(Images* imgs) {
    imgs->map = al_load_bitmap("images/map.png");
    must_init(imgs->map, "map image");
    imgs->menu = al_load_bitmap("images/menu.jpg");
    must_init(imgs->menu, "menu image");
    imgs->end_game = al_load_bitmap("images/end_game.jpeg");
    must_init(imgs->end_game, "end game image");
    imgs->game_over = al_load_bitmap("images/game_over.jpeg");
    must_init(imgs->game_over, "game over image");
    imgs->challenges[0] = al_load_bitmap("images/challenge-1.jpeg");
    must_init(imgs->challenges[0], "challenge 1 image");
    imgs->challenges[1] = al_load_bitmap("images/challenge-2.png");
    must_init(imgs->challenges[1], "challenge 2 image");
    imgs->challenges[2] = al_load_bitmap("images/challenge-3.jpeg");
    must_init(imgs->challenges[2], "challenge 3 image");
    imgs->challenges[3] = al_load_bitmap("images/challenge-4.jpg");
    must_init(imgs->challenges[3], "challenge 4 image");
    imgs->challenges[4] = al_load_bitmap("images/challenge-3.jpeg");
    must_init(imgs->challenges[4], "challenge 5 image");
    imgs->play_btn = al_load_bitmap("images/play_btn.png");
    must_init(imgs->play_btn, "play button image");
    imgs->menu_btn = al_load_bitmap("images/menu_btn.png");
    must_init(imgs->play_btn, "menu button image");
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
    imgs->char_with_basket = al_load_bitmap("images/char_with_basket.png");
    must_init(imgs->char_with_basket, "char with basket image");
    imgs->heart_empty = al_load_bitmap("images/heart_empty.png");
    must_init(imgs->heart_empty, "heart empty image");
    imgs->heart_filled = al_load_bitmap("images/heart.png");
    must_init(imgs->heart_filled, "heart filled image");
    imgs->hunger_empty = al_load_bitmap("images/hunger_empty.png");
    must_init(imgs->hunger_empty, "hunger empty image");
    imgs->hunger_filled = al_load_bitmap("images/hunger.png");
    must_init(imgs->hunger_filled, "hunger filled image");
    imgs->bird_sprites.front[0] = al_load_bitmap("images/bird-front-1.png");
    must_init(imgs->bird_sprites.front[0], "bird front 1 image");
    imgs->bird_sprites.front[1] = al_load_bitmap("images/bird-front-2.png");
    must_init(imgs->bird_sprites.front[1], "bird front 2 image");
    imgs->bird_sprites.front[2] = al_load_bitmap("images/bird-front-3.png");
    must_init(imgs->bird_sprites.front[2], "bird front 3 image");
    imgs->bird_sprites.back[0] = al_load_bitmap("images/bird-back-1.png");
    must_init(imgs->bird_sprites.back[0], "bird back 1 image");
    imgs->bird_sprites.back[1] = al_load_bitmap("images/bird-back-2.png");
    must_init(imgs->bird_sprites.back[1], "bird back 2 image");
    imgs->bird_sprites.back[2] = al_load_bitmap("images/bird-back-3.png");
    must_init(imgs->bird_sprites.back[2], "bird back 3 image");
    imgs->bird_sprites.left[0] = al_load_bitmap("images/bird-left-1.png");
    must_init(imgs->bird_sprites.left[0], "bird left 1 image");
    imgs->bird_sprites.left[1] = al_load_bitmap("images/bird-left-2.png");
    must_init(imgs->bird_sprites.left[1], "bird left 2 image");
    imgs->bird_sprites.left[2] = al_load_bitmap("images/bird-left-3.png");
    must_init(imgs->bird_sprites.left[2], "bird left 3 image");
    imgs->bird_sprites.right[0] = al_load_bitmap("images/bird-right-1.png");
    must_init(imgs->bird_sprites.right[0], "bird right 1 image");
    imgs->bird_sprites.right[1] = al_load_bitmap("images/bird-right-2.png");
    must_init(imgs->bird_sprites.right[1], "bird right 2 image");
    imgs->bird_sprites.right[2] = al_load_bitmap("images/bird-right-3.png");
    must_init(imgs->bird_sprites.right[2], "bird right 3 image");
    imgs->rabbit_sprites.front[0] = al_load_bitmap("images/rabbit-front-1.png");
    must_init(imgs->rabbit_sprites.front[0], "rabbit front 1 image");
    imgs->rabbit_sprites.front[1] = al_load_bitmap("images/rabbit-front-2.png");
    must_init(imgs->rabbit_sprites.front[1], "rabbit front 2 image");
    imgs->rabbit_sprites.front[2] = al_load_bitmap("images/rabbit-front-3.png");
    must_init(imgs->rabbit_sprites.front[2], "rabbit front 3 image");
    imgs->rabbit_sprites.back[0] = al_load_bitmap("images/rabbit-back-1.png");
    must_init(imgs->rabbit_sprites.back[0], "rabbit back 1 image");
    imgs->rabbit_sprites.back[1] = al_load_bitmap("images/rabbit-back-2.png");
    must_init(imgs->rabbit_sprites.back[1], "rabbit back 2 image");
    imgs->rabbit_sprites.back[2] = al_load_bitmap("images/rabbit-back-3.png");
    must_init(imgs->rabbit_sprites.back[2], "rabbit back 3 image");
    imgs->rabbit_sprites.left[0] = al_load_bitmap("images/rabbit-left-1.png");
    must_init(imgs->rabbit_sprites.left[0], "rabbit left 1 image");
    imgs->rabbit_sprites.left[1] = al_load_bitmap("images/rabbit-left-2.png");
    must_init(imgs->rabbit_sprites.left[1], "rabbit left 2 image");
    imgs->rabbit_sprites.left[2] = al_load_bitmap("images/rabbit-left-3.png");
    must_init(imgs->rabbit_sprites.left[2], "rabbit left 3 image");
    imgs->rabbit_sprites.right[0] = al_load_bitmap("images/rabbit-right-1.png");
    must_init(imgs->rabbit_sprites.right[0], "rabbit right 1 image");
    imgs->rabbit_sprites.right[1] = al_load_bitmap("images/rabbit-right-2.png");
    must_init(imgs->rabbit_sprites.right[1], "rabbit right 2 image");
    imgs->rabbit_sprites.right[2] = al_load_bitmap("images/rabbit-right-3.png");
    must_init(imgs->rabbit_sprites.right[2], "rabbit right 3 image");
    imgs->goat_sprites.front[0] = al_load_bitmap("images/goat-front-1.png");
    must_init(imgs->goat_sprites.front[0], "goat front 1 image");
    imgs->goat_sprites.front[1] = al_load_bitmap("images/goat-front-2.png");
    must_init(imgs->goat_sprites.front[1], "goat front 2 image");
    imgs->goat_sprites.front[2] = al_load_bitmap("images/goat-front-3.png");
    must_init(imgs->goat_sprites.front[2], "goat front 3 image");
    imgs->goat_sprites.back[0] = al_load_bitmap("images/goat-back-1.png");
    must_init(imgs->goat_sprites.back[0], "goat back 1 image");
    imgs->goat_sprites.back[1] = al_load_bitmap("images/goat-back-2.png");
    must_init(imgs->goat_sprites.back[1], "goat back 2 image");
    imgs->goat_sprites.back[2] = al_load_bitmap("images/goat-back-3.png");
    must_init(imgs->goat_sprites.back[2], "goat back 3 image");
    imgs->goat_sprites.left[0] = al_load_bitmap("images/goat-left-1.png");
    must_init(imgs->goat_sprites.left[0], "goat left 1 image");
    imgs->goat_sprites.left[1] = al_load_bitmap("images/goat-left-2.png");
    must_init(imgs->goat_sprites.left[1], "goat left 2 image");
    imgs->goat_sprites.left[2] = al_load_bitmap("images/goat-left-3.png");
    must_init(imgs->goat_sprites.left[2], "goat left 3 image");
    imgs->goat_sprites.right[0] = al_load_bitmap("images/goat-right-1.png");
    must_init(imgs->goat_sprites.right[0], "goat right 1 image");
    imgs->goat_sprites.right[1] = al_load_bitmap("images/goat-right-2.png");
    must_init(imgs->goat_sprites.right[1], "goat right 2 image");
    imgs->goat_sprites.right[2] = al_load_bitmap("images/goat-right-3.png");
    must_init(imgs->goat_sprites.right[2], "goat right 3 image");
    imgs->sheep_sprites.front[0] = al_load_bitmap("images/sheep-front-1.png");
    must_init(imgs->sheep_sprites.front[0], "sheep front 1 image");
    imgs->sheep_sprites.front[1] = al_load_bitmap("images/sheep-front-2.png");
    must_init(imgs->sheep_sprites.front[1], "sheep front 2 image");
    imgs->sheep_sprites.front[2] = al_load_bitmap("images/sheep-front-3.png");
    must_init(imgs->sheep_sprites.front[2], "sheep front 3 image");
    imgs->sheep_sprites.back[0] = al_load_bitmap("images/sheep-back-1.png");
    must_init(imgs->sheep_sprites.back[0], "sheep back 1 image");
    imgs->sheep_sprites.back[1] = al_load_bitmap("images/sheep-back-2.png");    
    must_init(imgs->sheep_sprites.back[1], "sheep back 2 image");
    imgs->sheep_sprites.back[2] = al_load_bitmap("images/sheep-back-3.png");
    must_init(imgs->sheep_sprites.back[2], "sheep back 3 image");
    imgs->sheep_sprites.left[0] = al_load_bitmap("images/sheep-left-1.png");
    must_init(imgs->sheep_sprites.left[0], "sheep left 1 image");
    imgs->sheep_sprites.left[1] = al_load_bitmap("images/sheep-left-2.png");
    must_init(imgs->sheep_sprites.left[1], "sheep left 2 image");
    imgs->sheep_sprites.left[2] = al_load_bitmap("images/sheep-left-3.png");
    must_init(imgs->sheep_sprites.left[2], "sheep left 3 image");
    imgs->sheep_sprites.right[0] = al_load_bitmap("images/sheep-right-1.png");
    must_init(imgs->sheep_sprites.right[0], "sheep right 1 image");
    imgs->sheep_sprites.right[1] = al_load_bitmap("images/sheep-right-2.png");
    must_init(imgs->sheep_sprites.right[1], "sheep right 2 image");
    imgs->sheep_sprites.right[2] = al_load_bitmap("images/sheep-right-3.png");
    must_init(imgs->sheep_sprites.right[2], "sheep right 3 image");
    imgs->cat_sprites.front[0] = al_load_bitmap("images/cat-front-1.png");
    must_init(imgs->cat_sprites.front[0], "cat front 1 image");
    imgs->cat_sprites.front[1] = al_load_bitmap("images/cat-front-2.png");
    must_init(imgs->cat_sprites.front[1], "cat front 2 image");
    imgs->cat_sprites.front[2] = al_load_bitmap("images/cat-front-3.png");
    must_init(imgs->cat_sprites.front[2], "cat front 3 image");
    imgs->cat_sprites.back[0] = al_load_bitmap("images/cat-back-1.png");
    must_init(imgs->cat_sprites.back[0], "cat back 1 image");
    imgs->cat_sprites.back[1] = al_load_bitmap("images/cat-back-2.png");
    must_init(imgs->cat_sprites.back[1], "cat back 2 image");
    imgs->cat_sprites.back[2] = al_load_bitmap("images/cat-back-3.png");
    must_init(imgs->cat_sprites.back[2], "cat back 3 image");
    imgs->cat_sprites.left[0] = al_load_bitmap("images/cat-left-1.png");
    must_init(imgs->cat_sprites.left[0], "cat left 1 image");
    imgs->cat_sprites.left[1] = al_load_bitmap("images/cat-left-2.png");
    must_init(imgs->cat_sprites.left[1], "cat left 2 image");
    imgs->cat_sprites.left[2] = al_load_bitmap("images/cat-left-3.png");
    must_init(imgs->cat_sprites.left[2], "cat left 3 image");
    imgs->cat_sprites.right[0] = al_load_bitmap("images/cat-right-1.png");
    must_init(imgs->cat_sprites.right[0], "cat right 1 image");
    imgs->cat_sprites.right[1] = al_load_bitmap("images/cat-right-2.png");
    must_init(imgs->cat_sprites.right[1], "cat right 2 image");
    imgs->cat_sprites.right[2] = al_load_bitmap("images/cat-right-3.png");
    must_init(imgs->cat_sprites.right[2], "cat right 3 image");
    imgs->snake_sprites.front[0] = al_load_bitmap("images/snake-front-1.png");
    must_init(imgs->snake_sprites.front[0], "snake front 1 image");
    imgs->snake_sprites.front[1] = al_load_bitmap("images/snake-front-2.png");
    must_init(imgs->snake_sprites.front[1], "snake front 2 image");
    imgs->snake_sprites.front[2] = al_load_bitmap("images/snake-front-3.png");
    must_init(imgs->snake_sprites.front[2], "snake front 3 image");
    imgs->snake_sprites.back[0] = al_load_bitmap("images/snake-back-1.png");
    must_init(imgs->snake_sprites.back[0], "snake back 1 image");
    imgs->snake_sprites.back[1] = al_load_bitmap("images/snake-back-2.png");
    must_init(imgs->snake_sprites.back[1], "snake back 2 image");
    imgs->snake_sprites.back[2] = al_load_bitmap("images/snake-back-3.png");
    must_init(imgs->snake_sprites.back[2], "snake back 3 image");
    imgs->snake_sprites.left[0] = al_load_bitmap("images/snake-left-1.png");    
    must_init(imgs->snake_sprites.left[0], "snake left 1 image");
    imgs->snake_sprites.left[1] = al_load_bitmap("images/snake-left-2.png");
    must_init(imgs->snake_sprites.left[1], "snake left 2 image");
    imgs->snake_sprites.left[2] = al_load_bitmap("images/snake-left-3.png");
    must_init(imgs->snake_sprites.left[2], "snake left 3 image");
    imgs->snake_sprites.right[0] = al_load_bitmap("images/snake-right-1.png");
    must_init(imgs->snake_sprites.right[0], "snake right 1 image");
    imgs->snake_sprites.right[1] = al_load_bitmap("images/snake-right-2.png");
    must_init(imgs->snake_sprites.right[1], "snake right 2 image");
    imgs->snake_sprites.right[2] = al_load_bitmap("images/snake-right-3.png");
    must_init(imgs->snake_sprites.right[2], "snake right 3 image");
}

void load_sounds(Sounds* sounds) {
    sounds->footstep[0] = al_load_sample("sounds/footstep-1.wav");
    must_init(sounds->footstep[0], "footstep 1 sound");
    sounds->footstep[1] = al_load_sample("sounds/footstep-2.wav");
    must_init(sounds->footstep[1], "footstep 2 sound");
}

void sort_destination(Animal* self) {
    switch (self->type) {
    case BIRD:
        self->destination.y = rand() % (MAP_SIZE + 700);

        if (self->position.x <= 0) {
            self->destination.x = MAP_SIZE;
        } else if (self->position.x >= DISPLAY_WIDTH) {
            self->destination.x = (-MAP_SIZE - 700);
        }

        self->birds_count = rand() % 7 + 1;
        break;
    case RABBIT:
    case GOAT:
    case SHEEP:
    case CAT:
    case SNAKE:
        self->destination.x = rand() % (int)(self->bounds.x2 - self->bounds.x1) + self->bounds.x1;
        self->destination.y = rand() % (int)(self->bounds.y2 - self->bounds.y1) + self->bounds.y1;
        break;
    }
}

void move_animal(Animal* self) {
    if (self->position.x < self->destination.x) {
        self->position.x += self->speed;
        if (self->position.x >= self->destination.x) self->position.x = self->destination.x;
    }
    if (self->position.x > self->destination.x) {
        self->position.x -= self->speed;
        if (self->position.x <= self->destination.x) self->position.x = self->destination.x;
    }
    if (self->position.y < self->destination.y) {
        self->position.y += self->speed;
        if (self->position.y >= self->destination.y) self->position.y = self->destination.y;
    }
    if (self->position.y > self->destination.y) {
        self->position.y -= self->speed;
        if (self->position.y <= self->destination.y) self->position.y = self->destination.y;
    }

    if (self->position.x == self->destination.x && self->position.y == self->destination.y) {
        self->is_moving = false;
    }
}

void set_context_to_default(Context* ctx) {
    ctx->imgs.char_sprites.current = ctx->imgs.char_sprites.front[0];
    ctx->player.x = DISPLAY_WIDTH/2.0 - PLAYER_WIDTH/2;
    ctx->player.y = DISPLAY_HEIGHT/2.0 - PLAYER_HEIGHT/2;
    ctx->map.x = INITIAL_MAP_X;
    ctx->map.y = INITIAL_MAP_Y;

    for (int i = 0; i < PLACEABLE_OBJECTS_LENGTH; i++) {
        ctx->c1.placeable_objects[i].position_index = i * 2;
        ctx->c1.placeable_objects[i].correct_position_index = i * 2 + 1;
        ctx->c1.placeable_objects[i].width = 100;
        ctx->c1.placeable_objects[i].height = 100;
    }

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

    for (int i = 0; i < WANTED_OBJECTS_LENGTH; i++) {
        ctx->c4.wanted_objects[i].selected = false;
        ctx->c4.fake_wanted_objects[i].selected = false;
    }

    ctx->has_user_lost = false;
    ctx->is_user_hallucinated = false;
    ctx->challenge_index = 0; // 0 até 4
    ctx->life_counter = 3; // 3 até 0
    ctx->hunger_counter = 3; // 3 até 0
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
            ctx->animals[i].speed = 8;
            ctx->animals[i].width = 50;
            ctx->animals[i].height = 50;
            ctx->animals[i].bounds.x1 = 1000;
            ctx->animals[i].bounds.x2 = 1200;
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
            ctx->animals[i].bounds.x2 = 1200;
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
            ctx->animals[i].speed = 5;
            ctx->animals[i].width = 25;
            ctx->animals[i].height = 25;
            ctx->animals[i].bounds.x1 = -500;
            ctx->animals[i].bounds.x2 = 500;
            ctx->animals[i].bounds.y1 = 1500;
            ctx->animals[i].bounds.y2 = 2400;
            break;
        }
    }

    // Obstaculos
    ctx->obstacles[0].position.x = 1000;
    ctx->obstacles[0].position.y = 1175;
    ctx->obstacles[0].width = 100;
    ctx->obstacles[0].height = 200;
    ctx->obstacles[1].position.x = 1070;
    ctx->obstacles[1].position.y = 1190;
    ctx->obstacles[1].width = 100;
    ctx->obstacles[1].height = 100;
    ctx->obstacles[2].position.x = 1100;
    ctx->obstacles[2].position.y = 1225;
    ctx->obstacles[2].width = 125;
    ctx->obstacles[2].height = 150;
    ctx->obstacles[3].position.x = 1800;
    ctx->obstacles[3].position.y = 1740;
    ctx->obstacles[3].width = 200;
    ctx->obstacles[3].height = 150;
    ctx->obstacles[4].position.x = 1700;
    ctx->obstacles[4].position.y = 1680;
    ctx->obstacles[4].width = 100;
    ctx->obstacles[4].height = 150;
    ctx->obstacles[5].position.x = 1600;
    ctx->obstacles[5].position.y = 1660;
    ctx->obstacles[5].width = 100;
    ctx->obstacles[5].height = 150;
    ctx->obstacles[6].position.x = 1550;
    ctx->obstacles[6].position.y = 1590;
    ctx->obstacles[6].width = 100;
    ctx->obstacles[6].height = 150;
    ctx->obstacles[7].position.x = 1500;
    ctx->obstacles[7].position.y = 1700;
    ctx->obstacles[7].width = 100;
    ctx->obstacles[7].height = 100;
    ctx->obstacles[8].position.x = 1570;
    ctx->obstacles[8].position.y = 1410;
    ctx->obstacles[8].width = 70;
    ctx->obstacles[8].height = 90;
    ctx->obstacles[9].position.x = 1380;
    ctx->obstacles[9].position.y = 1735;
    ctx->obstacles[9].width = 100;
    ctx->obstacles[9].height = 150;
    ctx->obstacles[10].position.x = 1310;
    ctx->obstacles[10].position.y = 1760;
    ctx->obstacles[10].width = 70;
    ctx->obstacles[10].height = 90;
    ctx->obstacles[11].position.x = 1450;
    ctx->obstacles[11].position.y = 1885;
    ctx->obstacles[11].width = 100;
    ctx->obstacles[11].height = 150;
    ctx->obstacles[12].position.x = 1550;
    ctx->obstacles[12].position.y = 2035;
    ctx->obstacles[12].width = 100;
    ctx->obstacles[12].height = 100;
    ctx->obstacles[13].position.x = 1610;
    ctx->obstacles[13].position.y = 2135;
    ctx->obstacles[13].width = 100;
    ctx->obstacles[13].height = 150;
    ctx->obstacles[14].position.x = 1950;
    ctx->obstacles[14].position.y = -100;
    ctx->obstacles[14].width = 100;
    ctx->obstacles[14].height = 130;
    ctx->obstacles[15].position.x = 1870;
    ctx->obstacles[15].position.y = -30;
    ctx->obstacles[15].width = 80;
    ctx->obstacles[15].height = 130;
    ctx->obstacles[16].position.x = 1750;
    ctx->obstacles[16].position.y = 100;
    ctx->obstacles[16].width = 130;
    ctx->obstacles[16].height = 130;
    ctx->obstacles[17].position.x = 1610;
    ctx->obstacles[17].position.y = -100;
    ctx->obstacles[17].width = 100;
    ctx->obstacles[17].height = 90;
    ctx->obstacles[18].position.x = 1490;
    ctx->obstacles[18].position.y = -50;
    ctx->obstacles[18].width = 120;
    ctx->obstacles[18].height = 90;
    ctx->obstacles[19].position.x = 1390;
    ctx->obstacles[19].position.y = 30;
    ctx->obstacles[19].width = 100;
    ctx->obstacles[19].height = 90;
    ctx->obstacles[20].position.x = 1290;
    ctx->obstacles[20].position.y = 90;
    ctx->obstacles[20].width = 100;
    ctx->obstacles[20].height = 80;
    ctx->obstacles[21].position.x = 1220;
    ctx->obstacles[21].position.y = -100;
    ctx->obstacles[21].width = 70;
    ctx->obstacles[21].height = 300;
    ctx->obstacles[22].position.x = 1200;
    ctx->obstacles[22].position.y = 245;
    ctx->obstacles[22].width = 70;
    ctx->obstacles[22].height = 90;
    ctx->obstacles[23].position.x = 1660;
    ctx->obstacles[23].position.y = 220;
    ctx->obstacles[23].width = 90;
    ctx->obstacles[23].height = 100;
    ctx->obstacles[24].position.x = 1570;
    ctx->obstacles[24].position.y = 245;
    ctx->obstacles[24].width = 90;
    ctx->obstacles[24].height = 100;
    ctx->obstacles[25].position.x = 1370;
    ctx->obstacles[25].position.y = 300;
    ctx->obstacles[25].width = 200;
    ctx->obstacles[25].height = 100;
    ctx->obstacles[26].position.x = 1340;
    ctx->obstacles[26].position.y = 340;
    ctx->obstacles[26].width = 30;
    ctx->obstacles[26].height = 120;
    ctx->obstacles[27].position.x = 1370;
    ctx->obstacles[27].position.y = 460;
    ctx->obstacles[27].width = 60;
    ctx->obstacles[27].height = 60;
    ctx->obstacles[28].position.x = 1430;
    ctx->obstacles[28].position.y = 520;
    ctx->obstacles[28].width = 120;
    ctx->obstacles[28].height = 200;
    ctx->obstacles[29].position.x = 1530;
    ctx->obstacles[29].position.y = 720;
    ctx->obstacles[29].width = 500;
    ctx->obstacles[29].height = 70;
    ctx->obstacles[30].position.x = 1670;
    ctx->obstacles[30].position.y = 790;
    ctx->obstacles[30].width = 50;
    ctx->obstacles[30].height = 30;
    ctx->obstacles[31].position.x = 1890;
    ctx->obstacles[31].position.y = 790;
    ctx->obstacles[31].width = 200;
    ctx->obstacles[31].height = 30;
    ctx->obstacles[32].position.x = 1455;
    ctx->obstacles[32].position.y = 810;
    ctx->obstacles[32].width = 70;
    ctx->obstacles[32].height = 90;
    ctx->obstacles[33].position.x = 1950;
    ctx->obstacles[33].position.y = 990;
    ctx->obstacles[33].width = 70;
    ctx->obstacles[33].height = 90;
    ctx->obstacles[34].position.x = 1850;
    ctx->obstacles[34].position.y = 970;
    ctx->obstacles[34].width = 100;
    ctx->obstacles[34].height = 90;
    ctx->obstacles[35].position.x = 1800;
    ctx->obstacles[35].position.y = 1000;
    ctx->obstacles[35].width = 50;
    ctx->obstacles[35].height = 60;
    ctx->obstacles[36].position.x = 1700;
    ctx->obstacles[36].position.y = 970;
    ctx->obstacles[36].width = 100;
    ctx->obstacles[36].height = 90;
    ctx->obstacles[37].position.x = 1600;
    ctx->obstacles[37].position.y = 970;
    ctx->obstacles[37].width = 100;
    ctx->obstacles[37].height = 150;
    ctx->obstacles[38].position.x = 1600;
    ctx->obstacles[38].position.y = 1170;
    ctx->obstacles[38].width = 100;
    ctx->obstacles[38].height = 100;
    ctx->obstacles[39].position.x = 1670;
    ctx->obstacles[39].position.y = 1120;
    ctx->obstacles[39].width = 30;
    ctx->obstacles[39].height = 50;
    ctx->obstacles[40].position.x = 1640;
    ctx->obstacles[40].position.y = 1270;
    ctx->obstacles[40].width = 150;
    ctx->obstacles[40].height = 170;
    ctx->obstacles[41].position.x = 1790;
    ctx->obstacles[41].position.y = 1440;
    ctx->obstacles[41].width = 90;
    ctx->obstacles[41].height = 70;
    ctx->obstacles[42].position.x = 1880;
    ctx->obstacles[42].position.y = 1510;
    ctx->obstacles[42].width = 150;
    ctx->obstacles[42].height = 70;
    ctx->obstacles[43].position.x = 1190;
    ctx->obstacles[43].position.y = 2170;
    ctx->obstacles[43].width = 100;
    ctx->obstacles[43].height = 100;
    ctx->obstacles[44].position.x = 1240;
    ctx->obstacles[44].position.y = 2070;
    ctx->obstacles[44].width = 100;
    ctx->obstacles[44].height = 100;
    ctx->obstacles[45].position.x = 1190;
    ctx->obstacles[45].position.y = 2000;
    ctx->obstacles[45].width = 50;
    ctx->obstacles[45].height = 100;
    ctx->obstacles[46].position.x = 1140;
    ctx->obstacles[46].position.y = 1950;
    ctx->obstacles[46].width = 50;
    ctx->obstacles[46].height = 50;
    ctx->obstacles[47].position.x = 1090;
    ctx->obstacles[47].position.y = 1900;
    ctx->obstacles[47].width = 120;
    ctx->obstacles[47].height = 50;
    ctx->obstacles[48].position.x = 1100;
    ctx->obstacles[48].position.y = 1830;
    ctx->obstacles[48].width = 100;
    ctx->obstacles[48].height = 70;
    ctx->obstacles[49].position.x = 970;
    ctx->obstacles[49].position.y = 1870;
    ctx->obstacles[49].width = 80;
    ctx->obstacles[49].height = 70;
    ctx->obstacles[50].position.x = 1030;
    ctx->obstacles[50].position.y = 1940;
    ctx->obstacles[50].width = 60;
    ctx->obstacles[50].height = 50;
    ctx->obstacles[51].position.x = 880;
    ctx->obstacles[51].position.y = 1890;
    ctx->obstacles[51].width = 90;
    ctx->obstacles[51].height = 70;
    ctx->obstacles[52].position.x = 850;
    ctx->obstacles[52].position.y = 1920;
    ctx->obstacles[52].width = 30;
    ctx->obstacles[52].height = 150;
    ctx->obstacles[53].position.x = 800;
    ctx->obstacles[53].position.y = 2070;
    ctx->obstacles[53].width = 50;
    ctx->obstacles[53].height = 50;
    ctx->obstacles[54].position.x = 700;
    ctx->obstacles[54].position.y = 2010;
    ctx->obstacles[54].width = 100;
    ctx->obstacles[54].height = 60;
    ctx->obstacles[55].position.x = 630;
    ctx->obstacles[55].position.y = 1910;
    ctx->obstacles[55].width = 100;
    ctx->obstacles[55].height = 100;
    ctx->obstacles[56].position.x = 560;
    ctx->obstacles[56].position.y = 1930;
    ctx->obstacles[56].width = 70;
    ctx->obstacles[56].height = 100;
    ctx->obstacles[57].position.x = 480;
    ctx->obstacles[57].position.y = 1930;
    ctx->obstacles[57].width = 80;
    ctx->obstacles[57].height = 100;
    ctx->obstacles[58].position.x = 520;
    ctx->obstacles[58].position.y = 2030;
    ctx->obstacles[58].width = 100;
    ctx->obstacles[58].height = 100;
    ctx->obstacles[59].position.x = 540;
    ctx->obstacles[59].position.y = 2130;
    ctx->obstacles[59].width = 100;
    ctx->obstacles[59].height = 150;
    ctx->obstacles[60].position.x = 240;
    ctx->obstacles[60].position.y = 2110;
    ctx->obstacles[60].width = 100;
    ctx->obstacles[60].height = 150;
    ctx->obstacles[61].position.x = 240;
    ctx->obstacles[61].position.y = 1930;
    ctx->obstacles[61].width = 120;
    ctx->obstacles[61].height = 150;
    ctx->obstacles[62].position.x = 190;
    ctx->obstacles[62].position.y = 2080;
    ctx->obstacles[62].width = 50;
    ctx->obstacles[62].height = 30;
    ctx->obstacles[63].position.x = 120;
    ctx->obstacles[63].position.y = 1880;
    ctx->obstacles[63].width = 200;
    ctx->obstacles[63].height = 50;
    ctx->obstacles[64].position.x = 190;
    ctx->obstacles[64].position.y = 2170;
    ctx->obstacles[64].width = 50;
    ctx->obstacles[64].height = 30;
    ctx->obstacles[65].position.x = 40;
    ctx->obstacles[65].position.y = 1930;
    ctx->obstacles[65].width = 80;
    ctx->obstacles[65].height = 50;
    ctx->obstacles[66].position.x = -20;
    ctx->obstacles[66].position.y = 1960;
    ctx->obstacles[66].width = 60;
    ctx->obstacles[66].height = 30;
    ctx->obstacles[67].position.x = -260;
    ctx->obstacles[67].position.y = 1880;
    ctx->obstacles[67].width = 240;
    ctx->obstacles[67].height = 80;
    ctx->obstacles[68].position.x = -360;
    ctx->obstacles[68].position.y = 1960;
    ctx->obstacles[68].width = 100;
    ctx->obstacles[68].height = 50;
    ctx->obstacles[69].position.x = -180;
    ctx->obstacles[69].position.y = 1840;
    ctx->obstacles[69].width = 100;
    ctx->obstacles[69].height = 40;
    ctx->obstacles[70].position.x = -300;
    ctx->obstacles[70].position.y = 1100;
    ctx->obstacles[70].width = 100;
    ctx->obstacles[70].height = 100;
    ctx->obstacles[71].position.x = -200;
    ctx->obstacles[71].position.y = 1100;
    ctx->obstacles[71].width = 100;
    ctx->obstacles[71].height = 100;
    ctx->obstacles[72].position.x = -100;
    ctx->obstacles[72].position.y = 1100;
    ctx->obstacles[72].width = 100;
    ctx->obstacles[72].height = 100;
    ctx->obstacles[73].position.x = -200;
    ctx->obstacles[73].position.y = 1000;
    ctx->obstacles[73].width = 100;
    ctx->obstacles[73].height = 100;
    ctx->obstacles[74].position.x = -100;
    ctx->obstacles[74].position.y = 1050;
    ctx->obstacles[74].width = 50;
    ctx->obstacles[74].height = 50;
    ctx->obstacles[75].position.x = -300;
    ctx->obstacles[75].position.y = 900;
    ctx->obstacles[75].width = 100;
    ctx->obstacles[75].height = 100;
    ctx->obstacles[76].position.x = -200;
    ctx->obstacles[76].position.y = 950;
    ctx->obstacles[76].width = 50;
    ctx->obstacles[76].height = 50;
    ctx->obstacles[77].position.x = -300;
    ctx->obstacles[77].position.y = 800;
    ctx->obstacles[77].width = 100;
    ctx->obstacles[77].height = 100;
    ctx->obstacles[78].position.x = -300;
    ctx->obstacles[78].position.y = 700;
    ctx->obstacles[78].width = 100;
    ctx->obstacles[78].height = 100;
    ctx->obstacles[79].position.x = -300;
    ctx->obstacles[79].position.y = 600;
    ctx->obstacles[79].width = 100;
    ctx->obstacles[79].height = 100;
    ctx->obstacles[80].position.x = -200;
    ctx->obstacles[80].position.y = 725;
    ctx->obstacles[80].width = 50;
    ctx->obstacles[80].height = 50;
    ctx->obstacles[81].position.x = -200;
    ctx->obstacles[81].position.y = 550;
    ctx->obstacles[81].width = 50;
    ctx->obstacles[81].height = 50;
    ctx->obstacles[82].position.x = -150;
    ctx->obstacles[82].position.y = 450;
    ctx->obstacles[82].width = 100;
    ctx->obstacles[82].height = 100;
    ctx->obstacles[83].position.x = -50;
    ctx->obstacles[83].position.y = 450;
    ctx->obstacles[83].width = 100;
    ctx->obstacles[83].height = 100;
    ctx->obstacles[84].position.x = 50;
    ctx->obstacles[84].position.y = 450;
    ctx->obstacles[84].width = 50;
    ctx->obstacles[84].height = 50;
    ctx->obstacles[85].position.x = 100;
    ctx->obstacles[85].position.y = 350;
    ctx->obstacles[85].width = 100;
    ctx->obstacles[85].height = 100;
    ctx->obstacles[86].position.x = 200;
    ctx->obstacles[86].position.y = 350;
    ctx->obstacles[86].width = 100;
    ctx->obstacles[86].height = 100;
    ctx->obstacles[87].position.x = 300;
    ctx->obstacles[87].position.y = 350;
    ctx->obstacles[87].width = 50;
    ctx->obstacles[87].height = 50;
    ctx->obstacles[88].position.x = 350;
    ctx->obstacles[88].position.y = 250;
    ctx->obstacles[88].width = 100;
    ctx->obstacles[88].height = 100;
    ctx->obstacles[89].position.x = 450;
    ctx->obstacles[89].position.y = 250;
    ctx->obstacles[89].width = 50;
    ctx->obstacles[89].height = 50;
    ctx->obstacles[90].position.x = 500;
    ctx->obstacles[90].position.y = 150;
    ctx->obstacles[90].width = 100;
    ctx->obstacles[90].height = 100;
    ctx->obstacles[91].position.x = 500;
    ctx->obstacles[91].position.y = 50;
    ctx->obstacles[91].width = 100;
    ctx->obstacles[91].height = 100;
    ctx->obstacles[92].position.x = 600;
    ctx->obstacles[92].position.y = 50;
    ctx->obstacles[92].width = 50;
    ctx->obstacles[92].height = 50;
    ctx->obstacles[93].position.x = 650;
    ctx->obstacles[93].position.y = -50;
    ctx->obstacles[93].width = 100;
    ctx->obstacles[93].height = 100;
    ctx->obstacles[94].position.x = 750;
    ctx->obstacles[94].position.y = 50;
    ctx->obstacles[94].width = 50;
    ctx->obstacles[94].height = 50;
    ctx->obstacles[95].position.x = 800;
    ctx->obstacles[95].position.y = 0;
    ctx->obstacles[95].width = 50;
    ctx->obstacles[95].height = 50;
    ctx->obstacles[96].position.x = 850;
    ctx->obstacles[96].position.y = -100;
    ctx->obstacles[96].width = 100;
    ctx->obstacles[96].height = 100;
    ctx->obstacles[97].position.x = 950;
    ctx->obstacles[97].position.y = -100;
    ctx->obstacles[97].width = 100;
    ctx->obstacles[97].height = 100;
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
    ctx->c1.placeable_positions[0].x = 5;
    ctx->c1.placeable_positions[0].y = 600;
    ctx->c1.placeable_positions[1].x = 10;
    ctx->c1.placeable_positions[1].y = 200;
    ctx->c1.placeable_positions[2].x = 150;
    ctx->c1.placeable_positions[2].y = 600;
    ctx->c1.placeable_positions[3].x = 150;
    ctx->c1.placeable_positions[3].y = 200;
    ctx->c1.placeable_positions[4].x = 300;
    ctx->c1.placeable_positions[4].y = 600;
    ctx->c1.placeable_positions[5].x = 400;
    ctx->c1.placeable_positions[5].y = 200;
    ctx->c1.placeable_positions[6].x = 450;
    ctx->c1.placeable_positions[6].y = 600;
    ctx->c1.placeable_positions[7].x = 550;
    ctx->c1.placeable_positions[7].y = 200;
    ctx->c1.placeable_positions[8].x = 700;
    ctx->c1.placeable_positions[8].y = 600;
    ctx->c1.placeable_positions[9].x = 700;
    ctx->c1.placeable_positions[9].y = 200;
    ctx->c1.selected_object_index = -1;

    // Challenge 2
    ctx->c2.selectable_objects[0].position.x = 100;
    ctx->c2.selectable_objects[0].position.y = 100;
    ctx->c2.selectable_objects[1].position.x = 300;
    ctx->c2.selectable_objects[1].position.y = 100;
    ctx->c2.selectable_objects[2].position.x = 500;
    ctx->c2.selectable_objects[2].position.y = 400;
    ctx->c2.selectable_objects[3].position.x = 700;
    ctx->c2.selectable_objects[3].position.y = 400;
    ctx->c2.selectable_objects[4].position.x = 900;
    ctx->c2.selectable_objects[4].position.y = 100;
    ctx->c2.selectable_objects[5].position.x = 1100;
    ctx->c2.selectable_objects[5].position.y = 100;
    ctx->c2.selectable_objects[6].position.x = 100;
    ctx->c2.selectable_objects[6].position.y = 500;
    
    // Challenge 4
    ctx->c4.wanted_objects[0].position.x = 100;
    ctx->c4.wanted_objects[0].position.y = 100;
    ctx->c4.wanted_objects[1].position.x = 300;
    ctx->c4.wanted_objects[1].position.y = 100;
    ctx->c4.wanted_objects[2].position.x = 500;
    ctx->c4.wanted_objects[2].position.y = 400;
    ctx->c4.wanted_objects[3].position.x = 700;
    ctx->c4.wanted_objects[3].position.y = 400;
    ctx->c4.fake_wanted_objects[0].position.x = 600;
    ctx->c4.fake_wanted_objects[0].position.y = 600;
    ctx->c4.fake_wanted_objects[1].position.x = 300;
    ctx->c4.fake_wanted_objects[1].position.y = 500;
    ctx->c4.fake_wanted_objects[2].position.x = 500;
    ctx->c4.fake_wanted_objects[2].position.y = 500;
    ctx->c4.fake_wanted_objects[3].position.x = 1000;
    ctx->c4.fake_wanted_objects[3].position.y = 400;
}

void free_context(Context* ctx) {
    al_destroy_bitmap(ctx->imgs.map);
    al_destroy_bitmap(ctx->imgs.menu);
    al_destroy_bitmap(ctx->imgs.end_game);
    al_destroy_bitmap(ctx->imgs.game_over);

    for (int i = 0; i < 5; i++) {
        al_destroy_bitmap(ctx->imgs.challenges[i]);
    }

    al_destroy_bitmap(ctx->imgs.play_btn);
    al_destroy_bitmap(ctx->imgs.menu_btn);
    al_destroy_bitmap(ctx->imgs.heart_empty);
    al_destroy_bitmap(ctx->imgs.heart_filled);
    al_destroy_bitmap(ctx->imgs.hunger_empty);
    al_destroy_bitmap(ctx->imgs.hunger_filled);

    for (int i = 0; i < SPRITES_LENGTH; i++) {
        al_destroy_bitmap(ctx->imgs.char_sprites.front[i]);
        al_destroy_bitmap(ctx->imgs.char_sprites.back[i]);
        al_destroy_bitmap(ctx->imgs.char_sprites.left[i]);
        al_destroy_bitmap(ctx->imgs.char_sprites.right[i]);
        al_destroy_bitmap(ctx->imgs.bird_sprites.front[i]);
        al_destroy_bitmap(ctx->imgs.bird_sprites.back[i]);
        al_destroy_bitmap(ctx->imgs.bird_sprites.left[i]);
        al_destroy_bitmap(ctx->imgs.bird_sprites.right[i]);
        al_destroy_bitmap(ctx->imgs.rabbit_sprites.front[i]);
        al_destroy_bitmap(ctx->imgs.rabbit_sprites.back[i]);
        al_destroy_bitmap(ctx->imgs.rabbit_sprites.left[i]);
        al_destroy_bitmap(ctx->imgs.rabbit_sprites.right[i]);
        al_destroy_bitmap(ctx->imgs.goat_sprites.front[i]);
        al_destroy_bitmap(ctx->imgs.goat_sprites.back[i]);
        al_destroy_bitmap(ctx->imgs.goat_sprites.left[i]);
        al_destroy_bitmap(ctx->imgs.goat_sprites.right[i]);
        al_destroy_bitmap(ctx->imgs.sheep_sprites.front[i]);
        al_destroy_bitmap(ctx->imgs.sheep_sprites.back[i]);
        al_destroy_bitmap(ctx->imgs.sheep_sprites.left[i]);
        al_destroy_bitmap(ctx->imgs.sheep_sprites.right[i]);
        al_destroy_bitmap(ctx->imgs.cat_sprites.front[i]);
        al_destroy_bitmap(ctx->imgs.cat_sprites.back[i]);
        al_destroy_bitmap(ctx->imgs.cat_sprites.left[i]);
        al_destroy_bitmap(ctx->imgs.cat_sprites.right[i]);
        al_destroy_bitmap(ctx->imgs.snake_sprites.front[i]);
        al_destroy_bitmap(ctx->imgs.snake_sprites.back[i]);
        al_destroy_bitmap(ctx->imgs.snake_sprites.left[i]);
        al_destroy_bitmap(ctx->imgs.snake_sprites.right[i]);
    }

    al_destroy_sample(ctx->sounds.footstep[0]);
    al_destroy_sample(ctx->sounds.footstep[1]);

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
        break;
    case OPEN_MAP:
        al_draw_bitmap(ctx->imgs.map, ctx->map.x, ctx->map.y, 0);

        for (int i = 2; i < ANIMALS_LENGTH; i++) {
            Animal* a = &ctx->animals[i];
            bool hide = false;
            switch (a->type) {
            case CAT:
                hide = a->position.x >= a->bounds.x1 + 200 && a->position.x <= a->bounds.x2 - 200 && a->position.y >= a->bounds.y1 + 200 &&
                       a->position.y <= a->bounds.y2 - 200;
                if (!hide) al_draw_bitmap(ctx->imgs.cat_sprites.current, a->position.x, a->position.y, 0);
                break;
            case RABBIT:
                hide = a->position.x >= a->bounds.x1 + 200 && a->position.x <= a->bounds.x2 - 200 && a->position.y >= a->bounds.y1 + 200 &&
                       a->position.y <= a->bounds.y2 - 200;
                if (!hide) al_draw_bitmap(ctx->imgs.rabbit_sprites.current, a->position.x, a->position.y, 0);
                break;
            case SNAKE:
                hide = a->position.x <= a->bounds.x2 - 150 && a->position.y >= a->bounds.y1 + 300;
                if (!hide) al_draw_bitmap(ctx->imgs.snake_sprites.current, a->position.x, a->position.y, 0);
                break;
            case GOAT:
                al_draw_bitmap(ctx->imgs.goat_sprites.current, a->position.x, a->position.y, 0);
                break;
            case SHEEP:
                al_draw_bitmap(ctx->imgs.sheep_sprites.current, a->position.x, a->position.y, 0);
                break;
            }
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

                  al_draw_bitmap(ctx->imgs.bird_sprites.current, x, y, 0);
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
        }
        break;
    case CHALLENGE:
        al_draw_bitmap(ctx->imgs.challenges[ctx->challenge_index], 0, 0, 0);

        if (ctx->challenge_index == 0) {
            for (int i = 0; i < PLACEABLE_POSITIONS_LENGTH; i++) {
                Coordinate* pos = &ctx->c1.placeable_positions[i];
                al_draw_filled_rectangle(pos->x, pos->y, pos->x + 100, pos->y + 100, al_map_rgb(50, 50, 50));
            }

            for (int i = 0; i < PLACEABLE_OBJECTS_LENGTH; i++) {
                int pos_i = ctx->c1.placeable_objects[i].position_index;
                float x = ctx->c1.placeable_positions[pos_i].x,
                      y = ctx->c1.placeable_positions[pos_i].y;
                int w = PLACEABLE_OBJECT_WIDTH,
                    h = PLACEABLE_OBJECT_HEIGHT;

                al_draw_filled_rectangle(x, y, x + w, y + h, al_map_rgb(255, 0, 255)); 
                if (ctx->c1.selected_object_index == i) {
                    al_draw_rectangle(x - 5, y - 5, x + w + 5, y + h + 5, al_map_rgb(255, 255, 255), 1);
                }
                al_draw_textf(ctx->font, al_map_rgb(255, 255, 255), x + 10, y + 10, 0, "%d", i + 1);
            }  
        }

        if (ctx->challenge_index == 1) {
            for (int i = 0; i < SELECTABLE_OBJECTS_LENGTH_C2; i++) {
                Selectable_Object* obj = &ctx->c2.selectable_objects[i];
                int w = SELECTABLE_OBJECT_WIDTH,
                    h = SELECTABLE_OBJECT_HEIGHT;

                al_draw_filled_rectangle(obj->position.x, obj->position.y, obj->position.x + w, obj->position.y + h, al_map_rgb(255, 255, 255));
                if (obj->selected) {
                    al_draw_rectangle(obj->position.x - 5, obj->position.y - 5, obj->position.x + w + 5, obj->position.y + h + 5, al_map_rgb(255, 0, 0), 1);
                }
            }
        }
            
        if (ctx->challenge_index == 2) {
            al_draw_bitmap(ctx->imgs.char_with_basket, ctx->c3.player_position.x, ctx->c3.player_position.y, 0);
            al_draw_textf(ctx->font, al_map_rgb(255, 0, 0), 1180, 0, 0, "Maçãs: %d", ctx->c3.apples_counter);
            al_draw_textf(ctx->font, al_map_rgb(0, 0, 255), 1180, 20, 0, "Cogumelos: %d", ctx->c3.mushrooms_counter);

            for (int i = 0; i < FALLING_OBJECTS_LENGTH; i++) {
                Falling_Object* obj = &ctx->c3.falling_objects[i];
                int w = FALLING_OBJECT_WIDTH,
                    h = FALLING_OBJECT_HEIGHT;
            
                ALLEGRO_COLOR color;
                if (obj->id == 0) {
                    color = al_map_rgb(255, 0, 0);
                } else {
                    color = al_map_rgb(0, 0, 255);
                }
                al_draw_filled_rectangle(obj->position.x, obj->position.y, obj->position.x + w, obj->position.y + h, color);
            }
        }

        if (ctx->challenge_index == 3) {
            for (int i = 0; i < WANTED_OBJECTS_LENGTH; i++) {
                Wanted_Object* obj = &ctx->c4.wanted_objects[i];
                Wanted_Object* fake_obj = &ctx->c4.fake_wanted_objects[i];
                int w = WANTED_OBJECT_WIDTH,
                    h = WANTED_OBJECT_HEIGHT;
                
                if (ctx->is_user_hallucinated && !fake_obj->selected) {
                    obj = fake_obj;
                }
                    
                if (obj->selected) {
                    al_draw_rectangle(obj->position.x - 5, obj->position.y - 5, obj->position.x + w + 5, obj->position.y + h + 5, al_map_rgb(255, 0, 0), 1);
                }

                al_draw_filled_rectangle(obj->position.x, obj->position.y, obj->position.x + w, obj->position.y + h, al_map_rgb(255, 205, 170));
            }

            time_t current_time = time(0);
            int seconds_left = ctx->c4.duration_in_seconds - (current_time - ctx->c4.start_time);
            al_draw_textf(ctx->font, al_map_rgb(0, 0, 0), 0, 20, 0, "Tempo: %d segundos", seconds_left);
        }

        al_draw_filled_rectangle(1000, 600, 1200, 700, al_map_rgb(0, 50, 0));
        al_draw_text(ctx->font, al_map_rgb(255, 255, 255), 1000, 600, 0, "Pronto!");
        break;
    case GAME_OVER:
        if (ctx->has_user_lost) {
            al_draw_bitmap(ctx->imgs.game_over, 0, 0, 0);
        }
        else {
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

void move_camera(Context* ctx) {
    bool is_player_y_centered = ctx->player.y == (DISPLAY_HEIGHT/2.0 - PLAYER_HEIGHT/2);
    bool is_player_x_centered = ctx->player.x == (DISPLAY_WIDTH/2.0 - PLAYER_WIDTH/2);

    Coordinate player = {ctx->player.x, ctx->player.y};
    Coordinate map = {ctx->map.x, ctx->map.y};
    Coordinate obstacles[OBSTACLES_LENGTH];
    Coordinate animals_positions[ANIMALS_LENGTH];
    Coordinate animals_destinations[ANIMALS_LENGTH];
    Rectangle animals_bounds[ANIMALS_LENGTH];

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
    }

    switch (ctx->event.keyboard.keycode) {
    case ALLEGRO_KEY_UP:
    case ALLEGRO_KEY_W:
        if (ctx->map.y < 0 && is_player_y_centered) {
            ctx->map.y += PLAYER_SPEED;
            for (int i = 0; i < OBSTACLES_LENGTH; i++) {
                ctx->obstacles[i].position.y += PLAYER_SPEED;
                
                if (i < ANIMALS_LENGTH) {
                    Animal* a = &ctx->animals[i];
                    a->position.y += PLAYER_SPEED;
                    a->destination.y += PLAYER_SPEED;
                    a->bounds.y1 += PLAYER_SPEED;
                    a->bounds.y2 += PLAYER_SPEED;
                }
            }
        } else if (ctx->player.y >= ctx->map.y) {
            ctx->player.y -= PLAYER_SPEED;
        }
        break;
    case ALLEGRO_KEY_DOWN:
    case ALLEGRO_KEY_S:
        if (ctx->map.y + MAP_SIZE > DISPLAY_HEIGHT && is_player_y_centered) {
            ctx->map.y -= PLAYER_SPEED;
            for (int i = 0; i < OBSTACLES_LENGTH; i++) {
                ctx->obstacles[i].position.y -= PLAYER_SPEED;
            
                if (i < ANIMALS_LENGTH) {
                    Animal* a = &ctx->animals[i];
                    a->position.y -= PLAYER_SPEED;
                    a->destination.y -= PLAYER_SPEED;
                    a->bounds.y1 -= PLAYER_SPEED;
                    a->bounds.y2 -= PLAYER_SPEED;
                }
            }
        } else if (ctx->player.y + PLAYER_HEIGHT <= ctx->map.y + MAP_SIZE) {
            ctx->player.y += PLAYER_SPEED;
        }
        break;
    case ALLEGRO_KEY_LEFT:
    case ALLEGRO_KEY_A:
        if (ctx->map.x < 0 && is_player_x_centered) {
            ctx->map.x += PLAYER_SPEED;
            for (int i = 0; i < OBSTACLES_LENGTH; i++) {
                ctx->obstacles[i].position.x += PLAYER_SPEED;

                if (i < ANIMALS_LENGTH) {
                    Animal* a = &ctx->animals[i];
                    a->position.x += PLAYER_SPEED;
                    a->destination.x += PLAYER_SPEED;
                    a->bounds.x1 += PLAYER_SPEED;
                    a->bounds.x2 += PLAYER_SPEED;
                }
            }
        } else if (ctx->player.x >= ctx->map.x) {
            ctx->player.x -= PLAYER_SPEED;
        }
        break;
    case ALLEGRO_KEY_RIGHT:
    case ALLEGRO_KEY_D:
        if (ctx->map.x + MAP_SIZE > DISPLAY_WIDTH && is_player_x_centered) {
            ctx->map.x -= PLAYER_SPEED;
            for (int i = 0; i < OBSTACLES_LENGTH; i++) {
                ctx->obstacles[i].position.x -= PLAYER_SPEED;
            
                if (i < ANIMALS_LENGTH) {
                    Animal* a = &ctx->animals[i];
                    a->position.x -= PLAYER_SPEED;
                    a->destination.x -= PLAYER_SPEED;
                    a->bounds.x1 -= PLAYER_SPEED;
                    a->bounds.x2 -= PLAYER_SPEED;
                }
            }
        } else if (ctx->player.x + PLAYER_WIDTH <= ctx->map.x + MAP_SIZE) {
            ctx->player.x += PLAYER_SPEED;
        }
        break;
    }

    if (check_obstacles_collision(ctx)) {
        ctx->player.x = player.x;
        ctx->player.y = player.y;
        ctx->map.x = map.x;
        ctx->map.y = map.y;
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
        }
    }
}

int get_quarter_from_timer(ALLEGRO_TIMER* timer) {
    // Calcula o frame atual do jogo (0-29)
    float cyclic_timer = al_get_timer_count(timer) % FPS;

    // Divide o timer em quatro partes
    bool is_one_quarter = cyclic_timer >= 0 && cyclic_timer <= 7.5;
    bool is_two_quarters = cyclic_timer > 7.5 && cyclic_timer <= 15;
    bool is_three_quarters = cyclic_timer > 15 && cyclic_timer <= 22.5;
    bool is_four_quarters = cyclic_timer > 22.5 && cyclic_timer <= 30;

    if (is_one_quarter) return 1;
    if (is_two_quarters) return 2;
    if (is_three_quarters) return 3;
    if (is_four_quarters) return 4;

    return -1;
}

void change_character_sprite(Context* ctx) {
    int quarter = get_quarter_from_timer(ctx->timer);
    if (quarter == -1) return;

    bool is_player_standing = ctx->event.type == ALLEGRO_EVENT_KEY_UP;

    ALLEGRO_BITMAP* current = ctx->imgs.char_sprites.current;
    switch (ctx->event.keyboard.keycode) {
    case ALLEGRO_KEY_UP:
    case ALLEGRO_KEY_W:
        if (quarter == 2) current = ctx->imgs.char_sprites.back[1];
        if (quarter == 4) current = ctx->imgs.char_sprites.back[2];
        if (quarter == 1 || quarter == 3 || is_player_standing) current = ctx->imgs.char_sprites.back[0];
        break;
    case ALLEGRO_KEY_DOWN:
    case ALLEGRO_KEY_S:
        if (quarter == 2) current = ctx->imgs.char_sprites.front[1];
        if (quarter == 4) current = ctx->imgs.char_sprites.front[2];
        if (quarter == 1 || quarter == 3 || is_player_standing) current = ctx->imgs.char_sprites.front[0];
        break;
    case ALLEGRO_KEY_LEFT:
    case ALLEGRO_KEY_A:
        if (quarter == 2) current = ctx->imgs.char_sprites.left[1];
        if (quarter == 4) current = ctx->imgs.char_sprites.left[2];
        if (quarter == 1 || quarter == 3 || is_player_standing) current = ctx->imgs.char_sprites.left[0];
        break;
    case ALLEGRO_KEY_RIGHT:
    case ALLEGRO_KEY_D:
        if (quarter == 2) current = ctx->imgs.char_sprites.right[1];
        if (quarter == 4) current = ctx->imgs.char_sprites.right[2];
        if (quarter == 1 || quarter == 3 || is_player_standing) current = ctx->imgs.char_sprites.right[0];
        break;
    } 
    ctx->imgs.char_sprites.current = current;

    float cyclic_timer = al_get_timer_count(ctx->timer) % FPS;
    if (cyclic_timer == 10) {
        al_stop_samples();
        al_play_sample(ctx->sounds.footstep[0], 0.7, 0.0, 1.5, ALLEGRO_PLAYMODE_ONCE, NULL);
    }
    if (cyclic_timer == 25) {
        al_stop_samples();
        al_play_sample(ctx->sounds.footstep[1], 0.7, 0.0, 1.5, ALLEGRO_PLAYMODE_ONCE, NULL);
    }
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
        ctx->has_user_lost = true;
        return;
    }

    if (ctx->challenge_index == 4) {
        ctx->state = GAME_OVER;
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
}

int get_event_index(ALLEGRO_EVENT_TYPE event_type) {
    int index;

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
    case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
        index = 4;
        break;
    default:
        index = -1;
        break;
    }
    
    return index;
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
    if (check_collision(mouse, 1000, 1200, 600, 700)) {
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
        if (check_collision(mouse, obj->position.x, obj->position.x + 100, obj->position.y, obj->position.y + 100)) {
            obj->selected = !obj->selected;
        }
    }

    // Verifica se o jogador conseguiu completar o desafio
    if (check_collision(mouse, 1000, 1200, 600, 700)) {
        bool success = true;
        for (int i = 0; i < 7; i++) {
            if ((c2->selectable_objects[i].selected && !c2->selectable_objects[i].correct) || 
                (!c2->selectable_objects[i].selected && c2->selectable_objects[i].correct)) {
                success = false;
                break;
            }
        }
        finish_challenge(success, ctx);
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
