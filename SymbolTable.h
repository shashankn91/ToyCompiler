#include<stdio.h>
#include<stdlib.h>
#include"parser.h"

// N.SHASHANK - 2009B5A7585P
// D.ADITYA   - 2009B5A7669P

typedef struct 
{
char name[100];
char funname[100];
char type[100];
int scope;
int offset;
}SYElement;


typedef struct{
SYElement e;
int error; 
} SYResult;

typedef struct SYnode *SYNODE;
struct SYnode
{
  SYElement e;
  SYNODE link;
};
struct SYlistinfo
{
  SYNODE head;
  int size;
};
typedef struct SYlistinfo SYLIST;
typedef struct
{
  SYLIST elements;
  
} SYBucket;

struct SYhashTable
{
  SYBucket *buckets;
  int size;
};

typedef struct SYhashTable *SYHashTable;

extern int SYhash (char s[], int size);
extern SYHashTable createSYHashTable (int size);
extern void insertSYElement (SYHashTable h, SYElement e);
extern SYResult findSYElement (SYHashTable h, char name[],int scope);
extern void symboltable(TREENODE ast,SYHashTable h,LHashTable l,HashTable record);


