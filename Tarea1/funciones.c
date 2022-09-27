#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#include "funciones.h"

struct producto{
	char descripcion[30];
	int precio;
	int codigo;
	int tiempo;
};

void disponibles_print(char* file_disponible){ //param: char que se está buscando
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
		if(texto[a] == '\n'||feof(ptr)){ // si hay salto de linea o EOF, se sale del while
			a = -1; //-1 para que cuando salga del if se haga 0
			s = strtok(texto, ","); //separa texto en la primera coam que encuaentre
			printf("%s\n", s);
		}
		a++;
	}
	
	fclose(ptr); // cerrar archivo
}

struct producto lec_hijo(int codin, char* file_disponible){ 
	FILE* ptr; // se declara puntero para arreglo donde se guarda lo que esta en el .txt
	char ch;
	char *s; // puntero para split
	char texto[100]; // array para guardar linea
	int a = 0;
	struct producto prod;
	ptr = fopen(file_disponible, "r");
	if (NULL == ptr) {
		printf("file can't be opened \n");
	}

	// se leen la linea del archivo de texto
	while(!feof(ptr)){
		ch = fgetc(ptr); // lee un caracter del archivo de texto
		texto[a] = ch;
		if(texto[a] == '\n'||feof(ptr)){ // si hay salto de linea, se sale del while
			a = -1;
			// se guardan los datos ordenados en un struct
			s = strtok(texto, ",");
			memset(prod.descripcion,'\0',sizeof(prod.descripcion)); // rellena descripcion con caracteres nulos
			strcpy(prod.descripcion,s); // iguala dos string (string copy)
			int n = 0;
			while(s != NULL){
				s = strtok(NULL,",");
				switch(n){ // guarda en el struct
					case 0: prod.precio = atoi(s);
					case 1: prod.codigo = atoi(s);
					case 2: prod.tiempo = atoi(s);
				}
				n++;
			}
    
			// comparar el argumento con el codigo actual
			if (codin==prod.codigo){
				break;
			}
		}
		a++;
	}
	
	fclose(ptr); // cerrar archivo
	return prod;
}

struct producto lec_padre(char descrin[], char* file_disponible){ 
	FILE* ptr; // se declara puntero para arreglo donde se guarda lo que esta en el .txt
	char ch;
	char *s; // puntero para split
	char texto[100]; // array para guardar linea
	int a = 0;
	int flag = 0; // flag para verificar si encuentra el producto
	struct producto prod;
	ptr = fopen(file_disponible, "r");
	if (NULL == ptr) {
		printf("file can't be opened \n");
	}

	// se leen la linea del archivo de texto
	while(!feof(ptr)){
		ch = fgetc(ptr); // lee un caracter del archivo de texto
		texto[a] = ch;
		if(texto[a] == '\n'||feof(ptr)){ // si hay salto de linea, se sale del while
			a = -1;
			// se guardan los datos ordenados en un struct
			s = strtok(texto, ",");
			memset(prod.descripcion,'\0',sizeof(prod.descripcion)); // rellena descripcion con caracteres nulos
			strcpy(prod.descripcion,s); // iguala dos string (string copy)
			int n = 0;
			while(s != NULL){
				s = strtok(NULL,",");
				switch(n){ // guarda en el struct
					case 0: prod.precio = atoi(s);
					case 1: prod.codigo = atoi(s);
					case 2: prod.tiempo = atoi(s);
				}
				n++;
			}
    
			// comparar el argumento con la desc actual
			if (strcmp(prod.descripcion,descrin)==0){
				flag = 1;
				break;
			}
		}
		a++;
	}
	
    if(flag == 0){
		strcpy(prod.descripcion,"error");
		prod.precio = 0;
		prod.codigo = 0;
		prod.tiempo = 0;
	}
	
	fclose(ptr); // cerrar archivo
	return prod;
}

int padre(int codigos[], char* file_pedidos, char* file_disponible){//arg puntero al arreglo de codigo
	int suma = 0; //para guardar total recaudado
	FILE* ptr; // se declara puntero para arreglo donde se guarda lo que esta en el .txt
	char ch;
	char palabra[100]; // array para guardar linea
	memset(palabra,'\0',sizeof(palabra));
	int a = 0;
	struct producto prod;
	//producto *Pprod = &prod;
	ptr = fopen(file_pedidos, "r");
	if (NULL == ptr) {
		printf("file can't be opened \n");
	}

	// se leen la linea del archivo de texto
	int i = 0; //indice de arreglo codigos
	do{
		ch = fgetc(ptr); // lee un caracter del archivo de texto
		if(ch == ','|| feof(ptr) ){ //guarda caracteres hasta que encuentra una coma
			prod = lec_padre(palabra, file_disponible); //busca descripción en file disponible
			// preguntar si el prod no es de error
			if(prod.precio == 0){
				printf("El producto %s no esta disponible.\n", palabra);
			}
			else{
				codigos[i]=prod.codigo;
				suma+=prod.precio;
				printf("El producto %s tiene un valor de $%d.\n",prod.descripcion,prod.precio);
				i++;
			}
			a = 0;
			memset(palabra,'\0',sizeof(palabra));
		}
		else if (ch != '\n'){	
			palabra[a] = ch;
			//printf("ch: %d\n",(int)(ch));
			a++;
		}
	}while(!feof(ptr));
  
	fclose(ptr);
	return suma;
}