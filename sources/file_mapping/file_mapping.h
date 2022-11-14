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

void addRoom(char* name_file, int nbMapsToAdd);

void printRoom(Room* room);

void checkFileExtension(char* file_source);

void freeRoom(Room* room);

int getLastId(char* name_file);

// map manipulation functions

void printMap(Room** arrayMaps, int nbMaps);

char* getAllMapName();

// CRUD
void createMap(char* file_source);

Room** readMap(char* file_source, int* ptrNbMaps);

// void editRoom(char* file_source, int choiceOfRoom);

void deleteMap(char* file_source);

void deleteRoom(Room** arrayMaps, int nbMaps);

#endif //FILE_MAPPING_H
