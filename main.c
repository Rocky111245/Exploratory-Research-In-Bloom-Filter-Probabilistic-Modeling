
#include <string.h>
#include "Functions.h"

#define MAX_STRINGS 40     // Maximum number of strings in the database
#define MAX_STRING_LENGTH 100 // Maximum length of each string
hashElement nodes[30];

int main() {
    char bloomFilterArray[21] = {0};
    char *sampleString = "example"; // Sample null-terminated string
    //int size=sizeof(sampleString)/sizeof(sampleString[0]);
    printf("%s\n",sampleString);
    char database[MAX_STRINGS][MAX_STRING_LENGTH]; // 2D array of chars
    memset(database, 0, sizeof(database)); // Initialize all strings to empty

    insertIntoHashFunction(bloomFilterArray, sampleString, 21, nodes);
    insertIntoHashFunction(bloomFilterArray, sampleString, 21, nodes);
    insertIntoHashFunction(bloomFilterArray, sampleString, 21, nodes);
    return 0;
}





