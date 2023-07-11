parse: lex.yy.c parse.c tokens.h
	gcc -o parse -g parse.c lex.yy.c -ll

lex.yy.c:	lexer.l
	flex lexer.l

clean:
	rm parse 