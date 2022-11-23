/*
**  Filename : game_run.h
**
**  Made by : Djason Gadiou <djason.gadiou.sio@gmail.com>
**
**  Description : Give the player the possibility to map the keyboard and play the game
*/
#include "../file_mapping/file_mapping.h"

#ifndef GAME_RUN_H_
#define GAME_RUN_H_

typedef enum Keystroke Keystroke;
typedef struct Player Player;

void playerMovement(Room** arrayMaps, int nbMaps);

void iniatializeRoom(Room** arrayMaps, int *ptrNbMaps, Player Player);

#endif /* GAME_RUN_H_ */