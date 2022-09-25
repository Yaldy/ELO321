struct producto lec_hijo(int codin, char* file_disponible) //param: char que se está buscando
{
	FILE* ptr; // se declara puntero para arreglo donde se guarda lo que esta en el .txt
	char ch;
	char *s; // puntero para split
	char texto[100]; // array para guardar linea
	int a = 0;
	struct producto prod;
	//producto *Pprod = &prod;
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