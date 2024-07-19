assembler: main.o func1.o
	gcc -Wall -ansi -pedantic main.o func1.o -o assembler

main.o: main.c header.h
	gcc -Wall -ansi -pedantic -c main.c -o main.o

func1.o: func1.c header.h
	gcc -Wall -ansi -pedantic -c func1.c -o func1.o

clean:
	rm -f *.o assembler
