#include "funciones.h"

struct producto lec_padre(char descrin[], char* file_disponible) //param: char que se está buscando
{
  FILE* ptr; // se declara puntero para arreglo donde se guarda lo que esta en el .txt
  char ch;
  char *s; // puntero para split
  char texto[100]; // array para guardar linea
  int a = 0;
  struct producto prod;
  //producto *Pprod = &prod;
  ptr = fopen("test.txt", "r");
  if (NULL == ptr) {
    printf("file can't be opened \n");
  }

  // se leen la linea del archivo de texto
  while(!feof(ptr)){
    ch = fgetc(ptr); // lee un caracter del archivo de texto
    texto[a] = ch;
    if(texto[a] == '\n'){ // si hay salto de linea, se sale del while
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
      break;
    }
    
    //printf("%s\n", prod.descripcion);
    }
    a++;
  }
 // printf("%s\n", texto);

  // Closing the file
  fclose(ptr);
  return prod;
}

struct producto lec_hijo(int codin, char* file_disponible) //param: char que se está buscando
{
  FILE* ptr; // se declara puntero para arreglo donde se guarda lo que esta en el .txt
  char ch;
  char *s; // puntero para split
  char texto[100]; // array para guardar linea
  int a = 0;
  struct producto prod;
  //producto *Pprod = &prod;
  ptr = fopen("test.txt", "r");
  if (NULL == ptr) {
    printf("file can't be opened \n");
  }

  // se leen la linea del archivo de texto
  while(!feof(ptr)){
    ch = fgetc(ptr); // lee un caracter del archivo de texto
    texto[a] = ch;
    if(texto[a] == '\n'){ // si hay salto de linea, se sale del while
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
    if (codin==prod.codigo){
      break;
    }
    
    //printf("%s\n", prod.descripcion);
    }
    a++;
  }
 // printf("%s\n", texto);

  // Closing the file
  fclose(ptr);
  return prod;
}

int padre(int codigos[], char* file_pedidos, char* file_disponible){//arg puntero al arreglo de codigos


	int suma = 0; //para guardar total recaudado
	FILE* ptr; // se declara puntero para arreglo donde se guarda lo que esta en el .txt
	char ch;
	char palabra[100]; // array para guardar linea
	int a = 0;
	struct producto prod;
	//producto *Pprod = &prod;
	ptr = fopen("test.txt", "r");
	if (NULL == ptr) {
		printf("file can't be opened \n");
	}

	// se leen la linea del archivo de texto
	int i = 0; //indice de arreglo codigos
	while(!feof(ptr)){
		ch = fgetc(ptr); // lee un caracter del archivo de texto
		
		if(ch==','){ //guarda caracteres hasta que encuentra una coma
			prod = lec_padre(palabra, file_disponible); //busca descripción en file disponible
			codigos[i]=prod.codigo;
			suma+=prod.precio;
			a=0;
			i++;
		}
		else{	
			palabra[a] = ch;
			a++;
		}
	}
	fclose(ptr);
	return suma;
}

