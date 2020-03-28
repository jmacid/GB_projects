#include <stdio.h>
#include <gb/gb.h>

#include "GameCharacter.h"
#include "GameSprites/GameSprites.h"


struct GameCharacter ship;
struct GameCharacter bug;
UBYTE spriteSize = 8;

void performantdelay(UINT8 numloops){
    UINT8 i =0;
    for (i = 0; i < numloops; i++){
        wait_vbl_done();
    }
}

void moveGameCharacter(struct GameCharacter* character, UINT8 x, UINT8 y){
    move_sprite(character->spritids[0], x, y);
    move_sprite(character->spritids[1], x + spriteSize, y);
    move_sprite(character->spritids[2], x , y + spriteSize);
    move_sprite(character->spritids[3], x + spriteSize, y + spriteSize);
}

void setupShip(){
    ship.x = 80;
    ship.y = 130;
    ship.width = 16;
    ship.height = 16;

    // set sprite for ship
    set_sprite_tile(0, 0);
    ship.spritids[0] = 0;
    set_sprite_tile(1, 1);
    ship.spritids[1] = 1;
    set_sprite_tile(2, 2);
    ship.spritids[2] = 2;
    set_sprite_tile(3, 3);
    ship.spritids[3] = 3;

    moveGameCharacter(&ship, ship.x, ship.y);

}

void setupBug(){
    bug.x = 30;
    bug.y = 0;
    bug.width = 16;
    bug.height = 16;

    // set sprite for bug
    set_sprite_tile(4, 4);
    bug.spritids[0] = 4;
    set_sprite_tile(5, 5);
    bug.spritids[1] = 5;
    set_sprite_tile(6, 6);
    bug.spritids[2] = 6;
    set_sprite_tile(7, 7);
    bug.spritids[3] = 7;

    moveGameCharacter(&bug, bug.x, bug.y);

}

void main (void) {

    set_sprite_data(0, 8, GameSprites);

    setupShip();
    setupBug();
    SHOW_SPRITES;
    DISPLAY_ON;

    while(1){
        if( joypad() & J_LEFT){
            ship.x -= 2;
            moveGameCharacter( &ship, ship.x, ship.y);
        }
        if( joypad() & J_RIGHT){
            ship.x += 2;
            moveGameCharacter( &ship, ship.x, ship.y);
        }

        bug.y += 5;

        if (bug.y >= 144){
            bug.y = 0;
            bug.x = ship.x;
        }

        moveGameCharacter(&bug, bug.x, bug.y);

        performantdelay(5);
    }

}