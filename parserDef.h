/*
Batch 80
Naman Jain 2014A7PS100P
Saksham Nagar 2014A7PS040P
*/

#ifndef PARSERDEF
#define PARSERDEF

#define NONTERM_OFF 1500
#define NO_OF_TERM 59
#define NO_OF_NONTERM 55
#define NO_OF_PROD 107
#define MAX_RULE_LEN 25

#include "lexerDef.h"
#include "SymDef.h"
//#include "utility.h"

typedef int grammar[NO_OF_PROD][MAX_RULE_LEN + 2]; // +2 for the storing the nonterminal and size of the rule 
typedef int parseTable[NO_OF_NONTERM][NO_OF_TERM]; // the parse table stores production numbers for each (nonterminal, terminal) pair


typedef enum{

	program = NONTERM_OFF, moduleDeclarations, moduleDeclaration, otherModules, driverModule, module, ret, input_plist, N1, output_plist, N2, dataType, type, moduleDef, statements, statement, ioStmt, var, whichId, simpleStmt, assignmentStmt, whichStmt, lvalueIDStmt, lvalueARRStmt, Index, moduleReuseStmt, optional, idList, N3, expression, arithmeticOrBooleanExpr, AnyTerm,
	arithmeticExpr, N4, term, N5, factor, op1, op2, logicalOp, relationalOp, declareStmt, conditionalStmt, caseStmts, N9, value, Default, iterativeStmt, range, booleanOrNonBooleanArithmeticExpr, arithmeticOrBooleanExpr2, AnyTerm2, expressionWithLogOp, expressionWithRelOp, negOrPosArithmeticExpr

}pSymbol;

struct parsetree{

	int isTerminal;
	/*union{
		pSymbol nonTerminal;
		Symbol terminal;
	};*/
	int symbol;
	char lexeme[MAX_LEXEME_SIZE];
	int lineno;
	int type;
	IDE iden;
	struct parsetree* parent;
	struct parsetree* child; //many children
	struct parsetree* nextSibling;
	struct parsetree* prevSibling;
	int numChildren;

};

typedef struct parsetree* parseTree;

//Implementing Stack
struct node 
{
	int info;
	struct node *next;
};
typedef struct node *NODE;

#endif
