/*
Batch 80
Naman Jain 2014A7PS100P
Saksham Nagar 2014A7PS040P
*/

#include <stdio.h>
#include <string.h>

#include "lexerDef.h"
#include "parserDef.h"


int strToID (char *sr){
    int j;
    int number=0;

    if (strcmp(sr, "program" ) ==0) return program;
    else if (strcmp(sr, "moduleDeclarations" ) ==0) return moduleDeclarations;    
    else if (strcmp(sr, "moduleDeclaration" ) ==0) return moduleDeclaration; 
    else if (strcmp(sr, "otherModules" ) ==0) return otherModules; 
    else if (strcmp(sr, "driverModule" ) ==0) return driverModule; 
    else if (strcmp(sr, "module" ) ==0) return module; 
    else if (strcmp(sr, "ret" ) ==0) return ret; 
    else if (strcmp(sr, "input_plist" ) ==0) return input_plist; 
    else if (strcmp(sr, "N1" ) ==0) return N1; 
    else if (strcmp(sr, "output_plist" ) ==0) return output_plist; 
    else if (strcmp(sr, "N2" ) ==0) return N2; 
    else if (strcmp(sr, "dataType" ) ==0) return dataType; 
    else if (strcmp(sr, "moduleDef" ) ==0) return moduleDef; 
    else if (strcmp(sr, "statements" ) ==0) return statements; 
    else if (strcmp(sr, "statement" ) ==0) return statement; 
    else if (strcmp(sr, "ioStmt" ) ==0) return ioStmt; 
    else if (strcmp(sr, "var" ) ==0) return var; 
    else if (strcmp(sr, "whichId" ) ==0) return whichId; 
    else if (strcmp(sr, "simpleStmt" ) ==0) return simpleStmt; 
    else if (strcmp(sr, "assignmentStmt" ) ==0) return assignmentStmt; 
    else if (strcmp(sr, "whichStmt" ) ==0) return whichStmt; 
    else if (strcmp(sr, "lvalueIDStmt" ) ==0) return lvalueIDStmt; 
    else if (strcmp(sr, "lvalueARRStmt" ) ==0) return lvalueARRStmt; 
    else if (strcmp(sr, "Index" ) ==0) return Index; 
    else if (strcmp(sr, "moduleReuseStmt" ) ==0) return moduleReuseStmt; 
    else if (strcmp(sr, "optional" ) ==0) return optional; 
    else if (strcmp(sr, "idList" ) ==0) return idList; 
    else if (strcmp(sr, "N3" ) ==0) return N3; 
    else if (strcmp(sr, "expression" ) ==0) return expression; 
    else if (strcmp(sr, "arithmeticOrBooleanExpr" ) ==0) return arithmeticOrBooleanExpr; 
    else if (strcmp(sr, "AnyTerm" ) ==0) return AnyTerm; 
    else if (strcmp(sr, "arithmeticExpr" ) ==0) return arithmeticExpr; 
    else if (strcmp(sr, "N4" ) ==0) return N4; 
    else if (strcmp(sr, "term" ) ==0) return term; 
    else if (strcmp(sr, "N5" ) ==0) return N5; 
    else if (strcmp(sr, "factor" ) ==0) return factor; 
    else if (strcmp(sr, "op1" ) ==0) return op1; 
    else if (strcmp(sr, "op2" ) ==0) return op2; 
    else if (strcmp(sr, "logicalOp" ) ==0) return logicalOp; 
    else if (strcmp(sr, "relationalOp" ) ==0) return relationalOp; 
    else if (strcmp(sr, "declareStmt" ) ==0) return declareStmt; 
    else if (strcmp(sr, "conditionalStmt" ) ==0) return conditionalStmt; 
    else if (strcmp(sr, "caseStmts" ) ==0) return caseStmts; 
    else if (strcmp(sr, "N9" ) ==0) return N9; 
    else if (strcmp(sr, "value" ) ==0) return value; 
    else if (strcmp(sr, "Default" ) ==0) return Default; 
    else if (strcmp(sr, "iterativeStmt" ) ==0) return iterativeStmt; 
    else if (strcmp(sr, "range" ) ==0) return range; 
    else if (strcmp(sr, "INTEGER" ) ==0) return INTEGER; 
    else if (strcmp(sr, "REAL" ) ==0) return REAL; 
    else if (strcmp(sr, "BOOLEAN" ) ==0) return BOOLEAN; 
    else if (strcmp(sr, "OF" ) ==0) return OF; 
    else if (strcmp(sr, "ARRAY" ) ==0) return ARRAY;
    else if (strcmp(sr, "START" ) ==0) return START; 
    else if (strcmp(sr, "type" ) ==0) return type;
    else if (strcmp(sr, "END" ) ==0) return END; 
    else if (strcmp(sr, "DECLARE" ) ==0) return DECLARE; 
    else if (strcmp(sr, "MODULE" ) ==0) return MODULE; 
    else if (strcmp(sr, "DRIVER" ) ==0) return DRIVER;
    else if (strcmp(sr, "PROGRAM" ) ==0) return PROGRAM; 
    else if (strcmp(sr, "GET_VALUE" ) ==0) return GET_VALUE; 
    else if (strcmp(sr, "PRINT" ) ==0) return PRINT; 
    else if (strcmp(sr, "USE" ) ==0) return USE; 
    else if (strcmp(sr, "WITH" ) ==0) return WITH;
    else if (strcmp(sr, "PARAMETERS" ) ==0) return PARAMETERS; 
    else if (strcmp(sr, "TRUE" ) ==0) return TRUE; 
    else if (strcmp(sr, "FALSE" ) ==0) return FALSE; 
    else if (strcmp(sr, "takes" ) ==0) return takes; 
    else if (strcmp(sr, "RETURNS" ) ==0) return RETURNS;
    else if (strcmp(sr, "AND" ) ==0) return AND; 
    else if (strcmp(sr, "OR" ) ==0) return OR; 
    else if (strcmp(sr, "FOR" ) ==0) return FOR; 
    else if (strcmp(sr, "IN" ) ==0) return IN; 
    else if (strcmp(sr, "SWITCH" ) ==0) return SWITCH;\
    else if (strcmp(sr, "input" ) ==0) return input;
    else if (strcmp(sr, "CASE" ) ==0) return CASE; 
    else if (strcmp(sr, "BREAK" ) ==0) return BREAK; 
    else if (strcmp(sr, "DEFAULT" ) ==0) return DEFAULT; 
    else if (strcmp(sr, "WHILE" ) ==0) return WHILE; 
    else if (strcmp(sr, "PLUS" ) ==0) return PLUS;
    else if (strcmp(sr, "MINUS" ) ==0) return MINUS; 
    else if (strcmp(sr, "MUL" ) ==0) return MUL; 
    else if (strcmp(sr, "DIV" ) ==0) return DIV; 
    else if (strcmp(sr, "LT" ) ==0) return LT; 
    else if (strcmp(sr, "LE" ) ==0) return LE;
    else if (strcmp(sr, "GE" ) ==0) return GE; 
    else if (strcmp(sr, "GT" ) ==0) return GT; 
    else if (strcmp(sr, "EQ" ) ==0) return EQ;
    else if (strcmp(sr, "NE" ) ==0) return NE; 
    else if (strcmp(sr, "DEF" ) ==0) return DEF; 
    else if (strcmp(sr, "ENDDEF" ) ==0) return ENDDEF; 
    else if (strcmp(sr, "COLON" ) ==0) return COLON; 
    else if (strcmp(sr, "RANGEOP" ) ==0) return RANGEOP; 
    else if (strcmp(sr, "SEMICOL" ) ==0) return SEMICOL; 
    else if (strcmp(sr, "COMMA" ) ==0) return COMMA;
    else if (strcmp(sr, "ASSIGNOP" ) ==0) return ASSIGNOP; 
    else if (strcmp(sr, "SQBO" ) ==0) return SQBO; 
    else if (strcmp(sr, "SQBC" ) ==0) return SQBC; 
    else if (strcmp(sr, "BO" ) ==0) return BO; 
    else if (strcmp(sr, "BC" ) ==0) return BC;
    else if (strcmp(sr, "COMMENTMARK" ) ==0) return COMMENTMARK; 
    else if (strcmp(sr, "NUM" ) ==0) return NUM; 
    else if (strcmp(sr, "RNUM" ) ==0) return RNUM; 
    else if (strcmp(sr, "ID" ) ==0) return ID; 
    else if (strcmp(sr, "e" ) ==0) return e;
    else if (strcmp(sr, "NULL_PT" ) ==0) return NULL_PT; 
    else if (strcmp(sr, "$" ) ==0) return $;
    else if (strcmp(sr, "DRIVERENDDEF" ) ==0) return DRIVERENDDEF;
    else if (strcmp(sr, "DRIVERDEF" ) ==0) return DRIVERDEF;
    else if (sr[0] >= 48 && sr[0]<=57){
        for(j=0;j<strlen(sr); j++){
            number*=10;
            number += sr[j]-48;
        }
        return number;
    }

    //new non-terminals
    else if (strcmp(sr, "booleanOrNonBooleanArithmeticExpr" ) ==0) return booleanOrNonBooleanArithmeticExpr;
    else if (strcmp(sr, "expressionWithLogOp" ) ==0) return expressionWithLogOp;
    else if (strcmp(sr, "arithmeticOrBooleanExpr2" ) ==0) return arithmeticOrBooleanExpr2;
    else if (strcmp(sr, "expressionWithRelOp" ) ==0) return expressionWithRelOp;
    else if (strcmp(sr, "negOrPosArithmeticExpr" ) ==0) return negOrPosArithmeticExpr;
    else if (strcmp(sr, "AnyTerm2" ) ==0) return AnyTerm2;

}


char * IDtoStr(int qwd)
{
    if (qwd==program) return "program";
    else if (qwd==moduleDeclarations) return "moduleDeclarations";
    else if (qwd==moduleDeclaration) return "moduleDeclaration";
    else if (qwd==otherModules) return "otherModules";
    else if (qwd==driverModule) return "driverModule";
    else if (qwd==module) return "module";
    else if (qwd==ret) return "ret";
    else if (qwd==input_plist) return "input_plist";
    else if (qwd==N1) return "N1";
    else if (qwd==output_plist) return "output_plist";
    else if (qwd==N2) return "N2";
    else if (qwd==dataType) return "dataType";
    else if (qwd==moduleDef) return "moduleDef";
    else if (qwd==statements) return "statements";
    else if (qwd==statement) return "statement";
    else if (qwd==ioStmt) return "ioStmt";
    else if (qwd==var) return "var";
    else if (qwd==whichId) return "whichId";
    else if (qwd==simpleStmt) return "simpleStmt";
    else if (qwd==assignmentStmt) return "assignmentStmt";
    else if (qwd==whichStmt) return "whichStmt";
    else if (qwd==lvalueIDStmt) return "lvalueIDStmt";
    else if (qwd==lvalueARRStmt) return "lvalueARRStmt";
    else if (qwd==Index) return "Index";
    else if (qwd==moduleReuseStmt) return "moduleReuseStmt";
    else if (qwd==optional) return "optional";
    else if (qwd==idList) return "idList";
    else if (qwd==N3) return "N3";
    else if (qwd==expression) return "expression";
    else if (qwd==arithmeticOrBooleanExpr) return "arithmeticOrBooleanExpr";
    else if (qwd==AnyTerm) return "AnyTerm";
    else if (qwd==arithmeticExpr) return "arithmeticExpr";
    else if (qwd==N4) return "N4";
    else if (qwd==term) return "term";
    else if (qwd==N5) return "N5";
    else if (qwd==factor) return "factor";
    else if (qwd==op1) return "op1";
    else if (qwd==op2) return "op2";
    else if (qwd==logicalOp) return "logicalOp";
    else if (qwd==relationalOp) return "relationalOp";
    else if (qwd==declareStmt) return "declareStmt";
    else if (qwd==conditionalStmt) return "conditionalStmt";
    else if (qwd==caseStmts) return "caseStmts";
    else if (qwd==N9) return "N9";
    else if (qwd==value) return "value";
    else if (qwd==Default) return "Default";
    else if (qwd==iterativeStmt) return "iterativeStmt";
    else if (qwd==range) return "range";
    else if (qwd==INTEGER) return "INTEGER";
    else if (qwd==REAL) return "REAL";
    else if (qwd==BOOLEAN) return "BOOLEAN";
    else if (qwd==OF) return "OF";
    else if (qwd==ARRAY) return "ARRAY";
    else if (qwd==type) return "type";
    else if (qwd==START) return "START";
    else if (qwd==END) return "END";
    else if (qwd==DECLARE) return "DECLARE";
    else if (qwd==MODULE) return "MODULE";
    else if (qwd==DRIVER) return "DRIVER";
    else if (qwd==PROGRAM) return "PROGRAM";
    else if (qwd==GET_VALUE) return "GET_VALUE";
    else if (qwd==PRINT) return "PRINT";
    else if (qwd==USE) return "USE";
    else if (qwd==WITH) return "WITH";
    else if (qwd==PARAMETERS) return "PARAMETERS";
    else if (qwd==TRUE) return "TRUE";
    else if (qwd==FALSE) return "FALSE";
    else if (qwd==takes) return "takes";
    else if (qwd==RETURNS) return "RETURNS";
    else if (qwd==AND) return "AND";
    else if (qwd==OR) return "OR";
    else if (qwd==FOR) return "FOR";
    else if (qwd==IN) return "IN";
    else if (qwd==SWITCH) return "SWITCH";
    else if (qwd==input) return "input";
    else if (qwd==CASE) return "CASE";
    else if (qwd==BREAK) return "BREAK";
    else if (qwd==DEFAULT) return "DEFAULT";
    else if (qwd==WHILE) return "WHILE";
    else if (qwd==PLUS) return "PLUS";
    else if (qwd==MINUS) return "MINUS";
    else if (qwd==MUL) return "MUL";
    else if (qwd==DIV) return "DIV";
    else if (qwd==LT) return "LT";
    else if (qwd==LE) return "LE";
    else if (qwd==GT) return "GT";
    else if (qwd==GE) return "GE";
    else if (qwd==NE) return "NE";
    else if (qwd==EQ) return "EQ";
    else if (qwd==DEF) return "DEF";
    else if (qwd==ENDDEF) return "ENDDEF";
    else if (qwd==COLON) return "COLON";
    else if (qwd==RANGEOP) return "RANGEOP";
    else if (qwd==SEMICOL) return "SEMICOL";
    else if (qwd==COMMA) return "COMMA";
    else if (qwd==ASSIGNOP) return "ASSIGNOP";
    else if (qwd==SQBC) return "SQBC";
    else if (qwd==SQBO) return "SQBO";
    else if (qwd==BO) return "BO";
    else if (qwd==BC) return "BC";
    else if (qwd==COMMENTMARK) return "COMMENTMARK";
    else if (qwd==NUM) return "NUM";
    else if (qwd==RNUM) return "RNUM";
    else if (qwd==ID) return "ID";
    else if (qwd==e) return "e";
    else if (qwd==NULL_PT) return "NULL_PT";
    else if (qwd==$) return "$";
    else if (qwd==DRIVERDEF) return "DRIVERDEF";
    else if (qwd==DRIVERENDDEF) return "DRIVERENDDEF";

    //new non-terminals
    else if (qwd==booleanOrNonBooleanArithmeticExpr) return "booleanOrNonBooleanArithmeticExpr";
    else if (qwd==expressionWithLogOp) return "expressionWithLogOp";
    else if (qwd==arithmeticOrBooleanExpr2) return "arithmeticOrBooleanExpr2";
    else if (qwd==expressionWithRelOp) return "expressionWithRelOp";
    else if (qwd==negOrPosArithmeticExpr) return "negOrPosArithmeticExpr";
    else if (qwd==AnyTerm2) return "AnyTerm2";

}
