#include "read_monster.h"
#include "../more_string/more-string.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

Monster* newMonster(char* name,  float hpmax, char* shoot, char* ss, char* flight){
    Monster* m = malloc(sizeof(Monster));
    m->name = duplicateString(name);
    m->hpMax = hpmax;
    m->shoot = duplicateString(shoot);
    m->ss = duplicateString(ss);
    m->flight = duplicateString(flight);
    return m;
}

void printMonster(Monster monster){
    printf("name: %s \nhpmax: %.1f \nshoot: %s \nspectral shoot: %s \nflight: %s", monster.name, monster.hpMax, monster.shoot, monster.ss, monster.flight);
}

void printMonsterArray(Monster** arrayMonster, int nbOfMonsters){
    for(int i = 0; i < nbOfMonsters; i += 1){
        printf("name: %s \nhpmax: %.1f \nshoot: %s \nspectral shoot: %s \nflight: %s\n", arrayMonster[i]->name, arrayMonster[i]->hpMax, arrayMonster[i]->shoot, arrayMonster[i]->ss, arrayMonster[i]->flight);
    }
}


void freeMonsters(Monster** monster){
    for(int i = 0; i < 5; i += 1){
        free(monster[i]->name);
        free(monster[i]->shoot);
        free(monster[i]->ss);
        free(monster[i]->flight);
        free(monster[i]);
    }
    free(monster);
}

Monster** monstersMap(char *sourceFile, int* ptrNbOfMonster){
    FILE* f = fopen(sourceFile, "r");
    if(f != NULL){
        fscanf(f, "{%d}", ptrNbOfMonster);
        Monster **array = malloc(sizeof(Monster)**ptrNbOfMonster);
        fseek(f, 2, SEEK_CUR);

        for(int i = 0; i < 5; i += 1){
            char name[20];
            float hpMax = 0;
            char shoot[10] = "false";
            char ss[10] = "false";
            char flight[10] = "false";

            fseek(f, 5, SEEK_CUR);
            fscanf(f, "name=%s", name);

            fseek(f, 2, SEEK_CUR);
            fscanf(f, "hpMax=%f", &hpMax);

            fseek(f, 2, SEEK_CUR);
            if(getc(f) != '-'){
                fseek(f, -1, SEEK_CUR);
                if(getc(f) == 's'){
                    fseek(f, -1, SEEK_CUR);
                    fscanf(f,"shoot=%s", shoot);
                }
                fseek(f, 2, SEEK_CUR);
                if(getc(f) != '-'){
                    fseek(f, -1, SEEK_CUR);
                    if(getc(f) == 's'){
                        fseek(f, -1, SEEK_CUR);
                        fscanf(f,"ss=%s", ss);
                    }
                    fseek(f, -1, SEEK_CUR);
                    if(getc(f) == 'f'){
                        fseek(f, -1, SEEK_CUR);
                        fscanf(f,"flight=%s", flight);
                        fseek(f, 2, SEEK_CUR);
                    }else{
                        fseek(f, -1, SEEK_CUR);
                    }
                }
                else{
                    fseek(f, -1, SEEK_CUR);
                }
            }else{
                fseek(f, -1, SEEK_CUR);
            }
            array[i] = newMonster(name, hpMax, shoot, ss, flight);
        }
        fclose(f);
        return array;
    }else {
        printf("Erreur lors de l'ouverture du fichier");
        return NULL;
    }

}
// TODO CRUD