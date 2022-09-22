#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
  char descripcion[30];
  int precio;
  int codigo;
  int tiempo;
}producto;

int main()
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

  // se leen la linea del archivo de texto
  while(!feof(ptr)){
    ch = fgetc(ptr); // lee un caracter del archivo de texto
    texto[a] = ch;
    if(texto[a] == '\n'){ // si hay salto de linea, se sale del while
      a = -1;
      // se guardan los datos ordenados en un struct
      s = strtok(texto, ",");
      memset(Pprod->descripcion,'\0',sizeof(Pprod->descripcion)); // rellena descripcion con caracteres nulos
      strcpy(Pprod->descripcion,s); // iguala dos string (string copy)
      int n = 0;
      while(s != NULL){
        s = strtok(NULL,",");
        switch(n){ // guarda en el struct
          case 0: Pprod->precio = atoi(s);
          case 1: Pprod->codigo = atoi(s);
          case 2: Pprod->tiempo = atoi(s);
        }
        n++;
      }
    printf("%s\n", Pprod->descripcion);
    }
    a++;
  }
 // printf("%s\n", texto);

  // Closing the file
  fclose(ptr);
  return 0;
}
