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

// files manipulation functions and test functions

// get the last id of the file
int getLastId();

void deleteRoomFromFile(int roomID);

void deleteMapFromFile();

void checkFileExtension();

void freeRoom(Room* room);

void printRoom(Room* room);

// map manipulation functions

void printMap(Room** arrayMaps, int nbMaps);

void editRoom(int choiceOfRoom);

// CRUD
void createMap();

Room** readMap(int* ptrNbMaps);

void updateMap(int choiceOfRoom);

void deleteRoom(Room** arrayMaps);

#endif //FILE_MAPPING_H
