

#define MAX_TERM 100

// N.SHASHANK - 2009B5A7585P
// D.ADITYA   - 2009B5A7669P

typedef struct chain *CHAIN;

struct chain{
char term[MAX_TERM];
CHAIN next;
};

typedef struct chain Chain;
typedef struct{ 
char term[MAX_TERM];
CHAIN first;
CHAIN follow;
} FElement;

typedef struct{
FElement e;
int error; 
} FResult;

typedef struct Fnode *FNODE;
struct Fnode
{
  FElement e;
  FNODE link;
};
struct Flistinfo
{
  FNODE head;
  int size;
};
typedef struct Flistinfo FLIST;
typedef struct
{
  FLIST elements;
 
} FBucket;

struct FhashTable
{
  FBucket *buckets;
  int size;
};

typedef struct FhashTable *FHashTable;


extern FHashTable createFirstFollow (int size,char *file);
extern FResult findFElement (FHashTable h, char term[]);


