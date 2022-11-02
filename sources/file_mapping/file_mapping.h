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

Room* newRoom(char** map, int x, int y, int nbLevel);

Room** createMap(char* file_source);

void checkFileExtension(char* file_source);

void freeRoom(Room* room);

void printRoom(Room* room);

void printArrayMaps(Room** arrayMaps, int nbMaps);

#endif //FILE_MAPPING_H
