// N.SHASHANK - 2009B5A7585P
// D.ADITYA   - 2009B5A7669P

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"fcntl.h"
//#include"stack.h"
#include"parseDef.h"
#include"lexer.h"
#include"ElementParseTable.h"
#include<string.h>
#include"FirstAndFollow.h"
# define NUM_RULES 96  //need to change 

tokendata copytoken(tokenInfo nexttoken)
	{
	tokendata cur_tokendata;
	strcpy(cur_tokendata.tokenid,nexttoken.tokenid);
	strcpy(cur_tokendata.token,nexttoken.token);
	cur_tokendata.error=nexttoken.error;
	cur_tokendata.linenumber=nexttoken.linenumber;	
	}

void populateTable(struct grammar g,FHashTable h,VHashTable v)
{
VResult r;
FResult f;
int flag=0;
int done=1;
Element e;
RIGHT temp1,temp2;
CHAIN first,follow;
r=findVElement(v,g.left);
if(r.error==-1)
{
insertVElement(v,g.left);
r=findVElement(v,g.left);
}

temp1=g.right;
e.production=g.right;
e.rulenum=g.rulenum;
	while((temp1!=NULL)&&done!=0)
	{
		if(temp1->type==1)
		{
		f=findFElement (h,temp1->right);
			if(strcmp(f.e.first->term,"eps")==0)
			{
			done=1;
			first=f.e.first->next;
			}
			else
			{
			done=0;
			first=f.e.first;
			}
                        while(first!=NULL)
			{
		        strcpy(e.terminal,first->term);
			insertElement (r.e.h,e);
		        first=first->next;
			}

		temp1=temp1->next;

		}
		else 
		{         
			if(strcmp(temp1->right,"eps")==0)
			{done=1;temp1=temp1->next;}
			else
			{
			strcpy(e.terminal,temp1->right);
			insertElement (r.e.h,e);
			done=0;
			}

		}

	}

	if(done==1)
	{
	f=findFElement(h,g.left);
	follow=f.e.follow;
		while(follow!=NULL)
		{
		strcpy(e.terminal,follow->term);
		insertElement (r.e.h,e);
		follow=follow->next;
		}
	done=0;
	}
return ;
}



void createParseTable(char file[],FHashTable h,VHashTable v)
{
int i;
int rule=1;
FILE *fp;
struct grammar g;
char a[100];
RIGHT temp,head;
fp=fopen(file,"r");

for(i=0;i<NUM_RULES;i++,rule++)
	{
	fscanf(fp,"%s ",g.left);
	fscanf(fp,"%s",a);
		if(strcmp(a,"===>")==0)
		{
		fscanf(fp,"%s",a);
		head=(RIGHT)malloc(sizeof(struct rig));
		strcpy(head->right,a);
		        if(a[0]=='<')
		        head->type=1;
		        else 
		        head->type=0;
		head->next=NULL;
		g.right=head;
		g.rulenum=rule;
		
		fscanf(fp,"%s",a);
			while(strcmp(a,";")!=0)
			{
                         
			temp=(RIGHT)malloc(sizeof(struct rig));
			strcpy(temp->right,a);
                        if(a[0]=='<')
                	temp->type=1;
                	else 
                	temp->type=0;

			temp->next=NULL;
			head->next=temp;
                        head=head->next;
                        fscanf(fp,"%s",a);
			}

		}


	populateTable(g,h,v);
        }
return ;
}




TREENODE parseInputSourceCode(char *testcaseFile,VHashTable v,int printflag,int parseflag)
{
LResult r;
LHashTable h;
char *buffer;
char source[128],target[128];
int inhandle,outhandle,loopvar=1;
int  bufsize,err1,err2;
STACK s1,s2;
SNODE temp1,temp2;
tokenInfo nexttoken;
RIGHT prod;
VElement ev;
Element eh;
Result rh;
VResult rv;
HashTable hor;
char xyz[100];
char reverse[100];
int nont;
int flag=1;

TREENODE temptree,parent,tree1,returntree,tree2;
CHILD childlist;
s1=newStack();
s2=newStack();

bufsize=getBufsize();
buffer=malloc(bufsize*sizeof(char));

h=createLookupKeyword();
inhandle=open(testcaseFile,O_RDONLY); //change for giving args as argv[1] from "input.txt"
	if(inhandle==-1)
	{
	puts("cannot open file");
	exit(0);
	}

temptree=(TREENODE)malloc(sizeof(struct treenode));// return TREE is actual parse tree.

strcpy(temptree->term,"<program>");
temptree->head=NULL;
	strcpy(temptree->cur_tokendata.tokenid,"---");
	strcpy(temptree->cur_tokendata.token,"---");
	temptree->cur_tokendata.error=1;
	temptree->cur_tokendata.linenumber=1;	

returntree=temptree;
err1=push(s1,"<program>",temptree);
err1=1;

FILE* fp;
fp=fopen("LexicalOutput.txt","w");
while(loopvar==1&&flag==1)
	{
	nexttoken = getNextToken(buffer,inhandle,h);
	if(printflag==1&&nexttoken.error!=100)
			{
			printf("\ntoken: %s     Lexeme: %s      linenumber: %d",nexttoken.token,nexttoken.tokenid,nexttoken.linenumber);
			//printf("\ntoken: %s     Lexeme: %s",nexttoken.token,nexttoken.tokenid);
			}
        //printf("\ntoken: %s     Lexeme: %s      linenumber: %d",nexttoken.token,nexttoken.tokenid,nexttoken.linenumber);
		if(nexttoken.error<0||nexttoken.error==100)//lexical error
		{
                if(nexttoken.error==-11)
			printf("\nLexical Error ERROR_NO 1:Identifier at line %d is longer than the prescribed length of 20 characters. lexeme: %s\n",nexttoken.linenumber,nexttoken.tokenid);
		else if(nexttoken.error==-2)
			printf("\nLexical Error ERROR_NO 2: Unknown Symbol lexeme: %s at line %d   \n",nexttoken.tokenid,nexttoken.linenumber);
		else if(nexttoken.error==-1)
			printf("\nLexical Error ERROR_NO 3: Unknown pattern lexeme: %s at  line %d   \n",nexttoken.tokenid,nexttoken.linenumber);
		loopvar=0;
		} 
		else if(nexttoken.error==5)
		continue;
		

		

		else if(parseflag==1)
		{
		if(printflag==1)
			{
			//printf("\ntoken: %s     Lexeme: %s",nexttoken.token,nexttoken.tokenid);
			}
		nont=1;
		while(err1==1&&nont==1)
		{
		parent=pop(s1,xyz);
                  if(parent==NULL)
                  break;
			if(strcmp(xyz,"eps")==0)
			{
			continue;
			}


			if(xyz[0]=='<')
			{

			rv=findVElement(v,xyz);
			hor=rv.e.h;
			rh=findElement(hor,nexttoken.token);
			if(rh.error==-1)printf("\n\nFIND ERROR-->%s %s\n\n",nexttoken.token,xyz);
			//printf("\nRulenum: %d\n",rh.e.rulenum);
			prod=rh.e.production;

				
				temptree=(TREENODE)malloc(sizeof(struct treenode));
				
				strcpy(temptree->term,prod->right);
                                temptree->head=NULL;
                                temptree->rulenumused=rh.e.rulenum;// error prone
                                temptree->cur_tokendata = copytoken(nexttoken); // added for parser print specs
                                
                                parent->head=(CHILD)malloc(sizeof(struct child));
				parent->head->cur=temptree;  
				parent->head->next=NULL;

                                childlist=parent->head;
                                err2=push(s2,prod->right,temptree);
				prod=prod->next;

				while(prod!=NULL)
				{
				tree2=(TREENODE)malloc(sizeof(struct treenode));
				strcpy(tree2->term,prod->right);
				tree2->cur_tokendata = copytoken(nexttoken);
				tree2->rulenumused=rh.e.rulenum;
                                tree2->head=NULL;
				childlist->next=(CHILD)malloc(sizeof(struct child));
				childlist->next->cur=tree2;
				childlist->next->next=NULL;
				err2=push(s2,prod->right,tree2);
				prod=prod->next;
                                childlist=childlist->next;
                                 
				}

				while(isEmpty(s2)>0)
				{
				
				tree1=pop(s2,reverse);
				err2=push(s1,reverse,tree1);

				}

			}
			else
			{
                        nont=0;
		                if(strcmp(xyz,nexttoken.token)==0)
		                	{
		                	parent->cur_tokendata = copytoken(nexttoken);
		                	continue;
		                	}
		                else
				         {
					err1=1;
				        flag=0;
					printf("\n\nparsing error token: %s not matching top of stack: %s \nline %d rulenum= %d\n",nexttoken.token,xyz,nexttoken.linenumber,rh.e.rulenum);
					break;
				          }
 			}
		}
		}
}
close(inhandle);
close(fp);
return (returntree);
}




void DFS(TREENODE tr,char *term,FILE *fp)
{

CHILD cl;

cl=tr->head;
	if(cl==NULL)
	{
	//fprintf(fp," | %s, %s, %d %s LeafNode: yes |\n  ",tr->term,tr->cur_tokendata.tokenid,tr->cur_tokendata.linenumber,term);
	//printf(" | %s |\n  ",tr->term);
	if(tr->term[0]!='<')
			{
			fprintf(fp," | %s, %s, %s LeafNode: Yes |\n  ",tr->term,tr->cur_tokendata.tokenid,term);
	  		}//printf(" | %s |\n  ",tr->term);
		else
			{
			fprintf(fp," | %s, ------------ %s LeafNode: Yes |\n  ",tr->term,term);
			}
	}
	else
		{
		//fprintf(fp," | %s, %s, %d %s LeafNode: No |\n  ",tr->term,tr->cur_tokendata.tokenid,tr->cur_tokendata.linenumber,term);
		if(tr->term[0]!='<')
			{
			fprintf(fp," | %s, %s, %s LeafNode: No |\n  ",tr->term,tr->cur_tokendata.tokenid,term);
	  		}//printf(" | %s |\n  ",tr->term);
		else
			{
			fprintf(fp," | %s, ------------ %s LeafNode: No |\n  ",tr->term,term);
			}		
		}
for(;cl!=NULL;cl=cl->next)
DFS(cl->cur,tr->term,fp);

}

void printParseTree(TREENODE tr,char file[])
{

char dfsinput[100];
FILE *fp;
fp=fopen(file,"w");
	fprintf(fp,"\n\nParse Tree\n\n");
	strcpy(dfsinput,"TK_PROGRAM");
	DFS(tr,dfsinput,fp);
fclose(fp);	
}

//AST STARTS HERE


void ASTgrammarTable(char file[],GRAMMAR g)
{
int i;
int rule=1;
FILE *fp;
//Grammar g[NUM_RULES];
char a[100];
RIGHT temp,head;
fp=fopen(file,"r");

for(i=0;i<NUM_RULES;i++,rule++)
	{
	fscanf(fp,"%s ",g[i].left);
	fscanf(fp,"%s",a);
		if(strcmp(a,"===>")==0)
		{
		fscanf(fp,"%s",a);
		head=(RIGHT)malloc(sizeof(struct rig));
		strcpy(head->right,a);
		        if(a[0]=='<')
		        head->type=1;
		        else 
		        head->type=0;
		head->next=NULL;
		g[i].right=head;
		g[i].rulenum=rule;
		
		fscanf(fp,"%s",a);
			while(strcmp(a,";")!=0)
			{
                         
			temp=(RIGHT)malloc(sizeof(struct rig));
			strcpy(temp->right,a);
                        if(a[0]=='<')
                	temp->type=1;
                	else 
                	temp->type=0;

			temp->next=NULL;
			head->next=temp;
                        head=head->next;
                        fscanf(fp,"%s",a);
			}

		}

        }
return ;
}


void generateAST(TREENODE PT,TREENODE AST,GRAMMAR g)
{
RIGHT prod;
CHILD cpt,cast;
TREENODE tree2;
strcpy(AST->cur_tokendata.tokenid,PT->cur_tokendata.tokenid);
//printf("%s---%s--1---%s--%s--%d---%d\n",PT->cur_tokendata.tokenid,PT->term,AST->cur_tokendata.tokenid,AST->term,AST->rulenumused,PT->rulenumused);
if(PT->head!=NULL)
{
prod=g[PT->head->cur->rulenumused-1].right;

cpt=PT->head;

AST->head=(CHILD)malloc(sizeof(struct child));
cast=AST->head;

tree2=(TREENODE)malloc(sizeof(struct treenode));
strcpy(tree2->term,prod->right);
tree2->head=NULL;
tree2->rulenumused=PT->head->cur->rulenumused;// error prone
tree2->cur_tokendata =cpt->cur->cur_tokendata; // added for parser print specs
AST->head=(CHILD)malloc(sizeof(struct child));
AST->head->cur=tree2;  
AST->head->next=NULL;
cast=AST->head;                               
prod=prod->next;
//printf("%s---%s--2\n",PT->cur_tokendata.tokenid,PT->term);


	while(prod!=NULL)
	{


		tree2=(TREENODE)malloc(sizeof(struct treenode));
		strcpy(tree2->term,prod->right);
		tree2->cur_tokendata =cpt->cur->cur_tokendata;
		tree2->rulenumused=PT->head->cur->rulenumused;
                tree2->head=NULL;
		cast->next=(CHILD)malloc(sizeof(struct child));
		cast->next->cur=tree2;
		cast->next->next=NULL;
                prod=prod->next;
                cast=cast->next;
                //printf("%s---%s--3\n",PT->cur_tokendata.tokenid,PT->term);

	}


cast=AST->head;
	for(;cast!=NULL;cast=cast->next)
	{
	        for(;cpt!=NULL;cpt=cpt->next)
		{
                if(strcmp(cpt->cur->term,cast->cur->term)==0)//&&cpt->cur->term[0]=='<'
		{
                //printf("\ncpt->cur->term=%s\n",cpt->cur->term);
		generateAST(cpt->cur,cast->cur,g);
		break;
		}
		}
	
	}
}
return;
}

void pullingupAST(TREENODE AST)
{
CHILD cl,ccl;

if(AST!=NULL)
{
cl=AST->head;
	for(;cl!=NULL;cl=cl->next)
	{
         ccl=cl->cur->head;
         if(ccl!=NULL&&ccl->next==NULL)
         {
        
	cl->cur=ccl->cur;
         
	}
}
              cl=AST->head;
	
		for(;cl!=NULL;cl=cl->next)
		pullingupAST(cl->cur);

	
}
return ;
}

void deletingeps(TREENODE AST)
{
CHILD cl,ccl;

if(AST!=NULL)
{
cl=AST->head;
	if(cl!=NULL&&cl->next!=NULL)
	{
	ccl=NULL;
		for(;cl!=NULL;cl=cl->next)
		{
			if(strcmp(cl->cur->term,"eps")==0)
			{
				if(ccl!=NULL)
                                {
				ccl->next=cl->next;                                
                               
                                }
                                else
                                {
                                AST->head=cl->next;
				
                                }

		
			}
		 ccl=cl;
		}
	}

		cl=AST->head;
	
		for(;cl!=NULL;cl=cl->next)
		deletingeps(cl->cur);
}
return ;
}


TREENODE createAbstractSyntaxtree(TREENODE parsetree)
{
GRAMMAR g;
TREENODE abstracttree;
RIGHT r;
int i;
g=(GRAMMAR)malloc(NUM_RULES*sizeof(Grammar));

ASTgrammarTable("AST_rules.txt",g);
abstracttree=(TREENODE)malloc(sizeof(struct treenode));

	strcpy(abstracttree->term,"<program>");
	abstracttree->head=NULL;
	strcpy(abstracttree->cur_tokendata.tokenid,"------");
	strcpy(abstracttree->cur_tokendata.token,"------");
	abstracttree->cur_tokendata.error=1;
	abstracttree->cur_tokendata.linenumber=1;	

generateAST(parsetree,abstracttree,g);
pullingupAST(abstracttree);
deletingeps(abstracttree);
pullingupAST(abstracttree);
return abstracttree;


}

void DFS_AST(TREENODE tr,char *term,FILE *fp,int *mem)
{

CHILD cl;

cl=tr->head;
	if(cl==NULL)
	{
		if(tr->term[0]!='<')
			{
			fprintf(fp," | %s, %s, %s LeafNode: Yes |\n  ",tr->term,tr->cur_tokendata.tokenid,term);
	  		}//printf(" | %s |\n  ",tr->term);
		else
			{
			fprintf(fp," | %s, ------------ %s LeafNode: Yes |\n  ",tr->term,term);
			}
        *mem=*mem+sizeof(tr->cur_tokendata)+sizeof(tr->term)+sizeof(int);
	}
	else
	{
		if(tr->term[0]!='<')
			{
			fprintf(fp," | %s, %s, %s LeafNode: No |\n  ",tr->term,tr->cur_tokendata.tokenid,term);
	  		}//printf(" | %s |\n  ",tr->term);
		else
			{
			fprintf(fp," | %s, ------------ %s LeafNode: No |\n  ",tr->term,term);
			}
		//fprintf(fp," | %s, %s, %d %s LeafNode: No |\n  ",tr->term,tr->cur_tokendata.tokenid,tr->cur_tokendata.linenumber,term);
                *mem=*mem+sizeof(tr->cur_tokendata)+sizeof(tr->term)+sizeof(int);
	}
for(;cl!=NULL;cl=cl->next)
DFS_AST(cl->cur,tr->term,fp,mem);

}



void printAST(TREENODE tr, char *file)
{

char dfsinput[100];
FILE *fp;
int mem;
mem=0;
fp=fopen(file,"w");
	fprintf(fp,"\n\nABSTRACT SYNTAX TREE\n\n");
	strcpy(dfsinput,"TK_PROGRAM");
	DFS_AST(tr,dfsinput,fp,&mem);
	fprintf(fp,"\n\nMemory Occupied = %d bytes\n\n",mem);
fclose(fp);


}


