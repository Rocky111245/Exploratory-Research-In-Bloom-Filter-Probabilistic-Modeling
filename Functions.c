#include "Functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


unsigned long firstHashFunction(char *key, int bloomFilterSize) {
    unsigned long hash = 5381;
    int c;
    int i = 0;

    while (key[i] != '\0') {
        c = (unsigned char) key[i];
        hash = ((hash << 5) + hash) + c; // hash * 33 + c
        i++;
    }
    unsigned long value = hash % bloomFilterSize;
    printf("%lu\n", value);
    return value;
}

//jenkins
unsigned long secondHashFunction(char *key, int bloomFilterSize) {
    unsigned long hash = 0;
    int i = 0;

    while (key[i] != '\0') {
        hash += (unsigned char)key[i];
        hash += (hash << 10);
        hash ^= (hash >> 6);
        i++;
    }
    hash += (hash << 3);
    hash ^= (hash >> 11);
    hash += (hash << 15);
    unsigned long value = hash % bloomFilterSize;
    printf("%lu\n", value);
    return value;
}


//fnv1a_hash
unsigned long thirdHashFunction(char *key, int bloomFilterSize) {
    unsigned long hash = 0x811c9dc5; // 2166136261
    int i = 0;

    while (key[i] != '\0') {
        hash ^= (unsigned char)key[i];
        hash *= 0x01000193; // 16777619
        i++;
    }
    unsigned long value = hash % bloomFilterSize;
    printf("%lu\n", value);
    return value;
}

void insertIntoBloomFilter(char bloomFilterArray[],unsigned long hashFunctionResult){
    bloomFilterArray[hashFunctionResult]=1;
}


bool bloomFilterLoad(const char bloomFilter[],int bloomFilterSize){
    float count=0;
    float loadFactor;
    for (int i=0;i<bloomFilterSize;i++){
        if(bloomFilter[i]==1){
            count=count+1;
        }
    }
    loadFactor=count/(float)bloomFilterSize;

    if(loadFactor<=0.70){
        return false;
    }
    else{
        return true;
    }
}

double calculateLoadFactor(hashElement hashTable[], int tableSize) {
    int totalElements = 0;

    // Iterate over each bucket in the hash table
    for (int i = 0; i < tableSize; i++) {
        if (hashTable[i].value != NULL) {
            totalElements++; // Count the element in the bucket itself

            // Count elements in the linked list at this bucket
            hashElement *current = hashTable[i].headPointer;
            while (current != NULL) {
                totalElements++;
                current = current->headPointer;
            }
        }
    }

    // Calculate the load factor
    double loadFactor = (double)totalElements / (double)tableSize;
    return loadFactor;
}

void checkString(char *existingString, char *newString){
    int value;
    value=strcmp(existingString,newString);
    if (value!=0){
        //insert
    }
    else {
        return;
    }
}

bool checkExistenceOfString(const char bloomFilter[],int firstResult,int secondResult, int thirdResult){
    if((bloomFilter[firstResult] && bloomFilter[secondResult] && bloomFilter[thirdResult])==1){
        printf("There is a possibility that this string is in the database here already");
        return true;
    }
    else{
        printf("This value is not present in the database");
        return false;
    }
}



hashElement *createNewNode(char *value) {
    hashElement *node = malloc(sizeof(hashElement));
    if (node) {
        int length=strlen(value);
        node->value= malloc(length+1);
        if (node->value) {
            strncpy(node->value, value, length);
            node->value[length] = '\0'; // Ensure null termination
        }
        node->headPointer = NULL;
    }
    return node;
}




void insertIntoHashMap(hashElement array[], char *value, int hashIndex)
{
    int length = strlen(value);

    // If the hash index is empty
    if(array[hashIndex].value == NULL){
        // Allocate memory and copy the value
        array[hashIndex].value = malloc(length + 1);
        if(array[hashIndex].value == NULL) {
            // Handle memory allocation error
            fprintf(stderr, "Memory allocation failed\n");
            return;
        }
        strncpy(array[hashIndex].value, value, length);
        array[hashIndex].value[length] = '\0'; // Ensure null-termination
        array[hashIndex].headPointer = NULL;
    }
    else {
        // If the hash index is not empty, append to the linked list
        hashElement *temp = createNewNode(value);
        if(temp == NULL) {
            // Handle memory allocation error
            fprintf(stderr, "Memory allocation failed for new node\n");
            return;
        }
        if(array[hashIndex].headPointer == NULL) {
            // First element in the linked list
            array[hashIndex].headPointer = temp;
        } else {
            // Append to the existing linked list
            hashElement *tracker = array[hashIndex].headPointer;
            while(tracker->headPointer != NULL){
                tracker = tracker->headPointer;
            }
            tracker->headPointer = temp;
        }
    }
}


int secondLayerHashFunction(unsigned long firstHashFunctionValue,unsigned long secondHashFunctionValue,unsigned long thirdHashFunctionValue,int sizeofHashMap){
    unsigned long hashArrayIndex=firstHashFunctionValue+secondHashFunctionValue+thirdHashFunctionValue;
    return(hashArrayIndex%sizeofHashMap);
}

bool checkDatabase(int firstValue,int secondValue,int thirdValue){
    if(firstValue==1 && secondValue==1 && thirdValue==1){
        printf("There is a possible match, I should search the database before insertion\n");
        return true;
    }
    else{
        return false;
    }
}

void printHashTable(hashElement nodes[], int sizeofHashMap) {
    printf("\n");
    for (int i = 0; i < sizeofHashMap; i++) {
        // Print the value at the hash index
        printf("|%s|", nodes[i].value);

        // Check if there is a linked list at this hash index
        if (nodes[i].headPointer == NULL) {
            printf("NULL\n"); // Print NULL if no linked list
        } else {
            // If there is a linked list, traverse and print its elements
            hashElement *tracker = nodes[i].headPointer;
            while (tracker != NULL) {
                printf("|%p| ", nodes[i].headPointer);
                printf("-->|%s|", tracker->value);
                tracker = tracker->headPointer; // Move to the next node
            }
            printf("NULL\n"); // Print NULL after the last node
        }
    }
}

void printBloomFilter(char bloomFilter[], int size){
    for (int i=0;i<size;i++){
        printf("| %d |",bloomFilter[i]);
    }
}
void resetBloomFilter(char bloomFilter[], int size){
    for (int i=0;i<size;i++){
        bloomFilter[i]=0;
    }
}


void insertIntoHashFunction( char bloomFilterArray[], char *key, int bloomFilterSize,hashElement array[] ){
    int firstIndex= firstHashFunction(key,bloomFilterSize);
    printf("The first index is %d\n",firstIndex);
    insertIntoBloomFilter(bloomFilterArray,firstIndex);
    int secondIndex= secondHashFunction(key,bloomFilterSize);
    printf("The second index is %d\n",secondIndex);
    insertIntoBloomFilter(bloomFilterArray,secondIndex);
    int thirdIndex= thirdHashFunction(key,bloomFilterSize);
    printf("The third index is %d\n",thirdIndex);
    insertIntoBloomFilter(bloomFilterArray,thirdIndex);
    printf("\n");
    printf("Now passing these values to the hashTable");
    int result=secondLayerHashFunction(firstIndex,secondIndex,thirdIndex,30);
    insertIntoHashMap(array,key,result);
    printf("\n");
    printf("\n");
    printf("Printing the Bloom Filter");
    printf("\n");
    printf("\n");
    printBloomFilter(bloomFilterArray,21);
    printf("\n");
    printf("\n");
    printf("Printing the Hash Table");
    printf("\n");
    printHashTable(nodes,bloomFilterSize);
}
