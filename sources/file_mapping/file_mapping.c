#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include "file_mapping.h"

Room* newRoom(char** map, int x, int y, int nbLevel)
{
    Room* room = malloc(sizeof(Room));
    //room->map = malloc(sizeof(char*) * x);
    room->map = map;
    room->x = x;
    room->y = y;
    room->nbLevel = nbLevel;
    return room;
}

void checkFileExtension(char* file_source)
{
    char error_message[100] = "The file extension is not valid. Please use .rtbob for maps, .itbob for items or .mtbob for mobs\n";

    char* extension = strrchr(file_source, '.');

    if (strcmp(extension, ".rtbob") != 0)
    {
        printf("The file extension %s of the file is valid.\n", file_source);
    } 
    else if (strcmp(extension, ".itbob") != 0)
    {
        printf("The file extension %s of the file is valid.\n", file_source);
    } 
    else if (strcmp(extension, ".mtbob") != 0)
    {
        printf("The file extension %s of the file is valid.\n", file_source);
    }
    else
    {
        printf("%s", error_message);
    }
}

void createRoom(char* name_file)
{
    /*
        Getting the parameters 
        value from the function into a char with extra line
    */
    char tmp[50];

    // ex : /ressources/maps/config.rtbob
    strcpy(tmp, "./ressources/maps/");
    strcat(tmp, name_file);
    strcat(tmp, ".rtbob");

    FILE *test = fopen(tmp, "r");

    int file_test_lines = fgetc(test);

    if (file_test_lines == EOF)
    { 

        FILE *f = fopen(tmp, "a");

        // check if the file exists and the file extension is .rtbob
        checkFileExtension(tmp);

        int size_x = 0;
        int size_y = 0;
        int idMaps = 0;
        int nbMaps = 0;
        char c;

        printf("Enter the number of maps you want to create : \n");
        scanf("%d", &nbMaps);

        fseek(f, 0, SEEK_SET);
        fprintf(f, "{%d}\n", nbMaps);
        
            for (int i = 0; i < nbMaps+1; i += 1)
            {
                idMaps = i + 1;
                // get the size of the map of each map created

                printf("Enter the size of the map number %d.\n(For example : 7 16 = a map of size 7x16)\n", i += 1);
                scanf("%d %d", &size_x, &size_y);

                if (size_x > 0 && size_y < 100)
                {
                    printf("The size of the map can't be negative.\n");
                    exit(0);
                }
                else
                {
                    fseek(f, 0, SEEK_END);
                    fprintf(f, "[%d|%d]%d\n", size_x, size_y);
                }
            
                for (int i = 0; i < size_x; i += 1)
                {
                    for (int j = 0; j < size_y; j += 1)
                    {
                        printf("Enter the character at the position (%d, %d) : ", i, j);
                        scanf(" %c", &c);

                        if (c >= 'A' && c <= 'Z')
                        {
                            fprintf(f, "%c", c);
                        }
                        else
                        {
                            printf("The character %c is not valid.\n Please enter a character between A and Z.\n", c);
                            j -= 1;
                        }
                    }
                    fprintf(f, "\n");
                }
                fprintf(f, "\n");
            }
        fclose(f);
    }
    else
    {
        printf("The Room named %s already exists.\nPlease create an another one or edit the current one you choosed.", name_file);
        fclose(test);
    }
}

Room** readRoom(char* file_source)
{
    char tmp[50];
        
    // ex : /ressources/maps/config.rtbob
    strcpy(tmp, "./ressources/maps/");
    strcat(tmp, file_source);
    strcat(tmp, ".rtbob");

    FILE *f = fopen(file_source, "r");
    // check if the file exists and the file extension is .rtbob
    if (f == NULL)
    {
        printf("The file does not exist.\n");
        return NULL;
    }
    else
    {
        checkFileExtension(tmp);

        char c;

        int nbMaps = 0;
        int idMaps = 0;
        int size_x = 0;
        int size_y = 0;

        fscanf(f, "{%d}\n", &nbMaps);
        int *ptrNbMaps = nbMaps;
        //printf("nbMaps : %d\n", nbMaps);

        Room** Maps_Created = malloc(sizeof(Room)*nbMaps);

        int indexArrayMaps = 0;

        ///printf("%d %d %d %d \n", nbMaps, size_y, size_x, idMaps);

            for (int i = 0; i < nbMaps; i += 1)
            {
                fscanf(f,"[%d|%d]%d\n",&size_x, &size_y, &idMaps);
                //printf("\n[%d|%d]%d",size_y, size_x, idMaps);

                char** map = malloc((size_x) * sizeof(char*));

                for (int j = 0; j < size_x; j += 1)
                {
                    map[j] = malloc((size_y * 2 - 1) * sizeof(char));
                }

                for (int j = 0; j < size_x; j += 1)
                {
                    for (int k = 0; k < size_y*2-1; k += 1)
                    {
                        fscanf(f, "%c", &c);
                        map[j][k] = c;
                    }
                    fscanf(f, "\n");
                }
                /* for (int l = 0; l < nbMaps; l += 1)
                { */
                    // printf(Rooms_Created[l]->map[0]);
                // }
                Maps_Created[indexArrayMaps] = newRoom(map, size_x, size_y*2-1, idMaps);
                indexArrayMaps += 1;
            }

            /* TO_IMPROVE for stages : for (int room = 0; room < nbMaps; room += 1)
            {
                Rooms_Created[room] = room;
            } */

        fclose(f);
        return Maps_Created;
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

void printMap(Room** mapsArray, int nbMaps)
{
    for (int i = 0; i < nbMaps; i += 1)
    {
        printf("[%d|%d]%d\n", mapsArray[i]->x, (mapsArray[i]->y+1)/2, mapsArray[i]->nbLevel);
        for (int j = 0; j < mapsArray[i]->x; j += 1)
        {
            for (int k = 0; k < mapsArray[i]->y; k += 1)
            {
                printf("%c", mapsArray[i]->map[j][k]);
            }
            printf("\n");
        }
    }
}



void addRoom(char* name_file)
{
    /*
        Getting the parameters 
        value from the function into a char with extra line
    */

    char tmp[50];

    // ex : /ressources/maps/config.rtbob
    strcpy(tmp, "./ressources/maps/");
    strcat(tmp, name_file);
    strcat(tmp, ".rtbob");

    FILE *f = fopen(tmp, "a");
    // check if the file exists and the file extension is .rtbob
    checkFileExtension(tmp);

    int size_x = 0;
    int size_y = 0;
    int idMaps = 0;
    char c;
        
    printf("Enter the size of the map.\n(For example : 7 16 = a map of size 7x16)\n");
    scanf("%d %d", &size_x, &size_y);
    printf("Enter the id of the map : ");
    scanf("%d", &idMaps);
    fprintf(f, "{%d}\n[%d|%d]%d", idMaps,size_x, size_y, idMaps);

        fseek(f, 0, SEEK_SET);
        if (fscanf(f, "{%d}\n") >= idMaps && idMaps > 0)
        {
            fprintf(f, "{%d}\n", idMaps);
        }
        else
        {
            printf("Enter the id of the map : ");
            scanf("%d", &idMaps);
        }
        fseek(f, 0, SEEK_END);
 
        fprintf(f, "\n[%d|%d]%d", size_y, size_x, idMaps);

        for (int i = 0; i < size_x; i += 1)
        {
            for (int j = 0; j < size_y; j += 1)
            {
                printf("Enter the character at the position (%d, %d) : ", i, j);
                scanf(" %c", &c);
                fprintf(f, "%c", c);
            }
        }
        fclose(f);
}

void deleteRoom(Room** arrayMaps, int nbMaps)
{
    int idMaps = 0;
    printf("Enter the id of the map you want to delete : ");
    scanf("%d", &idMaps);

    for (int i = 0; i <= nbMaps; i += 1)
    {
        if (arrayMaps[i]->nbLevel == idMaps)
        {
            freeRoom(arrayMaps[i]);
            arrayMaps[i] = NULL;
        }
    }
}