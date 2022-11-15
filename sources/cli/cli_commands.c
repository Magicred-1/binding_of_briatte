#include <stdio.h>
#include <stdlib.h>
#include "../file_mapping/file_mapping.h"
#include "../cli/cli_commands.h"
#define MAX_LEN 200


// create a simple CLI to test the map CRUD commands
void cli_start()
{
    // Splash Screen is launched
    launch_splash_screen();

    // Map Editor is launched
    map_editor();
}

void map_editor()
{   
    printf("Choose an option between 1 and 4 :\n");
    int i = 0;

    Room** arrayMaps = readMap(&i);

    int numMaps = getLastId();
    int min = numMaps + 1;
    // create a map
    printf("1. Create a map..\n");

    // read map
    printf("2. Read a map..\n");

    // update map
    printf("3. Update a map..\n");

    // delete map
    printf("4. Delete a map..\n");

    // play game
    printf("5. Play game..\n");
    // exit
    printf("6. Exit..\n\n");

    fflush(stdin);

    int option = 0;
    option = getchar();

    switch (option)
    {
        // case 1:
        case 49:
            createMap();
            cli_start();
        // case 2:
        case 50:
            printf("Type the id of the map you want to show\n");
            int* id = 0;
            scanf("%d", &id);

            readMap(id);
            break;
        // case 3:
        case 51:
            updateMap(numMaps);
            cli_start();
        // case 4:
        case 52:
            /* readMap(arrayMaps);
            printf("Type the id of the map you want to delete\n");
            scanf("%d", &id); */
            break;
        case 53:
            printf("Coming soon ...\n");
            break;
        case 54:
            printf("Bye bye\n");
            exit(0);
            break;
        default:
            printf("Please enter a number between 1 and 4\n");
            cli_start();
    }
}

void launch_splash_screen()
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
        printf("%s", line);
    }
    printf("\n\n");
}