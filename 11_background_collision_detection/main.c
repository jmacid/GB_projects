#include <gb/gb.h>
#include <stdio.h>

#include "sprites/MazeMap.h"
#include "sprites/MazeSprites.h"
#include "sprites./Snail.h"

const char blankmap[1] = {0x00};
UINT8 playerLocation[2];
UBYTE debug, hasKey, gameRunning;

void performantdelay(UINT8 numloops){
    UINT8 i =0;
    for (i = 0; i < numloops; i++){
        wait_vbl_done();
    }
}

UBYTE canPlayerMove(INT8 newplayex, UINT8 newplayery){
    UINT16 indexTLx, indexTLy, tileindexTL;  // index top left 
    UBYTE result;

    indexTLx = ( newplayex - 8) / 8;  // minus offset divided by sprite size
    indexTLy = ( newplayery - 16) / 8;
    tileindexTL = 20 * indexTLy + indexTLx;  // mpa matrix: 20 byes per row + columns

    if( debug ){
        printf( "%u %u\n", (UINT16) newplayex, (UINT16) newplayery);
        printf( "%u %u %u\n", (UINT16) indexTLx, (UINT16) indexTLy, (UINT16) tileindexTL);
    }

    result = MazeMap[tileindexTL] == blankmap[0];

    if (tileindexTL == 321){
        // collect key
        set_bkg_tiles(1, 16, 1, 1, blankmap[0]);
        result = 1;
        hasKey = 1;
    }
    else if( tileindexTL == 263 && hasKey) {
        // open door
        set_bkg_tiles(3, 13, 1 , 1, blankmap);
        result = 1;
    }
    else if( tileindexTL == 340) {
        // finish game
        gameRunning = 0;
        HIDE_SPRITES;
        printf("\n \n \n \n \n \n \n \n \n      YOU WIN!");
        result = 1;
    }
    
    return result;
}


void animateSprite( UINT8 spriteindex, INT8 movex, INT8 movey){
    while(movex != 0){
        scroll_sprite( spriteindex, movex < 0 ? -1 : 1, 0);
        movex += ( movex < 0 ? 1 : -1 );
        wait_vbl_done();
    }
    while(movey != 0){
        scroll_sprite( spriteindex, 0, movey < 0 ? -1 : 1);
        movey += ( movey < 0 ? 1 : -1 );
        wait_vbl_done();
    }
}

void main (void){
    set_bkg_data(0,4, MazeSprites);
    set_bkg_tiles(0, 0, 20, 18, MazeMap);

    set_sprite_data(0,1, Snail);
    set_sprite_tile(0, 0);

    playerLocation[0] = 16;
    playerLocation[1] = 24;
    gameRunning = 1;

    move_sprite(0, playerLocation[0], playerLocation[1]);

    SHOW_SPRITES;
    SHOW_BKG;
    DISPLAY_ON;

    while(gameRunning){
        if ( joypad() & J_A){
            debug = 1;
        }
        if( joypad() & J_LEFT){
            if( canPlayerMove( playerLocation[0] - 8, playerLocation[1] )){
                playerLocation[0] -= 8;
                animateSprite(0, -8, 0 );
            }
        }
        else if ( joypad() & J_RIGHT){
            if( canPlayerMove( playerLocation[0] + 8, playerLocation[1] )){
                playerLocation[0] += 8;
                animateSprite(0, 8, 0 );
            }
        }
        else if ( joypad() & J_UP){
            if( canPlayerMove( playerLocation[0], playerLocation[1] - 8 ) ){
                playerLocation[1] -= 8;
                animateSprite(0, 0, -8);
            }
        }
        else if ( joypad() & J_DOWN){
            if( canPlayerMove( playerLocation[0], playerLocation[1] + 8)){
                playerLocation[1] += 8;  
                animateSprite(0, 0, 8);          
            }
        }

        performantdelay(6);
    }
}