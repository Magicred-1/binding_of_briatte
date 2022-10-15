#include "read_monsters.h"
#include <stdio.h>
#include <stdlib.h>
int main(int argc, char const *argv[])
{
    //Monster *array = malloc(sizeof(Monster)*2);
    //Monster* m = newMonster("Pooter", 6.5, 1, 0, 1);
    //Monster* m2 = newMonster("Posaefvfe", 6.5, 1, 0, 1);
    // array[0] = *m;
    // array[1] = *m2;
    //printMonsterArray(array);
    //freeMonster(m);
    //freeMonster(m2);
    int nbOfMonsters;
    Monster** arrayMonster = monstersMap("./monster.rtbob", &nbOfMonsters);
    printMonsterArray(arrayMonster, nbOfMonsters);
    freeMonsters(arrayMonster);
    return 0;
}
