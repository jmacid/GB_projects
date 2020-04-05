#include <stdio.h>
#include <gb/gb.h>

#include "img/GBG_data.c"
#include "img/GBG_map.c"
#include "simple_background/simple_background.h"
#include "simple_background/simpleBackgroundMap.h"

UINT8 i;

void performantdelay(UINT8 numloops){
    UINT8 i =0;
    for (i = 0; i < numloops; i++){
        wait_vbl_done();
    }
}


// E4 = 11 10 01 00
// F9 = 11 11 10 01
// FE = 11 11 11 10
// FF = 11 11 11 11
void fadeOut(){
    for(i =0; i < 4; i++){
        switch (i)
        {
        case 0:
            BGP_REG = 0xE4;
            break;
        case 1:
            BGP_REG = 0xF9;
            break;
        case 2:
            BGP_REG = 0xFE;
            break;
        case 3:
            BGP_REG = 0xFF;
            break;
        }
        performantdelay(40);
    }
}

void fadeIn(){
    for(i = 3; i >= 0; i--){
        switch (i)
        {
        case 0:
            BGP_REG = 0xE4;
            break;
        case 1:
            BGP_REG = 0xF9;
            break;
        case 2:
            BGP_REG = 0xFE;
            break;
        }
        performantdelay(40);
    }
}

void main(){
    set_bkg_data(0, 195, GBG_data);
    set_bkg_tiles(0, 0, 20, 18, GBG_map);

    SHOW_BKG;
    DISPLAY_ON;

    waitpad(J_START);

    fadeOut();

    set_bkg_data(0, 7, backgroundTiles);
    set_bkg_tiles(0, 0, 40, 18, simpleBackgroundMap);

    fadeIn();
    //printf("START OF MY GAME");

    //while(1){
    //
    //}

}