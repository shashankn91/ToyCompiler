// N.SHASHANK - 2009B5A7585P
// D.ADITYA   - 2009B5A7669P

#include<stdlib.h>
#include<stdio.h>
#include"Parse_hashing.h"
#include<string.h>



int hash (char s[], int size)
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



HashTable createHashTable (int size)
{
int i;
HashTable h;
Bucket *b;

h=(HashTable)malloc(sizeof(struct hashTable));
h->size=0;
h->buckets=NULL;

b=(Bucket *)malloc(size*(sizeof(Bucket)));
	for(i=0;i<size;i++)

	{
		b[i].elements.head=NULL;
	}
h->size=size;
h->buckets=b;
return h;

}


void insertElement (HashTable h, Element e)
{
int x;
Bucket *b;
NODE temp;
RIGHT temp1;
x=hash(e.terminal,h->size);
b=h->buckets;
temp=(struct node *)malloc(sizeof(struct node));
temp->e=e;
temp->link=b[x].elements.head;
b[x].elements.head=temp;
b[x].elements.size++;
return ;
}

Result findElement (HashTable h, char terminal[])
{
int x,i;
Bucket *b;
NODE temp;
Result ans;
x=hash(terminal,h->size);

b=h->buckets;
temp=b[x].elements.head;
	for(i=0;i<b[x].elements.size;i++)
	{

		if(strcmp(temp->e.terminal,terminal)==0)
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


