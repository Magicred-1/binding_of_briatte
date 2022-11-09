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
    newItem->shield = shield;
    newItem->hpMax = hpMax;
    newItem->dmg = dmg;
    newItem->ps = ps;
    newItem->ss = ss;
    newItem->flight = flight;
    return newItem;
}

void printItem(Item item){
    printf("name = %s \n" , item.name);
    if (item.hpMax != 0)
        printf("hpMax = %.1f \n" , item.hpMax);
    if (item.shield != 0)
        printf("shield = %lf\n", item.shield);
    if (item.dmg !=0)
        printf("dmg = %.1f \n", item.dmg);
    if (item.ps !=0)
        printf("ps = true \n");
    if (item.ss !=0)
        printf("ss = true \n");
    if (item.flight !=0)
        printf("flight = true \n");

    printf("/------------------------------/\n");
}

void freeItem(Item *item){
    free(item->name);
    free(item);
}

void printAllItems(Item **Items, int size){
    for (int i = 0; i < size; i++){
        printItem(*Items[i]);
    }
}

int getSize(char *fileName){
    int size;
    FILE *f = fopen(fileName, "r");
    fscanf(f,"{%d}", &size);
    fclose(f);
    return size;
}


Item** getItems( char *fileName, int *itemsSize) {

    Item **array = malloc(sizeof(Item)**itemsSize);
    formatFile(fileName);
    FILE *f = fopen(fileName, "r");
    if (f != NULL) {
        char c;
        char string[255];

        int nLines = 0;
        int index =0;
        while((c=fgetc(f)) != EOF)
        {
            if(c=='\n')
                nLines++;
        }
        printf(" nb lines : %d\n ", nLines);
        rewind(f);
        fscanf(f, "{%d}", itemsSize);
        //printf("item size : %d\n", *itemsSize);
        fseek(f, 5, SEEK_CUR);
        char name[255];
        double hpMax;
        int ss;
        int ps;
        char flight;
        double dmg;
        double shield;
        char tmp[55];
        int cpt = 1;

        for (int i = 0; i < nLines-1 ; ++i) {
            if(cpt == 1){
                strcpy(name, "");
                hpMax = 0;
                ss = 0;
                ps = 0;
                flight = 0;
                dmg = 0;
                shield = 0;
                cpt = 0;
            }

            fgets(string, 255, f);
            //printf("my string %d = %s",i, string);
            if(string[0] == 'n') {

                fseek(f, -strlen(string), SEEK_CUR);
                fscanf(f, "name=%s", name);
                //printf("name = %s\n" , name);
                fseek(f, 1, SEEK_CUR);
            }

            if(string[0] == 'h') {
                fseek(f, -strlen(string), SEEK_CUR);
                fscanf(f, "hpMax=%lf", &hpMax);
                fseek(f, 1, SEEK_CUR);
            }
            if(string[0] == 'd') {
                fseek(f, -strlen(string), SEEK_CUR);
                fscanf(f, "dmg=%lf", &dmg);
                fseek(f, 1, SEEK_CUR);
            }
            if(string[0] == 's' && string[1] == 'h') {
                fseek(f, -strlen(string), SEEK_CUR);
                fscanf(f, "shield=%lf", &shield);
                fseek(f, 1, SEEK_CUR);
            }


            if(string[0] == 'f') {
                fseek(f, -strlen(string), SEEK_CUR);
                fscanf(f, "flight=%s", tmp);
                if (strcmp(tmp , "true")==0)
                    flight = 1;
                else
                    flight = 0;
                fseek(f, 1, SEEK_CUR);
            }

            if(string[0] == 's' && string[1] == 's' ) {
                fseek(f, -strlen(string), SEEK_CUR);
                fscanf(f, "ss=%s", tmp);
                if (strcmp(tmp , "true")==0)
                    ss = 1;
                else
                    ss = 0;
                fseek(f, 1, SEEK_CUR);
            }

            if(string[0]== '-') {
                array[index] = newItem(name, hpMax, shield, dmg, ps, ss, flight);
                index++;
                cpt = 1;
            }

            if(string[0] == 'p') {
                fseek(f, -strlen(string), SEEK_CUR);
                fscanf(f, "ps=%s", tmp);
                if (strcmp(tmp , "true")==0)
                    ps = 1;
                else
                    ps = 0;
                fseek(f, 1, SEEK_CUR);
            }
        }

        printf("\nindex  : %d\n", index);
        fclose(f);
        return array;

    } else
    {
        printf("Erreur lors de l'ouverture du fichier");
        return NULL;

    }
}


Item **getItemz(char *fileName, int *itemsSize) {

    FILE *f = fopen(fileName, "r");
    if (f != NULL) {
        fscanf(f, "{%d}", itemsSize);
        Item **array = malloc(sizeof(Item)**itemsSize);
        fseek(f,2, SEEK_CUR);
        char *c = NULL;
        int cpt = 0 , cpt1 = 0;
        while (fgets(c, 255, f) != EOF){

            char name[30];
            double hpMax = 0;
            int ss = 0;
            int ps = 0;
            char flight = 0;
            double dmg = 0;
            double shield = 0;

            if(c[0] == 'n'){
                fseek(f,-strlen(c),SEEK_CUR);
                fscanf(f, "name=%s[^\n]", name);
                printf("name=%s", name);
                fseek(f,1,SEEK_CUR);

            }
            else if (c[0] == 's' && fgetc(f) == 'h'){
                fseek(f,-strlen(c),SEEK_CUR);
                fscanf(f, "shield=%lf", &shield);
                printf("shield = %lf\n", shield);
                fseek(f,1,SEEK_CUR);

            }
            else if(c[0] == 'h' && c[1] =='p'){
                fseek(f,-strlen(c),SEEK_CUR);
                fscanf(f, "hpMax=%lf", &hpMax);
                printf("hp max = %lf\n", hpMax);
                fseek(f,1,SEEK_CUR);

            }
            else if(c[0] == 'd'){
                fseek(f,-strlen(c),SEEK_CUR);
                fscanf(f, "dmg=%lf", &dmg);
                printf("dmg = %lf\n", hpMax);
                fseek(f,1,SEEK_CUR);

            }
            else if(c[0] == 'p'){
                fseek(f,-strlen(c),SEEK_CUR);                char value[20];
                fscanf(f, "ps=%s", value);
                if (strcmp(value, "true")==0)
                    ps = 1;
                else
                    ps = 0;
                printf("ps = %d\n", ps);
                fseek(f,1,SEEK_CUR);


            }
            else if (c[0] == 'f'){
                fseek(f,-strlen(c),SEEK_CUR);                char value[20];
                fscanf(f, "flight=%s", value);
                if (strcmp(value, "true")==0)
                    flight = 1;
                else
                    flight = 0;
                printf("flight = %d \n", flight);
                fseek(f,1,SEEK_CUR);


            }
            else if (c[0] == 's' && c[1] == 's'){
                fseek(f,-strlen(c),SEEK_CUR);
                char value[20];
                fscanf(f, "ss=%s", value);
                if (strcmp(value, "true")==0)
                    ss = 1;
                else
                    ss = 0;
                //printf("hp max = %lf", hpMax);
                fseek(f,1,SEEK_CUR);
            }

            else if(c[0] == '-'){
                cpt+=1;
                fseek(f,4,SEEK_CUR);
                array[cpt1] = newItem(name, hpMax, shield, dmg, ps, ss, flight);
            }


        }
        fclose(f);
        return array;
    } else {
        printf("Erreur lors de l'ouverture du fichier");
        return NULL;
    }
}

Item *creatItem(){
    char name[30] ="";
    double hpMax;
    double shield;
    double dmg;
    int ss;
    int ps;
    int flight;

    printf("Enter the name of the item you want to creat : \n");
    scanf("%s",name);
    printf("hello");
    printf("Enter the value of hpMax (double) : \n");
    scanf("%lf", &hpMax);
    printf("Enter the value of shield (double) : \n");
    scanf("%lf", &shield);
    printf("Enter the value of dmg (double) : \n");
    scanf("%lf", &dmg);
    printf("Set ss to \"true\" or \"false\" : \n");
    scanf("%d",&ss);
    printf("Set ps to \"true\" or \"false\" : \n");
    scanf("%d",&ps);
    printf("Set flight to \"true\" or \"false\" : \n");
    scanf("%d",&flight);

    Item *Item = newItem(name, hpMax, shield, dmg, ps, ss, flight);
    return Item;
}



void freeAllItems(Item **Items, int size) {
    for (int i = 0; i < size; i++) {
        freeItem(Items[i]);
    }
}

void formatFile(char* fileName){
    FILE *file = fopen(fileName,"a+");
    if (file != NULL)
    {
        fseek(file,-1,SEEK_END);
        if(fgetc(file) != '-'){
            fputs("\n---",file);
        }
        rewind(file);
        fclose(file);

        // On peut lire et écrire dans le fichier
    }
    else
    {
        // On affiche un message d'erreur si on veut
        printf("Impossible d'ouvrir le fichier test.txt");
    }


}












