#include <stdio.h>
#include <stdlib.h>
#include "./sources/file_mapping/file_mapping.h"
#include "sdlTest/sedlTest.h"
#include "./sources/itemCrud/itemCrud.h"
int main(int argc, char const *argv[])
{
    //fileMapping("./ressources/maps/config.rtbob");
    //sdlTest();

    Item* item = newItem("Doran_Shield",2,2,0,1,0,0);
    printItem(*item);
    freeItem(item);
    int size = getSize("items.itbob");
    Item *Items[size];
    getItems(Items, "items.itbob");
    printAllItems(Items, size);
    freeAllItems(Items, size);
    return 0;
}

