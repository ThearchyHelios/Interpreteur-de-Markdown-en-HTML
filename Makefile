PROGRAMS = markdown

all:$(PROGRAMS)

markdown.o: markdown.c analyse_lexicale.h parser.h
	gcc -g -Wall -c markdown.c

ast.o: ast.c ast.h
	gcc -g -Wall -c ast.c

analyse_lexicale.o: analyse_lexicale.c analyse_lexicale.h
	gcc -g -Wall -c analyse_lexicale.c

parser.o: parser.c parser.h
	gcc -g -Wall -c parser.c

markdown: markdown.o analyse_lexicale.o parser.o ast.o
	gcc -g -Wall -o markdown markdown.o analyse_lexicale.o parser.o ast.o

clean:
	rm -f *.o $(PROGRAMS)

