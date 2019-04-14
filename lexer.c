/*
Batch 80
Naman Jain 2014A7PS100P
Saksham Nagar 2014A7PS040P
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//#include "lexerDef.h"

//global buffer
char* buffer;
int line_num=1;
int j=0;

//HASHING FUNCTIONS
int hashFunc(char* key){
	return (key[0]*10+key[1])%HASH_SIZE;
}//end of hashFunc

DataItem hashSearch(char* key){

	int hash_index = hashFunc(key);

	while(hashArray[hash_index] != NULL){

		if(!strcmp(hashArray[hash_index]->key, key)){
			return hashArray[hash_index];
		}
		hash_index++;
		hash_index%=HASH_SIZE;

	}

	return NULL;

}//end of hashSearch


void hashInsert(char* key, Symbol data){

	DataItem newItem = (DataItem) malloc(sizeof(struct dataItem));
	newItem->data= data;
	strcpy(newItem->key, key);
	int hash_index = hashFunc(key);

	while(hashArray[hash_index] != NULL && strcmp(hashArray[hash_index]->key, "")){
		hash_index++;
		hash_index%=HASH_SIZE;
	}
	hashArray[hash_index] = newItem;

}//end of hashInsert

//Add the keywords of the language into a hash table
void populateHashTable(){
	int q;
	// for(q=0; q<HASH_SIZE;q++){
	// 	hashArray[q]->key[0] = '\0';
	// }
	hashInsert("integer", INTEGER);
	hashInsert("real", REAL);
	hashInsert("boolean", BOOLEAN);
	hashInsert("of", OF);
	hashInsert("array", ARRAY);
	hashInsert("start", START);
	hashInsert("end", END);
	hashInsert("declare", DECLARE);
	hashInsert("module", MODULE);
	hashInsert("driver", DRIVER);
	hashInsert("program", PROGRAM);
	hashInsert("get_value", GET_VALUE);
	hashInsert("print", PRINT);
	hashInsert("use", USE);
	hashInsert("with", WITH);
	hashInsert("parameters", PARAMETERS);
	hashInsert("true", TRUE);
	hashInsert("false", FALSE);
	hashInsert("takes", takes);
	hashInsert("input", input);
	hashInsert("returns", RETURNS);
	hashInsert("AND", AND);
	hashInsert("OR", OR);
	hashInsert("for", FOR);
	hashInsert("in", IN);
	hashInsert("switch", SWITCH);
	hashInsert("case", CASE);
	hashInsert("break", BREAK);
	hashInsert("default", DEFAULT);
	hashInsert("while", WHILE);
	

}//end of populateHashTable

//To fing in a hash table
Symbol find(char* lex){

	DataItem di = hashSearch(lex);
	if(di == NULL&& strlen(lex) <=9){
		return ID;
	}else if(di!= NULL){
		return di->data;
	}else{
		return e;
		//ERROR
	}

}//end of find




//To get a stream from the the file
FILE* getStream(FILE *fp){

	buffer = (char*) malloc(sizeof(char)*BUFFER_SIZE);

	buffer[0]= '\0';

	//Here, num_chars is the number of characters read into the buffer from the file
	int num_chars = fread(buffer, sizeof(char), (size_t)BUFFER_SIZE, fp);

	if(!num_chars){
		return NULL;
	}

	if(num_chars== BUFFER_SIZE){
		int i = BUFFER_SIZE-1;

		//Need to take only full tokens in the buffer
		while(!(buffer[i] == ' ' || buffer[i]=='\t' || buffer[i] =='\n')){
			i--;
		}
		buffer[i+1] = '\0';

		//Setting cursor for next buffer access
		fseek(fp, -(BUFFER_SIZE-1-i), SEEK_CUR);
	}
	//printf("%s \n",buffer);
	return fp;

}//end of getStream


//To get the next token of thr source code
tokenInfo getNextToken(){

	tokenInfo t = (tokenInfo) malloc(sizeof(struct tinfo));
	t->next=NULL;
	int ero=0;

	// char lex[20];
	int k=1; int wer=1;
//	flagp2=1;if(flagp) printf("%c",buffer[j]);
		switch(buffer[j]){
			case '+':
				strcpy(t->lexeme, "+");
				t->token = PLUS;
				break;
			case '-':
				strcpy(t->lexeme, "-");
				t->token = MINUS;
				break;
			case '/':
				strcpy(t->lexeme, "/");
				t->token = DIV;
				break;
			case ';':
				strcpy(t->lexeme, ";");
				t->token = SEMICOL;
				break;
			case ',':
				strcpy(t->lexeme, ",");
				t->token = COMMA;
				break;
			case '[':
				strcpy(t->lexeme, "[");
				t->token = SQBO;
				break;
			case ']':
				strcpy(t->lexeme, "]");
				t->token = SQBC;
				break;
			case '(':
				strcpy(t->lexeme, "(");
				t->token = BO;
				break;
			case ')':
				strcpy(t->lexeme, ")");
				t->token = BC;
				break;
			case '=':
				if(buffer[j+1] == '='){
					strcpy(t->lexeme, "==");
					t->token = EQ;
					j++;
				}else{
					strcpy(t->lexeme, "=");
					ero=1;
					flagp2=1;if(flagp) printf("Error: On line %d, Unknown pattern %s \n", line_num,t->lexeme);
				}
				break;
			case '!':
				if(buffer[j+1] == '='){
					strcpy(t->lexeme, "!=");
					t->token = NE;
					j++;
				}else{
					strcpy(t->lexeme, "!");
					ero=1;
					flagp2=1;if(flagp) printf("Error: On line %d, Unknown pattern %s \n", line_num,t->lexeme);
				}
				break;
			case '<':
				if(buffer[j+1] == '='){
					strcpy(t->lexeme, "<=");
					t->token = LE;
					j++;
				}else if(buffer[j+1] == '<'){
					if(buffer[j+2]=='<')
					{						
						strcpy(t->lexeme, "<<<");
						t->token = DRIVERDEF;
						j++; j++;

					}
					else 
					{					
						strcpy(t->lexeme, "<<");
						t->token = DEF;
						j++;
					}
					
				}
				else{
					strcpy(t->lexeme, "<");
					t->token = LT;
				}
				break;
			case '>':
				if(buffer[j+1] == '='){
					strcpy(t->lexeme, ">=");
					t->token = GE;
					j++;
				}else if(buffer[j+1] == '>'){
					if(buffer[j+2]=='>')
					{						
						strcpy(t->lexeme, ">>>");
						t->token = DRIVERENDDEF;
						j++; j++;

					}
					else 
					{					
						strcpy(t->lexeme, ">>");
						t->token = ENDDEF;
						j++;
					}
				}
				else{
					strcpy(t->lexeme, ">");
					t->token = GT;
				}
				break;
			case ':':
				if(buffer[j+1] == '='){
					strcpy(t->lexeme, ":=");
					t->token = ASSIGNOP;
					j++;
				}else{
					strcpy(t->lexeme, ":");
					t->token = COLON;
				}
				break;
			case '.':
				if(buffer[j+1] == '.'){
					strcpy(t->lexeme, "..");
					t->token = RANGEOP;
					j++;
				}
				else{
					strcpy(t->lexeme, ".");
					ero=1;
					flagp2=1;if(flagp) printf("Error: On line %d, Unknown pattern %s \n", line_num,t->lexeme);
				}
				break;

			//TO BE DONE WHEN DRIVER IS AVAILABLE
			case '*':
				if(buffer[j+1] == '*'){
					j++; j++;
					while(buffer[j] != '*' && buffer[j+1] != '*') j++;
					j++;
					strcpy(t->lexeme, "****");
					t->token = COMMENTMARK;
				}
				else{
					strcpy(t->lexeme, "*");
					t->token = MUL;
				}
				break;
			case '0':
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9':
				t->lexeme[0] = buffer[j];
				j++; 
				while(buffer[j]>=48 && buffer[j]<=57){
					t->lexeme[wer] = buffer[j];wer++;
					j++;
				}
				if(buffer[j] == '.'){
					if(buffer[j+1]=='.'){
						t->token = NUM;
						j--;
					}else if(buffer[j+1]>=48 && buffer[j+1]<=57){
						t->lexeme[wer] = buffer[j];wer++;
						j++;
						while(buffer[j]>=48 && buffer[j]<=57){
							t->lexeme[wer] = buffer[j];wer++;
							j++;
						}

						if(buffer[j] != 'E' && buffer[j] != 'e'){
							t->token = RNUM;
							j--;
						}else{

							if((buffer[j+1]== '+' || buffer[j+1]== '-') && (buffer[j+2]>=48 && buffer[j+2] <=57)){
								t->lexeme[wer] = buffer[j];wer++;
								j++;
								t->lexeme[wer] = buffer[j];wer++;
								j++;
								t->lexeme[wer] = buffer[j];wer++;
								j++;
								while(buffer[j]>=48 && buffer[j]<=57){
									t->lexeme[wer] = buffer[j];wer++;
									j++;
								}
								t->token = RNUM;
								j--;
							}
							else if((buffer[j+1]>=48 && buffer[j+1] <=57)){
								t->lexeme[wer] = buffer[j];wer++;
								j++;
								t->lexeme[wer] = buffer[j];wer++;
								j++;
								while(buffer[j]>=48 && buffer[j]<=57){
									t->lexeme[wer] = buffer[j];wer++;
									j++;
								}
								t->token = RNUM;
								j--;
							}
							else{
								flagp2=1;if(flagp) printf("Error: on line %d, Unknown pattern %s\n", line_num,t->lexeme);
								ero=1;
							}
						}

					}
					else{
						flagp2=1;if(flagp) printf("Error: on line %d, Unknown pattern %s \n", line_num,t->lexeme);
						ero = 1;
					}
				} else {
					j--;
					t->token=NUM;
				}

				t->lexeme[wer] = '\0';
				break;

			case 'a':
			case 'b':
			case 'c':
			case 'd':
			case 'e':
			case 'f':
			case 'g':
			case 'h':
			case 'i':
			case 'j':
			case 'k':
			case 'l':
			case 'm':
			case 'n':
			case 'o':
			case 'p':
			case 'q':
			case 'r':
			case 's':
			case 't':
			case 'u':
			case 'v':
			case 'w':
			case 'x':
			case 'y':
			case 'z':
			case 'A':
			case 'B':
			case 'C':
			case 'D':
			case 'E':
			case 'F':
			case 'G':
			case 'H':
			case 'I':
			case 'J':
			case 'K':
			case 'L':
			case 'M':
			case 'N':
			case 'O':
			case 'P':
			case 'Q':
			case 'R':
			case 'S':
			case 'T':
			case 'U':
			case 'V':
			case 'W':
			case 'X':
			case 'Y':
			case 'Z':
				
				t->lexeme[0] = buffer[j];
				j++;
				while(j<strlen(buffer)&&(buffer[j] >= 'a' && buffer[j] <='z') || (buffer[j] >= 'A' && buffer[j] <='Z')|| (buffer[j]== '_') || (buffer[j] >= '0' && buffer[j] <='9')){
					t->lexeme[k] = buffer[j];
					j++;k++;
				}
				t->lexeme[k] = '\0';
				if(strcmp(t->lexeme, "TRUE")==0)
					strcpy(t->lexeme, "true");
				else if(strcmp(t->lexeme, "FALSE")==0)
					strcpy(t->lexeme, "false");
				t->token = find(t->lexeme); j--;
				if (t->token==e)
				{
					flagp2=1;if(flagp) printf("Error: On line %d,identifier is longer than the prescribed length\n", line_num);
					t->token=ID;
				}
				break;
			// case ' ':
			// case '\n':
			// case '\t':
			// // case '\r':
			// break;

			default : flagp2=1;if(flagp) printf("Error: On line %d, unknown Symbol %c\n", line_num,buffer[j] );
			ero=1;

		}
		// flagp2=1;if(flagp) printf("%c ", buffer[j]);
		j++;
		t->lineno = line_num;
		// while(buffer[j+1] == '\n' || buffer[j+1] == ' ' || buffer[j+1] == '\t'){
			
		// 	if(buffer[j+1] == '\n')line_num++;
		// 	j++;
		// }
		while(j<strlen(buffer) && buffer[j] == '\n' || buffer[j] == '\r' || buffer[j] == ' ' || buffer[j] == '\t'){
			
			if(buffer[j] == '\n'){line_num++; }
			j++;
		}

	//	flagp2=1;if(flagp) printf("%s\n", t->lexeme);
		if (ero==1)
		{
			if(j<strlen(buffer))
			{
				//flagp2=1;if(flagp) printf("%c\n",buffer[j]);
				return getNextToken();
			}
			else return NULL;
		}
		else
			return t;

}//end of getNextToken




FILE* removeComments(char* testcaseFile, char* cleanFile){

	FILE *fr, *fw;
	fr=fopen(testcaseFile, "r");
	fw=fopen(cleanFile, "w+");
	int flu=0;

	while (1){
		fr=getStream(fr);
		if(fr!=NULL)
		{
			int t=0, l=strlen(buffer);
			while (t <l )
			{	if (flu==1)
				{
					while (t< l && !(buffer[t] == '*' && buffer[t+1] == '*'))
					{
						if (buffer[t]=='\n' || buffer[t] == '\r')
						fprintf(fw, "%c", buffer[t]);							
						t++;
					}
					if(t==l)
					{
						flu=1;
					}
					else 
					{
						t+=2;
						flu=0;
					}
					// printf("1");
				}
				else if((buffer[t]=='*' && buffer[t+1]=='*'))
				{
					t+=2;
					while (t< l && !(buffer[t] == '*' && buffer[t+1] == '*'))
					{
						if (buffer[t]=='\n' || buffer[t] == '\r')
						fprintf(fw, "%c", buffer[t]);							
						t++;
					}
					if(t==l)
					{
						flu=1;
					}
					else 
					{
						flu=0;
						t+=2;
					}
					// printf("2");
				}
				else
				{
					// if(buffer[t]=='\t')
					// {
					// 	fprintf(fw, "%s", "      ");
					// }
					// else
						fprintf(fw, "%c", buffer[t]);
					t++;
				}
			}
		} else break;

	}
	fclose(fw);
	fw=fopen(cleanFile, "r");
	return fw;


}//end of removeComments


//This will create a linked list of the tokens in a code
void createLinkedList(tokenInfo tList){
	int len = strlen(buffer);
	tokenInfo head;
	head=tList;
	while(head->next != NULL){
		head=head->next;
	}
	while(j<len){
		while(j<len && buffer[j] == '\n' || buffer[j] == '\r' || buffer[j] == ' ' || buffer[j] == '\t'){
			if(buffer[j] == '\n'){line_num++; }

			j++;
		}
		if(j<len)
		{
			head->next= getNextToken();
			head=head->next;
		}
		// printf("%s ", head->lexeme);
		// printf("%d ", head->token);
		// printf("%d\n", head->lineno);

	}
	j=0;

}





















