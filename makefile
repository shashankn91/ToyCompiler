#N.SHASHANK - 2009B5A7585P
# D.ADITYA   - 2009B5A7669P

.c.o:
	gcc -c $<

#exec: all
#	./driver testcase1.txt p1.txt a1.txt
	
all: toycompiler clean

toycompiler: lexer.o parser.o hashtable_chaining.o VerticalHash.o Parse_hashing_separatechaining.o FirstAndFollow.o stack.o SymbolTable.o SymbolHash.o SemanticAnalyser.o codeGeneration.o
	gcc -o toycompiler driver.c parser.o lexer.o hashtable_chaining.o VerticalHash.o Parse_hashing_separatechaining.o FirstAndFollow.o stack.o SymbolTable.o SymbolHash.o SemanticAnalyser.o codeGeneration.o
		

clean:
	rm -f *.o



