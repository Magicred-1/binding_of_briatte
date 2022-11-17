#include <stdio.h>
#include <stdlib.h>
#include "../file_mapping/file_mapping.h"
#include "../cli/cli_commands.h"
#include "../read_monsters/read_monster.h"
#define MAX_LEN 200

// RGB COLOR in console for the better display
#define RED   "\x1B[31m"
#define GREEN   "\x1B[32m"
#define BLUE   "\x1B[34m"
#define YELLOW   "\x1B[33m"
#define RESET "\x1B[0m"

// create a simple CLI to test the map CRUD commands
void cliStart()
{
    // Splash Screen is launched
    launchTextTitle();

    cliSelector();

    // Map Editor is launched
    //mapEditor();
}

void cliSelector()
{
    printf("\t1. Map Editor\n\t2. Monsters Editor\n\t3. Items Editor\n\t4. Exit\n");
    int answer = getOption();

    switch (answer)
    {
        case '1':
            mapEditor();
            break;
        case '2':
            monsterEditor();
            break;
        case '3':
            //itemEditor();
            break;
        case '4':
            exit(0);
            break;
        default:
            printf("Please select a valid option");
    }
}

void mapEditor()
{   
    while (1)
    {
        // We get the latest datas from the array of maps
        int nbMaps = 0;
        Room** mapsArray = readMap(&nbMaps);
        // numMaps updates everytime we add a new map automatically
        int numMaps = getLastId();

        // Display the menu
        printf("Choose an option between 1 and 6 :\n\n");

        // create a map
        printf("\t1. Create a map..\n");

        // read map
        printf("\t2. Read a map..\n");

        // update map
        printf("\t3. Update a map..\n");

        // delete map
        printf("\t4. Delete a map..\n");

        // play game
        printf("\t5. Play game..\n");
        // exit
        printf("\t6. Exit..\n\n");

        int res = getOption();

        fflush(stdin);
        switch (res)
        {
            // Create Map
            case '1':
                createMap(); // if file exists redirect to updateMap
                break;
            // Read Map all maps
            case '2':
                printMap(mapsArray, nbMaps);
                break;
            // Update Map
            case '3':
                updateMap(numMaps);
                break;
            // Delete Map
            case '4':
                printMap(mapsArray, nbMaps);
                deleteRoom(mapsArray);
                break;
            // Play game
            case '5':
                printf("Coming soon ...\n");
                break;
            // Exit
            case '6':
                printf("Bye bye\n");
                exit(0);
                break;

            default:
                printf("Please enter a number between 1 and 6\n");
                break;
        }
    }
}

void itemEditor()
{
    while (1)
    {
        // Display the menu
        printf("Choose an option between 1 and 3 :\n\n");

        // create an item
        printf("\t1. Create an item..\n");

        // read item
        printf("\t2. Read an item..\n");

        // delete item
        printf("\t3. Delete an item..\n");

        // exit
        printf("\t4. Exit..\n\n");

        int res = getOption();

        fflush(stdin);
        switch (res)
        {
            // Create Item
            case '1':
                printf("Coming soon ...\n");
                break;
            // Read Item
            case '2':
                printf("Coming soon ...\n");
                break;
            // Delete Item
            case '3':
                printf("Coming soon ...\n");
                break;
            // Exit
            case '4':
                printf("Bye bye\n");
                exit(0);
                break;

            default:
                printf("Please enter a number between 1 and 4\n");
                break;
        }
    }
    
}

void monsterEditor()
{
    while (1)
    {
        fflush(stdin);
        // Display the menu
        printf("Choose an option between 1 and 4 :\n\n");

        // create a monster
        printf("\t1. Create a monster..\n");

        // read monster
        printf("\t2. Read a monster..\n");

        // delete monster
        printf("\t3. Delete a monster..\n");

        // exit
        printf("\t4. Exit..\n\n");

        int res = getOption();

        fflush(stdin);
        switch (res)
        {
            // Create Monster
            case '1':
                printf("Coming soon ...\n");
                break;
            // Read Monster
            case '2':
                printf("Coming soon ...\n");
                break;
            // Delete Monster
            case '3':
                printf("Coming soon ...\n");
                break;
            // Exit
            case '4':
                printf("Bye bye\n");
                exit(0);
                break;

            default:
                printf("Please enter a number between 1 and 4\n");
        }
    }
    
}

// Display the ASCII Text Title
void launchTextTitle()
{
    // getting content of the file

    FILE* file = fopen("./sources/cli/splash_art.txt", "r");

    char line[MAX_LEN];

    if (file == NULL)
    {
        printf("Error opening file\n");
        exit(1);
    }

    while (fgets(line, MAX_LEN, file) != NULL)
    {
        printf(""YELLOW "%s" RESET"", line);
    }
    printf("\n\n");
}

// Get the option from the user
int getOption()
{
    int option = 0;
    printf("Enter your choice : ");
    option = getchar();
    printf("\n");

    return option;
}