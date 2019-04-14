/*
Batch 80
Naman Jain 2014A7PS100P
Saksham Nagar 2014A7PS040P
*/

#include <stdio.h>
#include <string.h>

/*
	global _start
	extern printf

	section .data
		abc: db	value

	section .text
_start: 
		
*/
FILE* fp;

char* inttochar(int p)
{
	char* buf=(char*)malloc(20*sizeof(char));
	sprintf(buf, "%d", p);
	return buf;
}
void postorderEval(parseTree root)
{
	if(root==NULL)
		return;

	postorderEval(root->child); // 1st child
    if (root->child != NULL && root ->child->nextSibling!=NULL) //rest of children
    {
        root = root->child->nextSibling;
        while (root != NULL)
        {
            postorderEval(root);
            root=root->nextSibling;
        }
    }


    

}

void readIO(parseTree root)
{	
	char ch[30];
	strcpy(ch, root->nextSibling->lexeme);
	strcat(ch, inttochar(root->nextSibling->iden->entity.ivar->lineno));
	fprintf(fp,"\t\tmov\trsi, %s \t\n", ch);
	fprintf(fp,"\t\tmov\trdi, inp \t\n");
	fprintf(fp,"\t\tcall scanf \t\n\n");
}

void writeIO(parseTree root)
{	
	char ch[30];
	//printf("dsgv\n");
	root=root->child;

	strcpy(ch, root->lexeme);
	strcat(ch, inttochar(root->iden->entity.ivar->lineno));
	fprintf(fp,"\t\tmov\trsi, [%s] \t\n", ch);
	fprintf(fp,"\t\tmov\trdi, inp \t\n");
	fprintf(fp,"\t\tcall printf \t\n\n");
}

void parseCodegen(parseTree root)
{
	if(root==NULL)
		return;
	//printf("%s\n", IDtoStr(root->symbol));
	if(root->symbol==GET_VALUE)
	{
		//printf("sex karo\n");
		readIO(root);
	}
	else if(root->symbol==PRINT)
	{
		//printf("sex karo\n");
		writeIO(root->nextSibling);
	}
	else if(root->symbol==assignmentStmt)
	{

		if(root->child->nextSibling->child->symbol==lvalueIDStmt)
		{
			postorderEval(root);
		}
		else if(root->child->nextSibling->child->symbol==lvalueARRStmt)
		{
			postorderEval(root);
		}
		return;
	}



	parseCodegen(root->child); // 1st child
    if (root->child != NULL && root ->child->nextSibling!=NULL) //rest of children
    {
        root = root->child->nextSibling;
        while (root != NULL)
        {
            parseCodegen(root);
            root=root->nextSibling;
        }

    }
}




void writeData()
{
	fprintf(fp, "\tsection .data\n");
	fprintf(fp, "\t\tinp:\t dw \t\"%cd\", 0\n\n",37);


	fprintf(fp, "\tsection .bss\n");
	int inq=1, km=0;
	for(km=0;km<hsize;km++)
	{
		if(ht[km]->flag)
		{
			Chain k = ht[km]->start;
			while(k!=NULL)
			{

				if (k->vof==0)
				{

					if(k->id->entity.ivar->arrOrVar==0 )
					{
						if(k->id->entity.ivar->aov.v->type==INTEGER)
						{
							fprintf(fp,"\t\t%s%d:\t resb\t%d\n", k->id->entity.ivar->ID, k->id->entity.ivar->lineno,k->id->entity.ivar->aov.v->width );
						}
						else if(k->id->entity.ivar->aov.v->type==BOOLEAN)
						{
							fprintf(fp,"\t\t%s%d:\t resb\t%d\n", k->id->entity.ivar->ID, k->id->entity.ivar->lineno,k->id->entity.ivar->aov.v->width );
						}
					}
					else
					{
						if(k->id->entity.ivar->aov.a->type==INTEGER)
						{
							fprintf(fp,"\t\t%s%d:\t resb\t%d\n", k->id->entity.ivar->ID, k->id->entity.ivar->lineno,k->id->entity.ivar->aov.a->width );
						}
						else if(k->id->entity.ivar->aov.a->type==BOOLEAN)
						{
							fprintf(fp,"\t\t%s%d:\t resb\t%d\n", k->id->entity.ivar->ID, k->id->entity.ivar->lineno,k->id->entity.ivar->aov.a->width );
						}
					}
				}
				k=k->next;
			}
		}
	}
}

void codegen (parseTree root, char* outfile)
{
    fp=fopen(outfile, "w");
//    printf("success\n");
	fprintf(fp,"\textern printf\n");
	fprintf(fp,"\textern scanf\n\n");
    writeData(fp);
    fprintf(fp, "\n\tsection .txt\n");
    fprintf(fp, "\t\tglobal main\n\n");
    fprintf(fp, "main:\n");
    parseCodegen(root);
    fprintf(fp,"\t\tmov\teax, 0 \t\n");
    fprintf(fp,"\t\tret\t\n");


}

