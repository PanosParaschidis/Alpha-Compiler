all:
	flex -olex.c al.l
	bison --yacc --defines --output=parser.c parser.y
	gcc -o al.out lex.c parser.c symtable.c functions.c quads.c targetCode.c avm.c -lm


clean:
	rm -rf *.out lex.c parser.c parser.h *.bin code.txt *.output *.o 
	
