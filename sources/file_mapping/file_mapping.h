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

// files manipulation functions

void addRoom(char* file_source);

void printRoom(Room* room);

void checkFileExtension(char* file_source);

void freeRoom(Room* room);

// map manipulation functions

void printMap(Room** arrayMaps, int nbMaps);

// CRUD
void createRoom(char* file_source);

Room** readRoom(char* file_source);

// void editRoom(char* file_source, int choiceOfRoom);

void deleteRoom(Room** arrayMaps, int nbMaps);

#endif //FILE_MAPPING_H
