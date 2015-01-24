// N.SHASHANK - 2009B5A7585P
// D.ADITYA   - 2009B5A7669P

#define MAX_terminal 70
#define MAX_production 256

typedef struct rig *RIGHT;
struct rig
{
char right[100];
int type;
RIGHT next;
};

struct grammar
{
char left[100];
RIGHT right;
int rulenum;
};

typedef struct grammar Grammar;
typedef struct grammar *GRAMMAR;

typedef struct{ 
char terminal[MAX_terminal];
RIGHT production;
int rulenum;
} Element;

typedef struct{
Element e;
int error; 
} Result;

typedef struct node *NODE;
struct node
{
  Element e;
  NODE link;
};
struct listinfo
{
  NODE head;
  int size;
};
typedef struct listinfo LIST;
typedef struct
{
  LIST elements;
  
} Bucket;

struct hashTable
{
  Bucket *buckets;
  int size;
};

typedef struct hashTable *HashTable;

extern int hash (char s[], int size);
extern HashTable createHashTable (int size);
extern void insertElement (HashTable h, Element e);
extern Result findElement (HashTable h, char terminal[]);


