// N.SHASHANK - 2009B5A7585P
// D.ADITYA   - 2009B5A7669P

//#include"stack.h"
#include"parseDef.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
STACK newStack()
{
STACK s=(STACK)malloc(sizeof(struct stack));
s->top=NULL;
s->size=0;
				
return s;
}



int isEmpty(STACK s)
{
	if(s==NULL)
		return 0;
else
return s->size;

}

int push(STACK s,char term[],TREENODE node)
{

	if(s==NULL)
		return 0;
        		
SNODE e=(SNODE)malloc(sizeof(struct snode));
e->next=NULL;
strcpy(e->term,term);
e->node=node;
	if(s->top==NULL)
		{
		s->top=e;
		s->size=1;
		}

	else
		{
		e->next=s->top;
		s->size++;
		s->top=e;
		}
return 1;
}


TREENODE pop(STACK s,char term[])
{
TREENODE node;
node=(TREENODE)malloc(sizeof(struct treenode));
SNODE e=NULL;
	if(s==NULL)
		return NULL;
		
if(s->top==NULL)
return NULL;


e=s->top;
strcpy(term,e->term);
node=e->node;
strcpy(node->term,e->node->term);
node->head=e->node->head;
s->top=s->top->next;

s->size--;
free(e);
return node;

}

