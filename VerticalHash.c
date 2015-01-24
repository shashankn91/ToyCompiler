// N.SHASHANK - 2009B5A7585P
// D.ADITYA   - 2009B5A7669P

#include<stdlib.h>
#include<stdio.h>
#include"ElementParseTable.h"
#include<string.h>
#define MAX_FIRST 100

VHashTable createVHashTable (int size)
{
int i;
VHashTable h;
VBucket *b;

h=(VHashTable)malloc(sizeof(struct VhashTable));
h->size=0;
h->buckets=NULL;

b=(VBucket *)malloc(size*(sizeof(VBucket)));
	for(i=0;i<size;i++)
		b[i].elements.head=NULL;
	
h->size=size;
h->buckets=b;
return h;

}


void insertVElement (VHashTable h, char nonterminal[])
{
int x;
VBucket *b;
VNODE temp;
HashTable newh;
VElement e;
x=hash(nonterminal,h->size);
newh=createHashTable (MAX_FIRST);
strcpy(e.nonterminal,nonterminal);
e.h=newh;

b=h->buckets;
temp=(struct Vnode *)malloc(sizeof(struct Vnode));
temp->e=e;
temp->link=b[x].elements.head;
b[x].elements.head=temp;
b[x].elements.size++;
return ;
}

VResult findVElement (VHashTable h, char nonterminal[])
{
int x,i;
VBucket *b;
VNODE temp;
VResult ans;
x=hash(nonterminal,h->size);
b=h->buckets;
temp=b[x].elements.head;
	for(i=0;i<b[x].elements.size;i++)
	{
		if(strcmp(temp->e.nonterminal,nonterminal)==0)
			{
			
			ans.error=0;
			ans.e=temp->e;
			return (ans);
			}
	temp=temp->link;
	
	}
ans.error=-1;

return (ans);

}


