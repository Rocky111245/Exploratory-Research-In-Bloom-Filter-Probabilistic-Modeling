
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "Functions.h"
#include "Hash Table.h"

#define MAX_STRINGS 40     // Maximum number of strings in the database
#define MAX_STRING_LENGTH 100 // Maximum length of each string

int main() {
    char bloomFilterArray[21] = {0};
    char sampleString[] = "example"; // Sample null-terminated string
    char database[MAX_STRINGS][MAX_STRING_LENGTH]; // 2D array of chars
    memset(database, 0, sizeof(database)); // Initialize all strings to empty

    insertIntoHashFunction(bloomFilterArray, sampleString, 21, nodes);


    return 0;
}





