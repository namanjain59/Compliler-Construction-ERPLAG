/*
Batch 80
Naman Jain 2014A7PS100P
Saksham Nagar 2014A7PS040P
*/

#include <stdio.h>
#include <string.h>
//#include "SymDef.h"
#include "hash.c"


//Function to return a scope tree node
scopeTree getScopeNode(int dp)
{
	scopeTree st = (scopeTree) malloc (sizeof(struct scopetree));
	st->depth = dp;
	st->parent=NULL;
	st->child=NULL;
	st->actdp=0;

}
int scovar=0;
int off=0;
scopeTree st;
hashTable ht;
struct idFunc* curmod;

//Function to create the symbol table
void preorderCreateSymTable(parseTree root)
{
//  flagp2=1;if(flagp) printf("1\n");
  if (root==NULL)
        return;

    //flagp2=1;if(flagp) printf("depth %d   scpvar    %d    %s\n", st->depth,scovar, IDtoStr(root->symbol));

    //To increase the scope
    if(root->symbol == START)
    {

        
        //flagp2=1;if(flagp) printf("1\n");
        scovar++;
        scopeTree sc=getScopeNode(scovar);
        sc->actdp=st->actdp+1;
        sc->scstart=root->lineno;
        st->child=sc;
    //  flagp2=1;if(flagp) printf("    %d        %d  \n", sc->depth, scovar);
        sc->parent=st;
        st=st->child;
    //  flagp2=1;if(flagp) printf("%d\n",scovar);
    //  flagp2=1;if(flagp) printf("%d\n",st->depth );
        //if(st->parent!=NULL)
        //      flagp2=1;if(flagp) printf("%d\n",st->parent->depth );
    //  flagp2=1;if(flagp) printf("    %d        %d  \n", st->depth, scovar);
        if(root->parent!=NULL && (root->parent->symbol==moduleDef))
        {
            curmod->scp=st;
        }

    }
    else if(root->symbol == END)
    { //To move a scope upwards
        if(root->parent!=NULL && root->parent->child !=NULL && root->parent->child->symbol==FOR)
        {
            //flagp2=1;if(flagp) printf("dfg\n");
            root->parent->child->nextSibling->nextSibling->iden->entity.ivar->forVar=0;
            // IDE ouefor=searchKey(ht,root->parent->child->nextSibling->nextSibling->lexeme, 0, st->depth);
            // ouefor->entity.ivar->forVar=0;
        }
    //  flagp2=1;if(flagp) printf("%d\n",st->depth);
        st->scend=root->lineno;
        if(st->parent!=NULL)
        {
            st=st->parent;
        }


    }
    else if(root->symbol==N3)
    {
        return;
    }
    else if(root->parent!=NULL && root->parent->symbol==N3)
    {
        return;
    }
    else if(root->symbol == value)
    {
        //To check for case statements
        parseTree pto=root;
        while (pto!=NULL && pto->symbol !=conditionalStmt)
        {
            pto=pto->parent;
        }
        if(pto!=NULL)
        {
            pto=pto->child->nextSibling->nextSibling;
            if(pto->iden->entity.ivar->aov.v->type == BOOLEAN)
            {
                if(root->child->symbol==NUM)
                {
                    flagp2=1;if(flagp) printf("Error: On line %d, type not matching, type should be boolean\n", root->child->lineno);
                }
            }
            else if(pto->iden->entity.ivar->aov.v->type == INTEGER)
            {
                if(root->child->symbol!=NUM)
                {
                    flagp2=1;if(flagp) printf("Error: On line %d, type not matching, type should be integer\n", root->child->lineno);
                }
            }
        }
    }

    else if(root->symbol == DRIVER)
    {
        //This will treat driver module as a module and add it to current scope
        off=0;
        IDE oue = (IDE) malloc (sizeof(struct idEnt));
        oue->entity.ifun = (struct idFunc*) malloc (sizeof(struct idFunc)); 
        curmod=oue->entity.ifun;
        strcpy(oue->entity.ifun->ID, root->lexeme);
        oue->entity.ifun->scope=0;
        oue->entity.ifun->lineno=root->lineno;
        oue->entity.ifun->status=defined;
        addKey(ht, oue,1);
    }
    else if(root->symbol == ID)
    {
        //To handle when an identifier comes
        //flagp2=1;if(flagp) printf("%s\n", root->lexeme);

        //for modules
        if(root->prevSibling != NULL && root->prevSibling->symbol == MODULE)
        {
            //  flagp2=1;if(flagp) printf("yes0 \n");
            //For declaring a module
            if(root->prevSibling->prevSibling->symbol == DECLARE)
            {
            //  flagp2=1;if(flagp) printf("yes\n");
                if(searchKey(ht,root->lexeme, 1, 0)==NULL)
                {
                //  flagp2=1;if(flagp) printf("dfs\n");
                    IDE oue = (IDE) malloc (sizeof(struct idEnt));
                    oue->entity.ifun = (struct idFunc*) malloc (sizeof(struct idFunc)); 
                    strcpy(oue->entity.ifun->ID, root->lexeme);
                //  flagp2=1;if(flagp) printf("hfdh\n");
                    oue->entity.ifun->scope=0;
                    oue->entity.ifun->lineno=root->lineno;
                    oue->entity.ifun->status=declared;
                //  flagp2=1;if(flagp) printf("sfd\n");
                    addKey(ht, oue,1);
                    root->iden=oue;
                //  flagp2=1;if(flagp) printf("dfff\n");
                }
                else
                {
                    //ERROR already declared
                    flagp2=1;if(flagp) printf("Error: On line %d, module %s already declared", root->lineno,root->lexeme);
                }

            }
            else if(root->prevSibling->prevSibling->symbol == DEF)
            {
                //for defining a module
                off=0;
                IDE oue=searchKey(ht,root->lexeme, 1, 0);
                if(oue == NULL)
                {
                    IDE oue = (IDE) malloc (sizeof(struct idEnt));
                    oue->entity.ifun = (struct idFunc*) malloc (sizeof(struct idFunc)); 
                    curmod=oue->entity.ifun;
                    strcpy(oue->entity.ifun->ID, root->lexeme);
                    oue->entity.ifun->scope=0;
                    oue->entity.ifun->lineno=root->lineno;
                    oue->entity.ifun->status=defined;
                    addKey(ht, oue,1);
                    root->iden=oue;
                }
                else if(oue->entity.ifun->status == declared )
                {
                    curmod=oue->entity.ifun;
                    oue->entity.ifun->status=defined;
                    oue->entity.ifun->lineno=root->lineno;
                    oue->entity.ifun->retParam = NULL;
                    oue->entity.ifun->inpParam = NULL;
                }
                else
                {
                    //ERROR already defined
                    flagp2=1;if(flagp) printf("Error: On line %d, module %s already defined\n", root->lineno, root->lexeme);
                }
            }
            else if(root->prevSibling->prevSibling->symbol == USE)
            {
                //For using a module
                IDE oue=searchKey(ht,root->lexeme, 1, 0);
                if (oue == NULL)
                {
                    flagp2=1;if(flagp) printf("Error: On line %d, Module %s being used is not present\n",root->lineno, root->lexeme);
                    //ERROR module not present
                }
                else if(strcmp(root->lexeme, curmod->ID)==0)
                {
                    flagp2=1;if(flagp) printf("Error: On line %d, Recursion is not allowed\n", root->lineno);
                }

                else
                    // while (root->nextSibling != NULL)
     //             {   
                        root=root->nextSibling;
                    // }
            }



        }
        // To tackle variables
        else if(root->parent != NULL && root->parent->parent != NULL && root->parent->parent->symbol == declareStmt )
        {
            parseTree rit ;int fla=0;
            parseTree ritu=root;
            while(ritu!=NULL)
            {
                if(ritu->symbol==iterativeStmt && ritu->child->symbol==FOR)
                {
                    if(strcmp(ritu->child->nextSibling->nextSibling->iden->entity.ivar->ID, root->lexeme)==0)
                        fla=1;

                    break;
                }
                ritu=ritu->parent;
            }

            // if(fla)
            // {
            // }
            // else
            // {
                IDE porthq=searchKey(ht,root->lexeme, 0, st->depth);
                // if(searchKey(ht,root->lexeme, 0, scovar)==NULL)
                // {
                    //flagp2=1;if(flagp) printf("%s ko abhi table mein daal raha hoon line %d\n", root->lexeme,root->lineno);
                    //To etract data type
                    rit = root->parent->nextSibling->nextSibling;
                    parseTree tiit = rit->nextSibling;
                    struct array* ar = (struct array*) malloc (sizeof(struct array));
                    int wid;
                    Symbol s=97754;
                    if(rit->child->symbol == INTEGER)
                    {
                        wid=2;
                        s=INTEGER;
                    }
                    else if(rit->child->symbol == REAL)
                    {
                        wid=4;
                        s=REAL;
                    }
                    else if(rit->child->symbol == BOOLEAN)
                    {
                        wid=1;
                        s=BOOLEAN;
                    }
                    else if(rit->child->symbol == ARRAY)
                    {
                        //flagp2=1;if(flagp) printf("%s\n",root->lexeme);
                        parseTree tut = rit->child->nextSibling;
                        tut=tut->nextSibling;
                        ar->rangeStart=atoi(tut->child->lexeme);
                        ar->rangeFinish=atoi(tut->child->nextSibling->nextSibling->lexeme);
                        ar->type= tut->nextSibling->nextSibling->nextSibling->child->symbol;
                        //flagp2=1;if(flagp) printf("%s\n", IDtoStr(ar->type));
                        if(ar->type==INTEGER)
                            ar->width=2*(ar->rangeFinish - ar->rangeStart+1);
                        else if(ar->type==REAL)
                            ar->width=4*(ar->rangeFinish - ar->rangeStart+1);
                        else if(ar->type==BOOLEAN)
                            ar->width=1*(ar->rangeFinish - ar->rangeStart+1);
                        wid=ar->width;
                    }
            //      flagp2=1;if(flagp) printf("432rg4var\n");
                    IDE oue = (IDE) malloc (sizeof(struct idEnt));
                    oue->entity.ivar = (struct idVar*) malloc (sizeof(struct idVar)); 
                    strcpy(oue->entity.ivar->ID, root->lexeme);
                    oue->entity.ivar->lineno=root->lineno;
                    oue->entity.ivar->lineno=root->lineno;
                    oue->entity.ivar->scp=st;
                    oue->entity.ivar->porv=0;
                    oue->entity.ivar->offset=off;
                    off+=wid;
                    oue->entity.ivar->scope=st->depth;
                    oue->entity.ivar->nstlevel=st->actdp;
                    oue->entity.ivar->conFun=curmod;

                    if(rit->child->symbol==ARRAY)
                    {
                    //  flagp2=1;if(flagp) printf("fdssge\n");

                        //oue->entity.ivar = (struct array*) malloc (sizeof(struct array));
                        oue->entity.ivar->arrOrVar =1;
                        oue->entity.ivar->aov.a =ar;
                        //flagp2=1;if(flagp) printf("fdssge\n");
                        //flagp2=1;if(flagp) printf("fdssge\n");
                    }
                    else if(s==INTEGER || s==REAL || s==BOOLEAN)
                    {
                    //  flagp2=1;if(flagp) printf("gsfg\n");
                        oue->entity.ivar->aov.v = (struct variable*) malloc (sizeof(struct variable));
                        oue->entity.ivar->arrOrVar =0;
                        oue->entity.ivar->aov.v->type=s;
                        oue->entity.ivar->aov.v->width=wid;
                        free(ar);
                    }
                    //flagp2=1;if(flagp) printf("%d\n",oue->entity.ivar->arrOrVar);
                    if(porthq==NULL && fla==0)
                    {
                        //flagp2=1;if(flagp) printf("daal diya %s %d\n", root->lexeme, root->lineno);
                        addKey(ht, oue, 0);
                    }
                    else if(fla==1)
                    {
                        flagp2=1;if(flagp) printf("Error: On line %d, iterative variable %s, cannot be declared here again\n", root->lineno, root->lexeme);

                    }
                    else
                    {
                        flagp2=1;if(flagp) printf("Error: On line %d variable %s already declared in this scope\n",root->lineno, root->lexeme);
                    }
                    root->iden = oue;
                    rit=root->nextSibling; //rit pointing to N3
                    //flagp2=1;if(flagp) printf("%s   %d\n", root->lexeme, scovar);
                    //flagp2=1;if(flagp) printf("%s\n", root->nextSibling->lexeme);

                    //flagp2=1;if(flagp) printf("fdg\n");
                    while (rit->child!=NULL && rit->child->symbol !=e)
                    {
                        //flagp2=1;if(flagp) printf("fdsf\n");
                        rit=rit->child->nextSibling;
                        parseTree ritu=rit;
                        int fla=0;
                        while(ritu!=NULL)
                        {
                            if(ritu->symbol==iterativeStmt && ritu->child->symbol==FOR)
                            {
                                if(strcmp(ritu->child->nextSibling->nextSibling->iden->entity.ivar->ID, rit->lexeme)==0)
                                    fla=1;

                                break;
                            }
                        ritu=ritu->parent;
                        }
                        if(fla)
                        {
                            flagp2=1;if(flagp) printf("Error: On line %d, iterative variable %s, cannot be declared here again\n", rit->lineno, rit->lexeme);
                            rit=rit->nextSibling;
                        }
                        else
                        {
                            if(searchKey(ht,rit->lexeme, 0, st->depth)==NULL)
                            {
                                IDE oue = (IDE) malloc (sizeof(struct idEnt));
                                oue->entity.ivar = (struct idVar*) malloc (sizeof(struct idVar)); 
                                strcpy(oue->entity.ivar->ID, rit->lexeme);
                                oue->entity.ivar->lineno=rit->lineno;
                                oue->entity.ivar->scope=st->depth;
                                oue->entity.ivar->scp=st;
                                oue->entity.ivar->porv=0;
                                oue->entity.ivar->nstlevel=st->actdp;
                                oue->entity.ivar->conFun=curmod;
                                oue->entity.ivar->offset=off;
                                off+=wid;
                                if(s==INTEGER || s==REAL || s==BOOLEAN)
                                {
                                    oue->entity.ivar->aov.v = (struct variable*) malloc (sizeof(struct variable));
                                    oue->entity.ivar->arrOrVar =0;
                                    oue->entity.ivar->aov.v->type=s;
                                    oue->entity.ivar->aov.v->width=wid;
                                    //free(ar);
                                }
                                else
                                {
                                //  flagp2=1;if(flagp) printf("fdssge\n");

                                    //oue->entity.ivar = (struct array*) malloc (sizeof(struct array));
                                    oue->entity.ivar->arrOrVar =1;
                                    oue->entity.ivar->aov.a =ar;
                                    //flagp2=1;if(flagp) printf("fdssge\n");
                                    //flagp2=1;if(flagp) printf("fdssge\n");
                                }
                                addKey(ht, oue, 0);
                                rit->iden=oue;  
                                rit=rit->nextSibling;           
                            }
                            else 
                            {
                                    ///updated can be removed
                                flagp2=1;if(flagp) printf("Error: On line %d, variable %s already declared in this scope\n", rit->lineno, rit->lexeme);
                                rit=rit->nextSibling;
                                //ERROR var already declared in this scope
                            }
                        }

                    }
                    return;
                    root=tiit;
                    //flagp2=1;if(flagp) printf("hfdh%s\n", IDtoStr(tiit->symbol));
                // }
                // else
                // {
                //  flagp2=1;if(flagp) printf("Error: On line %d variable %s already declared in this scope\n",root->lineno, root->lexeme);
                //  //ERROR var already declared in this scope

                //  //baki ke variable check karne hai na!
                // }
            
            return;

        }
        else
        {
            //To check if variables being used are declared or not
            scopeTree k=st;
            //flagp2=1;if(flagp) printf("var being used tested %s symbol %s line no %d\n",root->lexeme,IDtoStr(root->parent->symbol), root->lineno);
            IDE varus=searchKey(ht,root->lexeme, 0, st->depth);
            while(k!=NULL && varus==NULL)
            {
                varus=searchKey(ht,root->lexeme, 0, k->depth);
                    //flagp2=1;if(flagp) printf("%d\n %d", k->depth, scovar);
                k=k->parent;
            }
            if(varus!=NULL)
            {

                // if(k==NULL)
                // {
                //  //ERROR var not declared anywhere
                // }
                // else 
                if(root->parent!=NULL && root->parent->symbol==conditionalStmt)
                {
                    //flagp2=1;if(flagp) printf("sdds\n");
                    root->iden=varus;
                    varus->entity.ivar->conFun=curmod;
                    //flagp2=1;if(flagp) printf("sym tab pt added for %s, line %d, ident %s\n", root->lexeme, root->lineno, root->iden->entity.ivar->ID);
                    IDE ouefor=varus;
                    if(ouefor->entity.ivar->arrOrVar==1)
                    {
                        flagp2=1;if(flagp) printf("Error: On line %d can't use array type in Switch statement\n", root->lineno);
                    }
                    else
                    {
                        if(ouefor->entity.ivar->aov.v->type==REAL)
                        {
                            flagp2=1;if(flagp) printf("Error: On line %d can't use Real type in Switch statement\n", root->lineno);
                        }
                        else if(ouefor->entity.ivar->aov.v->type==BOOLEAN)
                        {
                            parseTree pto=root;
                            while(pto!=NULL && pto->symbol != Default)
                                pto=pto->nextSibling;
                            if(pto !=NULL && pto->child!= NULL && pto->child->symbol!=e)
                            {
                                flagp2=1;if(flagp) printf("Error: On line %d, boolean switch cannot have default\n", root->lineno);
                            }
                        }
                        else if(ouefor->entity.ivar->aov.v->type==INTEGER)
                        {
                            parseTree pto=root;
                            while(pto!=NULL && pto->symbol != Default)
                                pto=pto->nextSibling;
                            if(pto !=NULL && pto->child!= NULL && pto->child->symbol==e)
                            {
                                flagp2=1;if(flagp) printf("Error: On line %d, integer switch must have a default\n", root->lineno);
                            }
                        }

                    }
                }
                else if(root->parent!=NULL && root->parent->child !=NULL && root->parent->child->symbol==FOR)
                {
                    varus->entity.ivar->conFun=curmod;
                    root->iden=varus;
                    //flagp2=1;if(flagp) printf("sym tab pt added for %s, line %d, ident %s\n", root->lexeme, root->lineno, root->iden->entity.ivar->ID);
                    IDE ouefor=varus;
                    ouefor->entity.ivar->forVar=1;
                    ouefor->entity.ivar->valAss=1;
                    //flagp2=1;if(flagp) printf("%sklhkl\n", root->lexeme);
                }
                else
                {
                    if(varus!=NULL)
                        varus->entity.ivar->conFun=curmod;
                    root->iden=varus;//flagp2=1;if(flagp) printf("sdkjn\n");
                    //flagp2=1;if(flagp) printf("sym tab pt added for %s, line %d, ident %s\n", root->lexeme, root->lineno, root->iden->entity.ivar->ID);
                }
            }
            else
            {
                    flagp2=1;if(flagp) printf("Error: On line %d, variable %s not declared anywhere\n", root->lineno, root->lexeme);

                root->iden=varus;//flagp2=1;if(flagp) printf("sdkjn22\n");
                //varus->entity.ivar->conFun=curmod;
                //flagp2=1;if(flagp) printf("sym tab pt added for %s, line %d, ident %s\n", root->lexeme, root->lineno, root->iden->entity.ivar->ID);
            }

        }
    }
    else if(root->symbol== input_plist)
    {
        //To add variables belonging to input parameter list to the hash table
    //  flagp2=1;if(flagp) printf("4\n");
        parseTree pt=root->child;
        parseTree rit=pt->nextSibling->nextSibling ;
        struct array* ar = (struct array*) malloc (sizeof(struct array));

        Symbol s=87987; int wid;
        if(rit->child->symbol == INTEGER)
        {
            wid=2;
            s=INTEGER;
        }
        else if(rit->child->symbol == REAL)
        {
            wid=4;
            s=REAL;
        }
        else if(rit->child->symbol == BOOLEAN)
        {
            wid=1;
            s=BOOLEAN;
        }
        else if(rit->child->symbol == ARRAY)
        {
            parseTree tut = rit->child->nextSibling;
            tut=tut->nextSibling;
            ar->rangeStart=atoi(tut->child->lexeme);
            ar->rangeFinish=atoi(tut->child->nextSibling->nextSibling->lexeme);
            ar->type= tut->nextSibling->nextSibling->nextSibling->child->symbol;
            //flagp2=1;if(flagp) printf("%d   %d\n", ar->rangeStart, ar->type);
            if(ar->type==INTEGER)
                ar->width=2*(ar->rangeFinish - ar->rangeStart+1);
            else if(ar->type==REAL)
                ar->width=4*(ar->rangeFinish - ar->rangeStart+1);
            else if(ar->type==BOOLEAN)
                ar->width=1*(ar->rangeFinish - ar->rangeStart+1);
            wid=ar->width;

        }
        //flagp2=1;if(flagp) printf("%d\n", ar->type);
    //  flagp2=1;if(flagp) printf("4\n");
        Params param;
        param=(Params) malloc(sizeof(struct params));
        IDE oue = (IDE) malloc (sizeof(struct idEnt));
        oue->entity.ivar = (struct idVar*) malloc (sizeof(struct idVar)); 
        strcpy(oue->entity.ivar->ID, pt->lexeme);
        oue->entity.ivar->conFun=curmod;
        //flagp2=1;if(flagp) printf("%s\n",oue->entity.ivar->conFun->ID);
        oue->entity.ivar->nstlevel=1;
        pt->iden=oue;
        oue->entity.ivar->lineno=pt->lineno;
        oue->entity.ivar->offset=off;
        oue->entity.ivar->scp=st;
        oue->entity.ivar->porv=1;
        off+=wid;
        oue->entity.ivar->scope = scovar+1;
    //  flagp2=1;if(flagp) printf("4\n");
        if (rit->child->symbol==ARRAY)
        {
        //  flagp2=1;if(flagp) printf("fdssge\n");

            //oue->entity.ivar = (struct array*) malloc (sizeof(struct array));
            oue->entity.ivar->arrOrVar =1;
            oue->entity.ivar->aov.a =ar;
            //flagp2=1;if(flagp) printf("fdssge\n");
            param->aov=1;
            param->var.a=ar;
            //flagp2=1;if(flagp) printf("fdssge\n");
        //  flagp2=1;if(flagp) printf("%d\n", ar->width);
        }
        else
        {
            oue->entity.ivar->aov.v = (struct variable*) malloc (sizeof(struct variable));
            oue->entity.ivar->arrOrVar =0;
            param->aov=0;
            param->var.v =(struct variable*) malloc (sizeof(struct variable));
            param->var.v->type=s;
            oue->entity.ivar->aov.v->type=s;
            oue->entity.ivar->aov.v->width=wid;
            free(ar);
        }
        
        param->next=NULL;
        addKey(ht, oue, 0);
        parseTree perty = root->parent->child->nextSibling->nextSibling;
        IDE funse = searchKey(ht,perty->lexeme, 1, 0 );
        //flagp2=1;if(flagp) printf("fds3s\n");
        funse->entity.ifun->inpParam=param;
        //flagp2=1;if(flagp) printf("fd4ss\n");
        rit=rit->nextSibling;
        //flagp2=1;if(flagp) printf("%s\n",IDtoStr(rit->symbol));
        while (rit->child->symbol !=e)
        {

            rit=rit->child->nextSibling;
            //flagp2=1;if(flagp) printf("%s\n",IDtoStr(rit->symbol));
            struct array* ar = (struct array*) malloc (sizeof(struct array));
            pt = rit->nextSibling->nextSibling;
            Symbol s=45879; int wid;
            //flagp2=1;if(flagp) printf("fd4345ss\n");
            if(pt->child->symbol == INTEGER)
            {
                wid=2;
                s=INTEGER;
            }
            else if(pt->child->symbol == REAL)
            {
                wid=4;
                s=REAL;
            }
            else if(pt->child->symbol == BOOLEAN)
            {
                wid=1;
                s=BOOLEAN;
            }
            else if(pt->child->symbol == ARRAY)
            {
                parseTree tut = pt->child->nextSibling;
                tut=tut->nextSibling;
                ar->rangeStart=atoi(tut->child->lexeme);
                //flagp2=1;if(flagp) printf("____%d %s",atoi(tut->child->lexeme),tut->child->lexeme  );
                ar->rangeFinish=atoi(tut->child->nextSibling->nextSibling->lexeme);
                ar->type= tut->nextSibling->nextSibling->nextSibling->child->symbol;
                if(ar->type==INTEGER)
                    ar->width=2*(ar->rangeFinish - ar->rangeStart+1);
                else if(ar->type==REAL)
                    ar->width=4*(ar->rangeFinish - ar->rangeStart+1);
                else if(ar->type==BOOLEAN)
                    ar->width=1*(ar->rangeFinish - ar->rangeStart+1);
                ;;
                wid=ar->width;

                //flagp2=1;if(flagp) printf("____%d %s",);
            //  flagp2=1;if(flagp) printf("%d  %d\n",ar->rangeFinish - ar->rangeStart+1, wid);
            }
            //flagp2=1;if(flagp) printf("fd4345ss\n");
            if(searchKey(ht,rit->lexeme, 0, scovar+1)==NULL)
            {
                Params param1;
                param1=(Params) malloc(sizeof(struct params));

                IDE oue = (IDE) malloc (sizeof(struct idEnt));
                oue->entity.ivar = (struct idVar*) malloc (sizeof(struct idVar)); 
                strcpy(oue->entity.ivar->ID, rit->lexeme);
                oue->entity.ivar->conFun=curmod;
                //flagp2=1;if(flagp) printf("%s\n",curmod->ID);
                rit->iden=oue;
                oue->entity.ivar->lineno=rit->lineno;
                oue->entity.ivar->nstlevel=1;
                oue->entity.ivar->scope=scovar+1;
                oue->entity.ivar->scp=st;
                oue->entity.ivar->porv=1;
                oue->entity.ivar->offset=off;
                off+=wid;
                //flagp2=1;if(flagp) printf("fd4345ss\n");
                if(pt->child->symbol == ARRAY)
                {

                    //oue->entity.ivar = (struct array*) malloc (sizeof(struct array));
                    oue->entity.ivar->arrOrVar =1;
                    oue->entity.ivar->aov.a =ar;
                    param1->aov=1;
                    param1->var.a=ar;
                }
                else
                {
                    oue->entity.ivar->aov.v = (struct variable*) malloc (sizeof(struct variable));
                    oue->entity.ivar->arrOrVar =0;
                    param1->aov=0;
                    param1->var.v =(struct variable*) malloc (sizeof(struct variable));
                    param1->var.v->type=s;
                    oue->entity.ivar->aov.v->type=s;
                    oue->entity.ivar->aov.v->width=wid;
                    free(ar);
                }
                param1->next=NULL;
                param->next=param1;
                param=param->next;
                addKey(ht, oue, 0);                     
            }
            else
            {
                flagp2=1;if(flagp) printf("Error: On line %d, variable %s already declared in this scope\n", rit->lineno,rit->lexeme );
                //ERROR var already declared in this scope
            }
            rit=pt->nextSibling;
            //flagp2=1;if(flagp) printf("%s\n",IDtoStr(rit->symbol));
        }

        root=root->nextSibling;
    }
    else if(root->symbol == output_plist)
    {
        //To add variables belonging to return parameter list to the hast table
        //flagp2=1;if(flagp) printf("6\n");
        parseTree pt=root->child;
        parseTree rit=pt->nextSibling->nextSibling ;
        
        Symbol s=98677; int wid;
        if(rit->child->symbol == INTEGER)
        {
            wid=2;
            s=INTEGER;
        }
        else if(rit->child->symbol == REAL)
        {
            wid=4;
            s=REAL;
        }
        else if(rit->child->symbol == BOOLEAN)
        {
            wid=1;
            s=BOOLEAN;
        }
    //  flagp2=1;if(flagp) printf("4\n");
        Params param;
        param=(Params) malloc(sizeof(struct params));
        IDE oue = (IDE) malloc (sizeof(struct idEnt));
        oue->entity.ivar = (struct idVar*) malloc (sizeof(struct idVar)); 
        strcpy(oue->entity.ivar->ID, pt->lexeme);
        oue->entity.ivar->conFun=curmod;
        pt->iden=oue;
        oue->entity.ivar->lineno=pt->lineno;
        oue->entity.ivar->offset=off;
        oue->entity.ivar->retpar=1;
        oue->entity.ivar->scp=st;
        oue->entity.ivar->porv=1;
        oue->entity.ivar->nstlevel=st->actdp+1;
        off+=wid;
        oue->entity.ivar->scope=scovar+1;
        //flagp2=1;if(flagp) printf("4\n");

            oue->entity.ivar->aov.v = (struct variable*) malloc (sizeof(struct variable));
            oue->entity.ivar->arrOrVar =0;
            param->aov=0;
            param->var.v =(struct variable*) malloc (sizeof(struct variable));
            param->var.v->type=s;
            oue->entity.ivar->aov.v->type=s;
            oue->entity.ivar->aov.v->width=wid;;
        
        param->next=NULL;
        addKey(ht, oue, 0);
        //flagp2=1;if(flagp) printf("fd4ss\n");
        parseTree perty = root->parent->parent->child->nextSibling->nextSibling;
        IDE funse = searchKey(ht,perty->lexeme, 1, 0 );
        //flagp2=1;if(flagp) printf("fds3s\n");
        funse->entity.ifun->retParam=param;
        //flagp2=1;if(flagp) printf("fd4ss\n");
        rit=rit->nextSibling;
        //flagp2=1;if(flagp) printf("%s\n",IDtoStr(rit->symbol));
        while (rit->child->symbol !=e)
        {

            rit=rit->child->nextSibling;
            //flagp2=1;if(flagp) printf("%s\n",IDtoStr(rit->symbol));
            pt = rit->nextSibling->nextSibling;
            Symbol s=78568; int wid;
            //flagp2=1;if(flagp) printf("fd4345ss\n");
            if(pt->child->symbol == INTEGER)
            {
                wid=2;
                s=INTEGER;
            }
            else if(pt->child->symbol == REAL)
            {
                wid=4;
                s=REAL;
            }
            else if(pt->child->symbol == BOOLEAN)
            {
                wid=1;
                s=BOOLEAN;
            }

            //flagp2=1;if(flagp) printf("fd4345ss\n");
            if(searchKey(ht,rit->lexeme, 0, scovar+1)==NULL)
            {
                Params param1;
                param1=(Params) malloc(sizeof(struct params));

                IDE oue = (IDE) malloc (sizeof(struct idEnt));
                oue->entity.ivar = (struct idVar*) malloc (sizeof(struct idVar)); 
                strcpy(oue->entity.ivar->ID, rit->lexeme);
                oue->entity.ivar->conFun=curmod;
                rit->iden=oue;
                oue->entity.ivar->lineno=rit->lineno;
                oue->entity.ivar->offset=off;
                oue->entity.ivar->scp=st;
                oue->entity.ivar->porv=1;
                oue->entity.ivar->retpar=1;
                oue->entity.ivar->nstlevel=st->actdp+1;
                off+=wid;
                oue->entity.ivar->scope=scovar+1;
                //flagp2=1;if(flagp) printf("fd4345ss\n");
                if(s==INTEGER || s==REAL || s==BOOLEAN)
                {
                    oue->entity.ivar->aov.v = (struct variable*) malloc (sizeof(struct variable));
                    oue->entity.ivar->arrOrVar =0;
                    param1->aov=0;
                    param1->var.v =(struct variable*) malloc (sizeof(struct variable));
                    param1->var.v->type=s;
                    oue->entity.ivar->aov.v->type=s;
                    oue->entity.ivar->aov.v->width=wid;
                }

                param1->next=NULL;
                param->next=param1;
                param=param->next;
                addKey(ht, oue, 0);                     
            }
            else
            {
                flagp2=1;if(flagp) printf("Error: On line %d, variable %s is already discussed in this scope\n ", rit->lineno,rit->lexeme);

                //ERROR var already declared in this scope
            }
            rit=pt->nextSibling;
            //flagp2=1;if(flagp) printf("%s\n",IDtoStr(rit->symbol));
        }

        root=root->nextSibling;
    }
    //To check if a variable has been assigned a value ot not
    if(root->symbol ==ID && root->iden!=NULL && root->parent !=NULL && root->parent->symbol== assignmentStmt)
    {
        //flagp2=1;if(flagp) printf("%s %d\n", root->lexeme, root->lineno);
        root->iden->entity.ivar->valAss=1;
    }

    //flagp2=1;if(flagp) printf("    %d        %d  \n", st->depth, scovar);
    preorderCreateSymTable(root->child); // 1st child
   // flagp2=1;if(flagp) printf("    %d        %d  AFTWR\n", st->depth, scovar);
    if (root->child != NULL && root ->child->nextSibling!=NULL) //rest of children
    {
        //flagp2=1;if(flagp) printf("    %d        %d  %s\n", st->depth, scovar, IDtoStr(root->symbol));
        root = root->child->nextSibling;
        while (root != NULL)
        {
        //  flagp2=1;if(flagp) printf("    %d        %d  \n", st->depth, scovar);
            preorderCreateSymTable(root);
            root=root->nextSibling;
        }

    }
}


void printSymTable()
{
	printf("\n");
	int inq=1, km=0;
	for(km=0;km<hsize;km++)
	{
		if(ht[km]->flag)
		{
			Chain k = ht[km]->start;
			while(k!=NULL)
			{

				if (k->vof==0 && k->id->entity.ivar->porv==0)
				{

					printf("S.No. %d \t", inq); inq++;
					printf("%s\t",k->id->entity.ivar->ID);
					if(k->id->entity.ivar->arrOrVar==0 )
					{
						printf("%s\t\t\t",IDtoStr(k->id->entity.ivar->aov.v->type));
						printf("%s\t", k->id->entity.ivar->conFun->ID);
						printf("%d to %d \t",k->id->entity.ivar->scp->scstart,k->id->entity.ivar->scp->scend );
						printf("%d \t",k->id->entity.ivar->nstlevel );
						printf("%d \t",k->id->entity.ivar->aov.v->width);
						printf("%d \t",k->id->entity.ivar->offset );

					}
					else
					{
						printf("ARRAY(%d,%s)\t\t",1+k->id->entity.ivar->aov.a->rangeFinish - k->id->entity.ivar->aov.a->rangeStart,IDtoStr(k->id->entity.ivar->aov.a->type));
						printf("%s\t", k->id->entity.ivar->conFun->ID);
						printf("%d to %d \t",k->id->entity.ivar->scp->scstart,k->id->entity.ivar->scp->scend);
						printf("%d \t",k->id->entity.ivar->nstlevel );
						printf("%d \t",k->id->entity.ivar->aov.a->width);
						printf("%d \t",k->id->entity.ivar->offset );
					}
					printf("\n");

				}
				else if(k->vof==0 && k->id->entity.ivar->porv==1)
				{
					printf("S.No. %d \t", inq); inq++;
					printf("%s\t",k->id->entity.ivar->ID);
					if(k->id->entity.ivar->arrOrVar==0 )
					{
						printf("%s\t\t\t",IDtoStr(k->id->entity.ivar->aov.v->type));
						printf("%s\t", k->id->entity.ivar->conFun->ID);
						printf("%d to %d \t",k->id->entity.ivar->conFun->scp->scstart,k->id->entity.ivar->conFun->scp->scend );
						printf("%d \t",k->id->entity.ivar->nstlevel );
						printf("%d \t",k->id->entity.ivar->aov.v->width);
						printf("%d \t",k->id->entity.ivar->offset );

					}
					 else
					 {
					 	printf("ARRAY(%d,%s)\t\t",1+k->id->entity.ivar->aov.a->rangeFinish - k->id->entity.ivar->aov.a->rangeStart,IDtoStr(k->id->entity.ivar->aov.a->type) );
					 	printf("%s\t", k->id->entity.ivar->conFun->ID);
					 	printf("%d to %d \t",k->id->entity.ivar->conFun->scp->scstart,k->id->entity.ivar->conFun->scp->scend);
					 	printf("%d \t",k->id->entity.ivar->nstlevel );
					 	printf("%d \t",k->id->entity.ivar->aov.a->width);
					 	printf("%d \t",k->id->entity.ivar->offset );
					 }	
					printf("\n");
				}
				
				k=k->next;
			}

		}
	}

}
void checkRetVal()
{
    //Thi swill check if the return values of all the return variables are set or not
	int inq=1, km=0;
	for(km=0;km<hsize;km++)
	{
		if(ht[km]->flag)
		{
			Chain k = ht[km]->start;
			while(k!=NULL)
			{

				if (k->vof==0 && k->id->entity.ivar->retpar==1)
				{
					if(k->id->entity.ivar->valAss!=1)
                    {
						flagp2=1;if(flagp) printf("Error: On line %d, Return value not assigned for %s\n", k->id->entity.ivar->lineno, k->id->entity.ivar->ID);
                    }
				}
				
				k=k->next;
			}

		}
	}

}

void populateSymTable(parseTree p)
{
	ht = initializeHashTable();
	st = getScopeNode(0);
	preorderCreateSymTable(p);

}

void semanticAnalyze(parseTree root)
{
    if (root==NULL)
        return;
    //flagp2=1;if(flagp) printf("%s\n", IDtoStr(root->symbol));

    if(root->symbol==moduleReuseStmt)
    {
        //For type checking of the input paraemeters 
        IDE oue=searchKey(ht, root->child->nextSibling->lexeme,1, 0 );
        //flagp2=1;if(flagp) printf("%s\n",root->child->nextSibling->lexeme);
        if(oue != NULL)
        {
            if(oue->entity.ifun->retParam==NULL)
            {
                if(root->child->child!=NULL)
                {
                    flagp2=1;if(flagp) printf("Error: On line %d, calling function doesn't return anything\n",root->child->nextSibling->lineno );
                }
            }
            else if(root->child->child==NULL)
            {
                    flagp2=1;if(flagp) printf("Error: On line %d, no variables to store the return types\n",root->child->nextSibling->lineno);             
            }
            else
            {
                parseTree pt=root->child->child;
                //flagp2=1;if(flagp) printf("%s  %s\n", IDtoStr(pt->child->symbol), pt->child->lexeme);
                if(pt->child->iden!=NULL && pt->child->iden->entity.ivar->arrOrVar==0 && oue->entity.ifun->retParam->aov==0)
                {
            
                    if(pt->child->iden->entity.ivar->aov.v->type != oue->entity.ifun->retParam->var.v->type)
                    {
                        flagp2=1;if(flagp) printf("Error: On line %d, type mismatch for argument 1\n",root->child->nextSibling->lineno);
                    }
                }
                else if(pt->child->iden!=NULL && pt->child->iden->entity.ivar->arrOrVar==1 && oue->entity.ifun->retParam->aov==1)
                {
                    if(pt->child->iden->entity.ivar->aov.a->type != oue->entity.ifun->retParam->var.a->type)
                    {
                        flagp2=1;if(flagp) printf("Error: On line %d, type mismatch for argument 1\n",root->child->nextSibling->lineno);
                    }
                }
                else if(pt->child->iden!=NULL)
                {
                    flagp2=1;if(flagp) printf("Error: On line %d, type mismatch for argument 1\n",root->child->nextSibling->lineno);   
                }
                int argn=2;
                pt=pt->child->nextSibling;
                Params retarg = oue->entity.ifun->retParam;
                retarg=retarg->next;
                while (pt->child!=NULL && retarg!=NULL)
                {
                    if(pt->child->iden!=NULL && pt->child->iden->entity.ivar->arrOrVar==0 && retarg->aov==0)
                    {
                        if(pt->child->iden->entity.ivar->aov.v->type != retarg->var.v->type)
                        {
                            flagp2=1;if(flagp) printf("Error: On line %d, type mismatch for argument %d\n",root->child->nextSibling->lineno,argn++);
                        }
                    }
                    else if(pt->child->iden!=NULL && pt->child->iden->entity.ivar->arrOrVar==1 && retarg->aov==1)
                    {
                        if(pt->child->iden->entity.ivar->aov.a->type != retarg->var.a->type)
                        {
                            flagp2=1;if(flagp) printf("Error: On line %d, type mismatch for argument %d\n",root->child->nextSibling->lineno, argn++);
                        }
                    }
                    else if(pt->child->iden!=NULL)
                    {
                        flagp2=1;if(flagp) printf("Error: On line %d, type mismatch for argument %d\n",root->child->nextSibling->lineno, argn++);  
                    }
                    pt=pt->child->nextSibling;
                    retarg=retarg->next;
                }
                if(pt->child == NULL && retarg != NULL)
                {
                    flagp2=1;if(flagp) printf("Error: On line %d, too few arguments supplied\n",root->child->nextSibling->lineno); 
                }

                if(retarg == NULL && pt->child !=NULL)
                {
                    flagp2=1;if(flagp) printf("Error: On line %d, too many arguments supplied\n",root->child->nextSibling->lineno);    
                }

            }
            //return types checked
            //Now to check input types
            if(oue->entity.ifun->inpParam!=NULL)
            {
                parseTree pt=root->child->nextSibling->nextSibling;
                //flagp2=1;if(flagp) printf("%s  %s\n", IDtoStr(pt->child->symbol), pt->child->lexeme);
                if(pt->child->iden!=NULL && pt->child->iden->entity.ivar->arrOrVar==0 && oue->entity.ifun->inpParam->aov==0)
                {
            
                    if(pt->child->iden->entity.ivar->aov.v->type != oue->entity.ifun->inpParam->var.v->type)
                    {
                        flagp2=1;if(flagp) printf("Error: On line %d, type mismatch in input parameters for argument 1\n",root->child->nextSibling->lineno);
                    }
                }
                else if(pt->child->iden!=NULL && pt->child->iden->entity.ivar->arrOrVar==1 && oue->entity.ifun->inpParam->aov==1)
                {
                    if(pt->child->iden->entity.ivar->aov.a->type != oue->entity.ifun->inpParam->var.a->type)
                    {
                        flagp2=1;if(flagp) printf("Error: On line %d, type mismatch in input parameters for argument 1\n",root->child->nextSibling->lineno);
                    }
                }
                else if(pt->child->iden!=NULL )
                {
                    flagp2=1;if(flagp) printf("Error: On line %d, type mismatch in input parameters for argument 1\n",root->child->nextSibling->lineno);   
                }
                int argn=2;
                pt=pt->child->nextSibling;
                Params retarg = oue->entity.ifun->inpParam;
                retarg=retarg->next;
                while (pt->child!=NULL && retarg!=NULL)
                {
                    if(pt->child->iden!=NULL && pt->child->iden->entity.ivar->arrOrVar==0 && retarg->aov==0)
                    {
                        if(pt->child->iden->entity.ivar->aov.v->type != retarg->var.v->type)
                        {
                            flagp2=1;if(flagp) printf("Error: On line %d, type mismatch in input parameters for argument %d\n",root->child->nextSibling->lineno,argn++);
                        }
                    }
                    else if(pt->child->iden!=NULL && pt->child->iden->entity.ivar->arrOrVar==1 && retarg->aov==1)
                    {
                        if(pt->child->iden->entity.ivar->aov.a->type != retarg->var.a->type)
                        {
                            flagp2=1;if(flagp) printf("Error: On line %d, type mismatch in input parameters for argument %d\n",root->child->nextSibling->lineno, argn++);
                        }
                    }
                    else if(pt->child->iden!=NULL)
                    {
                        flagp2=1;if(flagp) printf("Error: On line %d, type mismatch in input parameters for argument %d\n",root->child->nextSibling->lineno, argn++);  
                    }
                    pt=pt->child->nextSibling;
                    retarg=retarg->next;
                }
                if(pt->child == NULL && retarg != NULL)
                {
                    flagp2=1;if(flagp) printf("Error: On line %d, too few input arguments supplied\n",root->child->nextSibling->lineno);   
                }

                if(retarg == NULL && pt->child !=NULL)
                {
                    flagp2=1;if(flagp) printf("Error: On line %d, too many input arguments supplied\n",root->child->nextSibling->lineno);  
                }

            }



        }
            
    }

    semanticAnalyze(root->child);

    if (root->child != NULL && root ->child->nextSibling!=NULL)
    {
        root = root->child->nextSibling;
        while (root != NULL)
        {
            semanticAnalyze(root);
            root=root->prevSibling->nextSibling->nextSibling;
        }

    }
}
