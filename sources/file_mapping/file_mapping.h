/*
**  Filename : file_mapping.h
**
**  Made by : Djason Gadiou <djason.gadiou.sio@gmail.com>
**
**  Description : Create a map (a two dimension array) from a file 
**  to be use in the game later on.
*/

#ifndef FILE_MAPPING_H
#define FILE_MAPPING_H

struct Room
{
    char** map;
    int x;
    int y;
    int nbLevel;
};

typedef struct Room Room;

Room** createMap(char* file_source, int* ptrNbLevel);

Room* newRoom(char** map, int x, int y, int nbLevel);

void freeRoom(Room* room);

void printRoom(Room* room);

#endif //FILE_MAPPING_H
