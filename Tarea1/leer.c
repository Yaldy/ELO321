#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
  char descripcion[30];
  int precio;
  int codigo;
  int tiempo;
}producto;

int leer_prod() //paramatros campo(),lo que se busca
{
  FILE* ptr; // se declara puntero para arreglo donde se guarda lo que esta en el .txt
  char ch;
  char *s; // puntero para split
  char texto[100]; // array para guardar linea
  int a = 0;
  producto prod;
  producto *Pprod = &prod;
  ptr = fopen("test.txt", "r");
  if (NULL == ptr) {
    printf("file can't be opened \n");
  }

  // se lee linea a linea el archivo de texto
  while(!feof(ptr)){
    ch = fgetc(ptr); // lee un caracter del archivo de texto
    texto[a] = ch;
    if(texto[a] == '\n'){ 
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
	  
	//comparar para encontrar lo que se busca (descripción o codigo)
	
	switch(){
		
	}
    printf("%s\n", prod.descripcion);
    }
    a++;
  }
 // printf("%s\n", texto);

  // Closing the file
  fclose(ptr);
  return 0;
}
