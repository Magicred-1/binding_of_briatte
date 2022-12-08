//
// Created by Alexis on 13/11/2022.
//

#include "generate_etage.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

void CreateEtage()
{
    srand(time(NULL));
    int array[11][11];
    for (int i = 0; i < 11; i += 1)
    {
        for (int j = 0; j < 11; j += 1)
        {
            array[i][j] = 0;
        }
    }
    array[5][5] = 1;
    int direction = 0;
    int secondDirection = 0;
    int countUpX = 0;
    int countUpY = 0;
    int countDownX = 0;
    int countDownY = 0;
    int countLeftX = 0;
    int countLeftY = 0;
    int countRightX = 0;
    int countRightY = 0;
    int id = 0;
    for (int i = 0; i < 10; i += 1)
    {
        direction = rand() % 4;
        id = rand() % 8+2;
        if (direction == 0) //up
        {
            if(countUpX <= 5 && countUpX >= -5)
            {
                secondDirection = rand() % 3;
                switch (secondDirection) {
                    case 0: array[5 + countUpX - 1][5 + countUpY] = id; //up
                            countUpX -= 1;
                            break;
                    case 1: if(array[5 + countUpX][5 + countUpY - 1] == 0 && countUpX != 0){ //left
                                array[5 + countUpX][5 + countUpY - 1] = id;
                                countUpY -= 1;
                                break;
                            }else{
                                i -= 1;
                                break;
                            }
                    case 2: if(array[5 + countUpX][5 + countUpY + 1] == 0 && countUpX != 0){ //right
                                array[5 + countUpX][5 + countUpY + 1] = id;
                                countUpY += 1;
                                break;
                            }else{
                                i -= 1;
                                break;
                            }
                }
            }else{
                i-=1;
            }
        }
        else if (direction == 1) //down
        {
            if(countDownX <= 5 && countDownX >= -5)
            {
                secondDirection = rand() % 3;
                switch (secondDirection) {
                    case 0: array[5 + countDownX + 1][5 + countDownY] = id; //down
                            countDownX += 1;
                            break;
                    case 1: if(array[5 + countDownX][5 + countDownY - 1] == 0 && countDownX != 0){ //left
                            array[5 + countDownX][5 + countDownY - 1] = id;
                            countDownY -= 1;
                            break;
                        }else{
                            i -= 1;
                            break;
                        }
                    case 2: if(array[5 + countDownX][5 + countDownY + 1] == 0 && countDownX != 0){ //right
                            array[5 + countDownX][5 + countDownY + 1] = id;
                            countDownY += 1;
                            break;
                        }else{
                            i -= 1;
                            break;
                        }
                }
            }else{
                i-=1;
            }
        }
        else if (direction == 2) //left
        {
            if(countLeftY < 5 && countLeftY > -5)
            {
                secondDirection = rand() % 3;
                switch (secondDirection) {
                    case 0: if(array[5 + countLeftX - 1][5 + countLeftY] == 0 && countLeftY < 0){ //up
                                array[5 + countLeftX - 1][5 + countLeftY] = id;
                                countLeftX -= 1;
                                break;
                            }else{
                                i-=1;
                                break;
                            }
                    case 1: if(array[5 + countLeftX + 1][5 + countLeftY] == 0 && countLeftY < 0){ //down
                            array[5 + countLeftX + 1][5 + countLeftY] = id;
                            countLeftX += 1;
                            break;
                        }else{
                            i-=1;
                            break;
                        }
                    case 2: if (array[5 + countLeftX][5 + countLeftY - 1] == 0) { //left
                            array[5 + countLeftX][5 + countLeftY - 1] = id;
                            countLeftY -= 1;
                            break;
                        } else {
                            i -= 1;
                            break;
                        }
                }
            }else{
                i-=1;
            }
        }
        else if (direction == 3) //right
        {
            if(countRightY <= 5 && countRightY >= -5)
            {
                secondDirection = rand() % 3;
                switch (secondDirection) {
                    case 0: if(array[5 + countRightX - 1][5 + countRightY] == 0 && countRightY > 0){ //up
                            array[5 + countRightX - 1][5 + countRightY] = id;
                            countRightX -= 1;
                            break;
                        }else{
                            i-=1;
                            break;
                        }
                    case 1: if(array[5 + countRightX + 1][5 + countRightY] == 0 && countRightY > 0){ //down
                            array[5 + countRightX + 1][5 + countRightY] = id;
                            countRightX += 1;
                            break;
                        }else{
                            i-=1;
                            break;
                        }
                    case 2: if (array[5 + countRightX][5 + countRightY + 1] == 0) { //right
                            array[5 + countRightX][5 + countRightY + 1] = id;
                            countRightY += 1;
                            break;
                        } else {
                            i -= 1;
                            break;
                        }
                }
            }else{
                i-=1;
            }
        }
    }


    printEtage(array);
}


void printEtage(int etage[11][11]){
    for(int l = 0; l < 11; l+=1){
        for(int m = 0; m < 11; m+=1){
            printf("%d ",etage[l][m]);
        }
        printf("\n");
    }
}
