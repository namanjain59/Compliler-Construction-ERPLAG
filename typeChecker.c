/*
Batch 80
Naman Jain 2014A7PS100P
Saksham Nagar 2014A7PS040P
*/

//#include "parserDef.h"

void typeCheck(parseTree p){

	parseTree root = p;

	if(root == NULL){
		return;
	}

	//Postorder traversal recursion
	typeCheck(root->child);

	parseTree q = root->child;

	if(q == NULL) return;

	while(q->nextSibling != NULL){
		typeCheck(q->nextSibling);
		q = q->nextSibling;
	}

	///////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////


	//Handling current node here (postorder traversal)

	//Errors for 'for' and 'while' loops:-
	//Test conditions should be boolean, and iterator should be integer
	if(root->symbol == iterativeStmt){
		if(root->child->nextSibling->symbol == arithmeticOrBooleanExpr){
			if(root->child->nextSibling->type == BOOLEAN){
				root->type = e;
			}else{
				flagp2=1;if(flagp)printf("Error: On line %d, the test condition of while loop should be a boolean expression\n", 
					root->child->lineno);
			}
		}
		else if(root->child->nextSibling->symbol == ID){
			if(root->child->nextSibling->iden != NULL)
			if(root->child->nextSibling->iden->entity.ivar->aov.v->type == INTEGER){
				root->type = e;
			}else{
				flagp2=1;if(flagp)printf("Error: On line %d, variable %s of for loop should be of type integer\n",
				 root->child->nextSibling->lineno, root->child->nextSibling->lexeme); 	//symbol contains the actual name of ID
			}
		}
	}

	//Cases in a caseStmt can only be of type integer or boolean
	else if(root->symbol == value){
		if(root->child->symbol == NUM){
			root->type = INTEGER;
		}
		else if(root->child->symbol == TRUE || root->child->symbol == FALSE){
			root->type = BOOLEAN;
		}
		else{	
			flagp2=1;if(flagp)printf("Error: On line %d, value of a case statement can only be of type integer or boolean\n",
				 root->child->lineno);
		}
	}


	//Array type IDs should have an index, and non-arrays should not
	else if(root->symbol == var){
		if(root->child->symbol == NUM){
			root->type = INTEGER;
		}else if(root->child->symbol == RNUM){
			root->type = REAL;
		}else if(root->child->symbol ==TRUE || root->child->symbol == FALSE){
			root->type = BOOLEAN;
		}
		else if(root->child->symbol == ID){
			if(root->child->iden != NULL){
			if(root->child->nextSibling->child == NULL){		//IMPORTANT. CHECK LATER
				if(root->child->iden->entity.ivar->arrOrVar == 0)
					root->type = root->child->iden->entity.ivar->aov.v->type;
				else
				{
					flagp2=1;if(flagp)printf("Error: On line %d, Array has to be indexed\n", root->child->lineno);
				}
			}else if(root->child->nextSibling->child != NULL){
				if(root->child->iden->entity.ivar->arrOrVar == 1){
					root->type = root->child->iden->entity.ivar->aov.a->type;
				}else{
					flagp2=1;if(flagp)printf("Error: On line %d, non-array variable cannot be indexed\n", root->child->lineno);
				}
			}
		}
		}
	}



	else if(root->symbol == factor && root->child->symbol == var){
		root->type = root->child->type;
		//printf("factor %s %d\n", IDtoStr(root->type), root->child->child->lineno);
	}


	//Handling conflicting types in MUL and DIV operations
	else if(root->symbol == N5){
		if(root->child == NULL){
			root->type = e;
		}
		else if(root->child->symbol == op2){
			if(root->child->nextSibling->type == 
				root->child->nextSibling->nextSibling->type || 
				root->child->nextSibling->nextSibling->child == NULL){

				root->type = root->child->nextSibling->type;
			}
			else{
				flagp2=1;if(flagp)printf("Error: On line %d, type mismatch - %s operation cannot be done on conflicting types\n", 
					root->child->child->lineno, IDtoStr(root->child->child->symbol));
			}
		}
	}

	else if(root->symbol == term){
		if(root->child->symbol == factor){
			if(root->child->type == 
				root->child->nextSibling->type || 
				root->child->nextSibling->child == NULL){

				root->type = root->child->type;

				//printf("term %s %d\n", IDtoStr(root->type), root->child->child->child->lineno);
			}
			else{
				//printf("Error: on line %d, type mismatch\n", root->child->child->child->lineno);
			}
		}
	}


	//Handling conflicting types in PLUS and MINUS operations
	else if(root->symbol == N4){
		if(root->child == NULL){
			root->type = e;
		}
		else if(root->child->symbol == op1){
			if(root->child->nextSibling->type == 
				root->child->nextSibling->nextSibling->type || 
				root->child->nextSibling->nextSibling->child == NULL){

				root->type = root->child->nextSibling->type;
			}
			else{
				flagp2=1;if(flagp)printf("Error: On line %d, type mismatch - %s operation cannot be done on conflicting types\n",
				 root->child->child->lineno, IDtoStr(root->child->child->symbol));
			}
		}
	}



	else if(root->symbol == arithmeticExpr){
		if(root->child->symbol == term){
			if(root->child->type == 
				root->child->nextSibling->type || 
				root->child->nextSibling->child == NULL){

				root->type = root->child->type;

			//printf("arithmeticExpr %s %d\n", IDtoStr(root->type), root->child->child->child->child->lineno);
			}
			else{
				//printf("ERROR on line %d : type mismatch\n", root->child->child->child->child->lineno);
			}
		}
	}


	///////////////////////////////////////////////////////
	//CHANGE OF RULES HERE!
	///////////////////////////////////////////////////////

	
	//New grammar rules cases



	else if(root->symbol == booleanOrNonBooleanArithmeticExpr){
		if(root->child->symbol == arithmeticExpr){
			root->type = root->child->type;
		}
	}

	else if(root->symbol == negOrPosArithmeticExpr){
		if(root->child->symbol == booleanOrNonBooleanArithmeticExpr){
			root->type = root->child->type;
		}else if(root->child->symbol == MINUS){
			root->type = root->child->nextSibling->type;
		}
	}


	//Two cases in relational operations:-
	//Multiple relational ops are not allowed, and relational expression should not have conflicting types
	else if(root->symbol == expressionWithRelOp){
		if(root->child == NULL){
			root->type = e;
		}else if(root->child->symbol == relationalOp){
			parseTree tempNOPAE = root->child->nextSibling;
			parseTree tempEWRO = root->child->nextSibling->nextSibling;
			if(tempEWRO->child != NULL){
				if(tempEWRO->type == tempNOPAE->type){
					root->type = BOOLEAN;
				}else if(tempEWRO->type == BOOLEAN){
					flagp2=1;if(flagp)printf("Error: On line %d, more than one relational operations being used\n", root->child->child->lineno);
				}else{
					flagp2=1;if(flagp)printf("Error: On line %d, type mismatch - conflicting types in the relational expression\n", root->child->child->lineno);
				}
				
			}else if(tempEWRO->child == NULL){
				root->type = tempNOPAE->type;
			}
			else{
				//printf("Error at line %d : type mismatch5\n", root->child->child->lineno);
			}
		}
	}


	else if(root->symbol == AnyTerm){
		parseTree tempAE = root->child;
		parseTree tempEWRO = root->child->nextSibling;
		if(tempEWRO->child != NULL){
			if(tempEWRO->type == tempAE->type){
				root->type = BOOLEAN;
			}else if(tempEWRO->type == BOOLEAN){
				flagp2=1;if(flagp)printf("Error: On line %d, more than one relational operations being used\n", root->child->child->child->child->child->lineno);
			}else{
				flagp2=1;if(flagp)printf("Error: On line %d, type mismatch - conflicting types in the relational expression\n", root->child->child->child->child->child->lineno);
			}
			
		}else if(tempEWRO->child == NULL){
			root->type = tempAE->type;
		}
		else{
			//printf("Error at line %d : type mismatch6\n", root->child->child->child->child->child->lineno);
		}
	}



	//check again
	else if(root->symbol == AnyTerm2){
		root->type = root->child->type;
	}


	//check again
	//Check all cases


	//Handling expressions with Logical op :- All expressions between AND and OR operators should be boolean
	else if(root->symbol == expressionWithLogOp){
		if(root->child == NULL){
			root->type = e;
		}else if(root->child->symbol == logicalOp){
			parseTree tempAT2 = root->child->nextSibling;
			parseTree tempEWLO = root->child->nextSibling->nextSibling;
			if(tempEWLO->child != NULL){
				if(tempAT2->type != BOOLEAN){
					flagp2=1;if(flagp)printf("Error: On line %d, expression has to be boolean to apply %s operation\n", root->child->child->lineno, IDtoStr(root->child->child->symbol));
				}else if(tempAT2->type == tempEWLO->type){	//both BOOLEAN
					root->type = tempAT2->type;
				}
			}else if(tempEWLO->child == NULL){
				if(tempAT2->type != BOOLEAN){
					flagp2=1;if(flagp)printf("Error: On line %d, expression has to be boolean to apply %s operation\n", root->child->child->lineno, IDtoStr(root->child->child->symbol));
				}else if(tempAT2->type == BOOLEAN){
					root->type = tempAT2->type;
				}
			}
			else{
				//printf("Error at line %d : type mismatch63\n", root->child->child->lineno);
			}

		}
	}

	//have to check

	//Logical Op should only be used with boolean expressions
	//boolean expressions should not be used with any other op
	else if(root->symbol == arithmeticOrBooleanExpr2){
		if(root->child == NULL){
			root->type = e;
		}else if(root->child->symbol == logicalOp){
			if(root->child->nextSibling->type == BOOLEAN){
				root->type = root->child->nextSibling->type;
			}else{
				flagp2=1;if(flagp)printf("Error: On line %d, types of expressions should be boolean\n", root->child->child->lineno);
			}
		}else{
			if(root->child->nextSibling->type != BOOLEAN){
				root->type = root->child->nextSibling->type;
			}else{
				flagp2=1;if(flagp)printf("Error: On line %d, can't use BOOLEAN type with %s operation\n", root->child->child->lineno, IDtoStr(root->child->child->symbol));
			}
		}
	}

	//check
	else if(root->symbol == arithmeticOrBooleanExpr){
		if(root->child->symbol == AnyTerm){
			parseTree tempAT = root->child;
			parseTree tempEWLO = root->child->nextSibling;

			if(tempEWLO->child != NULL){
				if(tempAT->type != BOOLEAN){
					flagp2=1;if(flagp)printf("Error: On line %d, type mismatch - have to use BOOLEAN types with %s operator\n", root->child->child->child->child->child->child->lineno, IDtoStr(tempEWLO->child->child->symbol));
				}else if(tempAT->type == tempEWLO->type){
					root->type = tempAT->type;
				}
			}else if(tempEWLO->child == NULL){
				root->type = tempAT->type;
			}
			else{
				//printf("Error: on line %d, type mismatch9\n", root->child->child->child->child->child->child->lineno);
			}
		}
		else if(root->child->symbol == arithmeticOrBooleanExpr){
			if(root->child->type == root->child->nextSibling->type || root->child->nextSibling->child == NULL){
				root->type = root->child->type;
			}else{
				flagp2=1;if(flagp)printf("Error: On line %d, type mismatch - conflicting types using %s operator\n",
					root->child->child->child->child->child->child->child->lineno, IDtoStr(root->child->nextSibling->child->child->symbol));	//check
			}
		}
	}


	///////////////////////////////////////////////////////
	///////////////////////////////////////////////////////



	///////////////////////////////////////////////////////////////////
	//Type checking in statements
	///////////////////////////////////////////////////////////////////


	//Array items can only be indexed by an integer variable
	//Arrays cannot be indexed by static values
	else if(root->symbol == Index){
		if(root->child->symbol == ID){
			if(root->child->iden != NULL)
			if(root->child->iden->entity.ivar->aov.v->type == INTEGER){
				root->type = INTEGER;
			}
			else{
				flagp2=1;if(flagp)printf("Error: On line %d, Array items cannot be indexed by a %s value\n", root->child->lineno, IDtoStr(
					root->child->iden->entity.ivar->aov.v->type));
			}
		}else if(root->child->symbol == NUM){
			flagp2=1;if(flagp)printf("Error: On line %d, Array items cannot be indexed by a static integer value\n", root->child->lineno);
		}
	}

	else if(root->symbol == lvalueARRStmt){
		if(root->child->symbol == Index){
			if(root->child->type == INTEGER){
				root->type =  root->child->nextSibling->nextSibling->type;	//type of expression
			}
		}
	}

	else if(root->symbol == lvalueIDStmt){
		root->type = root->child->nextSibling->type;
	}

	else if(root->symbol == whichStmt){
		root->type = root->child->type;
	}


	//Handling type mismatch in LHS and RHS of assignmentStmt
	//Handling special cases of array elements
	else if(root->symbol == assignmentStmt){
		if(root->child->iden != NULL){
			if(root->child->iden->entity.ivar->arrOrVar == 1){
				if(root->child->iden->entity.ivar->aov.a->type == root->child->nextSibling->type){

					root->type = root->child->iden->entity.ivar->aov.a->type;
				}
				else{
					flagp2=1;if(flagp)printf("Error: On line %d, type mismatch - in LHS and RHS of assignmentStmt\n", root->child->lineno);
				}
			}
			else{
				if(root->child->iden->entity.ivar->aov.v->type == root->child->nextSibling->type){

					root->type = root->child->iden->entity.ivar->aov.v->type;
				}
				else{
					flagp2=1;if(flagp)printf("Error: On line %d, type mismatch - in LHS and RHS of assignmentStmt\n", root->child->lineno);
				}
			}
		}
	}

	else if(root->symbol == whichId){
		if(root->child == NULL){
			root->type = e;
		}else if(root->child->symbol == ID){
			if(root->child->iden != NULL)
			if(root->child->iden->entity.ivar->aov.v->type == INTEGER){
				root->type = root->child->iden->entity.ivar->aov.v->type;
			}else{
				flagp2=1;if(flagp)printf("Error: On line %d, Array items cannot be indexed by a %s value\n", root->child->lineno, IDtoStr(
					root->child->iden->entity.ivar->aov.v->type));
			}
		}
	}


	else if(root->symbol == expression){
		if(root->child->symbol == arithmeticOrBooleanExpr){
			root->type = root->child->type;
		}else{
			root->type = root->child->nextSibling->type;
		}
	}


}//end of typeCheck
