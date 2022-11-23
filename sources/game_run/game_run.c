#include <stdio.h> 
#include <stdlib.h>
#include <conio.h>
#include "game_run.h"
#include "../file_mapping/file_mapping.h"
#include "../cli/cli_commands.h"

/*
    Z = UP
    S = DOWN
    Q = LEFT
    D = RIGHT
*/

typedef enum Keystroke
{
    UP = 122,
    DOWN = 155,
    LEFT = 113,
    RIGHT = 100,
    SPACE = 32,
    UP_SHOOT = 8,
    DOWN_SHOOT = 5,
    LEFT_SHOOT = 4,
    RIGHT_SHOOT = 6
} Keystroke;

typedef struct Player
{
    int x;
    int y;
} Player;

void iniatializeRoom(Room** arrayMaps, int *ptrNbMaps, Player Player)
{
    int nbMaps = *ptrNbMaps;

    int height = arrayMaps[nbMaps]->y;
    int width = arrayMaps[nbMaps]->x;

    for (int i = 0; i < width; i += 1)
    {
        for (int j = 0; j < height; j += 1)
        {
            // we localize the player on the map
            if (arrayMaps[nbMaps]->map[i][j] == 'P')
            {
                Player.x = i;
                Player.y = j;
            }
        }
    }

    // we print the map
        // launch the CLI
    // launch the game
    Room** room = readMap(&nbMaps);
    printRoom(room[4]);
}

void playerMovement(Room** arrayMaps, int nbMaps)
{
    // we initialize the player
    Player Player;
    Player.x = 0;
    Player.y = 0;

    // we initialize the room and the player position into it
    iniatializeRoom(arrayMaps, &nbMaps, Player);
    
    Keystroke key = 0;
    while (1)
    {
        if (kbhit())
        {
            key = getch();
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
                case UP_SHOOT:
                    printf("SHOOT UP");
                    break;
                case DOWN_SHOOT:
                    printf("DOWN SHOOT");
                    break;
                case LEFT_SHOOT:
                    printf("LEFT SHOOT");
                    break;
                case RIGHT_SHOOT:
                    printf("RIGHT SHOOT");
                    break;
                default:
                    break;
            }
            clearScreen();
        }
    }
}