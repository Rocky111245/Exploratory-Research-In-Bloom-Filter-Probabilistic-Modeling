#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#ifndef EXPLORATORY_RESEARCH_IN_BLOOM_FILTER_PROBABILISTIC_MODELING_HASH_TABLE_H
#define EXPLORATORY_RESEARCH_IN_BLOOM_FILTER_PROBABILISTIC_MODELING_HASH_TABLE_H

typedef struct hashElement {
    char *value;
    struct hashElement* headPointer;
} hashElement;

extern hashElement nodes[30];



// Declare any functions that operate on hashTable
hashElement *createNewNode(char *value) ;
void insertIntoHashMap(hashElement array[], char *value, int hashIndex) ; // Example function declaration


#endif //EXPLORATORY_RESEARCH_IN_BLOOM_FILTER_PROBABILISTIC_MODELING_HASH_TABLE_H
