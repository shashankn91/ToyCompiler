


// N.SHASHANK - 2009B5A7585P
// D.ADITYA   - 2009B5A7669P




#include"codeGeneration.h"
char id[10][100];
char op[10];
int  ind1,ind2;
FILE * fp;
char firt[100];
int copy_flag;
/*
void flush()
{
int i,j;
for(i=0;i<10;i++)
{
memset(id[i], 0, 100);
memset(op[i], 0, 100);
}
}
*/


void ass(TREENODE AST,SYHashTable h)
{

SYResult r,r1;
CHILD cl;
cl=AST->head;
	if(strcmp(AST->term,"TK_ID")==0)
	{
	
		r=findSYElement(h,AST->cur_tokendata.tokenid,1);
	r1=findSYElement(h,AST->cur_tokendata.tokenid,0);
   
			if(r.error==0||r1.error==0)
			{
			if(r.error==0)
			{
			
			//strcpy(id[ind1],r.e.name);
			ind1+=1;
			
			}
			else
			{
			
			//strcpy(id[ind1],r1.e.name);
			ind1+=1;
			}
			
			//printf("\n%s\n",AST->cur_tokendata.tokenid);
			//fprintf(fp,"MOV AX,%s\nPUSH AX\n ",AST->cur_tokendata.tokenid);
			fprintf(fp,"%20s %s\n%20s %s\n ","MOV AX,",AST->cur_tokendata.tokenid,"PUSH","AX");
			if(copy_flag==1)
			{
			strcpy(firt,AST->cur_tokendata.tokenid);
			copy_flag=0;
			}


			}
	}
	else if(strcmp(AST->term,"TK_NUM")==0)
	{
	//strcpy(id[ind1],AST->cur_tokendata.tokenid);
	ind1+=1;
	//printf("\n%s\n",AST->cur_tokendata.tokenid);
	//fprintf(fp,"MOV AX,%s\nPUSH AX\n ",AST->cur_tokendata.tokenid);
	fprintf(fp,"%20s %s\n%20s %s\n ","MOV AX,",AST->cur_tokendata.tokenid,"PUSH","AX");


	}
	else if(strcmp(AST->term,"TK_RNUM")==0)
	{
	//strcpy(id[ind1],AST->cur_tokendata.tokenid);
	ind1+=1;
	//fprintf(fp,"MOV AX,%s\nPUSH AX\n ",AST->cur_tokendata.tokenid);
	fprintf(fp,"%20s %s\n%20s %s\n ","MOV AX,",AST->cur_tokendata.tokenid,"PUSH","AX");

	}
	

	
	
	
	else if(strcmp(AST->term,"TK_ASSIGNOP")==0)
	{
	op[ind2]='=';
	//printf("\n=\n");
	ind2+=1;
	}
	else if(strcmp(AST->term,"TK_DIV")==0)
	{
	op[ind2]='/';
	ind2+=1;
	}
	else if(strcmp(AST->term,"TK_MUL")==0)
	{
	op[ind2]='*';
	ind2+=1;
	}
	else if(strcmp(AST->term,"TK_PLUS")==0)
	{
	op[ind2]='+';
	ind2+=1;
	}
	else if(strcmp(AST->term,"TK_MINUS")==0)
	{
	op[ind2]='-';
	ind2+=1;
	}

	
	
	for(;cl!=NULL;cl=cl->next)
		ass(cl->cur,h);
	


	
}
void operator()
{
int i=0;

for(i=ind2;i>=0;i--)
{

if(op[i]=='+')
{
fprintf(fp,"%20s \n%20s \n ","POP AX","POP BX");
fprintf(fp,"%20s\n%20s\n ","ADD AX,BX","PUSH AX");
}
else if(op[i]=='-')
{
fprintf(fp,"%20s \n%20s \n ","POP AX","POP BX");
fprintf(fp,"%20s\n%20s\n ","SUB AX,BX","PUSH AX");
}
else if(op[i]=='*')
{
fprintf(fp,"%20s \n%20s \n ","POP AX","POP CX");
fprintf(fp,"%20s\n%20s\n ","IMUL CX","PUSH AX");
}
else if(op[i]=='/')
{
fprintf(fp,"%20s \n%20s \n ","POP CX","POP AX");
fprintf(fp,"%20s\n%20s\n ","MOV DX,0","IDIV CX","PUSH AX");

}
else if(op[i]=='=')
fprintf(fp,"%20s\n%20s %s,%s\n ","POP AX","MOV",firt,"AX");



}

}





void CGA(TREENODE AST,SYHashTable h,LHashTable l,HashTable record)
{
CHILD cl;
cl=AST->head;
LElement e;
LResult r;
int i=0;

   
   	
	if(strcmp(AST->term,"<assignmentStmt>")==0)
	{
	        //flush();
	        for(i=0;i<10;i++)
	        {
	        op[i]='a';
	        }
	        ind2=0;
	        copy_flag=1;
	        
		ass(AST,h);
		operator();
		//printf("\n\n%s\n\n",op);
		
	
	}
	

	
	
	else
	{
	for(;cl!=NULL;cl=cl->next)
	CGA(cl->cur,h,l,record);
	}



}


void codeGen(TREENODE AST,SYHashTable h,LHashTable l,HashTable record,char * filename)
{
//printf("\n\n Inside Code Gen\n\n");

fp=fopen(filename,"w");//modified 18th 5pm "codegen.txt","w"
fprintf(fp,".MODEL SMALL\n.DATA\n");
int loopvar1=0,loopvar2=0;
TREENODE ast_tn;
while(loopvar1<h->size)
	{
	SYNODE cur;
	cur=h->buckets[loopvar1].elements.head;
	//printf("in while h->buckets->elements.size=%d\n",h->buckets[loopvar1].elements.size);
	loopvar2=0;
	while(loopvar2 < h->buckets[loopvar1].elements.size)
		{
		fprintf(fp,"%s DW 0\n",cur->e.name);
		cur=cur->link;
		loopvar2++;
		}
	loopvar1++;
	}
fprintf(fp,".CODE\n.STARTUP\n");
ind1=0;ind2=0;
CGA(AST,h,l,record);



fprintf(fp,".EXIT\nEND\n");

//code gen
fclose(fp);
//for(i)

}


