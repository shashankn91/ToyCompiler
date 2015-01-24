// N.SHASHANK - 2009B5A7585P
// D.ADITYA   - 2009B5A7669P

#include<stdlib.h>
#include<stdio.h>
#include"SymbolTable.h"
#include<string.h>



int SYhash (char s[], int size)
{
long unsigned int sum = 0;
  int i;
int a=41;
if(s[0] == '\0')
return -1;
sum=a*s[0];

  for (i = 1; s[i] != '\0'; i++)
    {
      sum = sum + toascii (s[i]);
	sum=sum*a;
    }
  return sum % size;
}



SYHashTable createSYHashTable (int size)
{
int i;
SYHashTable h;
SYBucket *b;

h=(SYHashTable)malloc(sizeof(struct SYhashTable));
h->size=0;
h->buckets=NULL;

b=(SYBucket *)malloc(size*(sizeof(SYBucket)));
	for(i=0;i<size;i++)

	{
		b[i].elements.head=NULL;
	}
h->size=size;
h->buckets=b;
return h;

}


void insertSYElement (SYHashTable h, SYElement e)
{
int x;
SYBucket *b;
SYNODE temp;
x=SYhash(e.name,h->size);
b=h->buckets;
temp=(struct SYnode *)malloc(sizeof(struct SYnode));
temp->e=e;
temp->link=b[x].elements.head;
b[x].elements.head=temp;
b[x].elements.size++;
return ;
}

SYResult findSYElement (SYHashTable h, char name[],int scope)
{
int x,i;
SYBucket *b;
SYNODE temp;
SYResult ans;
x=SYhash(name,h->size);

b=h->buckets;
temp=b[x].elements.head;
	for(i=0;i<b[x].elements.size;i++)
	{

		if((strcmp(temp->e.name,name)==0)&&temp->e.scope==scope)
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


