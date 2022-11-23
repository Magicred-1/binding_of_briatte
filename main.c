#include <stdio.h>
#include <stdlib.h>
#include "./sources/file_mapping/file_mapping.h"
#include "./sources/cli/cli_commands.h"
#include "./sources/file_extension_checker/file_extension_checker.h"
#include "./sources/game_run/game_run.h"

int main(int argc, char const *argv[])
{
    // launch the CLI
    int nbMaps = getLastId();
    // launch the game
    Room** room = readMap(&nbMaps);
    printRoom(room[4]);
    playerMovement(room, nbMaps);

    // playerMovement(arrayMaps, nbMaps);
    return 0;
}
