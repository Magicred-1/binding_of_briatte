#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "file_mapping.h"
#include "../file_extension_checker/file_extension_checker.h"
#include "../cli/cli_commands.h"

// RGB BOLD COLOR in console for the better display
#define RED   "\x1B[1;31m"
#define GREEN   "\x1B[1;32m"
#define BLUE   "\x1B[1;34m"
#define YELLOW   "\x1B[1;33m"
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

            return the last ID of the map
        */
        fscanf(file, "{%d}\n", &idMaps);
        fclose(file);
        return idMaps;
    }
    else
    {
        printf("The map file is empty.\n\n");
        createMap();
    }
}

void deleteMapFromFile()
{
    // 'w' mode removes all the content of the file
    FILE *file = fopen("./ressources/maps/config.rtbob", "w");
    FILE *temporaryFile = fopen("./ressources/maps/config2.rtbob", "w");

    if (file != NULL)
    {
        fclose(file);
        printf(""RED "The map file has been deleted." RESET"\n\n");
        if (temporaryFile != NULL)
        {
            fclose(temporaryFile);
            remove("./ressources/maps/config2.rtbob");
        }
    }
    else
    {
        printf("The map file is empty.\n\n");
    }
}

void deleteRoomFromFile(int roomID) //TODO
{
    char temporaryFile[80] = "./ressources/maps/config.rtbob";
    char temporaryFile2[80] = "./ressources/maps/config2.rtbob";

    char character;

    int idMaps = 0;
    int size_x = 0;
    int size_y = 0;
    // get all the exist maps except the one to delete
    int nbMaps = getLastId() - 1;

    FILE *file = fopen(temporaryFile, "r");
    FILE *fileTemp = fopen(temporaryFile2, "w");

    if (file != NULL)
    {
        fscanf(fileTemp, "{%d}\n", &nbMaps);
        for (int i = 0; i < nbMaps; i += 1)
        {
            fscanf(file, "[%d|%d]%d\n",&size_x, &size_y, &idMaps);
            // we filter the map the user want to delete
            if(fscanf(file, "]%d\n", &idMaps) != roomID)
            {
                fprintf(fileTemp, "[%d|%d]%d\n", size_x, size_y, idMaps);
                for (int j = 0; j < size_x; j += 1)
                {
                    for (int k = 0; k < size_y * 2 - 1; k += 1)
                    {
                        fscanf(file, "%c", &character);
                        fprintf(fileTemp, "%c", character);
                    }
                    fscanf(file, "\n");
                    fprintf(fileTemp, "\n");
                }
                fprintf(fileTemp, "\n");
            }
            else
            {
                fseek(file, size_x * size_y * 2, SEEK_CUR);
            }
        }
    }
    else
    {
        printf(""RED "The map file is empty." RESET"\n\n");
        fclose(file);
        fclose(fileTemp);
    }

    // we close files first
    fclose(file);
    fclose(fileTemp);

    // we delete the old file
    if (remove(temporaryFile) == 0)
    {
        printf(""BLUE "\nThe file %s has been deleted." RESET"\n", temporaryFile);
    }
    else
    {
        printf(""RED "\nThe file %s could not be deleted." RESET"\n", temporaryFile);
    }
    
    // we rename the new file like the old one
    if (rename(temporaryFile, temporaryFile2) == 0)
    {
        printf(""RED "\nThe file %s has been renamed." RESET"\n", temporaryFile2);
    }
    else
    {
        printf(""BLUE "\nThe file %s could not be renamed." RESET"\n", temporaryFile2);
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
            printf("Map ID : " YELLOW "%d\n" RESET "", mapsArray[i]->nbLevel);

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
    /*
        Getting the parameters 
        value from the function into a char with extra line
    */
    char temporaryFile[80] = "./ressources/maps/config.rtbob";

    FILE *f = fopen(temporaryFile, "r");

    if (fgetc(f) == EOF)
    {
        FILE *f = fopen(temporaryFile, "a");
        // check if the file exists and the file extension is .rtbob
        checkFileExtension(temporaryFile);

        int size_x;
        int size_y;
        int idMaps = 0;
        int nbMaps = 0;
        char c;

        printf("Enter the number of maps you want to create : \n");
        scanf("%d", &nbMaps);

        fseek(f, 0, SEEK_SET);
        fprintf(f, "{%d}\n", nbMaps);
        
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

                fseek(f, 0, SEEK_END);
                fprintf(f, "[%d|%d]%d\n", size_x, size_y, idMaps);

                fflush(stdin);
            
                for (int j = 0; j < size_x; j += 1)
                {
                    for (int k = 0; k < size_y; k += 1)
                    {
                        printf("Enter the character at the position (%d, %d) : ", j + 1, k + 1);
                        fflush(stdin);
                        scanf("%c", &c);


                        if ((c >= 'A' && c <= 'Z') || c == ' ')
                        {
                            fprintf(f, "%c ", c);
                        }
                        else
                        {
                            printf("The character %c is not valid.\n Please enter a character between A and Z.\n", c);
                            fflush(stdin);
                            k -= 1;
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
                Maps_Created[indexArrayMaps] = newRoom(map, size_x, size_y * 2 - 1, idMaps);
                indexArrayMaps += 1;
            }
        fclose(f);
        return Maps_Created;
}

void updateMap(int choiceOfRoom)
{
    char temporaryFile[80] = "./ressources/maps/config.rtbob";
    char temporaryFile2[80] = "./ressources/maps/config2.rtbob";

    char character;

    int nbMaps = 0;
    int idMaps = 0;
    int size_x = 0;
    int size_y = 0;
    
    FILE *f = fopen(temporaryFile, "r");
    FILE *f2 = fopen(temporaryFile2, "w");


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
                fscanf(f, "%c", &character);
                fprintf(f2, "%c", character);
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
    fprintf(f2, "[%d|%d]%d\n", size_x, size_y, choiceOfRoom+1);

    // we ask the user to enter the map and flush the buffer

    fflush(stdin);
            
    for (int m = 0; m < size_x; m += 1)
    {
        for (int l = 0; l < size_y; l += 1)
        {
            printf("Enter the character at the position (%d, %d) : ", m + 1, l + 1);
            fflush(stdin);
            scanf("%c", &character);

            if ((character >= 'A' && character <= 'Z') || character == ' ')
            {
                fprintf(f2, "%c ", character);
            }
            else
            {
                printf("The character %c is not valid.\n Please enter a character between A and Z.\n", character);
                fflush(stdin);
                // if the character is not valid we ask the user to enter a new one and flush the buffer
                l -= 1;
            }
        }
        fprintf(f2, "\n");
    }
    fprintf(f2, "\n");
    
    // before deleting the files we close them and renaming the new into the old one
    fclose(f);
    fclose(f2);

    // we delete the old file
    if (remove(temporaryFile) == 0)
    {
        printf("\nThe file %s has been deleted.\n", temporaryFile);
    }
    else
    {
        printf("\nThe file %s could not be deleted.\n", temporaryFile);
    }
    
    // we rename the new file like the old one
    if (rename(temporaryFile2, temporaryFile) == 0)
    {
        printf("\nThe file %s has been renamed.\n", temporaryFile2);
    }
    else
    {
        printf("\nThe file %s could not be renamed.\n", temporaryFile2);
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
            deleteRoomFromFile(arrayMaps[i]->nbLevel);
            freeRoom(arrayMaps[i]);
            arrayMaps[i] = NULL;
            printf("The map number %d has been deleted.\n", arrayMaps[i]->nbLevel);
        }
    }
}
