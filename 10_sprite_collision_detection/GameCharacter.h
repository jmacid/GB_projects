#include <gb/gb.h>

// generical character structure: id, position, graphics

typedef struct {
    UBYTE spritids[4]; //all character use 4 sprites
    UINT8 x;
    UINT8 y;
    UINT8 width;
    UINT8 height;
} GameCharacter;