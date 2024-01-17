#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Hash Table.h"
#include <string.h>

#ifndef EXPLORATORY_RESEARCH_IN_BLOOM_FILTER_PROBABILISTIC_MODELING_FUNCTIONS_H
#define EXPLORATORY_RESEARCH_IN_BLOOM_FILTER_PROBABILISTIC_MODELING_FUNCTIONS_H


unsigned long firstHashFunction(char *key,int bloomFilterSize);
unsigned long secondHashFunction(char *key,int bloomFilterSize);
unsigned long thirdHashFunction(char *key,int bloomFilterSize);
void insertIntoBloomFilter(char bloomFilterArray[],unsigned long hashFunctionResult);
void printHashTable(hashElement nodes[],int sizeofHashMap);
int secondLayerHashFunction(unsigned long firstHashFunctionValue,unsigned long secondHashFunctionValue,unsigned long thirdHashFunctionValue,int sizeofHashMap);
void insertIntoHashFunction( char bloomFilterArray[], char *key, int bloomFilterSize,hashElement array[] );
bool bloomFilterLoad(const char bloomFilter[],int bloomFilterSize);
#endif //EXPLORATORY_RESEARCH_IN_BLOOM_FILTER_PROBABILISTIC_MODELING_FUNCTIONS_H
