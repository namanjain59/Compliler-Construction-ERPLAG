/*
Batch 80
Naman Jain 2014A7PS100P
Saksham Nagar 2014A7PS040P
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int hashFunc(char* key);

DataItem hashSearch(char* key);

void hashInsert(char* key, Symbol data);

void populateHashTable();

Symbol find(char* lex);

FILE* getStream(FILE *fp);

tokenInfo getNextToken();

FILE* removeComments(char* testcaseFile, char* cleanFile);





















