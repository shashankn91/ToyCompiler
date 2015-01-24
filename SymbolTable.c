


// N.SHASHANK - 2009B5A7585P
// D.ADITYA   - 2009B5A7669P


#include<stdio.h>
#include<stdlib.h>
#include"SymbolTable.h"
//#include"symbol.h"
#include<string.h>

int scope;
char fun_name[100];
int offset;
char parameters[100];
int flag;


void rec(TREENODE AST,HashTable record)
{
TREENODE new;
int offset1=0;
int non2=1;
Element e;
CHILD cl,cl1;
RIGHT temp,head,head1;
cl=AST->head;

strcpy(e.terminal,cl->cur->cur_tokendata.tokenid);

cl=cl->next->cur->head;
cl1=cl->next;

cl=cl->cur->head;
//printf("type=%s  term=%s\n",cl->cur->term,cl->next->cur->cur_tokendata.tokenid);
head=(RIGHT)malloc(sizeof(struct rig));
strcpy(head->right,cl->next->cur->cur_tokendata.tokenid);




	if(strcmp(cl->cur->term,"TK_REAL")==0)
	{
		head->type=2;
		offset1+=4;
	}
	else if(strcmp(cl->cur->term,"TK_INT")==0)
	{	
		head->type=1;
		offset1+=2;
	}
	
head->next=NULL;
head1=head;


//printf("head1-->%s\n",head->right);
if((cl1!=NULL))
{

if(strcmp(cl1->cur->term,"<fieldDefinition>")==0)
{
non2=0;
cl=cl1->cur->head;

	temp=(RIGHT)malloc(sizeof(struct rig));
	
	strcpy(temp->right,cl->next->cur->cur_tokendata.tokenid);
	
		if(strcmp(cl->cur->term,"TK_REAL")==0)
		{
			temp->type=2;
			offset1+=4;
		}
		else if(strcmp(cl->cur->term,"TK_INT")==0)
		{
			temp->type=1;
			offset1+=2;
		}
	temp->next=NULL;
	head->next=temp;
	head=temp;

}
}
	while(cl1!=NULL&&non2==1)
	{
	
	cl=cl1->cur->head;
	cl1=cl->next;

	cl=cl->cur->head;
	temp=(RIGHT)malloc(sizeof(struct rig));
	
	strcpy(temp->right,cl->next->cur->cur_tokendata.tokenid);
	
		if(strcmp(cl->cur->term,"TK_REAL")==0)
		{
			temp->type=2;
			offset1+=4;
		}
		else if(strcmp(cl->cur->term,"TK_INT")==0)
		{
			temp->type=1;
			offset1+=2;
		}
	temp->next=NULL;
	head->next=temp;
	head=temp;
	
		
	

	//printf("type=%s  term=%s \n",cl->cur->term,cl->next->cur->cur_tokendata.tokenid);
	//printf("head-->%s\n",head->right);
		
		
	if(cl1!=NULL)
	{
		if(strcmp(cl1->cur->term,"<moreFields>")==0)
		{
			continue;
		}

		else if(strcmp(cl1->cur->term,"<fieldDefinition>")==0) 
		{
			cl1=cl1->cur->head;
			temp=(RIGHT)malloc(sizeof(struct rig));
			strcpy(temp->right,cl1->next->cur->cur_tokendata.tokenid);
	
			if(strcmp(cl1->cur->term,"TK_REAL")==0)
			{
				temp->type=2;
				offset1+=4;
			}
			else if(strcmp(cl1->cur->term,"TK_INT")==0)
			{	
				temp->type=1;
				offset1+=2;
			}
			temp->next=NULL;
			head->next=temp;
			head=head->next;

			//printf("type=%s  term=%s \n",cl1->cur->term,cl1->next->cur->cur_tokendata.tokenid);
			//printf("head-->%s\n",head->right);
			break;

		}
	
	}
	
	else
	break;
		
		
	}
	
	
        e.production=head1;
        e.rulenum=offset1;
        /*
        printf("\n");
        while(head1!=NULL)
        {
        printf("%s\t",head1->right);
        head1=head1->next;
        }
        printf("\n");
        */
       insertElement (record,e);


}



void funct(TREENODE AST,SYHashTable h,HashTable record)
{
CHILD cl,cl1;
cl=AST->head;
SYElement e;
SYResult r;
Result rec;
FILE *fp;
char new[100];
int i;
RIGHT rig;
int rflagr=0;
fp=fopen("SymbolTable.txt","a");
strcpy(new,"");

strcpy(e.name,cl->next->cur->cur_tokendata.tokenid);
//printf("\n\n||||%s-- %s--%s||||",cl->next->cur->cur_tokendata.tokenid,cl->next->cur->cur_tokendata.token,cl->next->cur->term);
strcpy(e.funname,fun_name);
strcpy(e.type,cl->cur->cur_tokendata.tokenid);

	if(strcmp(cl->cur->term,"<constructedDatatype>")==0)
	{
	cl1=cl->cur->head;
	strcpy(e.type,cl1->next->cur->cur_tokendata.tokenid);
	}


	if(flag==1)
	{
		strcat(parameters,e.type);
		strcat(parameters," ");
	}


	
e.offset=offset;

	if(cl->next->next==NULL)
		e.scope=scope;
	else 
	{
	
	//printf("\ncl->next->next=%s\n",cl->next->next->cur->term);
			
		if(strcmp(cl->next->next->cur->term,"TK_GLOBAL")==0)
		e.scope=0;
		else
		e.scope=scope;
	}

r=findSYElement(h,e.name,scope);


	if(r.error==0)
	{
		printf("ERROR in Line %d: variable %s already in use \n",cl->next->cur->cur_tokendata.linenumber,e.name);
		return ;
	}
	else
	{
		r=findSYElement(h,e.name,0);
		if(r.error==0)
		{
			printf("ERROR in Line %d: variable %s declared is a global variable\n",cl->next->cur->cur_tokendata.linenumber,e.name);
			return ;
		}
		else
		{
		if(e.scope!=0)
		{
			if(strcmp(cl->cur->term,"TK_INT")==0)
			{
				offset+=2;

			}
			else if(strcmp(cl->cur->term,"TK_REAL")==0)
				offset+=4;
			else
			{
			     rec=findElement (record,e.type);
			     if(rec.error==-1)
			     {
			     printf("ERROR in Line %d: Using record without defining\n",cl->next->cur->cur_tokendata.linenumber,e.name);
			     
			     }
			     else
			     {
			     offset+=rec.e.rulenum;
			     rig=rec.e.production;
			     while(rig!=NULL)
			     {
			     if(rig->type==1)
			     strcat(new,"int");
			     else if(rig->type==2)
			     strcat(new,"real");
			     strcat(new,"x");
			     rig=rig->next;
			     }
			     //strcpy(e.type,new);
			     rflagr=1;
			     }
			     
			
			}
		
		}
		else
		e.offset=-1;	
			insertSYElement(h,e);
			if(e.scope!=0)
			{
			if(rflagr==0)
			fprintf(fp,"%20s %20s %20s %20d\n",e.name,e.type,e.funname,e.offset);
			else
			fprintf(fp,"%20s %20s %20s %20d\n",e.name,new,e.funname,e.offset);
			}
			else
			{
			if(rflagr==0)
			fprintf(fp,"%20s %20s %20s %20s\n",e.name,e.type,"global","-");
			else
			fprintf(fp,"%20s %20s %20s %20s\n",e.name,new,"global","-");
			for(i=1;i<=scope;i++)
			{
			r=findSYElement(h,e.name,i);
			if(r.error==0)
			printf("ERROR in Line %d: variable %s cannot be declared twice as it is global variable\n",cl->next->cur->cur_tokendata.linenumber,e.name);
			}
			}
		}
	}
	fclose(fp);
}


void GLPS(TREENODE AST,char *a,SYHashTable h)
{
SYResult r,r1;
CHILD cl;
cl=AST->head;
	if(strcmp(AST->term,"TK_ID")==0)
	{
	
	//if(AST->)
	r=findSYElement(h,AST->cur_tokendata.tokenid,scope);
	r1=findSYElement(h,AST->cur_tokendata.tokenid,0);
   
			if(r.error==0||r1.error==0)
			{
			if(r.error==0)
			{
			//if(strcmp(r.e.type,"int")==0||strcmp(r.e.type,"real")==0)
			strcat(a,r.e.type);
			//else
			//printf("\n\ncaught %s\n\n",AST->cur_tokendata.tokenid);
			}
			else
			{
			//if(strcmp(r.e.type,"int")==0||strcmp(r.e.type,"real")==0)
			strcat(a,r1.e.type);
			}
			strcat(a," ");
			

			}
	}
	else if(strcmp(AST->term,"TK_NUM")==0)
	{
	strcat(a,"int ");

	}
	else if(strcmp(AST->term,"TK_RNUM")==0)
	{
	strcat(a,"real ");
	}
	
	for(;cl!=NULL;cl=cl->next)
		GLPS(cl->cur,a,h);
	
}



void funCallStmt(TREENODE AST,LHashTable l,SYHashTable h)
{
CHILD cl;
cl=AST->head;
LElement e;
LResult r;
int cflag=0;
char checkfun[256];
strcpy(checkfun,"0 ");



if(strcmp(cl->cur->term,"TK_FUNID")==0)
{
r=findLElement(l,cl->cur->cur_tokendata.tokenid);
cflag=1;
GLPS(cl->next->cur,checkfun,h);
}
else
{
r=findLElement(l,cl->next->cur->cur_tokendata.tokenid);
GLPS(cl->next->next->cur,checkfun,h);
strcat(checkfun,"1 ");
GLPS(cl->cur,checkfun,h);

}




if(r.error==0)
{
//	printf("\ncaluclated-->%s \noriginal-->%s \n\n%s\n\n",checkfun,r.e.keywordToken,cl->next->cur->cur_tokendata.tokenid);

if(strcmp(checkfun,r.e.keywordToken)!=0)
printf("ERROR in Line %d: function definition is not matching\n",cl->cur->cur_tokendata.linenumber);

if(strcmp(fun_name,r.e.keyword)==0)
printf("ERROR in Line %d: function %s is called recursively\n",cl->cur->cur_tokendata.linenumber,fun_name);
}
else
{
printf("ERROR in Line %d: function %s has not been defined earlier\n",cl->cur->cur_tokendata.linenumber,fun_name);
}

}



void tdef(TREENODE AST,SYHashTable h,LHashTable l,HashTable record)
{
CHILD cl;
cl=AST->head;
LElement e;
LResult r;
if(strcmp(AST->term,"<typeDefinition>")==0)
{
		rec(AST,record);
}

else
{
for(;cl!=NULL;cl=cl->next)
tdef(cl->cur,h,l,record);

}


}


void CST(TREENODE AST,SYHashTable h,LHashTable l,HashTable record)
{
CHILD cl;
cl=AST->head;
LElement e;
LResult r;
   
   	flag=0;

	if(strcmp(AST->term,"<function>")==0)
	{
	
		offset=0;
		scope+=1;
	 
		//printf("\nEntered function\n");

		strcpy(fun_name,cl->cur->cur_tokendata.tokenid);
		
		r=findLElement(l,cl->cur->cur_tokendata.tokenid);
		if(r.error==-1)
			strcpy(parameters,"0 ");
		else
			printf("ERROR in Line %d: Function name %s already in use\n",cl->cur->cur_tokendata.linenumber,cl->cur->cur_tokendata.tokenid);
			



		for(;cl!=NULL;cl=cl->next)
			CST(cl->cur,h,l,record);

	}
	else if(strcmp(AST->term,"TK_MAIN")==0)
	{
	scope+=1;
	offset=0;
	strcpy(fun_name,AST->cur_tokendata.tokenid);
	
	r=findLElement(l,fun_name);
	

		if(r.error==-1)
		{	
		
			strcpy(parameters,"0 ");
		}
		else
			printf("ERROR in Line %d:Already there is a main function in use\n",AST->cur_tokendata.linenumber);


		for(;cl!=NULL;cl=cl->next)
			CST(cl->cur,h,l,record);

	}

	else if(strcmp(AST->term,"<parameter_list>")==0)
	{
	        flag=1;
		funct(AST,h,record);
		for(;cl!=NULL;cl=cl->next)
			CST(cl->cur,h,l,record);
		
	}
	else if(strcmp(AST->term,"<remaining_list>")==0)
	{
	        flag=1;
		funct(AST,h,record);
		
	}
	

	else if(strcmp(AST->term,"<declaration>")==0)
	{

		funct(AST,h,record);
		

		
	}
/*	else if(strcmp(AST->term,"<typeDefinition>")==0)
	{
		rec(AST,record);
	}*/
	else if(strcmp(AST->term,"<funCallStmt>")==0)
	{
		funCallStmt(AST,l,h);
	}


	
	else
	{
		if(strcmp(AST->term,"TK_OUTPUT")==0)
			strcat(parameters,"1 ");
		else if(strcmp(AST->term,"<stmts>")==0)
			{
			strcpy(e.keyword,fun_name);
			strcpy(e.keywordToken,parameters);
			insertLElement (l,e);
			}
		
		
		for(;cl!=NULL;cl=cl->next)
			CST(cl->cur,h,l,record);
	}

}



void symboltable(TREENODE ast,SYHashTable h,LHashTable l,HashTable record)
{
FILE *fp;
fp=fopen("SymbolTable.txt","w");
//fprintf(fp,"\n%50s\n","Symbol Table");
fprintf(fp,"\n\n%20s %20s %20s %20s\n\n","Lexeme","Type","Scope","Offset");
fclose(fp);

scope=0;
tdef(ast,h,l,record);
CST(ast,h,l,record);
}
