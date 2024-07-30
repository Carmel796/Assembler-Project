assembler: main.o func1.o
	gcc -Wall -ansi -pedantic main.o func1.o -o assembler

main.o: main.c main.h
	gcc -Wall -ansi -pedantic -c main.c -o main.o

func1.o: util.c main.h
	gcc -Wall -ansi -pedantic -c func1.c -o func1.o

clean:
	rm -f *.o assembler
