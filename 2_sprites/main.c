#include <stdio.h>
#include <gb/gb.h>

#include "smilerSprite\smilerSprites.h"

void main(){
    UINT8 current_sprite_index = 0;
    set_sprite_data(0, 2, smiler);   
    set_sprite_tile(0, 0);
    move_sprite(0, 88, 78);
    SHOW_SPRITES;

    while(1){
        if ( !current_sprite_index ) {
            current_sprite_index = 1;
        } else {
            current_sprite_index = 0;
        }
        set_sprite_tile(0, current_sprite_index);
        delay(750);
        scroll_sprite(0, 10, 0);
    }
}

