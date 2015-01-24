// N.SHASHANK - 2009B5A7585P
// D.ADITYA   - 2009B5A7669P

#include<stdlib.h>
#include<stdio.h>
#include"ElementParseTable.h"
//#include"Parse_hashing.h"
#include<string.h>
#include"FirstAndFollow.h"
//#include"stack.h"
#include"parseDef.h"
#include"lexer.h"
extern void createParseTable(char file[],FHashTable h,VHashTable v);
extern TREENODE parseInputSourceCode(char *testcaseFile,VHashTable v,int printflag,int parseflag);
extern tokendata copytoken(tokenInfo nexttoken);
extern void DFS(TREENODE tr,char *term);
extern TREENODE createAbstractSyntaxtree(TREENODE parsetree);
extern void printAST(TREENODE tr, char *outFile);
