/*
Batch 80
Naman Jain 2014A7PS100P
Saksham Nagar 2014A7PS040P
*/

#include "lexerDef.h"

#define hsize 13

// Structures of scpue tree
struct scopetree{

	int depth;
	int actdp;
	struct scopetree* parent;
	struct scopetree* child; //many children
	int scstart;
	int scend;
};	
typedef struct scopetree* scopeTree;


typedef enum
{ 
	defined, declared
} funcStatus;

struct array
{
	int rangeStart;
	int rangeFinish;
	Symbol type;
	int width;
}; 

struct variable
{
	Symbol type;
	int width;
};
struct params
{
	union
	{
		struct array* a;
		struct variable* v;
	} var;
	int aov;
	struct params* next;
};
typedef struct params* Params;

struct idVar
{
	char ID[MAX_LEXEME_SIZE];
	int lineno;
//	int hcode;
	int arrOrVar; // 1 for array, 0 for variable
	int scope;
	int nstlevel;
	int offset;
	int porv; //parameter1 or var par0;
	union
	{
		struct variable* v;
		struct array* a;
	}aov;
	int valAss; //1 if val is assigned
	int retpar;
	struct idFunc* conFun;
	scopeTree scp;
	int forVar;

};

struct idFunc
{
	char ID[MAX_LEXEME_SIZE];
	int scope;
	int lineno;
	funcStatus status;
	Params inpParam;
	Params retParam;
	scopeTree scp;

};

// These are structures for hash table
struct idEnt
{
	union
	{
		struct idVar* ivar;
		struct idFunc* ifun;
	} entity;
};
typedef struct idEnt* IDE;
struct chain
{
	int vof; 
	IDE id;
	struct chain* next;
};
typedef struct chain* Chain;
struct cell
{
	int flag; // 1 means occupied ;0 mean available
	Chain start;
};

typedef struct cell *Cell;
typedef Cell *hashTable;		



