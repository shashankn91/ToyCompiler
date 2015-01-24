

#include<stdlib.h>
#include<stdio.h>
#include"lexerDef.h"
#include<string.h>

// N.SHASHANK - 2009B5A7585P
// D.ADITYA   - 2009B5A7669P


int Lhash (char s[], int size)
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



LHashTable createLHashTable (int size)
{
int i;
LHashTable h;
LBucket *b;

h=(LHashTable)malloc(sizeof(struct LhashTable));
h->size=0;
h->buckets=NULL;

b=(LBucket *)malloc(size*(sizeof(LBucket)));
	for(i=0;i<size;i++)
	{
		b[i].elements.head=NULL;
		b[i].elements.size=0;
		
	}
h->size=size;
h->buckets=b;
return h;

}


void insertLElement (LHashTable h, LElement e)
{
int x;
LBucket *b;
LNODE temp;
x=Lhash(e.keyword,h->size);
b=h->buckets;
temp=(struct Lnode *)malloc(sizeof(struct Lnode));
temp->e=e;
temp->link=b[x].elements.head;
b[x].elements.head=temp;
b[x].elements.size++;

return ;
}

LResult findLElement (LHashTable h, char keyword[])
{
int x,i;
LBucket *b;
LNODE temp;
LResult ans;
x=Lhash(keyword,h->size);
b=h->buckets;
temp=b[x].elements.head;
	for(i=0;i<b[x].elements.size;i++)
	{

		if(strcmp(temp->e.keyword,keyword)==0)
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



