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


void Items(char *fileName){
    FILE *f = fopen(fileName, "r");
    if (f==NULL)
        printf("Error when trying to open %s", fileName);
    else{
        int size;
        fscanf(f,"{%d}", &size);
        printf("%d",size);
    }
    fclose(f);
}

