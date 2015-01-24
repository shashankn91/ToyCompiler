// N.SHASHANK - 2009B5A7585P
// D.ADITYA   - 2009B5A7669P

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"tokenInfo.h" 

typedef struct treenode *TREENODE;
typedef struct child *CHILD;
struct child
{
TREENODE cur;
CHILD next;
};


struct treenode
{
char term[100];
CHILD head;
int rulenumused;
tokendata cur_tokendata; // error coz of this
};


typedef struct snode *SNODE;

struct snode
{
char term[100];
TREENODE node;
SNODE next;
}; 

typedef struct stack *STACK;


struct stack 
{
SNODE top;
int size;
};

extern STACK newStack();
extern int isEmpty(STACK s);
extern int push(STACK s,char term[],TREENODE node);
extern TREENODE pop(STACK s,char term[]);
