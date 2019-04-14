/*
Batch 80
Naman Jain 2014A7PS100P
Saksham Nagar 2014A7PS040P
*/

#ifndef LEXERDEF
#define LEXERDEF

#define BUFFER_SIZE 100
#define MAX_LEXEME_SIZE 25
#define HASH_SIZE 40

//SYMBOL TABLE
typedef enum{
NULL_PT=-1,
	INTEGER, REAL, BOOLEAN, OF, ARRAY, START, END, DECLARE, MODULE, DRIVER, PROGRAM, GET_VALUE, PRINT, USE, WITH, PARAMETERS, TRUE, FALSE, takes, input, RETURNS, AND, OR, FOR, IN,SWITCH, CASE, BREAK, DEFAULT, WHILE, PLUS, MINUS, MUL, DIV, LT, LE, GE, GT, EQ, NE, DEF, ENDDEF, COLON,RANGEOP, SEMICOL, COMMA, ASSIGNOP, SQBO, SQBC, BO, BC, COMMENTMARK, NUM, RNUM, ID, DRIVERDEF, DRIVERENDDEF, $, e

}Symbol;

//this encapsulation stores the lexeme token and the line number of occurrence of the token
struct tinfo{

	char lexeme[MAX_LEXEME_SIZE];
	Symbol token;
	int lineno;
	struct tinfo *next;

};

typedef struct tinfo *tokenInfo;

struct dataItem{
	char key[20];
	Symbol data;
};

typedef struct dataItem* DataItem;

DataItem hashArray[HASH_SIZE];


#endif