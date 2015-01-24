


// N.SHASHANK - 2009B5A7585P
// D.ADITYA   - 2009B5A7669P



//#include"SyntaxAnalysis.h" //mod
 #include"SemanticAnalyser.h"
int scope;
char fun_name[100];

void AREC(TREENODE AST,SYHashTable h,LHashTable l,HashTable record)
{
SYResult r,r1;
Result rec;
CHILD cl;
char type[100];
cl=AST->head;
int typeflag=0;

	if(cl==NULL)
	{
		if(strcmp(AST->term,"TK_ID")==0)
		{
		r=findSYElement(h,AST->cur_tokendata.tokenid,scope);
		r1=findSYElement(h,AST->cur_tokendata.tokenid,0);

			
			
			if(r.error==0)
			strcpy(AST->cur_tokendata.token,r.e.type);
			else if(r1.error==0)
			strcpy(AST->cur_tokendata.token,r1.e.type);
			
			else
			printf("ERROR: variable %s undeclared line no %d\n",AST->cur_tokendata.tokenid,AST->cur_tokendata.linenumber);
		}
	else if(strcmp(AST->term,"TK_NUM")==0||strcmp(AST->term,"TK_RNUM")==0)
	{
	if(strcmp(AST->term,"TK_NUM")==0)
	strcpy(AST->cur_tokendata.token,"int");
	else
	strcpy(AST->cur_tokendata.token,"real");

	}

	}

	else
	{
	//printf("\nIN AREC\n");
	for(;cl!=NULL;cl=cl->next)
	{
	AREC(cl->cur,h,l,record);
	//printf("\ncheck--> %s %s \n",cl->cur->cur_tokendata.tokenid,cl->cur->cur_tokendata.token);
	
	}
	cl=AST->head;
	
	for(;cl!=NULL;cl=cl->next)
	{
		if(strcmp(cl->cur->cur_tokendata.token,"int")==0||strcmp(cl->cur->cur_tokendata.token,"real")==0)
		{
			strcpy(type,cl->cur->cur_tokendata.token);
			break;
		}
	}
	cl=AST->head;
	//printf("\n||||TYPE=%s|||||\n");

	for(;cl!=NULL;cl=cl->next)
	{
		if(strcmp(cl->cur->cur_tokendata.token,"int")==0||strcmp(cl->cur->cur_tokendata.token,"real")==0)
			{
			//printf("\n %s %s %s\n",cl->cur->cur_tokendata.tokenid,type,cl->cur->cur_tokendata.token);
			if(strcmp(type,cl->cur->cur_tokendata.token)!=0)
			{
				printf("Error in Line %d:type mismatch %s %s\n",cl->cur->cur_tokendata.linenumber,cl->cur->cur_tokendata.tokenid,cl->cur->cur_tokendata.token);
				strcpy(AST->cur_tokendata.token,"Undefined");
				typeflag=1;
			}
			
			}
		/*
		rec=findElement(h,cl->cur->cur_tokendata.token);
		if(rec.error==0)
		{
		
		}
		*/
			
		
	}
	if(typeflag==0)
	strcpy(AST->cur_tokendata.token,type);
	}
	
	


}




void assignCheck(TREENODE AST,SYHashTable h,LHashTable l,HashTable record)
{
SYResult r,r1;
CHILD cl;
CHILD left,right;
cl=AST->head;
left=cl;
right=cl->next->next;
Result rec;
RIGHT att;
int attflag=0;

r=findSYElement(h,left->cur->cur_tokendata.tokenid,scope);
r1=findSYElement(h,left->cur->cur_tokendata.tokenid,0);

	if(r.error==-1&&r1.error==-1)
		printf("ERROR in Line %d: variable %s undeclared\n",left->cur->cur_tokendata.linenumber,left->cur->cur_tokendata.tokenid);
	else
	{
		if(r.error!=-1)
		{
		//printf("\nAssignment Check->%s %s \n",left->cur->cur_tokendata.token,r.e.type);
		strcpy(left->cur->cur_tokendata.token,r.e.type);
		}
		else
		{
		//printf("\nAssignment Check->%s %s \n",left->cur->cur_tokendata.token,r1.e.type);
		strcpy(left->cur->cur_tokendata.token,r1.e.type);
		
		}
	}
	
	AREC(right->cur,h,l,record);
	
	if(strcmp(left->cur->term,"<SingleOrRecId>")==0)
	{
	//printf("\n\n\nMAX RAAAAAAAA\n\n\n");
	attflag=1;
	rec=findElement(record,left->cur->cur_tokendata.token);
	att=rec.e.production;
	while(att!=NULL)
	{
	if(strcmp(att->right,left->cur->head->next->cur->head->next->cur->cur_tokendata.tokenid)==0)
	{
	attflag=2;
	if(att->type==1)
	{
	strcpy(left->cur->cur_tokendata.token,"int");
	}
	else
	{
	strcpy(left->cur->cur_tokendata.token,"real");
	}
	}
	att=att->next;
	}
	
	if(attflag==1)
	printf("ERROR in Line %d: no fields for %s with %s\n",left->cur->cur_tokendata.linenumber,left->cur->cur_tokendata.token,left->cur->head->next->cur->head->next->cur->cur_tokendata.tokenid);
	}
	
	//printf("\ntype=%s\nterm=%s\n",left->cur->cur_tokendata.token,left->cur->term);
	if(strcmp(left->cur->cur_tokendata.token,right->cur->cur_tokendata.token)!=0&&strcmp("Undefined",right->cur->cur_tokendata.token)!=0)
	{strcpy(AST->cur_tokendata.token,"Undefined");
	printf("ERROR in Line %d: type mismatch %s %s\n",cl->cur->cur_tokendata.linenumber,cl->cur->cur_tokendata.tokenid,cl->cur->cur_tokendata.token);
	}
	else
	strcpy(AST->cur_tokendata.token,left->cur->cur_tokendata.token);


	
}

void boolCheck(TREENODE AST,SYHashTable h,LHashTable l,HashTable record)
{
CHILD cl;
cl=AST->head;


	if(strcmp(cl->cur->term,"<booleanExpression>")==0)
	{
	boolCheck(cl->cur,h,l,record);
	boolCheck(cl->next->next->cur,h,l,record);
		if(strcmp(cl->cur->cur_tokendata.token,"Undefined")!=0&&strcmp("Undefined",cl->next->next->cur->cur_tokendata.token)!=0&&strcmp(cl->cur->cur_tokendata.token,cl->next->next->cur->cur_tokendata.token)==0)
		{
		strcpy(AST->cur_tokendata.token,cl->cur->cur_tokendata.token);
		}
		else
		{
		strcpy(AST->cur_tokendata.token,"Undefined");
		printf("ERROR in Line %d: type mismatch %s %s\n",cl->cur->cur_tokendata.linenumber,cl->cur->cur_tokendata.tokenid,cl->cur->cur_tokendata.token);
		}

	}
	
	else if(strcmp(cl->cur->term,"TK_NOT")==0)
	{
	boolCheck(cl->next->cur,h,l,record);
	strcpy(AST->cur_tokendata.token,cl->next->cur->cur_tokendata.token);
	}

	else
	{
	AREC(cl->cur,h,l,record);
	AREC(cl->next->next->cur,h,l,record);
		if(strcmp(cl->cur->cur_tokendata.token,"Undefined")!=0&&strcmp("Undefined",cl->next->next->cur->cur_tokendata.token)!=0&&strcmp(cl->cur->cur_tokendata.token,cl->next->next->cur->cur_tokendata.token)==0)
		{
			strcpy(AST->cur_tokendata.token,"boolean");
		}
		else
		{
			strcpy(AST->cur_tokendata.token,"Undefined");
			printf("ERROR in Line %d: type mismatch %s %s\n",cl->cur->cur_tokendata.linenumber,cl->cur->cur_tokendata.tokenid,cl->cur->cur_tokendata.token);
		}

	}
}


void SA(TREENODE AST,SYHashTable h,LHashTable l,HashTable record)
{
CHILD cl;
cl=AST->head;
LElement e;
LResult r;

//printf("\nSYNTAX ANALYSIS--->%s\n",AST->term);
   
   	
	if(strcmp(AST->term,"<assignmentStmt>")==0)
	{
	
	//assignCheck(cl,cl->next->next,h,l,record);
	assignCheck(AST,h,l,record);
	
	}
	else if(strcmp(AST->term,"<booleanExpression>")==0)
	{
	
	boolCheck(AST,h,l,record);
	
	}

	if(strcmp(AST->term,"<function>")==0)
	{
	
		//printf("\nIN funk\n");
		scope+=1;


		strcpy(fun_name,AST->cur_tokendata.tokenid);


		for(;cl!=NULL;cl=cl->next)
		SA(cl->cur,h,l,record);

	}
	else if(strcmp(AST->term,"<mainFunction>")==0)
	{
	scope+=1;
	//printf("\nIN main\n");
	
	strcpy(fun_name,AST->cur_tokendata.tokenid);
	
		for(;cl!=NULL;cl=cl->next)
		SA(cl->cur,h,l,record);

	}

	
	else
	{
	for(;cl!=NULL;cl=cl->next)
	SA(cl->cur,h,l,record);
	}



}



void syntaxAnalysis(TREENODE AST,SYHashTable h,LHashTable l,HashTable record)
{
scope=0;

SA(AST,h,l,record);

}
