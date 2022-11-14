#include <stdio.h>
#include <stdlib.h>
#include "../file_mapping/file_mapping.h"


// create a simple CLI to test the map CRUD commands
void cli_start()
{
    // create a map
    printf("1. Create a map\n");

    // edit a map
    printf("2. Edit a map\n");

    // play a map
    printf("3. Play a map\n");

    printf("Choose an option between 1 and 3 : ");

    char option = scanf("%d", &option);

    // printf("You entered: %d", res);

    switch (option)
    {
        case 1:
            printf("You choose to create a map\n");
            char* map_name = malloc(sizeof(char) * 50);
            printf("Enter the name of the map you want to create : ");
            cli_create_map(map_name);
            break;
        case 2:
            // cli_edit_map();
            break;
        case 3:
            // cli_play_map();
            break;
        default:
            printf("Please enter a number between 1 and 3\n");
            break;
    }
}

void cli_create_map(char* map_name)
{
    createMap(map_name);
}

void cli_play_map()
{

}
