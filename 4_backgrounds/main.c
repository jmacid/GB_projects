#include <gb/gb.h>
#include "simple_background/simple_background.h"
#include "simple_background/simpleBackgroundMap.h"

void main(void){
    // load
    set_bkg_data(0, 7, backgroundTiles);
    set_bkg_tiles(0, 0, 40, 18, simpleBackgroundMap);

    SHOW_BKG;
    DISPLAY_ON;

    while (1)
    {
        scroll_bkg(1,0);
        delay(100);
    }
    

}