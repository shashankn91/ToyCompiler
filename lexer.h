

#include"lexerDef.h"
// N.SHASHANK - 2009B5A7585P
// D.ADITYA   - 2009B5A7669P

extern int getStream(int inhandle, char buffer[],int buffersize);
extern tokenInfo  getNextToken(char buffer[],int inhandle,LHashTable h);
extern void setlinenum(int line);
extern int getBufsize();
extern LHashTable createLookupKeyword();
