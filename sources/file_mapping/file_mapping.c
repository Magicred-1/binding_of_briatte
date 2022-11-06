#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
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

void checkFileExtension(char* file_source)
{
    char* extension = strrchr(file_source, '.');
    if (strcmp(extension, ".rtbob") != 0)
    {
        printf("The file extension is not correct. Please use .rtbob\n");
        exit(1);
    }
}

Room** createMap(char* file_source)
{
    FILE *f = fopen(file_source, "r");
    // check if the file exists and the file extension is .rtbob
    if (f == NULL)
    {
        printf("The file does not exist.\n");
        return NULL;
    }
    else
    {
        checkFileExtension(file_source);

        char c;

        int nbMaps = 0;
        int idMaps = 0;
        int size_x = 0;
        int size_y = 0;

        fscanf(f, "{%d}\n", &nbMaps);
        printf("nbMaps : %d\n", nbMaps);

        ///printf("%d %d %d %d \n", nbMaps, size_y, size_x, idMaps);

            for (int i = 0; i <= nbMaps*2-1; i += 1)
            {
                if(i % 2 == 0){
                    fscanf(f,"\n[%d|%d]%d",&size_y, &size_x, &idMaps);
                    printf("\n[%d|%d]%d",size_y, size_x, idMaps);
                }

                char** map = malloc((size_x * 2 - 1) * sizeof(char*));

                for (int j = 0; j < size_x; j += 1)
                {
                    map[j] = malloc((size_y * 2 - 1) * sizeof(char));
                }

                for (int j = 0; j < size_x; j += 1)
                {
                    
                    for (int k = 0; k < size_y; k += 1)
                    {
                        fscanf(f, "%c", &c);
                        map[j][k] = c;
                    }
                }

                Room* room = newRoom(map, size_x, size_y, i);
                printRoom(room);
                //printf("i = %d\n",i);

            }

        fclose(f);
    }
}

// We can use this function to free the memory and avoid memory leaks
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
    // printf("nbLevel = %d", room->nbLevel);  

    for (int i = 0; i < room->x; i += 1)
    {
        for (int j = 0; j < room->y; j += 1)
        {
            printf("%c", room->map[i][j]);
        }
    }
}