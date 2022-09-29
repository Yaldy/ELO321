FILE1 = "disponible.txt"
FILE2 = "pedidos.txt"
default: tarea1
tarea1: funciones.o main.o
	gcc -g -Wall -o tarea1 main.o funciones.o
main.o: main.c funciones.o
	gcc -g -Wall -c main.c
funciones.o: funciones.c funciones.h
	gcc -g -Wall -c funciones.c
run:
	./tarea1 $(FILE1) $(FILE2)
clean:
	rm *.o
purge:
	rm tarea1