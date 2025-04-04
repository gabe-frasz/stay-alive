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
    imgs->map = al_load_bitmap("images/screens/map.png");
    must_init(imgs->map, "map image");
    imgs->menu = al_load_bitmap("images/screens/menu.jpg");
    must_init(imgs->menu, "menu image");
    imgs->end_game = al_load_bitmap("images/screens/end-game.jpeg");
    must_init(imgs->end_game, "end game image");
    imgs->game_over = al_load_bitmap("images/screens/game-over.jpeg");
    must_init(imgs->game_over, "game over image");
    imgs->challenges[0] = al_load_bitmap("images/screens/challenge-1.png");
    must_init(imgs->challenges[0], "challenge 1 image");
    imgs->challenges[1] = al_load_bitmap("images/screens/challenge-2.png");
    must_init(imgs->challenges[1], "challenge 2 image");
    imgs->challenges[2] = al_load_bitmap("images/screens/challenge-3.jpeg");
    must_init(imgs->challenges[2], "challenge 3 image");
    imgs->challenges[3] = al_load_bitmap("images/screens/challenge-4.png");
    must_init(imgs->challenges[3], "challenge 4 image");
    imgs->challenges[4] = al_load_bitmap("images/screens/challenge-5.png");
    must_init(imgs->challenges[4], "challenge 5 image");
    imgs->c5_bonfire = al_load_bitmap("images/screens/challenge-5-bonfire.png");
    must_init(imgs->c5_bonfire, "c5 bonfire image");
    imgs->play_btn = al_load_bitmap("images/buttons/play.png");
    must_init(imgs->play_btn, "play button image");
    imgs->next_btn = al_load_bitmap("images/buttons/next.png");
    must_init(imgs->next_btn, "next button image");
    imgs->menu_btn = al_load_bitmap("images/buttons/menu.png");
    must_init(imgs->play_btn, "menu button image");
    imgs->mute_btn = al_load_bitmap("images/buttons/mute.png");
    must_init(imgs->mute_btn, "mute button image");
    imgs->unmute_btn = al_load_bitmap("images/buttons/unmute.png");
    must_init(imgs->unmute_btn, "unmute button image");
    imgs->char_sprites.front[0] = al_load_bitmap("images/linus/standing-front.png");
    must_init(imgs->char_sprites.front[0], "char front image");
    imgs->char_sprites.front[1] = al_load_bitmap("images/linus/walking-front-1.png");
    must_init(imgs->char_sprites.front[1], "char walking 1 front image");
    imgs->char_sprites.front[2] = al_load_bitmap("images/linus/walking-front-2.png");
    must_init(imgs->char_sprites.front[2], "char walking 2 front image");
    imgs->char_sprites.back[0] = al_load_bitmap("images/linus/standing-back.png");
    must_init(imgs->char_sprites.back[0], "char back image");
    imgs->char_sprites.back[1] = al_load_bitmap("images/linus/walking-back-1.png");
    must_init(imgs->char_sprites.back[1], "char walking 1 back image");
    imgs->char_sprites.back[2] = al_load_bitmap("images/linus/walking-back-2.png");
    must_init(imgs->char_sprites.back[2], "char walking 2 back image");
    imgs->char_sprites.left[0] = al_load_bitmap("images/linus/standing-left.png");
    must_init(imgs->char_sprites.left[0], "char left image");
    imgs->char_sprites.left[1] = al_load_bitmap("images/linus/walking-left-1.png");
    must_init(imgs->char_sprites.left[1], "char walking 1 left image");
    imgs->char_sprites.left[2] = al_load_bitmap("images/linus/walking-left-2.png");
    must_init(imgs->char_sprites.left[2], "char walking 2 left image");
    imgs->char_sprites.right[0] = al_load_bitmap("images/linus/standing-right.png");
    must_init(imgs->char_sprites.right[0], "char right image");
    imgs->char_sprites.right[1] = al_load_bitmap("images/linus/walking-right-1.png");
    must_init(imgs->char_sprites.right[1], "char walking 1 right image");
    imgs->char_sprites.right[2] = al_load_bitmap("images/linus/walking-right-2.png");
    must_init(imgs->char_sprites.right[2], "char walking 2 right image");
    imgs->char_with_basket = al_load_bitmap("images/linus/char-with-basket.png");
    must_init(imgs->char_with_basket, "char with basket image");
    imgs->char_sprites_half_water.front[0] = al_load_bitmap("images/linus/standing-front-half-water.png");
    must_init(imgs->char_sprites_half_water.front[0], "char front half water image");
    imgs->char_sprites_half_water.front[1] = al_load_bitmap("images/linus/walking-front-1-half-water.png");
    must_init(imgs->char_sprites_half_water.front[1], "char walking 1 front half water image");
    imgs->char_sprites_half_water.front[2] = al_load_bitmap("images/linus/walking-front-2-half-water.png");
    must_init(imgs->char_sprites_half_water.front[2], "char walking 2 front half water image");
    imgs->char_sprites_half_water.back[0] = al_load_bitmap("images/linus/standing-back-half-water.png");
    must_init(imgs->char_sprites_half_water.back[0], "char back half water image");
    imgs->char_sprites_half_water.back[1] = al_load_bitmap("images/linus/walking-back-1-half-water.png");
    must_init(imgs->char_sprites_half_water.back[1], "char walking 1 back half water image");
    imgs->char_sprites_half_water.back[2] = al_load_bitmap("images/linus/walking-back-2-half-water.png");
    must_init(imgs->char_sprites_half_water.back[2], "char walking 2 back half water image");
    imgs->char_sprites_half_water.left[0] = al_load_bitmap("images/linus/standing-left-half-water.png");
    must_init(imgs->char_sprites_half_water.left[0], "char left half water image");
    imgs->char_sprites_half_water.left[1] = al_load_bitmap("images/linus/walking-left-1-half-water.png");
    must_init(imgs->char_sprites_half_water.left[1], "char walking 1 left half water image");
    imgs->char_sprites_half_water.left[2] = al_load_bitmap("images/linus/walking-left-2-half-water.png");
    must_init(imgs->char_sprites_half_water.left[2], "char walking 2 left half water image");
    imgs->char_sprites_half_water.right[0] = al_load_bitmap("images/linus/standing-right-half-water.png");
    must_init(imgs->char_sprites_half_water.right[0], "char right half water image");
    imgs->char_sprites_half_water.right[1] = al_load_bitmap("images/linus/walking-right-1-half-water.png");
    must_init(imgs->char_sprites_half_water.right[1], "char walking 1 right half water image");
    imgs->char_sprites_half_water.right[2] = al_load_bitmap("images/linus/walking-right-2-half-water.png");
    must_init(imgs->char_sprites_half_water.right[2], "char walking 2 right half water image");
    imgs->char_sprites_underwater.front = al_load_bitmap("images/linus/underwater-front.png");
    must_init(imgs->char_sprites_underwater.front, "char front underwater image");
    imgs->char_sprites_underwater.back = al_load_bitmap("images/linus/underwater-back.png");
    must_init(imgs->char_sprites_underwater.back, "char back underwater image");
    imgs->char_sprites_underwater.left = al_load_bitmap("images/linus/underwater-left.png");
    must_init(imgs->char_sprites_underwater.left, "char left underwater image");
    imgs->char_sprites_underwater.right = al_load_bitmap("images/linus/underwater-right.png");
    must_init(imgs->char_sprites_underwater.right, "char right underwater image");
    imgs->heart_empty = al_load_bitmap("images/icons/heart-empty.png");
    must_init(imgs->heart_empty, "heart empty image");
    imgs->heart_filled = al_load_bitmap("images/icons/heart.png");
    must_init(imgs->heart_filled, "heart filled image");
    imgs->hunger_empty = al_load_bitmap("images/icons/hunger-empty.png");
    must_init(imgs->hunger_empty, "hunger empty image");
    imgs->hunger_filled = al_load_bitmap("images/icons/hunger.png");
    must_init(imgs->hunger_filled, "hunger filled image");
    imgs->water_bubble = al_load_bitmap("images/icons/water-bubble.png");
    must_init(imgs->water_bubble, "water bubble image");
    imgs->animals[BIRD].front[0] = al_load_bitmap("images/animals/bird-front-1.png");
    must_init(imgs->animals[BIRD].front[0], "bird front 1 image");
    imgs->animals[BIRD].front[1] = al_load_bitmap("images/animals/bird-front-2.png");
    must_init(imgs->animals[BIRD].front[1], "bird front 2 image");
    imgs->animals[BIRD].front[2] = al_load_bitmap("images/animals/bird-front-3.png");
    must_init(imgs->animals[BIRD].front[2], "bird front 3 image");
    imgs->animals[BIRD].back[0] = al_load_bitmap("images/animals/bird-back-1.png");
    must_init(imgs->animals[BIRD].back[0], "bird back 1 image");
    imgs->animals[BIRD].back[1] = al_load_bitmap("images/animals/bird-back-2.png");
    must_init(imgs->animals[BIRD].back[1], "bird back 2 image");
    imgs->animals[BIRD].back[2] = al_load_bitmap("images/animals/bird-back-3.png");
    must_init(imgs->animals[BIRD].back[2], "bird back 3 image");
    imgs->animals[BIRD].left[0] = al_load_bitmap("images/animals/bird-left-1.png");
    must_init(imgs->animals[BIRD].left[0], "bird left 1 image");
    imgs->animals[BIRD].left[1] = al_load_bitmap("images/animals/bird-left-2.png");
    must_init(imgs->animals[BIRD].left[1], "bird left 2 image");
    imgs->animals[BIRD].left[2] = al_load_bitmap("images/animals/bird-left-3.png");
    must_init(imgs->animals[BIRD].left[2], "bird left 3 image");
    imgs->animals[BIRD].right[0] = al_load_bitmap("images/animals/bird-right-1.png");
    must_init(imgs->animals[BIRD].right[0], "bird right 1 image");
    imgs->animals[BIRD].right[1] = al_load_bitmap("images/animals/bird-right-2.png");
    must_init(imgs->animals[BIRD].right[1], "bird right 2 image");
    imgs->animals[BIRD].right[2] = al_load_bitmap("images/animals/bird-right-3.png");
    must_init(imgs->animals[BIRD].right[2], "bird right 3 image");
    imgs->animals[RABBIT].front[0] = al_load_bitmap("images/animals/rabbit-front-1.png");
    must_init(imgs->animals[RABBIT].front[0], "rabbit front 1 image");
    imgs->animals[RABBIT].front[1] = al_load_bitmap("images/animals/rabbit-front-2.png");
    must_init(imgs->animals[RABBIT].front[1], "rabbit front 2 image");
    imgs->animals[RABBIT].front[2] = al_load_bitmap("images/animals/rabbit-front-3.png");
    must_init(imgs->animals[RABBIT].front[2], "rabbit front 3 image");
    imgs->animals[RABBIT].back[0] = al_load_bitmap("images/animals/rabbit-back-1.png");
    must_init(imgs->animals[RABBIT].back[0], "rabbit back 1 image");
    imgs->animals[RABBIT].back[1] = al_load_bitmap("images/animals/rabbit-back-2.png");
    must_init(imgs->animals[RABBIT].back[1], "rabbit back 2 image");
    imgs->animals[RABBIT].back[2] = al_load_bitmap("images/animals/rabbit-back-3.png");
    must_init(imgs->animals[RABBIT].back[2], "rabbit back 3 image");
    imgs->animals[RABBIT].left[0] = al_load_bitmap("images/animals/rabbit-left-1.png");
    must_init(imgs->animals[RABBIT].left[0], "rabbit left 1 image");
    imgs->animals[RABBIT].left[1] = al_load_bitmap("images/animals/rabbit-left-2.png");
    must_init(imgs->animals[RABBIT].left[1], "rabbit left 2 image");
    imgs->animals[RABBIT].left[2] = al_load_bitmap("images/animals/rabbit-left-3.png");
    must_init(imgs->animals[RABBIT].left[2], "rabbit left 3 image");
    imgs->animals[RABBIT].right[0] = al_load_bitmap("images/animals/rabbit-right-1.png");
    must_init(imgs->animals[RABBIT].right[0], "rabbit right 1 image");
    imgs->animals[RABBIT].right[1] = al_load_bitmap("images/animals/rabbit-right-2.png");
    must_init(imgs->animals[RABBIT].right[1], "rabbit right 2 image");
    imgs->animals[RABBIT].right[2] = al_load_bitmap("images/animals/rabbit-right-3.png");
    must_init(imgs->animals[RABBIT].right[2], "rabbit right 3 image");
    imgs->animals[GOAT].front[0] = al_load_bitmap("images/animals/goat-front-1.png");
    must_init(imgs->animals[GOAT].front[0], "goat front 1 image");
    imgs->animals[GOAT].front[1] = al_load_bitmap("images/animals/goat-front-2.png");
    must_init(imgs->animals[GOAT].front[1], "goat front 2 image");
    imgs->animals[GOAT].front[2] = al_load_bitmap("images/animals/goat-front-3.png");
    must_init(imgs->animals[GOAT].front[2], "goat front 3 image");
    imgs->animals[GOAT].back[0] = al_load_bitmap("images/animals/goat-back-1.png");
    must_init(imgs->animals[GOAT].back[0], "goat back 1 image");
    imgs->animals[GOAT].back[1] = al_load_bitmap("images/animals/goat-back-2.png");
    must_init(imgs->animals[GOAT].back[1], "goat back 2 image");
    imgs->animals[GOAT].back[2] = al_load_bitmap("images/animals/goat-back-3.png");
    must_init(imgs->animals[GOAT].back[2], "goat back 3 image");
    imgs->animals[GOAT].left[0] = al_load_bitmap("images/animals/goat-left-1.png");
    must_init(imgs->animals[GOAT].left[0], "goat left 1 image");
    imgs->animals[GOAT].left[1] = al_load_bitmap("images/animals/goat-left-2.png");
    must_init(imgs->animals[GOAT].left[1], "goat left 2 image");
    imgs->animals[GOAT].left[2] = al_load_bitmap("images/animals/goat-left-3.png");
    must_init(imgs->animals[GOAT].left[2], "goat left 3 image");
    imgs->animals[GOAT].right[0] = al_load_bitmap("images/animals/goat-right-1.png");
    must_init(imgs->animals[GOAT].right[0], "goat right 1 image");
    imgs->animals[GOAT].right[1] = al_load_bitmap("images/animals/goat-right-2.png");
    must_init(imgs->animals[GOAT].right[1], "goat right 2 image");
    imgs->animals[GOAT].right[2] = al_load_bitmap("images/animals/goat-right-3.png");
    must_init(imgs->animals[GOAT].right[2], "goat right 3 image");
    imgs->animals[SHEEP].front[0] = al_load_bitmap("images/animals/sheep-front-1.png");
    must_init(imgs->animals[SHEEP].front[0], "sheep front 1 image");
    imgs->animals[SHEEP].front[1] = al_load_bitmap("images/animals/sheep-front-2.png");
    must_init(imgs->animals[SHEEP].front[1], "sheep front 2 image");
    imgs->animals[SHEEP].front[2] = al_load_bitmap("images/animals/sheep-front-3.png");
    must_init(imgs->animals[SHEEP].front[2], "sheep front 3 image");
    imgs->animals[SHEEP].back[0] = al_load_bitmap("images/animals/sheep-back-1.png");
    must_init(imgs->animals[SHEEP].back[0], "sheep back 1 image");
    imgs->animals[SHEEP].back[1] = al_load_bitmap("images/animals/sheep-back-2.png");
    must_init(imgs->animals[SHEEP].back[1], "sheep back 2 image");
    imgs->animals[SHEEP].back[2] = al_load_bitmap("images/animals/sheep-back-3.png");
    must_init(imgs->animals[SHEEP].back[2], "sheep back 3 image");
    imgs->animals[SHEEP].left[0] = al_load_bitmap("images/animals/sheep-left-1.png");
    must_init(imgs->animals[SHEEP].left[0], "sheep left 1 image");
    imgs->animals[SHEEP].left[1] = al_load_bitmap("images/animals/sheep-left-2.png");
    must_init(imgs->animals[SHEEP].left[1], "sheep left 2 image");
    imgs->animals[SHEEP].left[2] = al_load_bitmap("images/animals/sheep-left-3.png");
    must_init(imgs->animals[SHEEP].left[2], "sheep left 3 image");
    imgs->animals[SHEEP].right[0] = al_load_bitmap("images/animals/sheep-right-1.png");
    must_init(imgs->animals[SHEEP].right[0], "sheep right 1 image");
    imgs->animals[SHEEP].right[1] = al_load_bitmap("images/animals/sheep-right-2.png");
    must_init(imgs->animals[SHEEP].right[1], "sheep right 2 image");
    imgs->animals[SHEEP].right[2] = al_load_bitmap("images/animals/sheep-right-3.png");
    must_init(imgs->animals[SHEEP].right[2], "sheep right 3 image");
    imgs->animals[CAT].front[0] = al_load_bitmap("images/animals/cat-front-1.png");
    must_init(imgs->animals[CAT].front[0], "cat front 1 image");
    imgs->animals[CAT].front[1] = al_load_bitmap("images/animals/cat-front-2.png");
    must_init(imgs->animals[CAT].front[1], "cat front 2 image");
    imgs->animals[CAT].front[2] = al_load_bitmap("images/animals/cat-front-3.png");
    must_init(imgs->animals[CAT].front[2], "cat front 3 image");
    imgs->animals[CAT].back[0] = al_load_bitmap("images/animals/cat-back-1.png");
    must_init(imgs->animals[CAT].back[0], "cat back 1 image");
    imgs->animals[CAT].back[1] = al_load_bitmap("images/animals/cat-back-2.png");
    must_init(imgs->animals[CAT].back[1], "cat back 2 image");
    imgs->animals[CAT].back[2] = al_load_bitmap("images/animals/cat-back-3.png");
    must_init(imgs->animals[CAT].back[2], "cat back 3 image");
    imgs->animals[CAT].left[0] = al_load_bitmap("images/animals/cat-left-1.png");
    must_init(imgs->animals[CAT].left[0], "cat left 1 image");
    imgs->animals[CAT].left[1] = al_load_bitmap("images/animals/cat-left-2.png");
    must_init(imgs->animals[CAT].left[1], "cat left 2 image");
    imgs->animals[CAT].left[2] = al_load_bitmap("images/animals/cat-left-3.png");
    must_init(imgs->animals[CAT].left[2], "cat left 3 image");
    imgs->animals[CAT].right[0] = al_load_bitmap("images/animals/cat-right-1.png");
    must_init(imgs->animals[CAT].right[0], "cat right 1 image");
    imgs->animals[CAT].right[1] = al_load_bitmap("images/animals/cat-right-2.png");
    must_init(imgs->animals[CAT].right[1], "cat right 2 image");
    imgs->animals[CAT].right[2] = al_load_bitmap("images/animals/cat-right-3.png");
    must_init(imgs->animals[CAT].right[2], "cat right 3 image");
    imgs->animals[SNAKE].front[0] = al_load_bitmap("images/animals/snake-front-1.png");
    must_init(imgs->animals[SNAKE].front[0], "snake front 1 image");
    imgs->animals[SNAKE].front[1] = al_load_bitmap("images/animals/snake-front-2.png");
    must_init(imgs->animals[SNAKE].front[1], "snake front 2 image");
    imgs->animals[SNAKE].front[2] = al_load_bitmap("images/animals/snake-front-3.png");
    must_init(imgs->animals[SNAKE].front[2], "snake front 3 image");
    imgs->animals[SNAKE].back[0] = al_load_bitmap("images/animals/snake-back-1.png");
    must_init(imgs->animals[SNAKE].back[0], "snake back 1 image");
    imgs->animals[SNAKE].back[1] = al_load_bitmap("images/animals/snake-back-2.png");
    must_init(imgs->animals[SNAKE].back[1], "snake back 2 image");
    imgs->animals[SNAKE].back[2] = al_load_bitmap("images/animals/snake-back-3.png");
    must_init(imgs->animals[SNAKE].back[2], "snake back 3 image");
    imgs->animals[SNAKE].left[0] = al_load_bitmap("images/animals/snake-left-1.png");
    must_init(imgs->animals[SNAKE].left[0], "snake left 1 image");
    imgs->animals[SNAKE].left[1] = al_load_bitmap("images/animals/snake-left-2.png");
    must_init(imgs->animals[SNAKE].left[1], "snake left 2 image");
    imgs->animals[SNAKE].left[2] = al_load_bitmap("images/animals/snake-left-3.png");
    must_init(imgs->animals[SNAKE].left[2], "snake left 3 image");
    imgs->animals[SNAKE].right[0] = al_load_bitmap("images/animals/snake-right-1.png");
    must_init(imgs->animals[SNAKE].right[0], "snake right 1 image");
    imgs->animals[SNAKE].right[1] = al_load_bitmap("images/animals/snake-right-2.png");
    must_init(imgs->animals[SNAKE].right[1], "snake right 2 image");
    imgs->animals[SNAKE].right[2] = al_load_bitmap("images/animals/snake-right-3.png");
    must_init(imgs->animals[SNAKE].right[2], "snake right 3 image");
    imgs->medicinal_plants[0] = al_load_bitmap("images/challenge-objects/cuaxinguba.png");
    must_init(imgs->medicinal_plants[0], "medicinal plant 1 image");
    imgs->medicinal_plants[1] = al_load_bitmap("images/challenge-objects/dente-de-leao.png");
    must_init(imgs->medicinal_plants[1], "medicinal plant 2 image");
    imgs->medicinal_plants[2] = al_load_bitmap("images/challenge-objects/erva-de-sao-joao.png");
    must_init(imgs->medicinal_plants[2], "medicinal plant 3 image");
    imgs->medicinal_plants[3] = al_load_bitmap("images/challenge-objects/ginseng.png");
    must_init(imgs->medicinal_plants[3], "medicinal plant 4 image");
    imgs->medicinal_plants[4] = al_load_bitmap("images/challenge-objects/japecanga.png");
    must_init(imgs->medicinal_plants[4], "medicinal plant 5 image");
    imgs->snake_alert = al_load_bitmap("images/icons/snake-alert.png");
    must_init(imgs->snake_alert, "snake alert image");
    imgs->c1_placeable_objects[0] = al_load_bitmap("images/challenge-objects/plants-and-seaweeds.png");
    must_init(imgs->c1_placeable_objects[0], "c1 placeable object 1 image");
    imgs->c1_placeable_objects[1] = al_load_bitmap("images/challenge-objects/giraffe.png");
    must_init(imgs->c1_placeable_objects[1], "c1 placeable object 2 image");
    imgs->c1_placeable_objects[2] = al_load_bitmap("images/challenge-objects/lion.png");
    must_init(imgs->c1_placeable_objects[2], "c1 placeable object 3 image");
    imgs->c1_placeable_objects[3] = al_load_bitmap("images/challenge-objects/worms-and-bacteria.png");
    must_init(imgs->c1_placeable_objects[3], "c1 placeable object 4 image");
    imgs->c2_selectable_objects[0] = al_load_bitmap("images/challenge-objects/bottle.png");
    must_init(imgs->c2_selectable_objects[0], "c2 selectable object 1 image");
    imgs->c2_selectable_objects[1] = al_load_bitmap("images/challenge-objects/cloth.png");
    must_init(imgs->c2_selectable_objects[1], "c2 selectable object 2 image");
    imgs->c2_selectable_objects[2] = al_load_bitmap("images/challenge-objects/plastic-bag.png");
    must_init(imgs->c2_selectable_objects[2], "c2 selectable object 3 image");
    imgs->c2_selectable_objects[3] = al_load_bitmap("images/challenge-objects/bottle.png");
    must_init(imgs->c2_selectable_objects[3], "c2 selectable object 4 image");
    imgs->c2_selectable_objects[4] = al_load_bitmap("images/challenge-objects/stones.png");
    must_init(imgs->c2_selectable_objects[4], "c2 selectable object 5 image");
    imgs->c2_selectable_objects[5] = al_load_bitmap("images/challenge-objects/bottle-cap.png");
    must_init(imgs->c2_selectable_objects[5], "c2 selectable object 6 image");
    imgs->c2_selectable_objects[6] = al_load_bitmap("images/challenge-objects/wood-sticks.png");
    must_init(imgs->c2_selectable_objects[6], "c2 selectable object 7 image");
    imgs->c5_selectable_objects[0] = al_load_bitmap("images/challenge-objects/dry-leaves.png");
    must_init(imgs->c5_selectable_objects[0], "c5 selectable object 1 image");
    imgs->c5_selectable_objects[1] = al_load_bitmap("images/challenge-objects/dry-wood-sticks.png");
    must_init(imgs->c5_selectable_objects[1], "c5 selectable object 2 image");
    imgs->c5_selectable_objects[2] = al_load_bitmap("images/challenge-objects/wet-wood-sticks.png");
    must_init(imgs->c5_selectable_objects[2], "c5 selectable object 3 image");
    imgs->c5_selectable_objects[3] = al_load_bitmap("images/challenge-objects/leaves.png");
    must_init(imgs->c5_selectable_objects[3], "c5 selectable object 4 image");
    imgs->c5_selectable_objects[4] = al_load_bitmap("images/challenge-objects/sand.png");
    must_init(imgs->c5_selectable_objects[4], "c5 selectable object 5 image");
    imgs->c5_selectable_objects[5] = al_load_bitmap("images/challenge-objects/shell.png");
    must_init(imgs->c5_selectable_objects[5], "c5 selectable object 6 image");
    imgs->c5_selectable_objects[6] = al_load_bitmap("images/challenge-objects/seaweed.png");
    must_init(imgs->c5_selectable_objects[6], "c5 selectable object 7 image");
    imgs->c5_selectable_objects[7] = al_load_bitmap("images/challenge-objects/rotten-fruits.png");
    must_init(imgs->c5_selectable_objects[7], "c5 selectable object 8 image");
    imgs->apple = al_load_bitmap("images/challenge-objects/apple.png");
    must_init(imgs->apple, "apple image");
    imgs->mushroom = al_load_bitmap("images/challenge-objects/mushroom.png");
    must_init(imgs->mushroom, "mushroom image");
    imgs->rub_sprites[0] = al_load_bitmap("images/screens/rub-bonfire-1.png");
    must_init(imgs->rub_sprites[0], "rub bonfire 1 image");
    imgs->rub_sprites[1] = al_load_bitmap("images/screens/rub-bonfire-2.png");
    must_init(imgs->rub_sprites[1], "rub bonfire 2 image");
    imgs->rub_sprites[2] = al_load_bitmap("images/screens/rub-bonfire-3.png");
    must_init(imgs->rub_sprites[2], "rub bonfire 3 image");
    imgs->rub_sprites[3] = al_load_bitmap("images/screens/rub-bonfire-4.png");
    must_init(imgs->rub_sprites[3], "rub bonfire 4 image");
}

void load_sounds(Sounds* sounds) {
    sounds->footstep[0].sample = al_load_sample("sounds/footstep-1.wav");
    must_init(sounds->footstep[0].sample, "footstep 1 sound");
    sounds->footstep[1].sample = al_load_sample("sounds/footstep-2.wav");
    must_init(sounds->footstep[1].sample, "footstep 2 sound");
    sounds->water_footstep[0].sample = al_load_sample("sounds/water-footstep-1.wav");
    must_init(sounds->water_footstep[0].sample, "water footstep 1 sound");
    sounds->water_footstep[1].sample = al_load_sample("sounds/water-footstep-2.wav");
    must_init(sounds->water_footstep[1].sample, "water footstep 2 sound");
    sounds->typing.sample = al_load_sample("sounds/typing.wav");
    must_init(sounds->typing.sample, "typing sound");
    sounds->challenges[0].sample = al_load_sample("sounds/challenge-1.wav");
    must_init(sounds->challenges[0].sample, "challenge 1 sound");
    sounds->challenges[1].sample = al_load_sample("sounds/challenge-2.wav");
    must_init(sounds->challenges[1].sample, "challenge 2 sound");
    sounds->challenges[2].sample = al_load_sample("sounds/challenge-3.wav");
    must_init(sounds->challenges[2].sample, "challenge 3 sound");
    sounds->challenges[3].sample = al_load_sample("sounds/challenge-4.wav");
    must_init(sounds->challenges[3].sample, "challenge 4 sound");
    sounds->challenges[4].sample = al_load_sample("sounds/challenge-5.wav");
    must_init(sounds->challenges[4].sample, "challenge 5 sound");
    sounds->hurting.sample = al_load_sample("sounds/hurting.wav");
    must_init(sounds->hurting.sample, "hurting sound");
    sounds->panting.sample = al_load_sample("sounds/PRE-RI-GO.wav");
    must_init(sounds->panting.sample, "panting sound");
    sounds->water_bubbles.sample = al_load_sample("sounds/water-bubbles.wav");
    must_init(sounds->water_bubbles.sample, "water bubbles sound");
    sounds->animals[BIRD][0].sample = al_load_sample("sounds/seagulls-1.wav");
    must_init(sounds->animals[BIRD][0].sample, "bird 1 sound");
    sounds->animals[BIRD][1].sample = al_load_sample("sounds/seagulls-2.wav");
    must_init(sounds->animals[BIRD][1].sample, "bird 2 sound");
    sounds->animals[BIRD][2].sample = al_load_sample("sounds/seagulls-3.wav");
    must_init(sounds->animals[BIRD][2].sample, "bird 3 sound");
    sounds->animals[BIRD][3].sample = al_load_sample("sounds/seagulls-4.wav");
    must_init(sounds->animals[BIRD][3].sample, "bird 4 sound");
    sounds->animals[CAT][0].sample = al_load_sample("sounds/cat-1.wav");
    must_init(sounds->animals[CAT][0].sample, "cat 1 sound");
    sounds->animals[CAT][1].sample = al_load_sample("sounds/cat-2.wav");
    must_init(sounds->animals[CAT][1].sample, "cat 2 sound");
    sounds->animals[CAT][2].sample = al_load_sample("sounds/cat-3.wav");
    must_init(sounds->animals[CAT][2].sample, "cat 3 sound");
    sounds->animals[CAT][3].sample = al_load_sample("sounds/cat-4.wav");
    must_init(sounds->animals[CAT][3].sample, "cat 4 sound");
    sounds->animals[SHEEP][0].sample = al_load_sample("sounds/sheep-1.wav");
    must_init(sounds->animals[SHEEP][0].sample, "sheep 1 sound");
    sounds->animals[SHEEP][1].sample = al_load_sample("sounds/sheep-2.wav");
    must_init(sounds->animals[SHEEP][1].sample, "sheep 2 sound");
    sounds->animals[SHEEP][2].sample = al_load_sample("sounds/sheep-3.wav");
    must_init(sounds->animals[SHEEP][2].sample, "sheep 3 sound");
    sounds->animals[SHEEP][3].sample = al_load_sample("sounds/sheep-4.wav");
    must_init(sounds->animals[SHEEP][3].sample, "sheep 4 sound");
    sounds->animals[SNAKE][0].sample = al_load_sample("sounds/snake-1.wav");
    must_init(sounds->animals[SNAKE][0].sample, "snake 1 sound");
    sounds->animals[SNAKE][1].sample = al_load_sample("sounds/snake-2.wav");
    must_init(sounds->animals[SNAKE][1].sample, "snake 2 sound");
    sounds->animals[SNAKE][2].sample = al_load_sample("sounds/snake-3.wav");
    must_init(sounds->animals[SNAKE][2].sample, "snake 3 sound");
    sounds->animals[SNAKE][3].sample = al_load_sample("sounds/snake-4.wav");
    must_init(sounds->animals[SNAKE][3].sample, "snake 4 sound");
    sounds->animals[GOAT][0].sample = al_load_sample("sounds/goat-1.wav");
    must_init(sounds->animals[GOAT][0].sample, "goat 1 sound");
    sounds->animals[GOAT][1].sample = al_load_sample("sounds/goat-2.wav");
    must_init(sounds->animals[GOAT][1].sample, "goat 2 sound");
    sounds->animals[GOAT][2].sample = al_load_sample("sounds/goat-3.wav");
    must_init(sounds->animals[GOAT][2].sample, "goat 3 sound");
    sounds->animals[GOAT][3].sample = al_load_sample("sounds/goat-4.wav");
    must_init(sounds->animals[GOAT][3].sample, "goat 4 sound");
    sounds->success.sample = al_load_sample("sounds/success.wav");
    must_init(sounds->success.sample, "success sound");
}

void load_videos(Videos* videos) {
    videos->tutorials[0] = al_open_video("videos/challenge-1-in.ogv");
    must_init(videos->tutorials[0], "challenge 1 in video");
    videos->tutorials[1] = al_open_video("videos/challenge-1-out.ogv");
    must_init(videos->tutorials[1], "challenge 1 out video");
    videos->tutorials[2] = al_open_video("videos/challenge-1-linus-in.ogv");
    must_init(videos->tutorials[2], "challenge 1 linus in video");
    videos->tutorials[3] = al_open_video("videos/challenge-1-linus-out.ogv");
    must_init(videos->tutorials[3], "challenge 1 linus out video");
    videos->tutorials[4] = al_open_video("videos/challenge-2-in.ogv");
    must_init(videos->tutorials[4], "challenge 2 in video");
    videos->tutorials[5] = al_open_video("videos/challenge-2-out.ogv");
    must_init(videos->tutorials[5], "challenge 2 out video");
    videos->tutorials[6] = al_open_video("videos/challenge-2-linus-in.ogv");
    must_init(videos->tutorials[6], "challenge 2 linus in video");
    videos->tutorials[7] = al_open_video("videos/challenge-2-linus-out.ogv");
    must_init(videos->tutorials[7], "challenge 2 linus out video");
    videos->tutorials[8] = al_open_video("videos/challenge-3-in.ogv");
    must_init(videos->tutorials[8], "challenge 3 in video");
    videos->tutorials[9] = al_open_video("videos/challenge-3-out.ogv");
    must_init(videos->tutorials[9], "challenge 3 out video");
    videos->tutorials[10] = al_open_video("videos/challenge-4-in-p1.ogv");
    must_init(videos->tutorials[10], "challenge 4 pt 1 in video");
    videos->tutorials[11] = al_open_video("videos/challenge-4-out-p1.ogv");
    must_init(videos->tutorials[11], "challenge 4 pt 1 out video");
    videos->tutorials[12] = al_open_video("videos/challenge-4-in-p2.ogv");
    must_init(videos->tutorials[12], "challenge 4 pt 2 in video");
    videos->tutorials[13] = al_open_video("videos/challenge-4-out-p2.ogv");
    must_init(videos->tutorials[13], "challenge 4 pt 2 out video");
    videos->tutorials[14] = al_open_video("videos/challenge-4-in-p3.ogv");
    must_init(videos->tutorials[14], "challenge 4 in video");
    videos->tutorials[15] = al_open_video("videos/challenge-4-out-p3.ogv");
    must_init(videos->tutorials[15], "challenge 4 out video");
    videos->tutorials[16] = al_open_video("videos/challenge-5-in.ogv");
    must_init(videos->tutorials[16], "challenge 5 in video");
    videos->tutorials[17] = al_open_video("videos/challenge-5-out.ogv");
    must_init(videos->tutorials[17], "challenge 5 out video");
    videos->c2_distillation = al_open_video("videos/distillation.ogv");
    must_init(videos->c2_distillation, "c2 distilation video");
    videos->rescue = al_open_video("videos/rescue.ogv");
    must_init(videos->rescue, "rescue video");
    videos->island = al_open_video("videos/island-bg.ogv");
    must_init(videos->island, "island video");
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

void play_audio(Audio* audio, bool loop) {
    if (audio->is_playing) return;

    if (loop) {
        al_play_sample(audio->sample, audio->volume, audio->pan, audio->speed, ALLEGRO_PLAYMODE_LOOP, &audio->id);
        audio->is_playing = true;
    } else {
        al_play_sample(audio->sample, audio->volume, audio->pan, audio->speed, ALLEGRO_PLAYMODE_ONCE, &audio->id);
    }
}

void stop_audio(Audio* audio) {
    if (!audio->is_playing) return;

    al_stop_sample(&audio->id);
    audio->is_playing = false;
}

void set_audio(Audio* audio, float volume, float pan, float speed) {
    audio->volume = volume;
    audio->pan = pan;
    audio->speed = speed;
}

int calculate_seconds_left(time_t start_time, int duration_in_seconds) {
    time_t now = time(0);
    int seconds_left = duration_in_seconds - (now - start_time);
    return seconds_left;
}

void set_rectangle(Rectangle* r, float x1, float x2, float y1, float y2) {
    r->x1 = x1;
    r->x2 = x2;
    r->y1 = y1;
    r->y2 = y2;
}

void set_obstacle(Obstacle* obstacle, float x, float y, int width, int height) {
    obstacle->position.x = x;
    obstacle->position.y = y;
    obstacle->width = width;
    obstacle->height = height;
}

void set_animal(Animal* a, float initial_x, float initial_y, int width, int height, int speed, Rectangle bounds) {
    a->position.x = initial_x;
    a->position.y = initial_y;
    a->width = width;
    a->height = height;
    a->speed = speed;
    a->bounds = bounds;
    a->is_moving = false;
    a->birds_count = 0;
    a->move = &move_animal;
    a->sort_destination = &sort_destination;
}

void set_selectable_object(Selectable_Object* obj, float x, float y, int width, int height, bool correct) {
    obj->position.x = x;
    obj->position.y = y;
    obj->width = width;
    obj->height = height;
    obj->correct = correct;
}

void set_wanted_object(Wanted_Object* w, float x, float y, int width, int height) {
    w->position.x = x;
    w->position.y = y;
    w->width = width;
    w->height = height;
}
