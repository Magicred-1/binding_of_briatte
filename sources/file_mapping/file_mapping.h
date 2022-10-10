/*
**  Filename : file_mapping.h
**
**  Made by : Djason Gadiou <djason.gadiou.sio@gmail.com>
**
**  Description : Create a map (a two dimension array) from a file 
**  to be use in the game later on.
*/

#ifndef FILE_MAPPING_H
#define FILE_MAPPING_H
/*
** @param file_source : the path of the file (maps) to be read
** @return a two dimension array containing the map
*/
char fileMapping(char *file_source);


/*
** @param map : the map to be printed
** @return void
*/
void printMap(char *map[9][15]);

#endif //FILE_MAPPING_H
