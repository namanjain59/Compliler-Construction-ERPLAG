/*
Batch 80
Naman Jain 2014A7PS100P
Saksham Nagar 2014A7PS040P
*/

// #include <stdio.h>
// #include <string.h>
// #include <limits.h>
// #include <stdlib.h>

//#include "parser.h"
//#include "lexer.h"

// #include "lexerDef.h"
// #include "parserDef.h"

/////////////////////////////////////////////////////////////////////////

/*typedef enum{
NULL_PT=-1,
	INTEGER, REAL, BOOLEAN, OF, ARRAY, START, END, DECLARE, MODULE, DRIVER, PROGRAM, GET_VALUE, PRINT, USE, 
	WITH, PARAMETERS, TRUE, FALSE, takes, input, RETURNS, AND, OR, FOR, IN,SWITCH, CASE, BREAK, DEFAULT, WHILE, 
	PLUS, MINUS, MUL, DIV, LT, LE, GE, GT, EQ, NE, DEF, ENDDEF, COLON,RANGEOP, SEMICOL, COMMA, ASSIGNOP, SQBO, 
	SQBC, BO, BC, COMMENTMARK, NUM, RNUM, ID, DRIVERDEF, DRIVERENDDEF, $, e

}Symbol;*/


/*typedef enum{

	program = NONTERM_OFF, moduleDeclarations, moduleDeclaration, otherModules, driverModule, module, 
	ret, input_plist, N1, output_plist, N2, dataType, type, moduleDef, statements, statement, ioStmt, var, 
	whichId, simpleStmt, assignmentStmt, whichStmt, lvalueIDStmt, lvalueARRStmt, Index, moduleReuseStmt, 
	optional, idList, N3, expression, arithmeticOrBooleanExpr, N7, AnyTerm, N8, arithmeticExpr, N4, term, 
	N5, factor, op1, op2, logicalOp, relationalOp, declareStmt, conditionalStmt, caseStmts, N9, value, 
	Default, iterativeStmt, range

}pSymbol;*/


/*int isTerm(int x){
	if(x < NONTERM_OFF) return 1;
	else return 0;
}*/





int isUseful(int x){

	/*if(!isTerm(x)){
		switch(x){

			case INTEGER : return 1;
			case REAL : return 1;
			case BOOLEAN : return 1;
			case OF : return 0;
			case ARRAY : return 0;
			case START : return 0;
			case END : return 0;
			case DECLARE : return 0;
			case MODULE : return 0;
			case DRIVER : return 0;
			case PROGRAM : return 0;
			case GET_VALUE : return 0;
			case PRINT : return 0;
			case USE : return 0;
			case WITH : return 0;
			case PARAMETERS : return 0;
			case TRUE : return 1;
			case FALSE : return 1;
			case takes : return 0;
			case input : return 0;
			case RETURNS : return 0;
			case AND : return 1;
			case OR : return 1;
			case FOR : return 0;
			case IN : return 0;
			case SWITCH : return 0;
			case CASE : return 0;
			case BREAK : return 0;
			case DEFAULT : return 0;
			case WHILE : return 0;
			case PLUS : return 1;
			case MINUS : return 1;
			case MUL : return 1;
			case DIV : return 1;
			case LT : return 1;
			case LE : return 1;
			case GE : return 1;
			case GT : return 1;
			case EQ : return 1;
			case NE : return 1;
			case DEF : return 0;
			case ENDDEF : return 0;
			case COLON : return 0;
			case RANGEOP : return 0;
			case SEMICOL : return 0;
			case COMMA : return 0;
			case ASSIGNOP : return 0;
			case SQBO : return 0;
			case SQBC : return 0;
			case BO : return 0;
			case BC : return 0;
			case COMMENTMARK : return 0;
			case NUM : return 1;
			case RNUM : return 1;
			case ID : return 1;
			case DRIVERDEF : return 0;
			case DRIVERENDDEF : return 0;
			case e : return 0;


		}
	}
	else return 1;*/

	if(x == ID || x == NUM || x == RNUM || x == PLUS || x == MINUS || x== MUL || x==DIV || x == LT || x == LE ||
		x == GT || x == GE || x== EQ || x == NE || x == AND || x == OR || x == TRUE || x == FALSE || x == INTEGER ||
		x == REAL || x==BOOLEAN || x == ASSIGNOP || x == GET_VALUE || x == PRINT || x == WHILE || x == FOR){
		return 1;
	}
	else if(x >= NONTERM_OFF) return 1;

	else return 0;

}



//First we remove useless terminals from the parse tree, like SQBO, SQBC etc
void removeUselessTerminals(parseTree p){

	parseTree root = p;

	//printf("%s\n", IDtoStr(root->symbol));

	if(root == NULL){
		return;
	}


	//remove useless terminals in preorder
	//do things here

	parseTree r = root->child;

	if(r == NULL)
	{

		if(!isUseful(root->symbol)){
			root->parent->numChildren--;
			parseTree prev = root->prevSibling;
			parseTree next = root->nextSibling;
			if(prev==NULL && next==NULL)
			{
				root->parent->child=NULL;
			}
			else if(prev==NULL && next!=NULL)
			{
				root->parent->child=next;
				next->prevSibling=NULL;

			} 
			else if(prev !=NULL && next ==NULL)
			{
				prev->nextSibling=NULL;
			}
			else
			{
				prev->nextSibling=next;
				next->prevSibling=prev;
			}
			free(root);


			return;

			// if(prev != NULL)
			// 	prev->nextSibling = next;
			// else
			// 	root->parent->child = root->nextSibling;
			// if(next!= NULL)
			// 	next->prevSibling = prev;
			// return;
		
		}
	}

	parseTree child = root->child;
	while(child!=NULL)
	{
		removeUselessTerminals(child);
		child=child->nextSibling;
	}
	// //this is preorder recursion
	// removeUselessTerminals(root->child);
	// //printf("done\n");
	// parseTree q = root->child;	//q is temp variable
	// if(q==NULL)
	// 	return ;
	// while(q->nextSibling != NULL){
	// 	q = q->nextSibling;
	// 	removeUselessTerminals(q);
	// }

	return;

	///////////////////////////////////////////////////////////////

	/*if(!isUseful(root->symbol)){
		if(root->prevSibling == NULL){
			root->parent->child = root->nextSibling;
		}else{
			root->prevSibling->nextSibling = root->nextSibling;
			if(root->nextSibling != NULL){
				root->nextSibling->prevSibling = root->prevSibling;
			}
		}
		removeUselessTerminals(root->nextSibling);
	}

	if(root->child == NULL && root->nextSibling == NULL){
		removeUselessTerminals(root->parent);
	}
	else if(root->child == NULL){
		removeUselessTerminals(root->nextSibling);
	}
	else{
		removeUselessTerminals(root->child);
	}

	return;*/

}//end of removeUselessTerminals




//Then, we collapse linear vertical chains of non-terminals. They will just create a redundancy if present.
void collapseLinearChains(parseTree root){


	if(root==NULL){
		return;
	}

	//this is postorder recursion


	//do the thing here
	parseTree r = root->child;	//r is temp variable that goes till last child of linear chain

	if(r != NULL && root->numChildren == 1){
		while(r->child != NULL && r->numChildren == 1){
			r = r->child;
		}

		//replacing root with r

		r->nextSibling = root->nextSibling;
		r->prevSibling = root->prevSibling;
		r->parent=root->parent;

		if(root->nextSibling != NULL) 
			root->nextSibling->prevSibling = r;		
		
		if(root->prevSibling != NULL) 
			root->prevSibling->nextSibling = r;
		else root->parent->child=r;
		root=r;

	} 

	collapseLinearChains(root->child);
	parseTree q = root->child;	//q is temp variable
	if(q == NULL) return;
	while(q->nextSibling != NULL){
		q = q->nextSibling;
		collapseLinearChains(q);
	}


	

}//end of collapseLinearChains




//Finally, we collapse repeated recursion 
//(example if <term> -> <factor> <N4>, N4 is a non terminal that handles repeated recursion.
//We just compress that subtree into one list of children of the top most N4)
void collapseRepeatedRecursion(parseTree p){

	/*
	go down (preorder) till where epsilon comes/ the recursion ends with any set of terminals.
	apart from that last non terminal, there are some nodes on the left.
	transfer all of them above, in place of the recurring non-terminal.
	keep doing so till we have only one of those recurring non terminals and all of its subtree as its children.
	*/


	parseTree root = p;

	if(root == NULL){
		return;
	}

	//do things here
	parseTree r = root->child;

	while(r != NULL){

		if(r->symbol == root->symbol){
			//if r's child does not exist, remove r.

			if(r->child == NULL){
				if(r->prevSibling != NULL){
					r->prevSibling->nextSibling = r->nextSibling;
					if(r->nextSibling != NULL) r->nextSibling->prevSibling = r->prevSibling;
					r = r->nextSibling;
				}else if(r->nextSibling != NULL){
					r->parent->child = r->nextSibling;
					r = r->nextSibling;
				}
				continue;
			}

			//connect r's child to r's previous sibling
			r->child->prevSibling = r->prevSibling;
			if(r->prevSibling != NULL) r->prevSibling->nextSibling = r->child;
			else r->parent->child = r->child;
			r->child->parent = r->parent;
			//connect last one to r's next sibling
			parseTree pp = r->child;
			while(pp->nextSibling != NULL){
				pp = pp->nextSibling;
				pp->parent = r->parent;
			}
			pp->nextSibling = r->nextSibling;
			if(r->nextSibling != NULL){
				r->nextSibling->prevSibling = pp;
			}
			r = r->child;
		}
		else{
			r = r->nextSibling;
		}

	}



	//this is preorder recursion
	collapseRepeatedRecursion(root->child);
	parseTree q = root->child;	//q is temp variable
	if(q == NULL) return;
	while(q->nextSibling != NULL){
		q = q->nextSibling;
		collapseRepeatedRecursion(q);
	}

	return;

}//end of collapseRepeatedRecursion



/*
int isOperator(int x){

	if(x == PLUS || x== MINUS || x==DIV || x==MUL || x== LT || x==LE || x== GT || x==GE || x == EQ || x == NE
		|| x = AND || x == OR){

		return 1;
	}

	else return 0;

}//end of isOperator
*/



void createAST(parseTree p){			//USE THIS FUNCTION!!

	removeUselessTerminals(p);
	//printf("1 happened\n");
	//collapseLinearChains(p);
	//printf("2 happened\n");
	//collapseRepeatedRecursion(p);
	//printf("3 happened\n");

}//end of createAST


void preorderPrintAST(parseTree p){			//This is just for testing the AST. Good for use later.

	createAST(p);

	parseTree root = p;

	if(root != NULL){
		printf("%s\n", IDtoStr(root->symbol));

		preorderPrintAST(root->child);

		parseTree r = root->child;
		if(r == NULL) return;

		while(r->nextSibling != NULL){
			r = r->nextSibling;
			preorderPrintAST(r);
		}
	}

	return;

}//end of preorder
