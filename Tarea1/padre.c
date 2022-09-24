#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct producto{
  char descripcion[30];
  int precio;
  int codigo;
  int tiempo;
};

int padre(int codigos[], char* file_pedidos, char* file_disponible){//arg puntero al arreglo de codigos


	int suma = 0; //para guardar total recaudado
	FILE* ptr; // se declara puntero para arreglo donde se guarda lo que esta en el .txt
	char ch;
	char palabra[100]; // array para guardar linea
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
		
		if(ch==',' || feof(ptr)){ //guarda caracteres hasta que encuentra una coma
			prod = lec_padre(palabra, file_disponible); //busca descripción en file disponible
			codigos[i]=prod.codigo;
			//printf("debug: palabra= %s, desc= %s, codigo = %d\n", palabra, prod.descripcion, prod.codigo);
			suma+=prod.precio;
			// printear "tu pedido es ble y cuenta bla"
			a=0;
      memset(palabra,'\0',sizeof(palabra));
			i++;
		}
		else{	
			palabra[a] = ch;
			a++;
		}
	}while(!feof(ptr));
  
	fclose(ptr);
	return suma;
}