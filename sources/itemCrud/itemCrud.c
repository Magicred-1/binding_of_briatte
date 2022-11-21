//
// Created by Eliott GERMAIN on 11/10/2022.
//
#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "../more_string/more-string.h"
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

}

void freeItem(Item *item){
    free(item->name);
    free(item);
}

void printAllItems(Item **Items, int size){
    for (int i = 0; i < size; i++){
        printf("/------------- item number : %d -----------------/\n", i);
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
            if(string[0] == 'n') {

                fseek(f, -strlen(string), SEEK_CUR);
                fscanf(f, "name=%[^\n]s", name);
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

void changeElementNumber(char *fileName, int i){
    int nb;
    char data[255];
    nb = getSize(fileName);
    if(i == 0){
        nb -=1;
    }
    if (i == 1)
        nb +=1;

    FILE *f = fopen("items.itbob", "r");
    FILE *tmp = fopen("tmp.itbob", "w+");
    if (f != NULL)
    {
        fprintf(tmp, "{%d}\n",nb);
        fseek(f,5,SEEK_CUR);
        while (fgets(data, 255,f)){
            fputs(data, tmp);
        }
    } else
        printf("Cant open items.itbob");

    fclose(tmp);
    fclose(f);
    remove("items.itbob");
    rename("tmp.itbob", "items.itbob");
}

void createItem(){
    char name[30] ="";
    double hpMax;
    double shield;
    double dmg;
    char ss[30];
    char ps[30];
    char flight[30];
    formatFile("items.itbob");
    printf("Enter the name of the item you want to creat : \n");
    scanf("%[^\n]s",name);
    printf("hello");
    printf("Enter the value of hpMax (double) : \n");
    scanf("%lf", &hpMax);
    printf("Enter the value of shield (double) : \n");
    scanf("%lf", &shield);
    printf("Enter the value of dmg (double) : \n");
    scanf("%lf", &dmg);
    printf("Set ss to \"true\" or \"false\" : \n");
    scanf("%s",ss);
    printf("Set ps to \"true\" or \"false\" : \n");
    scanf("%s",ps);
    printf("Set flight to \"true\" or \"false\" : \n");
    scanf("%s",flight);
    printf("name = %s, hpMax = %lf , shield = %lf, dmg = %lf, ps = %s, ss = %s, flight = %s\n",name, hpMax, shield, dmg, ps, ss, flight);
    FILE *file = fopen("items.itbob","a+");
    if (file != NULL)
    {
        fprintf(file,"name=%s", name);
        if(hpMax != 0)
            fprintf(file,"\nhpMax=%lf", hpMax);
        if (shield != 0)
            fprintf(file,"\nshield=%lf", shield);
        if (dmg != 0)
            fprintf(file,"\ndmg=%lf", dmg);
        if (strcmp(ps, "true") == 0)
            fprintf(file,"\nps=true");
        if (strcmp(ss, "true") == 0)
            fprintf(file,"\nss=true");
        if (strcmp(flight, "true") == 0)
            fprintf(file,"\nflight=true");
        
        changeElementNumber("items.itbob", 1);
    }
    else
    {
        printf("Impossible to open items.itbob file");
    }

}

void freeAllItems(Item **Items, int size) {
    for (int i = 0; i < size; i++) {
        freeItem(Items[i]);
    }
}

void delItem(){
    formatFile("items.itbob");
    char item[55];
    printf("Enter the exact name of the item you want to delete : \n");
    scanf("%[^\n]s", item);
    printf("item name = %s\n", item);
    char data[255];
    char str1[255]="name=";
    strcat(str1, item);
    strcat(str1,"\n");
    printf("str1 :%s\n", str1);
    FILE *f = fopen("items.itbob", "r");
    FILE *tmp = fopen("tmp.itbob", "w+");
    if (f != NULL)
    {
        while(fgets(data, 255, f) != NULL ){

            if(strcmp(str1, data) == 0){
                printf("%s\n",data);
                printf("item found\n");
                while(strcmp(fgets(data, 255, f) ,"---\n") != 0){
                    continue;
                }
                //lol
                continue;
            }
            fputs(data, tmp);

        }
        fclose(f);
        fclose(tmp);
        remove("items.itbob");
        rename("tmp.itbob", "items.itbob");
    }
    else
    {
        printf("Impossible to open items.itbob file");
    }
    changeElementNumber("items.itbob", 0);
}

void formatFile(char* fileName){
    FILE *file = fopen(fileName,"a+");
    char data[55];
    if (file != NULL)
    {
        fseek(file,-4,SEEK_END);
        if(strcmp(fgets(data, 55,file), "---\n" )!=0){
            fputs("\n---\n",file);
        }
        rewind(file);
        fclose(file);

    }
    else
    {
        printf("Impossible to open items.itbob file");
    }

}










