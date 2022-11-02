#include <stdio.h> 
#include <stdlib.h>
#include "file_mapping.h"

Room* newRoom(char** map, int x, int y, int nbLevel)
{
    Room* room = malloc(sizeof(Room));
    room->map = map;
    room->x = x;
    room->y = y;
    room->nbLevel = nbLevel;
    return room;
}

Room** createMap(char* file_source, int* ptrNbLevel)
{
    FILE* file = fopen(file_source, "r");

    int x, y, nbLevel;

    Room** rooms = malloc(sizeof(Room*) * nbLevel);

    *ptrNbLevel = nbLevel;

    if(file != NULL)
    {
        fscanf(file, "%d %d %d", &x, &y, &nbLevel);

        for(int i = 0; i < nbLevel; i += 1) 
        {
            char** map = malloc(sizeof(char*) * y * x);
            for(int j = 0; j < y; j += 1) 
            {
                for(int k = 0; k < x; k += 1) 
                {
                // if the content of the file is not a number, 
                // it will be a letter between 'A' and 'Z'
                    if(fscanf(file, "%c", &map[j][k]) == 0)
                    {
                        k -= 1;
                    }
                    else 
                    {
                        map[j][k] = fgetc(file);
                    }
                }
                rooms[i] = newRoom(map, x, y, i);
            }
        }
    }
    else 
    {
        printf("Error: File not found.\n");
        exit(1);
    }
    fclose(file);
    return rooms;
}



void freeMap(Room** rooms, int nbLevel)
{
    for (int i = 0; i < nbLevel; i += 1)
    {
        freeRoom(rooms[i]);
    }
    free(rooms);
}

void printMap(Room** rooms, int nbLevel)
{
    for (int i = 0; i < nbLevel; i += 1)
    {
        printRoom(rooms[i]);
    }
}

// We can use this fucntion to free the memory and avoid memory leaks
void freeRoom(Room* room)
{
    for(int i = 0; i < room->x; i += 1)
    {
        for(int j = 0; j < room->y; j += 1)
        {
            free(room->map[i]);
        }
    }
    free(room->map);
    free(room);
}

void printRoom(Room* room)
{
    printf("nbLevel = %d", room->nbLevel);  

    for (int i = 0; i < room->y; i += 1)
    {
        for (int j = 0; j < room->x; j += 1)
        {
            printf("%c", room->map[i][j]);
        }
    }
}