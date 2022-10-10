#include <stdio.h> 
#include <stdlib.h>
#include "file_mapping.h"

void printMap(char *map[9][15])
{
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 15; j++)
        {
            printf("%s", map[i][j]);
        }
        printf("\n");
    }
}

char fileMapping(char *file_source) {
    char *map[9][15];

    // TODO : I need to try with a pointer like this instead char *line = NULL;
    
    // we check if we can open the file
    FILE *file = fopen(file_source, "r");


    if (file == NULL) 
    {
        printf("Error opening file. Please check if the file exist and if you have the right to read it. \nName of file : %s", file_source);
        exit(1);
    }
    else 
    {
    /* if successful, we read the file and scanf the content
    ** into a the map array
    */
    while (!feof(file))
    {
        for(int column = 0; column < 9; column += 1)
        {
            for(int row = 0; row < 15; row += 1)
            {
                fscanf(file, "%s", map[column][row]);
                printf("%s", map[column][row]);
            }
        }
    }
    fclose(file);
    free(file);
    printMap(map);
    }
}