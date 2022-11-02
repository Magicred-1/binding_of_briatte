#include <stdio.h>
#include <stdlib.h>
#include "./sources/file_mapping/file_mapping.h"

// create a simple CLI to test the map commands
void cli_start()
{
    printf("Welcome to the Binding of Briatte CLI for the maps.\n");
    printf("Please enter the path to the file you want to use.\n");
    printf("Example: ./ressources/maps/config.rtbob\n");
    printf("Path: ");

    char* path = malloc(sizeof(char) * 100);
    scanf("%s", path);

    printf("You entered: %s\n", path);

    printf("Please enter the size of the map you want to create : \n For example : 9 x 15\n");
    printf("Size: ");

    int x, y;
    scanf("%d %d", &x, &y);

    printf("You entered: %d x %d\n", x, y);

    printf("Please enter the number of levels you want to create : \n For example : 3\n");
    printf("Number of levels: ");

    int nbLevel;

    scanf("%d", &nbLevel);

    printf("You entered: %d\n", nbLevel);
}