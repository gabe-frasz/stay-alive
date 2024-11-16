#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <stdio.h>
#include <stdlib.h>
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
    imgs->challenges[4] = al_load_bitmap("images/challenge-5.png");
    must_init(imgs->challenges[4], "challenge 5 image");
    imgs->play_btn = al_load_bitmap("images/play-btn.png");
    must_init(imgs->play_btn, "play button image");
    imgs->menu_btn = al_load_bitmap("images/menu-btn.png");
    must_init(imgs->play_btn, "menu button image");
    imgs->small_next_btn = al_load_bitmap("images/small-next-btn.png");
    must_init(imgs->small_next_btn, "small next button image");
    imgs->small_play_btn = al_load_bitmap("images/small-play-btn.png");
    must_init(imgs->small_play_btn, "small play button image");
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
    imgs->animals[BIRD].front[0] = al_load_bitmap("images/bird-front-1.png");
    must_init(imgs->animals[BIRD].front[0], "bird front 1 image");
    imgs->animals[BIRD].front[1] = al_load_bitmap("images/bird-front-2.png");
    must_init(imgs->animals[BIRD].front[1], "bird front 2 image");
    imgs->animals[BIRD].front[2] = al_load_bitmap("images/bird-front-3.png");
    must_init(imgs->animals[BIRD].front[2], "bird front 3 image");
    imgs->animals[BIRD].back[0] = al_load_bitmap("images/bird-back-1.png");
    must_init(imgs->animals[BIRD].back[0], "bird back 1 image");
    imgs->animals[BIRD].back[1] = al_load_bitmap("images/bird-back-2.png");
    must_init(imgs->animals[BIRD].back[1], "bird back 2 image");
    imgs->animals[BIRD].back[2] = al_load_bitmap("images/bird-back-3.png");
    must_init(imgs->animals[BIRD].back[2], "bird back 3 image");
    imgs->animals[BIRD].left[0] = al_load_bitmap("images/bird-left-1.png");
    must_init(imgs->animals[BIRD].left[0], "bird left 1 image");
    imgs->animals[BIRD].left[1] = al_load_bitmap("images/bird-left-2.png");
    must_init(imgs->animals[BIRD].left[1], "bird left 2 image");
    imgs->animals[BIRD].left[2] = al_load_bitmap("images/bird-left-3.png");
    must_init(imgs->animals[BIRD].left[2], "bird left 3 image");
    imgs->animals[BIRD].right[0] = al_load_bitmap("images/bird-right-1.png");
    must_init(imgs->animals[BIRD].right[0], "bird right 1 image");
    imgs->animals[BIRD].right[1] = al_load_bitmap("images/bird-right-2.png");
    must_init(imgs->animals[BIRD].right[1], "bird right 2 image");
    imgs->animals[BIRD].right[2] = al_load_bitmap("images/bird-right-3.png");
    must_init(imgs->animals[BIRD].right[2], "bird right 3 image");
    imgs->animals[RABBIT].front[0] = al_load_bitmap("images/rabbit-front-1.png");
    must_init(imgs->animals[RABBIT].front[0], "rabbit front 1 image");
    imgs->animals[RABBIT].front[1] = al_load_bitmap("images/rabbit-front-2.png");
    must_init(imgs->animals[RABBIT].front[1], "rabbit front 2 image");
    imgs->animals[RABBIT].front[2] = al_load_bitmap("images/rabbit-front-3.png");
    must_init(imgs->animals[RABBIT].front[2], "rabbit front 3 image");
    imgs->animals[RABBIT].back[0] = al_load_bitmap("images/rabbit-back-1.png");
    must_init(imgs->animals[RABBIT].back[0], "rabbit back 1 image");
    imgs->animals[RABBIT].back[1] = al_load_bitmap("images/rabbit-back-2.png");
    must_init(imgs->animals[RABBIT].back[1], "rabbit back 2 image");
    imgs->animals[RABBIT].back[2] = al_load_bitmap("images/rabbit-back-3.png");
    must_init(imgs->animals[RABBIT].back[2], "rabbit back 3 image");
    imgs->animals[RABBIT].left[0] = al_load_bitmap("images/rabbit-left-1.png");
    must_init(imgs->animals[RABBIT].left[0], "rabbit left 1 image");
    imgs->animals[RABBIT].left[1] = al_load_bitmap("images/rabbit-left-2.png");
    must_init(imgs->animals[RABBIT].left[1], "rabbit left 2 image");
    imgs->animals[RABBIT].left[2] = al_load_bitmap("images/rabbit-left-3.png");
    must_init(imgs->animals[RABBIT].left[2], "rabbit left 3 image");
    imgs->animals[RABBIT].right[0] = al_load_bitmap("images/rabbit-right-1.png");
    must_init(imgs->animals[RABBIT].right[0], "rabbit right 1 image");
    imgs->animals[RABBIT].right[1] = al_load_bitmap("images/rabbit-right-2.png");
    must_init(imgs->animals[RABBIT].right[1], "rabbit right 2 image");
    imgs->animals[RABBIT].right[2] = al_load_bitmap("images/rabbit-right-3.png");
    must_init(imgs->animals[RABBIT].right[2], "rabbit right 3 image");
    imgs->animals[GOAT].front[0] = al_load_bitmap("images/goat-front-1.png");
    must_init(imgs->animals[GOAT].front[0], "goat front 1 image");
    imgs->animals[GOAT].front[1] = al_load_bitmap("images/goat-front-2.png");
    must_init(imgs->animals[GOAT].front[1], "goat front 2 image");
    imgs->animals[GOAT].front[2] = al_load_bitmap("images/goat-front-3.png");
    must_init(imgs->animals[GOAT].front[2], "goat front 3 image");
    imgs->animals[GOAT].back[0] = al_load_bitmap("images/goat-back-1.png");
    must_init(imgs->animals[GOAT].back[0], "goat back 1 image");
    imgs->animals[GOAT].back[1] = al_load_bitmap("images/goat-back-2.png");
    must_init(imgs->animals[GOAT].back[1], "goat back 2 image");
    imgs->animals[GOAT].back[2] = al_load_bitmap("images/goat-back-3.png");
    must_init(imgs->animals[GOAT].back[2], "goat back 3 image");
    imgs->animals[GOAT].left[0] = al_load_bitmap("images/goat-left-1.png");
    must_init(imgs->animals[GOAT].left[0], "goat left 1 image");
    imgs->animals[GOAT].left[1] = al_load_bitmap("images/goat-left-2.png");
    must_init(imgs->animals[GOAT].left[1], "goat left 2 image");
    imgs->animals[GOAT].left[2] = al_load_bitmap("images/goat-left-3.png");
    must_init(imgs->animals[GOAT].left[2], "goat left 3 image");
    imgs->animals[GOAT].right[0] = al_load_bitmap("images/goat-right-1.png");
    must_init(imgs->animals[GOAT].right[0], "goat right 1 image");
    imgs->animals[GOAT].right[1] = al_load_bitmap("images/goat-right-2.png");
    must_init(imgs->animals[GOAT].right[1], "goat right 2 image");
    imgs->animals[GOAT].right[2] = al_load_bitmap("images/goat-right-3.png");
    must_init(imgs->animals[GOAT].right[2], "goat right 3 image");
    imgs->animals[SHEEP].front[0] = al_load_bitmap("images/sheep-front-1.png");
    must_init(imgs->animals[SHEEP].front[0], "sheep front 1 image");
    imgs->animals[SHEEP].front[1] = al_load_bitmap("images/sheep-front-2.png");
    must_init(imgs->animals[SHEEP].front[1], "sheep front 2 image");
    imgs->animals[SHEEP].front[2] = al_load_bitmap("images/sheep-front-3.png");
    must_init(imgs->animals[SHEEP].front[2], "sheep front 3 image");
    imgs->animals[SHEEP].back[0] = al_load_bitmap("images/sheep-back-1.png");
    must_init(imgs->animals[SHEEP].back[0], "sheep back 1 image");
    imgs->animals[SHEEP].back[1] = al_load_bitmap("images/sheep-back-2.png");    
    must_init(imgs->animals[SHEEP].back[1], "sheep back 2 image");
    imgs->animals[SHEEP].back[2] = al_load_bitmap("images/sheep-back-3.png");
    must_init(imgs->animals[SHEEP].back[2], "sheep back 3 image");
    imgs->animals[SHEEP].left[0] = al_load_bitmap("images/sheep-left-1.png");
    must_init(imgs->animals[SHEEP].left[0], "sheep left 1 image");
    imgs->animals[SHEEP].left[1] = al_load_bitmap("images/sheep-left-2.png");
    must_init(imgs->animals[SHEEP].left[1], "sheep left 2 image");
    imgs->animals[SHEEP].left[2] = al_load_bitmap("images/sheep-left-3.png");
    must_init(imgs->animals[SHEEP].left[2], "sheep left 3 image");
    imgs->animals[SHEEP].right[0] = al_load_bitmap("images/sheep-right-1.png");
    must_init(imgs->animals[SHEEP].right[0], "sheep right 1 image");
    imgs->animals[SHEEP].right[1] = al_load_bitmap("images/sheep-right-2.png");
    must_init(imgs->animals[SHEEP].right[1], "sheep right 2 image");
    imgs->animals[SHEEP].right[2] = al_load_bitmap("images/sheep-right-3.png");
    must_init(imgs->animals[SHEEP].right[2], "sheep right 3 image");
    imgs->animals[CAT].front[0] = al_load_bitmap("images/cat-front-1.png");
    must_init(imgs->animals[CAT].front[0], "cat front 1 image");
    imgs->animals[CAT].front[1] = al_load_bitmap("images/cat-front-2.png");
    must_init(imgs->animals[CAT].front[1], "cat front 2 image");
    imgs->animals[CAT].front[2] = al_load_bitmap("images/cat-front-3.png");
    must_init(imgs->animals[CAT].front[2], "cat front 3 image");
    imgs->animals[CAT].back[0] = al_load_bitmap("images/cat-back-1.png");
    must_init(imgs->animals[CAT].back[0], "cat back 1 image");
    imgs->animals[CAT].back[1] = al_load_bitmap("images/cat-back-2.png");
    must_init(imgs->animals[CAT].back[1], "cat back 2 image");
    imgs->animals[CAT].back[2] = al_load_bitmap("images/cat-back-3.png");
    must_init(imgs->animals[CAT].back[2], "cat back 3 image");
    imgs->animals[CAT].left[0] = al_load_bitmap("images/cat-left-1.png");
    must_init(imgs->animals[CAT].left[0], "cat left 1 image");
    imgs->animals[CAT].left[1] = al_load_bitmap("images/cat-left-2.png");
    must_init(imgs->animals[CAT].left[1], "cat left 2 image");
    imgs->animals[CAT].left[2] = al_load_bitmap("images/cat-left-3.png");
    must_init(imgs->animals[CAT].left[2], "cat left 3 image");
    imgs->animals[CAT].right[0] = al_load_bitmap("images/cat-right-1.png");
    must_init(imgs->animals[CAT].right[0], "cat right 1 image");
    imgs->animals[CAT].right[1] = al_load_bitmap("images/cat-right-2.png");
    must_init(imgs->animals[CAT].right[1], "cat right 2 image");
    imgs->animals[CAT].right[2] = al_load_bitmap("images/cat-right-3.png");
    must_init(imgs->animals[CAT].right[2], "cat right 3 image");
    imgs->animals[SNAKE].front[0] = al_load_bitmap("images/snake-front-1.png");
    must_init(imgs->animals[SNAKE].front[0], "snake front 1 image");
    imgs->animals[SNAKE].front[1] = al_load_bitmap("images/snake-front-2.png");
    must_init(imgs->animals[SNAKE].front[1], "snake front 2 image");
    imgs->animals[SNAKE].front[2] = al_load_bitmap("images/snake-front-3.png");
    must_init(imgs->animals[SNAKE].front[2], "snake front 3 image");
    imgs->animals[SNAKE].back[0] = al_load_bitmap("images/snake-back-1.png");
    must_init(imgs->animals[SNAKE].back[0], "snake back 1 image");
    imgs->animals[SNAKE].back[1] = al_load_bitmap("images/snake-back-2.png");
    must_init(imgs->animals[SNAKE].back[1], "snake back 2 image");
    imgs->animals[SNAKE].back[2] = al_load_bitmap("images/snake-back-3.png");
    must_init(imgs->animals[SNAKE].back[2], "snake back 3 image");
    imgs->animals[SNAKE].left[0] = al_load_bitmap("images/snake-left-1.png");    
    must_init(imgs->animals[SNAKE].left[0], "snake left 1 image");
    imgs->animals[SNAKE].left[1] = al_load_bitmap("images/snake-left-2.png");
    must_init(imgs->animals[SNAKE].left[1], "snake left 2 image");
    imgs->animals[SNAKE].left[2] = al_load_bitmap("images/snake-left-3.png");
    must_init(imgs->animals[SNAKE].left[2], "snake left 3 image");
    imgs->animals[SNAKE].right[0] = al_load_bitmap("images/snake-right-1.png");
    must_init(imgs->animals[SNAKE].right[0], "snake right 1 image");
    imgs->animals[SNAKE].right[1] = al_load_bitmap("images/snake-right-2.png");
    must_init(imgs->animals[SNAKE].right[1], "snake right 2 image");
    imgs->animals[SNAKE].right[2] = al_load_bitmap("images/snake-right-3.png");
    must_init(imgs->animals[SNAKE].right[2], "snake right 3 image");
    imgs->medicinal_plants[0] = al_load_bitmap("images/cuaxinguba.png");
    must_init(imgs->medicinal_plants[0], "medicinal plant 1 image");
    imgs->medicinal_plants[1] = al_load_bitmap("images/dente-de-leao.png");
    must_init(imgs->medicinal_plants[1], "medicinal plant 2 image");
    imgs->medicinal_plants[2] = al_load_bitmap("images/erva-de-sao-joao.png");
    must_init(imgs->medicinal_plants[2], "medicinal plant 3 image");
    imgs->medicinal_plants[3] = al_load_bitmap("images/ginseng.png");
    must_init(imgs->medicinal_plants[3], "medicinal plant 4 image");
    imgs->medicinal_plants[4] = al_load_bitmap("images/japecanga.png");
    must_init(imgs->medicinal_plants[4], "medicinal plant 5 image");
    imgs->snake_alert = al_load_bitmap("images/snake-alert.png");
    must_init(imgs->snake_alert, "snake alert image");
    imgs->c1_placeable_objects[0] = al_load_bitmap("images/plants-and-seaweeds.png");
    must_init(imgs->c1_placeable_objects[0], "c1 placeable object 1 image");
    imgs->c1_placeable_objects[1] = al_load_bitmap("images/giraffe.png");
    must_init(imgs->c1_placeable_objects[1], "c1 placeable object 2 image");
    imgs->c1_placeable_objects[2] = al_load_bitmap("images/lion.png");
    must_init(imgs->c1_placeable_objects[2], "c1 placeable object 3 image");
    imgs->c1_placeable_objects[3] = al_load_bitmap("images/worms-and-bacteria.png");
    must_init(imgs->c1_placeable_objects[3], "c1 placeable object 4 image");
}

void load_sounds(Sounds* sounds) {
    sounds->footstep[0] = al_load_sample("sounds/footstep-1.wav");
    must_init(sounds->footstep[0], "footstep 1 sound");
    sounds->footstep[1] = al_load_sample("sounds/footstep-2.wav");
    must_init(sounds->footstep[1], "footstep 2 sound");
    sounds->typing = al_load_sample("sounds/typing.wav");
    must_init(sounds->typing, "typing sound");
}

void load_videos(Videos* videos) {
    videos->tutorials[0] = al_open_video("videos/challenge-1-in.ogv");
    must_init(videos->tutorials[0], "challenge 1 in video");
    videos->tutorials[1] = al_open_video("videos/challenge-1-out.ogv");
    must_init(videos->tutorials[1], "challenge 1 out video");
    videos->tutorials[2] = al_open_video("videos/challenge-2-in.ogv");
    must_init(videos->tutorials[2], "challenge 2 in video");
    videos->tutorials[3] = al_open_video("videos/challenge-2-out.ogv");
    must_init(videos->tutorials[3], "challenge 2 out video");
    videos->tutorials[4] = al_open_video("videos/challenge-2-linus-in.ogv");
    must_init(videos->tutorials[4], "challenge 2 linus in video");
    videos->tutorials[5] = al_open_video("videos/challenge-2-linus-out.ogv");
    must_init(videos->tutorials[5], "challenge 2 linus out video");
    videos->tutorials[6] = al_open_video("videos/challenge-3-in.ogv");
    must_init(videos->tutorials[6], "challenge 3 in video");
    videos->tutorials[7] = al_open_video("videos/challenge-3-out.ogv");
    must_init(videos->tutorials[7], "challenge 3 out video");
    videos->tutorials[8] = al_open_video("videos/challenge-4-in-p1.ogv");
    must_init(videos->tutorials[8], "challenge 4 pt 1 in video");
    videos->tutorials[9] = al_open_video("videos/challenge-4-in-p1.ogv");
    must_init(videos->tutorials[9], "challenge 4 pt 1 out video");
    videos->tutorials[10] = al_open_video("videos/challenge-4-in-p2.ogv");
    must_init(videos->tutorials[10], "challenge 4 pt 2 in video");
    videos->tutorials[11] = al_open_video("videos/challenge-4-in-p2.ogv");
    must_init(videos->tutorials[11], "challenge 4 pt 2 out video");
    videos->tutorials[12] = al_open_video("videos/challenge-4-in-p3.ogv");
    must_init(videos->tutorials[12], "challenge 4 pt 3 in video");
    videos->tutorials[13] = al_open_video("videos/challenge-4-in-p3.ogv");
    must_init(videos->tutorials[13], "challenge 4 pt 3 out video");
    videos->tutorials[14] = al_open_video("videos/challenge-5-in.ogv");
    must_init(videos->tutorials[14], "challenge 5 in video");
    videos->tutorials[15] = al_open_video("videos/challenge-5-in.ogv");
    must_init(videos->tutorials[15], "challenge 5 out video");
    
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

void sort_destination(Animal* self) {
    switch (self->type) {
    case BIRD:
        self->destination.y = rand() % (MAP_SIZE + 700);

        if (self->position.x <= 0) {
            self->destination.x = MAP_SIZE + 700;
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
    default:
        self->destination.x = rand() % (int)(self->bounds.x2 - self->bounds.x1) + self->bounds.x1;
        self->destination.y = rand() % (int)(self->bounds.y2 - self->bounds.y1) + self->bounds.y1;
        break;
    }
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
