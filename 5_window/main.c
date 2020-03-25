#include <gb/gb.h>
#include <gb/font.h>
#include "simple_background/simple_background.h"
#include "simple_background/simpleBackgroundMap.h"
#include "simple_background/windowMap.h"

void main(void){
    font_t min_font;

    font_init();
    min_font = font_load(font_min); // 36 tiles
    font_set(min_font);

    // load
    set_bkg_data(37, 7, backgroundTiles);
    set_bkg_tiles(0, 0, 40, 18, simpleBackgroundMap);

    set_win_tiles(0, 0, 5, 1, windowMap);

    move_win(7,120);



    SHOW_BKG;
    SHOW_WIN;
    DISPLAY_ON;

    while (1)
    {
        scroll_bkg(1,0);
        delay(100);
    }
    

}