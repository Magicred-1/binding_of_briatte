#include <stdio.h> 
#include <stdlib.h>
#include "game_run.h"

typedef enum 
{
    UP = 72,
    DOWN = 80,
    LEFT = 75,
    RIGHT = 77,
    SPACE = 32
} keystroke;

void playerMovement()
{
    keystroke key = 0;
    key = getchar();
    switch (key)
    {
        case UP:
            printf("UP");
            break;
        case DOWN:
            printf("DOWN");
            break;
        case LEFT:
            printf("LEFT");
            break;
        case RIGHT:
            printf("RIGHT");
            break;
        case SPACE:
            printf("SPACE");
            break;
        default:
            printf("ERROR");
            break;
    }
}