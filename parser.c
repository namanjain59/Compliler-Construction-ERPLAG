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
grammar g;


int firstsets[NO_OF_NONTERM][NO_OF_TERM];
int followsets[NO_OF_NONTERM][NO_OF_TERM];
int parsecount=0;
int astcount=0;

//To populate the grammar
void populateGrammar(){

    FILE *f;
    f = fopen("grammar.txt", "rb");
    char s[25];

    int i=0;
    int j=0;


    do{

        fscanf(f, "%s", s);

        int k;

        g[i][j] = strToID(s);

        j++;
        fscanf(f, "%s", s);
        g[i][j] = strToID(s);
//printf("the number is %d\n", g[i][j]);
        int p = g[i][j];
        for(k=0;k<p;k++){
            j++;
            fscanf(f, "%s", s);
            g[i][j] = strToID(s);
        }
        i++;
        j=0;

    }while(!feof(f));

}//end of populateGrammar

int* cfirst(int lrule, int *rrule, int nrule, int *firstset) {
    /* generates the first set for a string of symbols
     * using first sets of the individual symbols
     */
    int tempset[NO_OF_TERM];
    int i, j;
    int br=0;

    // initialize the firstSet to all false
    for(i = 0; i < NO_OF_TERM; i++)
        firstset[i] = 0;

    for(i=0; i < nrule && !br; i++) {
        if(rrule[i]>=0 && rrule[i]<=e) {
            // terminal - first set will just contain itself
            for(j = 0; j < NO_OF_TERM; j++)
                tempset[j] = 0;
            tempset[rrule[i]] = 1;
        }
        else if(rrule[i]>=NONTERM_OFF)
            for(j = 0; j < NO_OF_TERM; j++)
                tempset[j] = firstsets[rrule[i]-NONTERM_OFF][j];
        

        if(tempset[e] == 0)
            br = 1;
        else

            tempset[e] = 0;

        for(j = 0; j < NO_OF_TERM; j++)
            if(tempset[j] == 1)
                firstset[j] = 1;

    }

    // if(br==1)
    // {
    //             for(j = 0; j < NO_OF_TERM; j++)
    //             {
    //                 if(followsets[lrule-NONTERM_OFF][j]==1)   
    //                 firstset[j] = followsets[lrule-NONTERM_OFF][j];
    //             }

    // }

    if(nrule==i && !br)
        // the string can go to eps
        firstset[e] = 1;
    return firstset;
}

void createParseTable(parseTable t) {
    // generates the parse table for the grammar g and puts it into t
    int i, k, lrule;
    int rrule[MAX_RULE_LEN];

    // initialize the parse table to all -1s
    for(i = 0; i < NO_OF_NONTERM; i++)
        for(k = 0; k < NO_OF_TERM; k++)
            t[i][k] = -1;

    for(i = 0; i < NO_OF_PROD; i++) {
        lrule = g[i][0];
                        
        // get the right side of the productions
        int ruleLen = g[i][1];
        for(k = 0; k < ruleLen; k++)
            rrule[k] = g[i][k + 2];
        
        int fset[NO_OF_TERM];
        cfirst (lrule,rrule,ruleLen,fset);
        //comptute fset=cfirst(rrule) generates first set for a string of symbols
        if (fset[e]==1)
        {


            for (k=0;k<NO_OF_TERM;k++)
                if(followsets[lrule-NONTERM_OFF][k] == 1)
                    fset[k]=followsets[lrule-NONTERM_OFF][k];
             fset[e] = 0;
        }

        for(k = 0; k < NO_OF_TERM-1; k++)
            if(fset[k] == 1)
                {
            t[lrule-NONTERM_OFF][k] = i;
                }
    }
  //  t[0][7]=0;
}

//For stack
NODE getnode()
{
    NODE p;
    p=(NODE) malloc (sizeof(struct node));
    return (p);
};

//NODE stFirst, stTop;

void push(NODE* stack, int data)
{
    NODE p=getnode();
    p->info=data;

    if(*stack == NULL){
        *stack = p;
        p->next = NULL;
    }
    else{
        p->next = *stack;
        *stack = p;
    }

}

int pop(NODE* stack)
{
    
    if(*stack == NULL){
        return -1;
    }

    NODE p = *stack;
    NODE q = p;
    *stack = p->next;
    return q->info;
    free(q);

}

int top(NODE* stack)
{
    return (*stack)->info;
}


//Creation of Parse tree
parseTree getParseTreeNode(){
    parseTree pt;
    pt= (parseTree) malloc(sizeof(struct parsetree));
    pt->nextSibling=NULL;
    pt->prevSibling = NULL; //added prevSibling pointer
    pt->parent=NULL;
    pt->child=NULL;
    pt->iden=NULL;
    return pt;
}



parseTree parseInputSourceCode(tokenInfo tokenList, parseTable t){

    parseTree root = getParseTreeNode();
    NODE* stack = (NODE*) malloc (sizeof(NODE));
    tokenInfo lookahead = tokenList;
    push(stack, $);
    push(stack, program);

    root->isTerminal =0;
    root->symbol = program;
    root->parent=NULL;
    strcpy(root->lexeme, IDtoStr(root->symbol));
        int success=0;


    while(lookahead != NULL){
       // flagp2=1;if(flagp) printf("fesjn \n");


        int x = top(stack);
    //    flagp2=1;if(flagp) printf("%d\n", x);
    //    flagp2=1;if(flagp) printf("efa \n");

 //       flagp2=1;if(flagp) printf("%s\n", IDtoStr(x));
        if(x>=NONTERM_OFF){
 //           flagp2=1;if(flagp) printf("1\n");
            if(t[x-NONTERM_OFF][lookahead->token] == -1){
                // flagp2=1;if(flagp) printf("%s", IDtoStr(x));
                // flagp2=1;if(flagp) printf(" %s \n", IDtoStr(lookahead->token));
                success =0;
                flagp2=1;if(flagp) printf("Error: On line %d, The token %s for the lexeme %s does not match, the expected token here is %s\n", lookahead->lineno, IDtoStr(lookahead->token), lookahead->lexeme, IDtoStr(x));
                break;
            }
            else{
                pop(stack);
                root->numChildren = g[t[x-NONTERM_OFF][lookahead->token]][1];

                int ii;
                for(ii=root->numChildren-1;ii>=0;ii--){
                    push(stack, g[t[x-NONTERM_OFF][lookahead->token]][ii+2]);
             //       flagp2=1;if(flagp) printf("%s  ", IDtoStr(g[t[x-NONTERM_OFF][lookahead->token]][ii+2]));
                }

                int in;
                parseTree ch = getParseTreeNode();
                ch->symbol = g[t[x-NONTERM_OFF][lookahead->token]][2];
                    
                if(ch->symbol >=0 && ch->symbol<=DRIVERENDDEF){
                    ch->isTerminal=1;
                }else{
                    ch->isTerminal=0;
                }
                ch->parent=root;
                root->child = ch;

                for(in =1; in<root->numChildren;in++){
                    ch->nextSibling = getParseTreeNode();
                    ch->nextSibling->prevSibling = ch;  //added prevSibling pointer
                    ch = ch->nextSibling;
                    
                    ch->symbol = g[t[x-NONTERM_OFF][lookahead->token]][in+2];
                    
                    if(ch->symbol >=0 && ch->symbol<=DRIVERENDDEF){
                        ch->isTerminal=1;
                    }else{
                        ch->isTerminal=0;
                    }

                    ch->parent=root;

                }

                root = root->child;
                continue;

            }
        }else if((x>=0 && x<=DRIVERENDDEF) ){
//            flagp2=1;if(flagp) printf("2\n");

            if(x == lookahead->token){
                pop(stack);
                //flagp2=1;if(flagp) printf("%s\n", IDtoStr(root->nextSibling->symbol));
                
                //flagp2=1;if(flagp) printf("%s\n", IDtoStr(lookahead->token));
                strcpy(root->lexeme, lookahead->lexeme);
            
                root->lineno = lookahead->lineno;

                lookahead = lookahead->next;
                while(root->nextSibling==NULL){
                    if(root->parent != NULL) root = root->parent;
                    else if(top(stack) == $){
                        //SUCCESS
                        success=1;
                        break;
                    }else{
                        //ERROR
                        success=0;
            
                        flagp2=1;if(flagp) printf("Error: On line %d, The token %s for the lexeme %s does not match, the expected token here is %s\n", lookahead->lineno, IDtoStr(lookahead->token), lookahead->lexeme, IDtoStr(x));


                        break;
                    }
                }
              
                if(root->nextSibling!=NULL){
                    root=root->nextSibling;
                    continue;
                }


            }else{
                
                flagp2=1;if(flagp) printf("Error: On line %d, The token %s for the lexeme %s does not match, the expected token here is %s\n", lookahead->lineno, IDtoStr(lookahead->token), lookahead->lexeme, IDtoStr(x));

                success=0;
                break;
            }

        }

        else if(x==e){
 //           flagp2=1;if(flagp) printf("3\n");
            pop(stack);
            while(root->nextSibling==NULL){
                if(root->parent != NULL) root = root->parent;
                else if(top(stack) == $){
                    //SUCCESS
                    success=1;
                        break;
                }else{
                    //ERROR
                    success=0;
                    flagp2=1;if(flagp) printf("Error: On line %d, The token %s for the lexeme %s does not match, the expected token here is %s\n", lookahead->lineno, IDtoStr(lookahead->token), lookahead->lexeme, IDtoStr(x));
                        break;
                }
            }
            if(root->nextSibling!=NULL){
                root=root->nextSibling;
                continue;
            }
        }

        else if(x==$){
 //           flagp2=1;if(flagp) printf("4\n");
            if(lookahead->token == $){
                //SUCCESS
                success=1;
                        break;
            }else{
                //ERROR
                success=0;
                flagp2=1;if(flagp) printf("Error: On line %d, The token %s for the lexeme %s does not match, the expected token here is %s\n", lookahead->lineno, IDtoStr(lookahead->token), lookahead->lexeme, IDtoStr(x));
                        break;
            }
            lookahead=lookahead->next;
        }

        else if(x!= $ && lookahead->token == $){
            //ERROR
            success=0;
            flagp2=1;if(flagp) printf("Error: On line %d, The token %s for the lexeme %s does not match, the expected token here is %s\n", lookahead->lineno, IDtoStr(lookahead->token), lookahead->lexeme, IDtoStr(x));
                        break;
        }

    }

    return root;

}



void inorder(parseTree root, FILE* fp)
{
  if (root==NULL)
        return;

    inorder(root->child,fp);

    if(root->isTerminal)
    {
        fprintf(fp, "%s\t", root->lexeme);
        fprintf(fp, "%d\t\t", root->lineno);
    }
    else
        fprintf(fp, "%s\t\t\t", "----");


    fprintf(fp, "%s\t\t", IDtoStr(root->symbol));

    if (root->symbol==NUM || root->symbol ==RNUM)
    fprintf(fp, "%s\t\t", root->lexeme);

    if (root->parent ==NULL)
        fprintf(fp, "%s\t\t", "ROOT");
    else
        fprintf(fp, "%s\t\t", IDtoStr(root->parent->symbol)); 
    
    if (root->isTerminal)        
        fprintf(fp, "%s\t\t", "yes");
    else
        fprintf(fp, "%s\t\t", "no");


    if (!root->isTerminal)        
        fprintf(fp, "%s\t\t",IDtoStr(root->symbol) ); 


        fprintf(fp, "%s\n"," " ); 


    if (root->child != NULL && root ->child->nextSibling!=NULL)
    {
        root = root->child->nextSibling;
        while (root != NULL)
        {
            inorder(root,fp);
            root=root->nextSibling;
        }

    }
}

void preorder(parseTree root)
{
  if (root==NULL)
        return;

    printf("%s numofchildren %d\n", IDtoStr(root->symbol), root->numChildren);

    preorder(root->child);

    if (root->child != NULL && root ->child->nextSibling!=NULL)
    {
        root = root->child->nextSibling;
        while (root != NULL)
        {
            preorder(root);
            root=root->prevSibling->nextSibling->nextSibling;
        }

    }
    //printf("\n\n\n");
}

//To count the number of nodes in AST
void countnoast(parseTree root)
{
  if (root==NULL)
        return;

    astcount++;
    countnoast(root->child);

    if (root->child != NULL && root ->child->nextSibling!=NULL)
    {
        root = root->child->nextSibling;
        while (root != NULL)
        {
            countnoast(root);
            root=root->prevSibling->nextSibling->nextSibling;
        }

    }
    //printf("\n\n\n");
}
//To count number of nodes in parsetree
void countnoparse(parseTree root)
{
  if (root==NULL)
        return;

    parsecount++;
    countnoparse(root->child);

    if (root->child != NULL && root ->child->nextSibling!=NULL)
    {
        root = root->child->nextSibling;
        while (root != NULL)
        {
            countnoparse(root);
            root=root->prevSibling->nextSibling->nextSibling;
        }

    }
    //printf("\n\n\n");
}

void printParseTree (parseTree root, char* outfile)
{
    FILE* fp;
    fp=fopen(outfile, "w");
//    printf("success\n");
    inorder(root, fp);

}

//To print parse tree on the console
void printParseTreeConsole(parseTree root)
{
    if (root==NULL)
       return;

    printParseTreeConsole(root->child);

    if(root->isTerminal)
    {
        printf("%s\t", root->lexeme);
        printf("%d\t\t", root->lineno);
    }
    else
        printf("%s\t\t\t", "----");


    printf("%s\t\t", IDtoStr(root->symbol));

    if (root->symbol==NUM || root->symbol ==RNUM)
    printf("%s\t\t", root->lexeme);

    if (root->parent ==NULL)
        printf("%s\t\t", "ROOT");
    else
        printf("%s\t\t", IDtoStr(root->parent->symbol)); 
    
    if (root->isTerminal)        
        printf("%s\t\t", "yes");
    else
        printf("%s\t\t", "no");


    if (!root->isTerminal)        
        printf("%s\t\t",IDtoStr(root->symbol) ); 


        printf("\n" ); 


    if (root->child != NULL && root ->child->nextSibling!=NULL)
    {
        root = root->child->nextSibling;
        while (root != NULL)
        {
            printParseTreeConsole(root);
            root=root->nextSibling;
        }

    }
}


//To populate first and follow sets
void firstAndFollowSets(){

    FILE * fp;
    fp = fopen("first.txt", "rb");
    
    if(fp == NULL){
        printf("Error opening file\n");
    }

    char str [100];
    char *tok;
    int i=0;

    while(1){
        if(fgets(str, 100, fp) != NULL){
            tok = strtok(str, " \n");
            //printf("FIRST %s\n", tok);
            while(tok != NULL){
                firstsets[i][strToID(tok)] = 1;
                tok = strtok(NULL, " \n");
            }
            i++;
        }
        else{
            break;
        }
    }
   

    fclose(fp);

    FILE * fp2;
    fp2 = fopen("follow.txt", "rb");
    
    if(fp2 == NULL){
        printf("Error opening file\n");
    }

    char str2 [100];
    char *tok2;
    int i2=0;

    while(1){
        if(fgets(str2, 100, fp2) != NULL){
            tok2 = strtok(str2, " \n");
            //printf("FOLLOW %s\n", tok2);
            while(tok2 != NULL){
                followsets[i2][strToID(tok2)] = 1;
                tok2 = strtok(NULL, " \n");
            }
            i2++;
        }
        else{
            break;
        }
    }


    fclose(fp2);

}


// int main(){

//     populateGrammar();

//     firstAndFollowSets();


//     // printf("%d\n", g[22][0]);

//     int i,j;
//     for(i=0;i<NO_OF_NONTERM;i++){printf("Success. No syntactic
//         printf("%d ",i);
//         for(j=0;j<NO_OF_TERM;j++){
//             printf("%d ",firstsets[i][j]);
//         }
//         printf("\n");
//     }
//     printf("\n");

//     for(i=0;i<NO_OF_NONTERM;i++){
//         printf("%d ",i);
//         for(j=0;j<NO_OF_TERM;j++){
//             printf("%d ",followsets[i][j]);
//         }
//         printf("\n");
//     }
//     printf("\n");

//     parseTable t;

//         int k;
//     for(i=0;i<NO_OF_PROD;i++)
//     {
//         for(k=0;k<MAX_RULE_LEN+2;k++)
//         {
//             printf("%d  ", g[i][k] );
//         }
//         printf("\n");
//     }

//     createParseTable(t);
//     for(i=0;i<NO_OF_NONTERM;i++)
//     {
//         for(k=0;k<NO_OF_TERM;k++)
//         {
//             printf("%d ", t[i][k] );
//         }
//         printf("\n");
//     }



//     return 0;

// }
