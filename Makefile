build:
	yacc -d opl.y
	lex opl.l
	gcc lex.yy.c y.tab.c -ll -ly -o opl

run:
	./opl main.txt

remove:
	rm -f y.tab.c
	rm -f y.tab.h
	rm -f opl
	rm -f lex.yy.c