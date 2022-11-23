/*
**  Filename : cli_commands.h
**
**  Made by : Djason Gadiou <djason.gadiou.sio@gmail.com>
**
**  Description : Create a CLI to test the map CRUD commands and being used for the game.
*/

#ifndef CLI_COMMANDS_H_
#define CLI_COMMANDS_H_

void cliStart();

// selection between map editor / item editor / monster editor
void cliSelector();

// clear the screen
void clearScreen();

// CRUD of Map / Monsters / Items
// Map Editor is launched
void mapEditor();

// Monster Editor is launched
void monsterEditor();

// Item Editor is launched
void itemEditor();

// ASCII Text Art Text Title
void launchTextTitle();

// Get the option from the user
int getOption();

// Get the map ID from the file
void getLatestDatas();

#endif /* !CLI_COMMANDS_H_ */