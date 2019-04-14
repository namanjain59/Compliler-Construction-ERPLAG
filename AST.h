/*
Batch 80
Naman Jain 2014A7PS100P
Saksham Nagar 2014A7PS040P
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>



int isUseful(int x);


void removeUselessTerminals(parseTree p);


void collapseLinearChains(parseTree root);


void collapseRepeatedRecursion(parseTree p);

void createAST(parseTree p);

void preorderPrintAST(parseTree p)