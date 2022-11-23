//
// Created by Eliott GERMAIN on 11/10/2022.
//

#ifndef BINDING_OF_BRIATTE_ITEMCRUD_H
#define BINDING_OF_BRIATTE_ITEMCRUD_H
typedef struct Item Item;

struct Item{
    char *name;
    double hpMax;
    double shield;
    double dmg;
    int ps;
    int ss;
    int flight;
};
/**
 * function to create a new item
 * @param name
 * @param hpMax
 * @param shield
 * @param dmg
 * @param ps
 * @param ss
 * @param flight
 * @return item
 */
Item *newItem(char *name, double hpMax, double shield, double dmg, int ps, int ss, int flight);


/**
 * this function print an item
 */
void printItem(Item);

/**
 * free an item
 */
void freeItem(Item*);


/**
 * Parsing items from items.itbob file
 * @param filename
 * @return
 */
Item** getItems(char *fileName, int *itemsSize);


/**
 *
 * @param fileName
 * @return int number of items in file items.itboob
 */
int getSize(char * fileName);

/**
 * printing an array of items
 * @param Items
 * @param size
 */
void printAllItems(Item **Items, int size);

/**
 * free ana array of items
 * @param Items
 * @param size
 */
void freeAllItems(Item **Items, int size);

/**
 * adding an item in items.itbob
 */
void createItem();

/**
 * format items.itbob before parsing
 * @param fileName
 */
void formatFile(char *fileName);

void delItem();

void changeElementNumber(char *fileName, int i);

#endif //BINDING_OF_BRIATTE_ITEMCRUD_H
