#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#ifndef EXPLORATORY_RESEARCH_IN_BLOOM_FILTER_PROBABILISTIC_MODELING_FUNCTIONS_H
#define EXPLORATORY_RESEARCH_IN_BLOOM_FILTER_PROBABILISTIC_MODELING_FUNCTIONS_H

typedef struct hashElement {
    char *value;
    struct hashElement* headPointer;
} hashElement;

extern hashElement nodes[30];



// Declare any functions that operate on hashTable
hashElement *createNewNode(char *value) ;
void insertIntoHashMap(hashElement array[], char *value, int hashIndex) ; // Example function declaration
unsigned long firstHashFunction(char *key,int bloomFilterSize);
unsigned long secondHashFunction(char *key,int bloomFilterSize);
unsigned long thirdHashFunction(char *key,int bloomFilterSize);
void insertIntoBloomFilter(char bloomFilterArray[],unsigned long hashFunctionResult);
void resetBloomFilter(char bloomFilter[], int size);
void printHashTable(hashElement nodes[],int sizeofHashMap);
int secondLayerHashFunction(unsigned long firstHashFunctionValue,unsigned long secondHashFunctionValue,unsigned long thirdHashFunctionValue,int sizeofHashMap);
void insertIntoHashFunction( char bloomFilterArray[], char *key, int bloomFilterSize,hashElement array[] );
void printBloomFilter(char bloomFilter[], int size);
bool bloomFilterLoad(const char bloomFilter[],int bloomFilterSize);
void checkString(char *existingString, char *newString);
double calculateLoadFactor(hashElement hashTable[], int tableSize);
#endif //EXPLORATORY_RESEARCH_IN_BLOOM_FILTER_PROBABILISTIC_MODELING_FUNCTIONS_H
