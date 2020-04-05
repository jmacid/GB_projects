#include <stdio.h>
#include <gb/gb.h>

#include "img/GBG_data.c"
#include "img/GBG_map.c"


void main(){
    set_bkg_data(0, 195, GBG_data);
    set_bkg_tiles(0, 0, 20, 18, GBG_map);

    SHOW_BKG;
    DISPLAY_ON;

    waitpad(J_START);

    printf("START OF MY GAME");
    //while(1){
    //
    //}

}