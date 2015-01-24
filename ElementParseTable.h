
#define MAX_nonterminal 50
#define MAX_production 256
#include"Parse_hashing.h"
// N.SHASHANK - 2009B5A7585P
// D.ADITYA   - 2009B5A7669P

typedef struct{ 
char nonterminal[MAX_nonterminal];
HashTable h;
} VElement;

typedef struct{
VElement e;
int error; 
} VResult;

typedef struct Vnode *VNODE;
struct Vnode
{
  VElement e;
  VNODE link;
};
struct Vlistinfo
{
  VNODE head;
  int size;
};
typedef struct Vlistinfo VLIST;
typedef struct
{
  VLIST elements;
 
} VBucket;

struct VhashTable
{
  VBucket *buckets;
  int size;
};

typedef struct VhashTable *VHashTable;


extern VHashTable createVHashTable (int size);
extern void insertVElement (VHashTable h,char nonterminal[]);
extern VResult findVElement (VHashTable h, char nonterminal[]);


