
#include"FirstAndFollow.h"
#include<stdlib.h>
#include<string.h>
#include<stdio.h>
// N.SHASHANK - 2009B5A7585P
// D.ADITYA   - 2009B5A7669P


 int Fhash (char s[], int size)
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


 void insertFElement (FHashTable h,FElement e)
{
int x;
FBucket *b;
FNODE temp;

x=Fhash(e.term,h->size);
b=h->buckets;
temp=(struct Fnode *)malloc(sizeof(struct Fnode));
temp->e=e;
temp->link=b[x].elements.head;
b[x].elements.head=temp;
b[x].elements.size++;



return ;

}

 FHashTable createFirstFollow (int size,char *file)
{
int i,x;
FILE *fp;
FHashTable h;
FBucket *b;
fp=fopen(file,"r");
h=(FHashTable)malloc(sizeof(struct FhashTable));
h->size=0;
h->buckets=NULL;

b=(FBucket *)malloc(2*size*(sizeof(FBucket)));
	for(i=0;i<size;i++)

	{
		b[i].elements.head=NULL;
		b[i].elements.size=0;
		
	}
h->size=2*size;
h->buckets=b;
char a[200];
FElement e;
CHAIN head,cur,temp;
	for(i=0;i<size;i++)
	{
	fscanf(fp,"%s",a);

		if(strcmp(a,"term")==0)
		{
		fscanf(fp,"%s",a);
		strcpy(e.term,a);
		fscanf(fp,"%s",a);
                
			if(strcmp(a,"first")==0)
			{
                        head=(CHAIN)malloc(sizeof(struct chain));
                        fscanf(fp,"%s",a);
                        strcpy(head->term,a);
			head->next=NULL;
			e.first=head;
                        cur=head;
                                fscanf(fp,"%s",a);
                        
				while(strcmp(a,"follow")!=0)
				{
				
				temp=(CHAIN)malloc(sizeof(struct chain));
		                strcpy(temp->term,a);
				temp->next=NULL;
		                cur->next=temp;
                                cur=cur->next;
				fscanf(fp,"%s",a);
		                
				}


			head=(CHAIN)malloc(sizeof(struct chain));
                        fscanf(fp,"%s",a);
                        strcpy(head->term,a);
			head->next=NULL;
			e.follow=head;
                        cur=head;
                                 fscanf(fp,"%s",a);
				while(strcmp(a,"term")!=0)
				{
				
				temp=(CHAIN)malloc(sizeof(struct chain));
		                strcpy(temp->term,a);
				temp->next=NULL;
		                cur->next=temp;
                                cur=cur->next;
		                fscanf(fp,"%s",a);
				}
                              fseek(fp,-4,SEEK_CUR);
	


		}
	}




                         insertFElement (h,e);

			}

	
return h;
}



 FResult findFElement (FHashTable h, char term[])
{
int x,i;
FBucket *b;
FNODE temp;
FResult ans;
x=Fhash(term,h->size);
b=h->buckets;
temp=b[x].elements.head;
	for(i=0;i<b[x].elements.size;i++)
	{

		if(strcmp(temp->e.term,term)==0)
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



















