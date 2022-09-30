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

int main(int argc, char *argv[]){
	int codigos[100];
	
	//inicializar arreglo para evitar problemas
	int ini = 0;
	for (ini;ini < 100; ini++){
		codigos[ini] = 0;
	}
	
	int suma;
	//int i;
	char* archivo_disp = argv[1];
	char* archivo_ped = argv[2];
	disponibles_print(archivo_disp);
	printf("\n");
    pid_t of1,of2; //Creamos el pid para guardar el retorno del fork
    int tuberia[2];	//Creamos la variable para el pipe  
    pipe(tuberia);  //Creamos el pipe
    of1 = fork(); //Hacemos fork para crear el proceso hijo 1
	
    if (of1 < 0){ //Ocurrio un error
        printf("Fallo el fork");
        return 1;
    }
    else if (of1 == 0){ //Este es el proceso hijo 1
        int codigo; //Variable para lectura
        close(tuberia[1]); //Cerramos el lado de escritura del pipe
        int i = 0;
		struct producto prod; //creear variable struct
        while(1){
            read(tuberia[0],&codigo,sizeof(int)); //Leemos datos del pipe
            i++;
            if (codigo==0){ //condicion para salir del while
                break;
            }
            prod = lec_hijo(codigo,archivo_disp);
            usleep(prod.tiempo);
			printf("Soy el repartidor 1 y entrego %s.\n", prod.descripcion);
        }
        return 0;
    }
	
    of2 = fork(); //Hacemos fork para crear el proceso hijo 2
    if (of2 < 0){ //Ocurrio un error
        printf("Fallo el fork");
        return 1;
    }
    else if (of2 == 0){ //Este es el proceso hijo 2
        int codigo; //Variable para lectura
        close(tuberia[1]); //Cerramos el lado de escritura del pipe
        int i = 0;
		struct producto prod; //creear variable struct
        while(1){
            read(tuberia[0],&codigo,sizeof(int)); //Leemos datos del pipe
            i++;
            if (codigo==0){
                break;
            }
			prod = lec_hijo(codigo,archivo_disp);
            usleep(prod.tiempo);
			printf("Soy el repartidor 2 y entrego %s.\n", prod.descripcion);
        }
        return 0;
    }
	
    //Proceso padre
	suma = padre(codigos, archivo_ped, archivo_disp);
	printf("\n");
    close(tuberia[0]); //Cerramos el lado de lectura del pipe
    write(tuberia[1],codigos,sizeof(codigos)); //Escribimos en el pipe los datos
    wait(NULL); //El padre espera a que termine el proceso hijo 1
    wait(NULL); //El padre espera a que termine el proceso hijo 2
    printf("\n");
    printf("El total recaudado es $%d.\n", suma);
    return 0;  
}

