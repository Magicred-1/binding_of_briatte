//
// Created by Eliott GERMAIN on 11/10/2022.
//
#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "../more-string/more-string.h"
#include "itemCrud.h"


Item *newItem(char *name, double hpMax, double shield, double dmg, int ps, int ss, int flight){
    Item *newItem = malloc(sizeof(Item));
    newItem->name = duplicateString(name);
    newItem->hpMax = hpMax;
    newItem->shield = shield;
    newItem->dmg = dmg;
    newItem->ps = ps;
    newItem->ss = ss;
    newItem->flight = flight;
    return newItem;
}

void printItem(Item item){
    printf("name = %s \n" , item.name);
    if (item.hpMax != 0)
        printf("hpMax=%.1f \n" , item.hpMax);
    if (item.shield !=0)
        printf("shield=%.1f\n", item.shield);
    if (item.dmg !=0)
        printf("dmg=%f,1 \n", item.dmg);
    if (item.ps !=0)
        printf("ps=true \n");
    if (item.ss !=0)
        printf("ss=true \n");
    if (item.flight !=0)
        printf("flight=true \n");
}

void freeItem(Item *item){
    free(item->name);
    free(item);
}

void printAllItems(Item **Items, int size){
    for (int i = 0; i < size; i++){
        printf("%s  \n", Items[i]->name);
    }
}

int getSize(char *fileName){
    int size;
    FILE *f = fopen(fileName, "r");
    fscanf(f,"{%d}", &size);
    fclose(f);
    return size;
}


void getItems(Item **Items, char *fileName){
    FILE *f = fopen(fileName, "r");

        int size;
        int i = 0;
        fscanf(f,"{%d}", &size);
        printf("%d",size);
        char data[40];
        char key[40];
            while(fscanf(f,"%s=%s", key,data ) != EOF){
                    if(strcmp(key , "name")== 0){
                        strcpy(Items[i]->name, data);
                        i++;
                    }
            }

    fclose(f);
}

void freeAllItems(Item **Items, int size) {
    for (int i = 0; i < size; i++) {
        freeItem(Items[i]);
    }
}
