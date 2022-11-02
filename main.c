#include <stdio.h>
#include <stdlib.h>
#include "./sources/file_mapping/file_mapping.h"
#include "./sources/cli/cli_commands.h"

int main(int argc, char const *argv[])
{
    createMap("./ressources/maps/config.rtbob");

    // freeRoom(test);
    
    return 0;
}
