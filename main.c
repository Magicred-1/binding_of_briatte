#include <stdio.h>
#include <stdlib.h>
#include "./sources/file_mapping/file_mapping.h"
#include "sdlTest/sedlTest.h"
#include "./sources/itemCrud/itemCrud.h"
int main(int argc, char const *argv[])
{

    int size;
    Item **Items = getItems("items.itbob",&size);
    printAllItems(Items, size);
    freeAllItems(Items, size);
    //creatItem();
    //delItem();
    //changeElementNumber("items.itbob",0);
    return 0;
}

