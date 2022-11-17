/*
**  Filename : read_monster.h
**
**  Made by : Alexis Duquenne <alexisduquenne01@gmail.com>
**
**  Description : Create a map (a two dimension array) from a file 
**  to be use in the game to define monsters.
*/

#ifndef READ_MONSTER_H
#define READ_MONSTER_H

struct Monster
{
    char* name;      //name of the monster
    float hpMax;          //heal point max of the monster
    char* shoot;          //If the monster is able to shoot
    char* ss;             //If the monster have spectral shoot
    char* flight;         //If the monster is able to fly
};

typedef struct Monster Monster;

/**
 * 
*/
Monster* newMonsters(char* name, float hpmax, char* shoot, char* ss, char* flight);

/**
 * @param sourceFile Path of the source file which contains monsters
*/
Monster** monstersMap(char *sourceFile, int *ptrNbOfMonsters);


/**
** @param monster : the array to be printed
*/
void printMonster(Monster monster);

void printMonsterArray(Monster** monster, int NbOfMonster);

void freeMonsters(Monster** monster);

#endif //READ_MONSTER_H
