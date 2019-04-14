/*
Batch 80
Naman Jain 2014A7PS100P
Saksham Nagar 2014A7PS040P
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include "utility.h"

void populateGrammar();

int* cfirst(int lrule, int *rrule, int nrule, int *firstset);

void createParseTable(parseTable t);

//For stack
NODE getnode();
//NODE stFirst, stTop;

void push(NODE* stack, int data);

int pop(NODE* stack);

int top(NODE* stack);

//Creation of Parse tree
parseTree getParseTreeNode();


parseTree parseInputSourceCode(tokenInfo tokenList, parseTable t);

void inorder(parseTree root, FILE* fp);

void preorder(parseTree root);

void countnoast(parseTree root);

void countnoparse(parseTree root);

void printParseTree (parseTree root, char* outfile);

void printParseTreeConsole(parseTree root);

void firstAndFollowSets();