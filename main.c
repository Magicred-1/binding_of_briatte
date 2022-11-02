#include <stdio.h>
#include <stdlib.h>
#include "./sources/file_mapping/file_mapping.h"

int main(int argc, char const *argv[])
{
    int* ptrNbLevel = malloc(sizeof(int));
    Room** rooms = createMap("./ressources/maps/config.rtbob", ptrNbLevel);
    int i = 0;
    for (i = 0; i < *ptrNbLevel; i++)
    {
        printRoom(rooms[i]);
    }
    free(ptrNbLevel);
    for (i = 0; i < *ptrNbLevel; i++)
    {
        freeRoom(rooms[i]);
    }
    free(rooms);
    return 0;
}
