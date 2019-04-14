/*
Batch 80
Naman Jain 2014A7PS100P
Saksham Nagar 2014A7PS040P
*/

#include <stdio.h>
#include <string.h>
#include "hash.c"

scopeTree getScopeNode(int dp);

void preorderCreateSymTable(parseTree root);

void printSymTable();

void checkRetVal();

void populateSymTable(parseTree p);

void semanticAnalyze(parseTree root);