#include <stdio.h>
#include <gb/gb.h>

volatile INT8 player_location[2] = {10, 100};       //stores two INT8 x and y position of player
volatile BYTE jumping = 0;                          // jumping variable. (0 is not jumping, 1 is jumping) 
const UINT8 gravity = -2;
volatile UINT8 currentspeedY = 0;
const UINT8 floorYposition = 100;

unsigned char bloke[] =
{
  0x00,0x00,0x38,0x38,0x7C,0x44,0x7F,0x7F,
  0x44,0x74,0x46,0x7C,0x40,0x78,0x24,0x3C,
  0x18,0x3C,0x00,0x24,0x00,0x24,0x00,0x24,
  0x00,0x24,0x00,0x36,0x00,0x00,0x00,0x00,
  0x00,0x00,0x38,0x38,0x7C,0x44,0x7F,0x7F,
  0x44,0x74,0x46,0x7C,0x40,0x78,0x24,0x3C,
  0x18,0x3C,0x00,0x22,0x00,0x22,0x00,0x22,
  0x00,0x23,0x00,0x30,0x00,0x00,0x00,0x00,
  0x00,0x00,0x38,0x38,0x7C,0x44,0x7F,0x7F,
  0x44,0x74,0x46,0x7C,0x40,0x78,0x24,0x3C,
  0x18,0x3C,0x00,0x42,0x00,0x42,0x00,0x42,
  0x00,0x42,0x00,0x63,0x00,0x00,0x00,0x00,
  0x00,0x00,0x38,0x38,0x7C,0x44,0x7F,0x7F,
  0x44,0x74,0x46,0x7C,0x40,0x78,0x24,0x3C,
  0x18,0x3C,0x00,0x44,0x00,0x44,0x00,0x44,
  0x00,0x64,0x00,0x06,0x00,0x00,0x00,0x00
};

void performantdelay(UINT8 numloops){
    UINT8 i =0;
    for (i = 0; i < numloops; i++){
        wait_vbl_done();
    }
}

INT8 would_hit_surface( UINT8 projectedYposition){
    if ( projectedYposition >= floorYposition)
        return floorYposition;
    
    return -1;
}

void jump(UINT8 spriteID, UINT8 spriteLocation[2]){
    INT8 possibleSurfaceY ;
    if( !jumping ) {
        jumping = 1;
        currentspeedY = 10;
    }
    
    // work out current speed - effect of graviries aceleration down
    currentspeedY = currentspeedY + gravity;

    spriteLocation[1] -= currentspeedY;

    possibleSurfaceY = would_hit_surface(spriteLocation[1]);

    if (possibleSurfaceY > -1) {
        jumping = 0;
        spriteLocation[1] = floorYposition;
    }

    move_sprite( spriteID, spriteLocation[0], spriteLocation[1]);
}

void main(void){
    
    set_sprite_data(0, 8, bloke);   //defines the sprite data
    set_sprite_tile(0,0);           //defines the tile numbers

    // player_location[0] = 10;
    // player_location[1] = 100;
    move_sprite(0, player_location[0], player_location[1]);        // move sprite 0 to (10,100)

    DISPLAY_ON;

    SHOW_SPRITES;

    while (1){
        
        if ( ( joypad() & J_A ) || jumping ){
            jump(0, player_location);
        }

        if ( joypad() & J_LEFT) {
            player_location[0] -= 2;
            move_sprite(0, player_location[0], player_location[1]);
        }
        if ( joypad() & J_RIGHT) {
            player_location[0] += 2;
            move_sprite(0, player_location[0], player_location[1]);
        }

        performantdelay(5);

    }
    
}