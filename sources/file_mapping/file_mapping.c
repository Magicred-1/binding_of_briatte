#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "file_mapping.h"
#include "../file_extension_checker/file_extension_checker.h"

// RGB COLOR in console for the better display
#define RED   "\x1B[31m"
#define GREEN   "\x1B[32m"
#define BLUE   "\x1B[34m"
#define YELLOW   "\x1B[33m"
#define RESET "\x1B[0m"

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

/* 
    can be used when only more than room has been already created
    in the map file.
*/
int getLastId()
{
    int idMaps = 0;
    FILE *file = fopen("./ressources/maps/config.rtbob", "r");
    if (file != NULL)
    {
        /*
            get the last ID of the map 
            (number of max rooms created) 
            inside the map file.
        */
        fscanf(file, "{%d}\n", &idMaps);
        fclose(file);
        return idMaps;
    }
    else
    {
        printf("The map file is empty.\n\n");
        // createMap();
    }
}

void deleteRoomFromFile(int roomID) //TODO
{
    int idMaps = roomID;
    int size_x = 0;
    int size_y = 0;
    int nbMaps = getLastId();

    FILE *file = fopen("./ressources/maps/config.rtbob", "r");
    FILE *fileTemp = fopen("./ressources/maps/configTemp.rtbob", "w");

    char getCharacter;
    if (file != NULL)
    {
        while (fgetc(file) != EOF)
        {
            fprintf(fileTemp, "{%d}\n", nbMaps = nbMaps - idMaps);
        }
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
    // print the amount of maps available
    if (nbMaps > 0) 
    {
        printf("There's " BLUE "%d" RESET " maps in the file.\n\n", nbMaps);

        for (int i = 0; i < nbMaps; i += 1)
        {
            printf("Map number : " YELLOW "%d\n" RESET "", mapsArray[i]->nbLevel);
            printf("[%d|%d]" YELLOW "%d" RESET"\n", mapsArray[i]->x, (mapsArray[i]->y+1)/2, mapsArray[i]->nbLevel);
            for (int j = 0; j < mapsArray[i]->x; j += 1)
            {
                for (int k = 0; k < mapsArray[i]->y; k += 1)
                {
                    printf("%c", mapsArray[i]->map[j][k]);
                }
                printf("\n");
            }
            printf("\n");
        }
    }
    else
    {
        printf("" RED "There's no map available please create at least one first.\n\n" RESET "");
    }
}

// CRUD 
void createMap()
{
    char temporarySource[80] = "./ressources/maps/config.rtbob";
    
    int size_x;
    int size_y;
    int idMaps = 0;
    int nbMaps = 0;

    char character;

    FILE *file = fopen(temporarySource, "r");

    // if the file is empty 
    if (file == NULL)
    {
        FILE *file = fopen(temporarySource, "a");
        // check if the file exists and the file extension is .rtbob
        checkFileExtension(temporarySource);

        printf("Enter the number of maps you want to create : \n");
        scanf("%d", &nbMaps);

        fseek(file, 0, SEEK_SET);
        fprintf(file, "{%d}\n", nbMaps);
        
            for (int i = 0; i < nbMaps; i += 1)
            {
                idMaps = i + 1;
                // get the size of the map of each map created

                printf("Enter the size of the map number %d.\n(For example : 7 16 = a map of size 7x16)\n", i+1);
                scanf("%d %d", &size_x, &size_y);
                
                /* 
                    we want to both verify that the user inputs are numbers
                    the size of the map to be between 1 and 100
                */
                if (isdigit(size_x) && isdigit(size_y))
                {
                    if (size_x >= 1 && size_x <= 100 && size_y >= 1 && size_y <= 100) 
                    {
                        printf("\nThe size of the map is not valid.\nPlease enter a size between 1 and 100.\n");
                        // if the size is not valid we delete the file and exit the program
                        exit(0);
                    }
                }

                fseek(file, 0, SEEK_END);
                fprintf(file, "[%d|%d]%d\n", size_x, size_y, idMaps);

                // fflush(stdin);
            
                for (int j = 0; j < size_x; j += 1)
                {
                    for (int k = 0; k < size_y; k += 1)
                    {
                        /* 
                            we get the character from the user and print each place of the 
                            of the char in the array. 
                            Start with : Enter the character at the position (1, 1).
                        */
                        printf("Enter the character at the position (%d, %d) : ", j + 1, k + 1);
                        fflush(stdin);
                        scanf("%c", &character);


                        if ((character >= 'A' && character <= 'Z') || character == ' ')
                        {
                            fprintf(file, "%c ", character);
                        }
                        else
                        {
                            printf("The character %c is not valid.\n Please enter a character between A and Z.\n", character);
                            fflush(stdin);
                            k -= 1;
                        }
                    }
                    fprintf(file, "\n");
                }
                fprintf(file, "\n");
            }
        fclose(file);
    }
    else
    {
        printf("The file already exists.\n\nRedirecting to the update function\n\n");
        updateMap(getLastId());
    }
}

Room** readMap(int* ptrNbMaps)
{
    char temporarySource[80] = "./ressources/maps/config.rtbob";

    FILE *f = fopen(temporarySource, "r");
    // check if the file exists and the file extension is .rtbob
        // checkFileExtension(temporarySource);

        char c;

        int nbMaps = 0;
        int idMaps = 0;
        int size_x = 0;
        int size_y = 0;

        fscanf(f, "{%d}\n", &nbMaps);
        
        *ptrNbMaps = nbMaps;
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
                    for (int k = 0; k < size_y * 2 - 1; k += 1)
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
                Maps_Created[indexArrayMaps] = newRoom(map, size_x, size_y * 2 - 1, idMaps);
                indexArrayMaps += 1;
            }

            /* TO_IMPROVE for stages : for (int room = 0; room < nbMaps; room += 1)
            {
                Rooms_Created[room] = room;
            } */

        fclose(f);
        return Maps_Created;
}

void updateMap(int choiceOfRoom)
{
    // TODO : Give the option to the user to edit a map
    char temporarySource[80] = "./ressources/maps/config.rtbob";
    char temporarySource2[80] = "./ressources/maps/config2.rtbob";

    if (choiceOfRoom == 0)
    {
        printf("You have to create a Map first to update.\n");
        return;
    }
    
    FILE *f = fopen(temporarySource, "r");
    FILE *f2 = fopen(temporarySource2, "w");

    char c;

    int nbMaps = 0;
    int idMaps = 0;
    int size_x = 0;
    int size_y = 0;

    fscanf(f, "{%d}\n", &nbMaps);

    fprintf(f2, "{%d}\n", nbMaps + 1);

        for (int i = 0; i < nbMaps; i += 1)
        {
            fscanf(f, "[%d|%d]%d\n",&size_x, &size_y, &idMaps);
            //printf("\n[%d|%d]%d",size_y, size_x, idMaps);

            fprintf(f2, "[%d|%d]%d\n", size_x, size_y, idMaps);

            for (int j = 0; j < size_x; j += 1)
            {
                for (int k = 0; k < size_y * 2 - 1; k += 1)
                {
                    fscanf(f, "%c", &c);
                    fprintf(f2, "%c", c);
                }
                fscanf(f, "\n");
                fprintf(f2, "\n");
            }
            fprintf(f2, "\n");
        }

        // we add the new map
        printf("Enter the size of the map number %d.\n(For example : 7 16 = a map of size 7x16)\n", choiceOfRoom+1);
        scanf("%d %d", &size_x, &size_y);
                    
        /* 
            we want to both verify that the user inputs are numbers
            the size of the map to be between 1 and 100
        */
        if (isdigit(size_x) && isdigit(size_y))
        {
            if (size_x >= 1 && size_x <= 100 && size_y >= 1 && size_y <= 100) 
            {
            printf("\nThe size of the map is not valid.\nPlease enter a size between 1 and 100.\n");
            // if the size is not valid we delete the file and exit the program
            exit(0);
            }
        }

        fseek(f2, 0, SEEK_END);

        // we increment the choice of the room to have the id of the new map properly set
        fprintf(f2, "[%d|%d]%d\n", size_x, size_y, choiceOfRoom + 1);

        // we ask the user to enter the map and flush the buffer

        fflush(stdin);
                
        for (int m = 0; m < size_x; m += 1)
        {
            for (int n = 0; n < size_y; n += 1)
            {
                printf("Enter the character at the position (%d, %d) : ", m + 1, n + 1);
                fflush(stdin);
                scanf("%c", &c);

            if ((c >= 'A' && c <= 'Z') || c == ' ')
            {
                fprintf(f2, "%c ", c);
            }
            else
            {
                printf("The character %c is not valid.\n Please enter a character between A and Z.\n", c);
                fflush(stdin);
                n -= 1;
            }
            fprintf(f2, "\n");
        }
        
        fprintf(f2, "\n");
        
        // we close the files to then delete the old one and rename the new one
        fclose(f);
        fclose(f2);

        // we delete the old file
        remove(temporarySource);

        // we rename the new file
        rename(temporarySource2, temporarySource);
    }
}

void deleteRoom(Room** arrayMaps)
{
    int idMaps = 0;
    int nbMaps = getLastId();

    printf("Enter the id of the map you want to delete : ");
    scanf("%d", &idMaps);

    

    for (int i = 0; i <= nbMaps; i += 1)
    {
        if (arrayMaps[i]->nbLevel == idMaps)
        {
            freeRoom(arrayMaps[i]);
            arrayMaps[i] = NULL;
            printf("The map number %d has been deleted.\n", arrayMaps[i]->nbLevel);
        }
    }
}
