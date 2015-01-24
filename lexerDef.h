

//#include "Element.h"
//#include"tokenInfo.h"

#define MAX_keyword 100
#define MAX_keywordToken 256

// N.SHASHANK - 2009B5A7585P
// D.ADITYA   - 2009B5A7669P
typedef struct{ 
char keyword[MAX_keyword];
 char keywordToken[MAX_keywordToken];
} LElement;

typedef struct{
LElement e;
int error; 
} LResult;

typedef struct{
char tokenid[100];
char token[20];
int error;
int linenumber;
} tokenInfo;

typedef struct Lnode *LNODE;
struct Lnode
{
  LElement e;
  LNODE link;
};
struct Llistinfo
{
  LNODE head;
  int size;
};
typedef struct Llistinfo LLIST;
typedef struct
{
  LLIST elements;
 
} LBucket;

struct LhashTable
{
  LBucket *buckets;
  int size;
};

typedef struct LhashTable *LHashTable;

extern int Lhash (char s[], int size);
extern LHashTable createLHashTable (int size);
extern void insertLElement (LHashTable h, LElement e);
extern LResult findLElement (LHashTable h, char keyword[]);


