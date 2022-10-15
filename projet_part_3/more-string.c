#include "more-string.h"
#include <string.h>
#include <stdlib.h>



char* duplicateString(char* str){
    if(str == NULL){
        return NULL;
    }
    int size = strlen(str);

    char* newStr = malloc(sizeof(char) * (size + 1));
    return strcpy(newStr, str);
}