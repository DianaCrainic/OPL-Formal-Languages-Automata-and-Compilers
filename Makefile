build:
	yacc -d opl.y
	lex opl.l
	gcc lex.yy.c y.tab.c -ll -ly -o opl

run:
	./opl main.txt