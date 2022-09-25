#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void diponibles_print(char* file_disponible) //param: char que se está buscando
{
	FILE* ptr; // se declara puntero para arreglo donde se guarda lo que esta en el .txt	
	char ch;
	char *s; // puntero para split
	char texto[100]; // array para guardar linea
	int a = 0;
	ptr = fopen(file_disponible, "r");
	if (NULL == ptr) {
		printf("file can't be opened \n");
	}
	
	printf("Los productos disponibles son:\n");
	// se leen la linea del archivo de texto
	while(!feof(ptr)){
		ch = fgetc(ptr); // lee un caracter del archivo de texto
		texto[a] = ch;
		if(texto[a] == '\n'){ // si hay salto de linea, se sale del while
			a = -1;
			s = strtok(texto, ",");
			printf("%s\n", s);
		}
		a++;
	}
	// Closing the file
	fclose(ptr);
}