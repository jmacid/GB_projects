#include <stdio.h>
#include <gb/gb.h>

#include "smilerSprite\smilerSprites.h"

#define STEP_SPRITE 5

void main(){
    UINT8 current_sprite_index = 0;
    set_sprite_data(0, 2, smiler);   
    set_sprite_tile(0, 0);
    move_sprite(0, 88, 78);
    SHOW_SPRITES;

    while(1){
        
        switch ( joypad() ){
        case J_LEFT:
            scroll_sprite(0, -1 * STEP_SPRITE, 0);
            break;
        case J_RIGHT:
            scroll_sprite(0, STEP_SPRITE, 0);
            break;
        case J_UP:
            scroll_sprite(0, 0, -1 * STEP_SPRITE);
            break;
        case J_DOWN:
            scroll_sprite(0, 0, STEP_SPRITE);
            break;
        }


        delay(75);
        
    }
}

