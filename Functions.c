#include "Functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <string.h>
hashElement nodes[30] = {{0}};
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
    int length= strlen(value);
    if(strcmp(array[hashIndex].value,"")==0){
        // Directly copy the value into the array at hashIndex
        strncpy(array[hashIndex].value, value, length);
        array[hashIndex].value[length] = '\0'; // Ensure null-termination
        array[hashIndex].headPointer = NULL;
    }
    else if(strcmp(array[hashIndex].value,"")!=0){
       hashElement *temp=createNewNode(value);
       hashElement *tracker=array[hashIndex].headPointer;
       while(tracker->headPointer!=NULL){
           tracker=tracker->headPointer;
       }
       tracker->headPointer=temp;
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

void printHashTable(hashElement nodes[],int sizeofHashMap){
    for(int i=0;i<sizeofHashMap;i++){
        printf("Value ");
        printf("Pointer        ");
    }
    printf("\n");
    for(int i=0;i<sizeofHashMap;i++){
        printf("|%s|",nodes[i].value);
        printf("|%p|-->",nodes[i].headPointer);
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
    printHashTable(nodes,bloomFilterSize);
}
