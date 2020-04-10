#include <gb/gb.h>
#include <stdio.h>
#include "include/keyboarddata.h"
#include "include/keyboardmap.h"
#include "include/sprites.h"
#include "include/cursor.h"


struct Cursor cursor;
UBYTE keydown;
const UINT8 mincursorx = 12;
const UINT8 mincursory = 80;
const UINT8 maxcursorx = 156;
const UINT8 maxcursory = 128;
UINT8 nameCharacterIndex;
UINT8 playerName[18];
UBYTE playerHasName;

void performantdelay(UINT8 numloops){
    UINT8 i =0;
    for (i = 0; i < numloops; i++){
        wait_vbl_done();
    }
}

UBYTE isWithinKeyboard(UINT8 x, UINT8 y){
    if( x  == 140 && y == 144 || x  == 156 && y == 144 ) {
        return 1;
    } 
    return x >= mincursorx  && x <= maxcursorx && y >= mincursory && y <= maxcursory;  

}

void removeFromPlayerName() {
    if( nameCharacterIndex > 0){
        nameCharacterIndex --;
        playerName[nameCharacterIndex] = 0;
    }
}

void addToPlayerName(struct Cursor* cursor){
    UINT8 characterIndex = cursor->row * 10 + cursor->col + 1;

    if ( nameCharacterIndex == 18) return;

    playerName[ nameCharacterIndex] = characterIndex;
    nameCharacterIndex ++;

}

void drawPlayerName(){
    set_bkg_tiles( 1, 4, 18, 1, playerName);
}

void updatePlayerName(struct Cursor* cursor){
    if (cursor->col == 8 && cursor->row == 4) { 
        // backspace - delete
        removeFromPlayerName();
        drawPlayerName();

    }
    else if(cursor->col == 9 && cursor->row == 4){
        //player finished
        playerHasName = 1;
    }
    else{
        // add to player name
        addToPlayerName(cursor);
        drawPlayerName();
    }

}



void main(){
    // load cursor sprite
    set_sprite_data(0, 1, sprites);
    set_sprite_tile(0, 0);

    cursor.x = 12;
    cursor.y = 80;
    cursor.col = 0;
    cursor.row = 0;
    move_sprite(0, cursor.x, cursor.y);
    
    set_bkg_data(0, 45, keyboarddata);
    set_bkg_tiles(0, 0, 20, 18, keyboardmap);
    scroll_bkg(-4 , 0); //move half a sprite to give even spacing either side of keyboard

    SHOW_BKG;
    SHOW_SPRITES;
    DISPLAY_ON;

    while ( !playerHasName )
    {
        if( keydown ){
            waitpadup();
            keydown = 0;
        }
        switch ( joypad() )
        {
        case J_UP:
            if ( isWithinKeyboard (cursor.x, cursor.y - 16) ){
                cursor.y -= 16;
                cursor.row --;
                scroll_sprite(0, 0, -16);
                keydown = 1;                    
            }
            break;
        case J_DOWN:
        if ( isWithinKeyboard (cursor.x, cursor.y + 16) ){
                cursor.y += 16;
                cursor.row ++;
                scroll_sprite(0, 0, 16);
                keydown = 1;
            }
            break;
        case J_LEFT:
            if ( isWithinKeyboard (cursor.x - 16, cursor.y) ){
                cursor.x -= 16;
                cursor.col --;
                scroll_sprite(0, -16, 0);
                keydown = 1;
            }
            break;
        case J_RIGHT:
            if ( isWithinKeyboard (cursor.x + 16, cursor.y ) ){
                cursor.x += 16;
                cursor.col ++;
                scroll_sprite(0, 16, 0);
                keydown = 1;
            }
            break;
        case J_A:
            updatePlayerName( &cursor);
            keydown = 1;
            break;
        }

        performantdelay(2);
    }

    

}
