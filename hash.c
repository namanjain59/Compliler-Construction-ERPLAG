/*
Batch 80
Naman Jain 2014A7PS100P
Saksham Nagar 2014A7PS040P
*/

hashTable initializeHashTable()
{
	hashTable hays=(hashTable) malloc(hsize*sizeof(struct cell*));
	int i=0;

	while(i<hsize)
	{
		//printf("%d",i);
		hays[i] = (struct cell*) malloc (sizeof(struct cell));
		hays[i]->flag=0;
		hays[i]->start=NULL;
// //		hays[i]->id=NULL;
		i++;
	}
	return hays;
}

int hCode(char *key)
{
	int i,t=key[0]-'0',len=strlen(key);
	for(i=1;i<len;i++)
		t+=(key[i]-'0');
	return t % hsize;
}

//op ==1 means function; 0 mean var
void addKey(hashTable T, IDE id, int op)
{
	int l;
	if(op==1)
		l=hCode(id->entity.ifun->ID);
	else
		l=hCode(id->entity.ivar->ID);

	Chain c= (Chain) malloc (sizeof(struct chain));
	c->id=id;
	c->vof=op;
	c->next=NULL;
	if(T[l]->flag==0)
	{
		T[l]->flag=1;
		T[l]->start=c;
		//printf("mhfk ug %s     ",c->id->entity.ivar->ID );

	}
	else
	{
		Chain k=T[l]->start;
			while(k->next !=NULL)
			{
			//	printf("%s     ",k->id->entity.ivar->ID );

				k=k->next;
			}
		k->next=c;
	}
}

IDE searchKey(hashTable T, char* sch, int op, int sco)
{
	int l=hCode(sch);
	if(T[l]->flag==0)
	{
		return NULL;
	}

	Chain k=T[l]->start;
	
	if (op==1)
	{
		while(k!=NULL)
		{
			if(k->vof==op && strcmp(k->id->entity.ifun->ID, sch)==0 && k->id->entity.ifun->scope == sco)
			{
				break;
			}
			k=k->next;	
		}	
	}
	else
	{
		while(k!=NULL)
		{
			if(k->vof==op && strcmp(k->id->entity.ivar->ID, sch)==0 && k->id->entity.ivar->scope == sco)
			{
			//	printf("%s     ",k->id->entity.ivar->ID );
				break;
			}
			k=k->next;	
		}	
	}
	
	if(k==NULL)
		return NULL;
	return k->id;

}
