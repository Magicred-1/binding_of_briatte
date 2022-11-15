#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "./file_extension_checker.h"

void checkFileExtension(char* filename)
{
    char error_message[100] = "The file extension is not valid. Please use .rtbob for maps, .itbob for items or .mtbob for mobs\n";

    char* extension = strrchr(filename, '.');

    if (strcmp(extension, ".rtbob") != 0)
    {
        printf("The file extension %s of the file is valid.\n", extension);
    } 
    else if (strcmp(extension, ".itbob") != 0)
    {
        printf("The file extension %s of the file is valid.\n", extension);
    } 
    else if (strcmp(extension, ".mtbob") != 0)
    {
        printf("The file extension %s of the file is valid.\n", extension);
    }
    else
    {
        printf("%s", error_message);
        exit(0);
        free(extension);
    }
}