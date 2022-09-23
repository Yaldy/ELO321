#include <stdio.h>
#include

int padre(){//arg puntero al arreglo de codigos
	FILE* ptr; // se declara puntero para arreglo donde se guarda lo que esta en el .txt
	char ch;
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
		if(ch==','){
			a=0;
		}
			
		texto[a] = ch;
		a++;	
	}
}

/*
al principio
	1. crear variable de suma de precios
dentro de lectura de archivo pedidos
	1. llamar a lec_padre para que retore la estructura de lo pedido
	2. extraer precio y sumarlo
	3. extraer codigo y agregarlo al arreglo
al final 
	1. retornar suma
*/