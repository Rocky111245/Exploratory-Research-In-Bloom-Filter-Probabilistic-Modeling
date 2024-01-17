//
// Created by rakib on 12/1/2024.
//

#include "Array Utils.h"
#include <stdio.h>



int elementCountR(const int *array) {
    int count = 0;
    int i=0;
    while (array[i] != 0) {
        count++;
        i++;
    }
    return count;
}

void printArray(const int *array, int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
}


void printArrayUntilZero(const int *array) {
    int i = 0;
    while (array[i] != 0) {
        printf("%d ", array[i]);
        i++;
    }
    printf("\n");
}

int countOnesR(const int *array, int size) {
    int count = 0;
    for (int i = 0; i < size; i++) {
        if (array[i] == 1) {
            count++;
        }
    }
    return count;
}
