#make program

runme: main.o tema.o
	gcc -o runme tema.o main.o

main.o: main.c
	gcc -c main.c

tema.o: tema.c
	gcc -c tema.c
