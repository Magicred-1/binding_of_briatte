#include <stdio.h>
#include <stdlib.h>
#include "./sources/file_mapping/file_mapping.h"
#include "sdlTest/sedlTest.h"
#include "./sources/itemCrud/itemCrud.h"
int main(int argc, char const *argv[])
{
    //fileMapping("./ressources/maps/config.rtbob");
    //sdlTest();
    //Item* item = newItem("Doran_Shield",2,2,0,1,0,0);
    //printItem(*item);
    //freeItem(item);
    int size;
    Item **Items = getItems("items.itbob",&size);

    printAllItems(Items, size);
    freeAllItems(Items, size);
    creatItem();
    //Item *item = creatItem();
    // printItem(*item);
    //Item *itemArr [getSize("items.itbob")];
    ////printItem(*itemArr[1]);
    //freeAllItems(itemArr, getSize("items.itbob"));

    //printItem(*itemArr[1]);


    return 0;
}

