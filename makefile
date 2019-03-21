

a.out: main.o deklaracje.o 
	gcc -std=c99 main.o deklaracje.o -Wall

main.o: main.c  deklaracje.h
	gcc -c -std=c99 main.c -Wall

deklaracje.o: deklaracje.c deklaracje.h 
	gcc -c -std=c99 deklaracje.c -Wall






