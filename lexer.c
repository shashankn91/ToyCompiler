#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include"fcntl.h"
#include"lexerDef.h"
#define SIZE 50
#define BUFSIZE 10025


int global_buffer_curpointer=0;
int global_buffer_endpointer=0;
int linenum=1,bytes,endofprogram=0;

// N.SHASHANK - 2009B5A7585P
// D.ADITYA   - 2009B5A7669P


void setlinenum(int line)
{
linenum=line;
return;
}





int getBufsize()
	{
        return(BUFSIZE);
	}

LHashTable createLookupKeyword()
{

LHashTable h; // hashtable for keywords
FILE *fp;
char p1[32];
char p2[32];
LElement e;
int pop,linenum;
linenum = 1;
setlinenum(linenum);
h=createLHashTable(SIZE);
fp=fopen("keywords.txt","r");
for(pop=0;pop<SIZE;pop++)
	{
	fscanf(fp,"%s",p1);
	fscanf(fp,"%s",p2);
	strcpy(e.keyword,p1);
	strcpy(e.keywordToken,p2);
	insertLElement(h,e);
	}

return h;
}

void lexerror(int linenum)
	{
	
	//printf("\nLexical Error at line %d\n",linenum);
	return ;
	}
int getStream(int inhandle, char buffer[],int buffersize)
	{
	int fp;//it is int for read
	//printf("\ninhandle before call = %d  ",inhandle);
	fp=read(inhandle,buffer,buffersize);
	//printf("\nBUFFER RELOADED\nfp = %d  ",fp);
	return(fp);
	}
	

///new comment handler

int commentHandle(char buffer[],int inhandle)
    {
      //i = global_buffer_curpointer;
      //printf("\n\n\nInside comment\n\n");
      int i,bufsize = BUFSIZE;
      while(buffer[global_buffer_curpointer]!='\n')
        {
            if((global_buffer_curpointer)>=global_buffer_endpointer) //check this for i++ error //old (golbufcurpoint+1)>=
                {
                bytes=getStream(inhandle,buffer,bufsize);
                if(bytes==0)
                    {
                    return (-1);//end of program error;
                    }
                else if(bytes==bufsize)
                    {
                   // printf("bytes==bufsize");
                    int i;
                    for(i=0;i<bytes;i++)// for for buffer end stragling problems
                        {
                        if(buffer[bytes-i-1]==' '|| buffer[bytes-i-1]=='\n' || buffer[bytes-i-1]=='\t'|| buffer[bytes-i-1]==';'||(buffer[bytes-i-1]=='e'&&buffer[bytes-i-1]=='n'&&buffer[bytes-i-3]=='d'))
                            {
                            bytes = bytes - i;
                            int retlseek;
                            //printf("lol");
                            retlseek = lseek(inhandle, -i,SEEK_CUR);
                            //inhandle = inhandle - i;
                           // printf("\ninside buf set loop new bytes = %d lseek = %d\n",bytes,retlseek);
                            break; // to break the loop
                            }
                        }
                global_buffer_endpointer = bufsize - 1 - i;
                }
		//global_buffer_endpointer = bufsize - 1 - i;//this was the old one
            else
                {
                //printf("bytes!=bufsize");
                global_buffer_endpointer = bytes;
                }
           // printf("\nInside load buffer endpointer=%d i=%d curpointer=%d endpointer=%d\n",global_buffer_endpointer,i,global_buffer_curpointer,global_buffer_endpointer);
            global_buffer_curpointer = 0;
            }

            global_buffer_curpointer++;
        }
    //  printf("\n[%c]\n",buffer[global_buffer_curpointer]);
      if(buffer[global_buffer_curpointer]=='\n')
            {
            //printf("\n&& Next is backslash n");
            return (global_buffer_curpointer);
            }
    return (-2); //error in function
    }


///new comment handler






//global_buffer_curpointer = i;

tokenInfo  getNextToken(char buffer[],int inhandle,LHashTable h)
	{
       // printf("\nEntering get next token curpointer=%d endpointer=%d",global_buffer_curpointer,global_buffer_endpointer);
	tokenInfo return_token;
	int endoftk=0,startoftk=0,i=0,loopvar;
	int backoff = 0, bufsize = BUFSIZE; // bufsize = 512
	if((global_buffer_curpointer)>=global_buffer_endpointer) //check this for i++ error //old (golbufcurpoint+1)>=
		{
		bytes=getStream(inhandle,buffer,bufsize);
		if(bytes==0)
			{
			strcpy(return_token.tokenid,"END_OF_PROGRAM");
			strcpy(return_token.token,"**LEX_ERROR_100**");//END OF PROGRAM
			return_token.error=100;
			return_token.linenumber=linenum;
			return (return_token);
			lexerror(linenum); // if nothing matches
			}
		else if(bytes==bufsize)	
			{
			//printf("bytes==bufsize");
			for(i=0;i<bytes;i++)// for for buffer end stragling problems
				{
				if(buffer[bytes-i-1]==' '|| buffer[bytes-i-1]=='\n' || buffer[bytes-i-1]=='\t'|| buffer[bytes-i-1]==';'||(buffer[bytes-i-1]=='e'&&buffer[bytes-i-1]=='n'&&buffer[bytes-i-3]=='d'))
					{
					bytes = bytes - i;
					int retlseek;
					//printf("lol");
					retlseek = lseek(inhandle, -i,SEEK_CUR);
					//inhandle = inhandle - i;
					//printf("\ninside buf set loop new bytes = %d lseek = %d\n",bytes,retlseek);
					break; // to break the loop
					}
				}
			global_buffer_endpointer = bufsize - 1 - i;
			}
		//global_buffer_endpointer = bufsize - 1 - i;//this was the old one
		else
			{
			//printf("bytes!=bufsize");
			global_buffer_endpointer = bytes;
			}
		//printf("\nInside load buffer endpointer=%d i=%d curpointer=%d endpointer=%d\n",global_buffer_endpointer,i,global_buffer_curpointer,global_buffer_endpointer);
		global_buffer_curpointer = 0;
		}
	i = global_buffer_curpointer;
	/*if(i>1)
		{
		i++;
		} // Very Imp
	*/	
	int p;
	for(p=0;p<1;p++)
		{
		 //printf("Inside loop for lexical\n");
		 while(buffer[i]==' '|| buffer[i]=='\n' || buffer[i]=='\t')
		 	{
		 	if (buffer[i]=='\n')
		 		{
		 		linenum++;
		 		//colnum = 1;
		 		}
		 	else if(buffer[i]==' ')
		 		{
		 		//colnum++;
		 		}
		 	else if(buffer[i]=='\t')
		 		{
		 		//linenum++;
		 		//colnum = colnum+4;
		 		}	
		 	//printf(" NotAToK ");
		 	i++;
		 	if(i==global_buffer_endpointer)
		 		{
		 	        //printf("\n**i==global_buffer_endpointer because of spaces and newline**\n");
		 		//global_buffer_curpointer=global_buffer_endpointer;
		 		global_buffer_curpointer=i;
		 		return_token=getNextToken(buffer,inhandle,h); //added on 10th march error prone for buffer reload;
		 		return(return_token);
		 		}
		 	}
		 
		 if(buffer[i]=='[')
		 	{
		 	//printf(" TK_[ ");//remove later, only for testing
		        int lookahead = 0;
		 	return_token.error = 1;
			strcpy(return_token.token,"TK_SQL");
			for(loopvar=0;loopvar<100;loopvar++)
				 {
				 if(loopvar<=lookahead)
				 	{
				 	return_token.tokenid[loopvar]=buffer[i+loopvar];
				 	}
				 else
				 	{
				 	return_token.tokenid[loopvar]='\0';
				 	}
				 }
			i++;
			global_buffer_curpointer = i;
			return_token.linenumber = linenum;
			return(return_token);
		 	continue;
		 	}
		 else if(buffer[i]==',')
		 	{
		 	//printf(" TK_[ ");//remove later, only for testing
		        int lookahead = 0;
		 	return_token.error = 1;
			strcpy(return_token.token,"TK_COMMA");
			for(loopvar=0;loopvar<100;loopvar++)
				 {
				 if(loopvar<=lookahead)
				 	{
				 	return_token.tokenid[loopvar]=buffer[i+loopvar];
				 	}
				 else
				 	{
				 	return_token.tokenid[loopvar]='\0';
				 	}
				 }
			i++;
			global_buffer_curpointer = i;
			return_token.linenumber = linenum;
			return(return_token);
		 	continue;
		 	}
		 else if(buffer[i]==']')
		 	{
			//printf(" TK_] ");//remove later, only for testing
			int lookahead = 0;
		 	return_token.error = 1;
			strcpy(return_token.token,"TK_SQR");
			for(loopvar=0;loopvar<100;loopvar++)
				 {
				 if(loopvar<=lookahead)
				 	{
				 	return_token.tokenid[loopvar]=buffer[i+loopvar];
				 	}
				 else
				 	{
				 	return_token.tokenid[loopvar]='\0';
				 	}
				 }
			i++;
			global_buffer_curpointer = i;
			return_token.linenumber = linenum;
			return(return_token);
		 	continue;
		 	}
		 
		 else if(buffer[i]=='(')
		 	{
		 	//printf(" TK_( ");//remove later, only for testing
		 	int lookahead = 0;
		 	return_token.error = 1;
			strcpy(return_token.token,"TK_OP");
			for(loopvar=0;loopvar<100;loopvar++)
				 {
				 if(loopvar<=lookahead)
				 	{
				 	return_token.tokenid[loopvar]=buffer[i+loopvar];
				 	}
				 else
				 	{
				 	return_token.tokenid[loopvar]='\0';
				 	}
				 }
			i++;
			global_buffer_curpointer = i;
			return_token.linenumber = linenum;
			return(return_token);
		 	continue;
		 	}
		 else if(buffer[i]==')')
		 	{
		 	//printf(" TK_) ");//remove later, only for testing
		 	int lookahead = 0;
		 	return_token.error = 1;
			strcpy(return_token.token,"TK_CL");
			for(loopvar=0;loopvar<100;loopvar++)
				 {
				 if(loopvar<=lookahead)
				 	{
				 	return_token.tokenid[loopvar]=buffer[i+loopvar];
				 	}
				 else
				 	{
				 	return_token.tokenid[loopvar]='\0';
				 	}
				 }
			i++;
			global_buffer_curpointer = i;
			return_token.linenumber = linenum;
			return(return_token);
		 	continue;
		 	}
		 else if(buffer[i]=='+')
		 	{
		 	//printf(" TK_+ ");//remove later, only for testing
		 	int lookahead = 0;
		 	return_token.error = 1;
			strcpy(return_token.token,"TK_PLUS");
			for(loopvar=0;loopvar<100;loopvar++)
				 {
				 if(loopvar<=lookahead)
				 	{
				 	return_token.tokenid[loopvar]=buffer[i+loopvar];
				 	}
				 else
				 	{
				 	return_token.tokenid[loopvar]='\0';
				 	}
				 }
			i++;
			global_buffer_curpointer = i;
			return_token.linenumber = linenum;
			return(return_token);
		 	continue;
		 	}
		 else if(buffer[i]=='-')
		 	{
		 	//printf(" TK_- ");//remove later, only for testing
		 	int lookahead = 0;
		 	return_token.error = 1;
			strcpy(return_token.token,"TK_MINUS");
			for(loopvar=0;loopvar<100;loopvar++)
				 {
				 if(loopvar<=lookahead)
				 	{
				 	return_token.tokenid[loopvar]=buffer[i+loopvar];
				 	}
				 else
				 	{
				 	return_token.tokenid[loopvar]='\0';
				 	}
				 }
			i++;
			global_buffer_curpointer = i;
			return_token.linenumber = linenum;
			return(return_token);
		 	continue;
		 	}
		 else if(buffer[i]=='/')
		 	{
		 	//printf(" TK_/ ");//remove later, only for testing
		 	int lookahead = 0;
		 	return_token.error = 1;
			strcpy(return_token.token,"TK_DIV");
			for(loopvar=0;loopvar<100;loopvar++)
				 {
				 if(loopvar<=lookahead)
				 	{
				 	return_token.tokenid[loopvar]=buffer[i+loopvar];
				 	}
				 else
				 	{
				 	return_token.tokenid[loopvar]='\0';
				 	}
				 }
			i++;
			global_buffer_curpointer = i;
			return_token.linenumber = linenum;
			return(return_token);
		 	continue;
		 	}
		 else if(buffer[i]=='*')
		 	{
		 	//printf(" TK_* ");//remove later, only for testing
		 	int lookahead = 0;
		 	return_token.error = 1;
			strcpy(return_token.token,"TK_MUL");
			for(loopvar=0;loopvar<100;loopvar++)
				 {
				 if(loopvar<=lookahead)
				 	{
				 	return_token.tokenid[loopvar]=buffer[i+loopvar];
				 	}
				 else
				 	{
				 	return_token.tokenid[loopvar]='\0';
				 	}
				 }
			i++;
			global_buffer_curpointer = i;
			return_token.linenumber = linenum;
			return(return_token);
		 	continue;
		 	}
		 	/// new comment part
		    else if(buffer[i]=='%')
		 	{
		 	//printf(" TK_%s ", "%");//remove later, only for testing
		 	int lookahead = 0;


		 	return_token.error = 5;// 5 for comment so as to neglect it
			strcpy(return_token.token,"TK_COMMENT");
			for(loopvar=0;loopvar<100;loopvar++)
				 {
				 if(loopvar<=lookahead)
				 	{
				 	return_token.tokenid[loopvar]=buffer[i+loopvar];
				 	}
				 else
				 	{
				 	return_token.tokenid[loopvar]='\0';
				 	}
				 }


          		global_buffer_curpointer = i;// new nfs
         		//printf("\nFunction Called globalcurpointer = %d, globalendpointer = %d\n",global_buffer_curpointer,global_buffer_endpointer);
            		i = commentHandle(buffer, inhandle);  //new add to NFS lex
            		//printf("\nFunction Returned globalcurpointer = %d, globalendpointer = %d\n",global_buffer_curpointer,global_buffer_endpointer);
            		if (i==-2)
                		{
                		//printf("\nError in function commentHandle\n");
               			}
            		if (i==-1)
                		{
                		strcpy(return_token.tokenid,"END_OF_PROGRAM");
                		strcpy(return_token.token,"**LEX_ERROR_100**");//END OF PROGRAM
                		return_token.error=100;
                		return_token.linenumber=linenum;
                		return (return_token);
                		}

			i++;
			linenum++;
			global_buffer_curpointer = i;

			return_token.linenumber = linenum;
			return(return_token);
		 	continue;
		 	}
		 /// new comment part
		 else if(buffer[i]==';')
		 	{
		 	//printf(" TK_; ");//remove later, only for testing
		 	int lookahead = 0;
		 	return_token.error = 1;
			strcpy(return_token.token,"TK_SEM");
			for(loopvar=0;loopvar<100;loopvar++)
				 {
				 if(loopvar<=lookahead)
				 	{
				 	return_token.tokenid[loopvar]=buffer[i+loopvar];
				 	}
				 else
				 	{
				 	return_token.tokenid[loopvar]='\0';
				 	}
				 }
			i++;
			global_buffer_curpointer = i;
			return_token.linenumber = linenum;
			return(return_token);
		 	continue;
		 	}
		 else if(buffer[i]==':')
		 	{
		 	//printf(" TK_: ");//remove later, only for testing
		 	int lookahead = 0;
		 	return_token.error = 1;
			strcpy(return_token.token,"TK_COLON");
			for(loopvar=0;loopvar<100;loopvar++)
				 {
				 if(loopvar<=lookahead)
				 	{
				 	return_token.tokenid[loopvar]=buffer[i+loopvar];
				 	}
				 else
				 	{
				 	return_token.tokenid[loopvar]='\0';
				 	}
				 }
			i++;
			global_buffer_curpointer = i;
			return_token.linenumber = linenum;
			return(return_token);
		 	continue;
		 	} 
		 else if(buffer[i]=='.')
		 	{
		 	//printf(" TK_. ");//remove later, only for testing
		 	int lookahead = 0;
		 	return_token.error = 1;
			strcpy(return_token.token,"TK_DOT");
			for(loopvar=0;loopvar<100;loopvar++)
				 {
				 if(loopvar<=lookahead)
				 	{
				 	return_token.tokenid[loopvar]=buffer[i+loopvar];
				 	}
				 else
				 	{
				 	return_token.tokenid[loopvar]='\0';
				 	}
				 }
			i++;
			global_buffer_curpointer = i;
			return_token.linenumber = linenum;
			return(return_token);
		 	continue;
		 	}
		 else if(buffer[i]=='&')
		 	{
		 	if(buffer[i+1]=='&')
		 		{
		 		if(buffer[i+2]=='&')
		 			{
		 			//printf(" TK_&&& ");//remove later, only for testing
		 			
		 			int lookahead = 2;
		 			return_token.error = 1;
					strcpy(return_token.token,"TK_AND");
					for(loopvar=0;loopvar<100;loopvar++)
					 	{
					 	if(loopvar<=lookahead)
					 		{
					 		return_token.tokenid[loopvar]=buffer[i+loopvar];
					 		}
					 	else
					 		{
					 		return_token.tokenid[loopvar]='\0';
					 		}
						 }
					i = i+2;
					i++;
					global_buffer_curpointer = i;
					return_token.linenumber = linenum;
					return(return_token);
					
		 			continue;
		 			}
		 		else
		 			{
		 			lexerror(linenum);
		 			i = i+1;
		 			global_buffer_curpointer = i;
		 			return_token.error = -1;//No matches found therefore error	
					i++;
					return_token.linenumber = linenum;
					return (return_token);
		 			continue;
		 			}	
		 		}
		 	else
		 		{
		 		//printf("error"); 
		 		lexerror(linenum);
		 		return_token.error = -1;//No matches found therefore error	
				i++;
				global_buffer_curpointer = i;
				return_token.linenumber = linenum;
				return (return_token);
		 		continue;
		 		}	
		 	}
		 else if(buffer[i]=='@')
		 	{
		 	if(buffer[i+1]=='@')
		 		{
		 		if(buffer[i+2]=='@')
		 			{
		 			//printf(" TK_@@@ ");//remove later, only for testing
		 			
		 			int lookahead = 2;
		 			return_token.error = 1;
					strcpy(return_token.token,"TK_OR");
					for(loopvar=0;loopvar<100;loopvar++)
					 	{
					 	if(loopvar<=lookahead)
					 		{
					 		return_token.tokenid[loopvar]=buffer[i+loopvar];
					 		}
					 	else
					 		{
					 		return_token.tokenid[loopvar]='\0';
					 		}
						 }
					i = i+2;
					i++;
					global_buffer_curpointer = i;
					return_token.linenumber = linenum;
					return(return_token);
					continue; // to go next iteration of loop
		 			}
		 		else
		 			{
		 			lexerror(linenum);
		 			i = i+1;
		 			i++;
		 			global_buffer_curpointer = i;
		 			return_token.error = -1;//No matches found therefore error	
		 			return_token.linenumber = linenum;
					return (return_token);
		 			continue;
		 			}
		 		}
		 	else
		 		{
		 		lexerror(linenum);
		 		return_token.error = -1;//No matches found therefore error
		 		i++;
		 		global_buffer_curpointer = i;	
		 		return_token.linenumber = linenum;
				return (return_token);
		 		continue;
		 		}	
		 	}
		 else if(buffer[i]=='~')
		 	{
		 	//printf(" TK_~ ");//remove later, only for testing
		 	int lookahead = 0;
		 	return_token.error = 1;
			strcpy(return_token.token,"TK_NOT");
			for(loopvar=0;loopvar<100;loopvar++)
				 {
				 if(loopvar<=lookahead)
				 	{
				 	return_token.tokenid[loopvar]=buffer[i+loopvar];
				 	}
				 else
				 	{
				 	return_token.tokenid[loopvar]='\0';
				 	}
				 }
			i++;
			global_buffer_curpointer = i;
			return_token.linenumber = linenum;
			return(return_token);
		 	continue;
		 	}
		 else if(buffer[i]=='=')
		 	{
		 	if(buffer[i+1]=='=')
		 		{
		 		//printf(" TK_== ");//remove later, only for testing
		 		
		 		int lookahead = 1;
		 		return_token.error = 1;
				strcpy(return_token.token,"TK_EQ");
				for(loopvar=0;loopvar<100;loopvar++)
				 	{
				 	if(loopvar<=lookahead)
				 		{
				 		return_token.tokenid[loopvar]=buffer[i+loopvar];
				 		}
				 	else
				 		{
				 		return_token.tokenid[loopvar]='\0';
				 		}
					 }
				i = i+1;
				i++;
				global_buffer_curpointer = i;
				return_token.linenumber = linenum;
				return(return_token);
				
		 		continue;// to go next iteration of loop
		 		}
		 	else
	 			{
				lexerror(linenum);
		 		//i = i+1;
		 		return_token.error = -1;//No matches found therefore error	
				i++;
				global_buffer_curpointer = i;
				return_token.linenumber = linenum;
				return (return_token);
		 		continue;
		 		}	
		 	}
		 else if(buffer[i]=='>')
		 	{
		 	if(buffer[i+1]=='=')
		 		{
		 		//printf(" TK_>= ");//remove later, only for testing
		 		
		 		int lookahead = 1;
		 		return_token.error = 1;
				strcpy(return_token.token,"TK_GE");
				for(loopvar=0;loopvar<100;loopvar++)
				 	{
				 	if(loopvar<=lookahead)
				 		{
				 		return_token.tokenid[loopvar]=buffer[i+loopvar];
				 		}
				 	else
				 		{
				 		return_token.tokenid[loopvar]='\0';
				 		}
					 }
				i = i+1;
				i++;
				global_buffer_curpointer = i;
				return_token.linenumber = linenum;
				return(return_token);
				
		 		continue;// to go next iteration of loop
		 		}
		 	else
		 		{
		 		//printf(" TK_>");
		 		int lookahead = 0;
		 		return_token.error = 1;
				strcpy(return_token.token,"TK_GT");
				for(loopvar=0;loopvar<100;loopvar++)
					 {
					 if(loopvar<=lookahead)
					 	{
					 	return_token.tokenid[loopvar]=buffer[i+loopvar];
					 	}
					 else
					 	{
					 	return_token.tokenid[loopvar]='\0';
					 	}
					 }
				i++;
				global_buffer_curpointer = i;
				return_token.linenumber = linenum;
				return(return_token);
		 		continue;
		 		}
		 	
		 	
		 	}
		 else if(buffer[i]=='<')
		 	{
		 	if(buffer[i+1]=='=')
		 		{
		 		//printf(" TK_<= ");//remove later, only for testing
		 		
		 		int lookahead = 1;
		 		return_token.error = 1;
				strcpy(return_token.token,"TK_LE");
				for(loopvar=0;loopvar<100;loopvar++)
				 	{
				 	if(loopvar<=lookahead)
				 		{
				 		return_token.tokenid[loopvar]=buffer[i+loopvar];
				 		}
				 	else
				 		{
				 		return_token.tokenid[loopvar]='\0';
				 		}
					 }
				i = i+1;
				i++;
				global_buffer_curpointer = i;
				return_token.linenumber = linenum;
				return(return_token);
				
		 		continue;// to go next iteration of loop
		 		}
		 	else if(buffer[i+1]=='-')
		 		{
		 		if(buffer[i+2]=='-')
		 			{
		 			if(buffer[i+3]=='-')
		 				{
		 				//printf(" TK_<--- ");//remove later, only for testing
		 				
		 				int lookahead = 3;
		 				return_token.error = 1;
						strcpy(return_token.token,"TK_ASSIGNOP");
						for(loopvar=0;loopvar<100;loopvar++)
						 	{
						 	if(loopvar<=lookahead)
						 		{
						 		return_token.tokenid[loopvar]=buffer[i+loopvar];
						 		}
						 	else
						 		{
						 		return_token.tokenid[loopvar]='\0';
						 		}
							 }
						i = i+3;
						i++;
						global_buffer_curpointer = i;
						return_token.linenumber = linenum;
						return(return_token);
						
		 				continue;// to go next iteration of loop
		 				} 
		 			else
	 					{
						lexerror(linenum);
		 				i = i+2;
		 				i++;
		 				global_buffer_curpointer = i;
		 				return_token.error = -1;//No matches found therefore error	
		 				return_token.linenumber = linenum;
						return (return_token);
		 				continue;
		 				}			
		 			}
		 		else
	 				{
					lexerror(linenum);
		 			i = i+1;
		 			i++;
		 			global_buffer_curpointer = i;
		 			return_token.error = -1;//No matches found therefore error	
		 			return_token.linenumber = linenum;
					return (return_token);
		 			continue;
		 			}	
		 		}
		 	else 
		 		{
		 		//printf(" TK_<");
		 		int lookahead = 0;
		 		return_token.error = 1;
				strcpy(return_token.token,"TK_LT");
				for(loopvar=0;loopvar<100;loopvar++)
					 {
					 if(loopvar<=lookahead)
					 	{
					 	return_token.tokenid[loopvar]=buffer[i+loopvar];
					 	}
					 else
					 	{
					 	return_token.tokenid[loopvar]='\0';
					 	}
					 }
				i++;
				global_buffer_curpointer = i;
				return_token.linenumber = linenum;
				return(return_token);
		 		continue; 
		 		}
		 	}
		 else if(buffer[i]=='!')
		 	{
		 	if(buffer[i+1]=='=')
		 		{
		 		//printf(" TK_!= ");//remove later, only for testing
		 		
		 		int lookahead = 1;
		 		return_token.error = 1;
				strcpy(return_token.token,"TK_NE");
				for(loopvar=0;loopvar<100;loopvar++)
				 	{
				 	if(loopvar<=lookahead)
				 		{
				 		//printf("\nloopvar = %d %c\n",loopvar,buffer[i+loopvar]); //remove this and remove this too i =i+1
				 		return_token.tokenid[loopvar]=buffer[i+loopvar];
				 		}
				 	else
				 		{
				 		return_token.tokenid[loopvar]='\0';
				 		}
					 }
				i = i+1;
				i++;
				global_buffer_curpointer = i;
				return_token.linenumber = linenum;
				return(return_token);
				
		 		continue;// to go next iteration of loop
		 		}
		 	else
	 			{
				lexerror(linenum);
		 		//i = i+1;
		 		i++;
		 		global_buffer_curpointer = i;
		 		return_token.error = -1;//No matches found therefore error	
		 		return_token.linenumber = linenum;
				return (return_token);
		 		continue;
		 		}
		 	}
		 else if(buffer[i]=='#') // error prone check later; Record Id ( RI )
		 	{
		 	
		 	if (buffer[i+1]>'z' && buffer[i+1]<'a')
		 		{
		 		lexerror(linenum);
		 		//i = i+1;
		 		i++;
		 		global_buffer_curpointer = i;
		 		return_token.error = -1;//No matches found therefore error	
		 		return_token.linenumber = linenum;
				return (return_token);
		 		continue;
		 		}
		 	else if (buffer[i+1]>='a' && buffer[i+1]<='z')
		 		{
		 		
		        	int lookahead = 2;
		 		while(buffer[i+lookahead]>='a' && buffer[i+lookahead]<='z')
		 			{
		 			lookahead ++;
		 			}
		 		endoftk = i + lookahead - 1 ;
		 		startoftk = i;
		 		//printf(" TK_RecordID ");
		 		
		 		
		 		lookahead = lookahead - 1;
		 		return_token.error = 1;
				strcpy(return_token.token,"TK_RECORDID");
				for(loopvar=0;loopvar<100;loopvar++)
				 	{
				 	if(loopvar<=lookahead)
				 		{
				 		return_token.tokenid[loopvar]=buffer[i+loopvar];
				 		}
				 	else
				 		{
				 		return_token.tokenid[loopvar]='\0';
				 		}
					 }
				i = i + lookahead; // check for correctness
				i++;
				global_buffer_curpointer = i;
				return_token.linenumber = linenum;
				return(return_token);
				
		 		continue;// to go next iteration of loop
		 		}
		 	
		 		
		 	}
		 
		 else if (buffer[i]<='9' && buffer[i]>='0') // for Real Num and Integers
		 	{
		 	int lookahead = 1;
		 	while(buffer[i+lookahead]>='0' && buffer[i+lookahead]<='9')
		 		{
		 		lookahead ++;
		 		}
		 	if(buffer[i+lookahead]!='.')
		 		{
		 		endoftk = i + lookahead - 1 ;
		 		startoftk = i;
		 		//printf(" TK_Integer ");
		 		
		 		
		 		lookahead = lookahead - 1;
		 		return_token.error = 1;
				strcpy(return_token.token,"TK_NUM");
				for(loopvar=0;loopvar<100;loopvar++)
				 	{
				 	if(loopvar<=lookahead)
				 		{
				 		return_token.tokenid[loopvar]=buffer[i+loopvar];
				 		}
				 	else
				 		{
				 		return_token.tokenid[loopvar]='\0';
				 		}
					 }
				i = i+lookahead;
			        i++;
				global_buffer_curpointer = i;
				return_token.linenumber = linenum;
				return(return_token);
				
		 		continue;// to go next iteration of loop
		 		// send token as int
		 		}
		 	else if(buffer[i+lookahead]=='.')	
		 		{
		 		lookahead++;
		 		if(buffer[i+lookahead]>='0' && buffer[i+lookahead]<='9')
		 			{
		 			 lookahead++;
		 			 if(buffer[i+lookahead]>='0' && buffer[i+lookahead]<='9')
		 			 	{
		 			 	endoftk = i + lookahead; //check
		 				startoftk = i;
		 				//printf(" TK_RealNum ");
		 				
		 				
		 				
				 		return_token.error = 1;
						strcpy(return_token.token,"TK_RNUM");
						for(loopvar=0;loopvar<100;loopvar++)
						 	{
						 	if(loopvar<=lookahead)
						 		{
						 		return_token.tokenid[loopvar]=buffer[i+loopvar];
						 		}
						 	else
						 		{
						 		return_token.tokenid[loopvar]='\0';
						 		}
							 }
						i = i + lookahead; //check
						i++;
						global_buffer_curpointer = i;
						return_token.linenumber = linenum;
						return(return_token);
		 			
		 				continue;// to go next iteration of loop
		 			 	// send realnum token
		 		 		}
		 		 	else 
		 				{
		 				lexerror(linenum);
		 	 			i = i+lookahead-1;
		 	 			i++;
		 				global_buffer_curpointer = i;
		 				return_token.error = -1;//No matches found therefore error
		 				return_token.linenumber = linenum;	
						return (return_token);
		 				continue;
		 			 	}	
		 			}
		 		else 
		 			{
		 			lexerror(linenum);
		 	 		i = i+lookahead-1;
		 	 	        i++;
		 			global_buffer_curpointer = i;
		 			return_token.error = -1;//No matches found therefore error	
		 			return_token.linenumber = linenum;
					return (return_token);
		 			continue;
		 			}	
		 		}
		 	
		 	else 
		 		{
		 		lexerror(linenum);
		 	 	//i = i+lookahead-1;
		 	 	i++;
		 	 	global_buffer_curpointer = i;
		 	 	return_token.error = -1;//No matches found therefore error
		 	 	return_token.linenumber = linenum;	
				return (return_token);
		 		continue;
		 		}	
		 	
		 	}
		 else if (buffer[i]=='_') // Func ID
		 	{
		 	char temp1[2];
		 	char test[6];// some sorcery here. Its supposed to be 5 but it works with 2!!
 		 	int ko,vo;
		 	for(vo=0;vo<5;vo++)
		 		{
		 		test[vo]=buffer[i+vo];
		 		}
		 		test[5]='\0';
		 	//printf("\n:%s:\n",test);
		 	if(strcmp(test,"_main")==0)
		 		{
		 		//printf(" TK_MAIN %s", test);
		 		
		 		int lookahead = 4;
		 		return_token.error = 1;
				strcpy(return_token.token,"TK_MAIN");
				for(loopvar=0;loopvar<100;loopvar++)
					 {
					 if(loopvar<=lookahead)
					 	{
					 	return_token.tokenid[loopvar]=buffer[i+loopvar];
					 	}
					 else
					 	{
					 	return_token.tokenid[loopvar]='\0';
					 	}
					 }
				i = i+4;
				i++;
				global_buffer_curpointer = i;
				return_token.linenumber = linenum;
				return(return_token);
				
		 		continue;
		 		}
		 	
		 	int lookahead = 1;
		 	if ((buffer[i+lookahead]>'Z' && buffer[i+lookahead]<'a') || (buffer[i+lookahead]<'A' && buffer[i+lookahead]>'z')) //errorprone
		 		{
		 		lexerror(linenum);
		 	 	//i = i+lookahead-1;
		 	 	return_token.error = -1;//No matches found therefore error
		 	 	i++;
		 	 	global_buffer_curpointer = i;
		 	 	return_token.linenumber = linenum;	
				return (return_token);
		 		continue;
		 		}
		 	while( (buffer[i+lookahead]>='a' && buffer[i+lookahead]<='z') || (buffer[i+lookahead]>='A' && buffer[i+lookahead]<='Z') )
		 		{
		 		lookahead ++;
		 		}
		 	if (lookahead>1)
		 		{
		 		while(buffer[i+lookahead]>='0' && buffer[i+lookahead]<='9')
		 			{
		 			lookahead ++;
		 			}
		 		endoftk = i + lookahead - 1 ;
		 		startoftk = i;
		 		
		 		//printf(" TK_FuncId ");
		 		
		 		lookahead = lookahead -1;
		 		return_token.error = 1;
				strcpy(return_token.token,"TK_FUNID");
				for(loopvar=0;loopvar<100;loopvar++)
					 {
					 if(loopvar<=lookahead)
					 	{
					 	return_token.tokenid[loopvar]=buffer[i+loopvar];
					 	}
					 else
					 	{
					 	return_token.tokenid[loopvar]='\0';
					 	}
					 }
				i = i +lookahead;
				i++;
				global_buffer_curpointer = i;
				return_token.linenumber = linenum;
				return(return_token);
		 		
		 		continue;// to go next iteration of loop
		 		}
		 	
		 	}
		
		 else if (buffer[i]>='b' && buffer[i]<='d' && buffer[i+1]>='2' && buffer[i+1]<='7') // identifiers
		 	{
		 	if (buffer[i+1]>='2' && buffer[i+1]<='7')
		 		{
		 		int lookahead = 2;
		 		while(buffer[i+lookahead]>='b' && buffer[i+lookahead]<='d')
		 			{
		 			lookahead++;
		 			}
		 		while(buffer[i+lookahead]>='2' && buffer[i+lookahead]<='7')
		 			{
		 			lookahead++;
		 			}
		 		endoftk = i + lookahead - 1 ;
		 		startoftk = i;
		 		int lengthoftoken;
		 		lengthoftoken = endoftk-startoftk+1;
		 		//printf(" TK_ID ");
		 		
		 		lookahead = lookahead ;
		 		if(lengthoftoken>20)
		 			{
		 			printf("\nlengthoftoken=%d\n" , lengthoftoken);
		 			return_token.error = -11;
		 			}
		 		else	
		 			{
		 			return_token.error = 1; // token lenght too long, token error_no 1 as per mam's format
		 			}	
				strcpy(return_token.token,"TK_ID");
				for(loopvar=0;loopvar<100;loopvar++)
					 {
					 if(loopvar<lookahead)
					 	{
					 	return_token.tokenid[loopvar]=buffer[i+loopvar];
					 	}
					 else
					 	{
					 	return_token.tokenid[loopvar]='\0';
					 	}
					 }
				i = i+lookahead-1;
				i++;
				global_buffer_curpointer = i;
				return_token.linenumber = linenum;
				return(return_token);
				
		 		continue;// to go next iteration of loop
		 		}
		 	else 
		 		{
		 		lexerror(linenum);
		 	 	//i = i+lookahead-1;
		 	 	return_token.error = -1;//No matches found therefore error
		 	 	i++;
		 	 	global_buffer_curpointer = i;
		 	 	return_token.linenumber = linenum;	
				return (return_token);
		 		continue;
		 		}
		 	}
		 else if (buffer[i]>='a' && buffer[i]<='z')  // for field name
		 	{
		 	//printf("Near if for hash %c-",buffer[i]);
		 	int lookahead = 1;
		 	while(buffer[i+lookahead]>='a' && buffer[i+lookahead]<='z')
		 		{
		 		//printf("%c-",buffer[lookahead+i]);
		 		lookahead ++;
		 	        
		 		}
		 	endoftk = i + lookahead - 1 ;
		 	startoftk = i;
		 	
		 	int sizeoftk,loopvar1=0;
		 	sizeoftk = lookahead+1;
		 	char *tk;
		 	tk = malloc(sizeoftk*sizeof(char));
		 	//printf("mallock done lookahea =%d\n",lookahead);
		 	for(loopvar1=0;loopvar1<lookahead;loopvar1++)
		 		{
		 		tk[loopvar1]=buffer[i+loopvar1];
		 		//printf("hi");
		 		}
		 	tk[lookahead]='\0';
		      //  printf("%s",tk);
		 	LResult hashreturn;
		        //printf("\nchecking for match in hashtable\n");
		 	hashreturn = findLElement (h,tk);
		 	//printf("Return error val of findelement function:%d \n",hashreturn.error);
		 	if (hashreturn.error==-1)
		 		{
		 		//printf(" TK_FieldId ");
		 		
		 		lookahead = lookahead -1;//error prone
		 		return_token.error = 1;
				strcpy(return_token.token,"TK_FIELDID");
				for(loopvar=0;loopvar<100;loopvar++)
					 {
					 if(loopvar<=lookahead)
					 	{
					 	return_token.tokenid[loopvar]=buffer[i+loopvar];
					 	}
					 else
					 	{
					 	return_token.tokenid[loopvar]='\0';
					 	}
					 }
				i = i + lookahead;
				i++;
				global_buffer_curpointer = i;
				free(tk);
				return_token.linenumber = linenum;
				return(return_token);
				
		 		}
		 	else 
		 		{
		 		//printf(" %s ",hashreturn.e.keywordToken);
		 		
		 		return_token.error = 1;
				strcpy(return_token.token,hashreturn.e.keywordToken);
				strcpy(return_token.tokenid,tk);
				i = i + lookahead - 1; //error prone
				i++;
				global_buffer_curpointer = i;
				free(tk);
				return_token.linenumber = linenum;
				return(return_token);
				 
		 		}
		 	
		 	//i = i + lookahead - 1;
		 	continue;// to go next iteration of loop
		 	}
		/* else if (buffer[i]=='I')
		 	{
		 	char temp[6];// some sorcery. Its supposed to work for 5 but is working for 2 !!!
		 	int ko;
		 	if(buffer[i+1]=='f')
		 		{
		 		//printf(" TK_IF ");
		 		//temp[0]='I';temp[1]='f';temp[2]'\0';		 		
		 		
		 		return_token.error = 1;
				strcpy(return_token.token,"TK_IF");
				strcpy(return_token.tokenid,"If");
		 		i = i+1;
		 		i++;
		 		global_buffer_curpointer = i;
		 		return_token.linenumber = linenum;
		 		return(return_token);
		 		continue;
		 		}
		 	for(ko=0;ko<5;ko++)
		 		{
		 		temp[ko]=buffer[i+ko];
		 		}
		 	temp[5]='\0';
		 	if(strcmp(temp,"Input")==0)
		 		{
		 		//printf(" TK_INPUT %s", temp);
		 		return_token.error = 1;
				strcpy(return_token.token,"TK_INPUT");
				strcpy(return_token.tokenid,"Input");
				
		 		i = i+4;
		 		i++;
		 	        global_buffer_curpointer = i;
		 	        return_token.linenumber = linenum;
		 	        return(return_token);
		 		}
		 	else 
		 		{
		 		//printf("\nSTRCMP error this was read ||%s||",temp);
		 		}
		 	}*/
		else 
			{
			int lookahead=0;
			return_token.error = -2;//No symbol matches found therefore error	
			return_token.linenumber = linenum;
			char errorlexeme[21];
			int errloop;
			for(errloop=0;errloop<21;errloop++)
				{
					if(errloop<=lookahead){errorlexeme[errloop]=buffer[i+errloop];}
					else{errorlexeme[errloop]='\0';}
				}
			strcpy(return_token.tokenid,errorlexeme);
			strcpy(return_token.token,"**LEX_ERROR_2**");
			//printf("i=%d GlobalCurPointer=%d \n+%s+\n",i,global_buffer_curpointer,errorlexeme);
			i++;
			global_buffer_curpointer = i;
			return (return_token);
			lexerror(linenum); // if nothing matches
			}
		}
	return_token.error = -1;//No matches found therefore error
	i++;
	global_buffer_curpointer = i;
	return_token.linenumber = linenum;	
	return (return_token);
	}


