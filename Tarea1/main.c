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
  int suma;
  int i;
  char* archivo_disp = argv[1];
  char* archivo_ped = argv[2];
  //printf("\n%s   %s\n\n",archivo_disp,archivo_ped);
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
        //printf("Soy el repartidor 1, mi PID es %d\n",getpid());
        int codigo; //Variable para lectura
        close(tuberia[1]); //Cerramos el lado de escritura del pipe
        int i = 0;
		    struct producto prod; //creear variable struct
        while(1){
            read(tuberia[0],&codigo,sizeof(int)); //Leemos datos del pipe
            //printf("el codigo es %d\n",codigo1);
            i++;
            if (codigo==0){ //Queremos leer 9 veces
                break;
            }
            //printf("hijo1: n1: %d y n2: %d, i= %d\n",buffer[0],buffer[1],i);
			      prod = lec_hijo(codigo,archivo_disp);
            usleep(prod.tiempo);
			      // por aca tiene que decir quien es y que está entregando
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
        //printf("Soy el repartidor 2, mi PID es %d\n",getpid());
        int codigo; //Variable para lectura
        close(tuberia[1]); //Cerramos el lado de escritura del pipe
        int i = 0;
		    struct producto prod; //creear variable struct
        while(1){
            read(tuberia[0],&codigo,sizeof(int)); //Leemos datos del pipe
            //printf("el codigo es %d\n",codigo2);
            i++;
            if (codigo==0){ //Queremos leer 9 veces
                //printf("bi");
                break;
            }
            //printf("hijo1: n1: %d y n2: %d, i= %d\n",buffer[0],buffer[1],i);
			      prod = lec_hijo(codigo,archivo_disp);
            usleep(prod.tiempo);
			      // por aca tiene que decir quien es y que está entregando
			      printf("Soy el repartidor 2 y entrego %s.\n", prod.descripcion);
        }
        return 0;
    }
    //Proceso padre
	/*	manda array por el pipe
		espera a que los hijos terminen
		imprime suma
		*/
	// crear arreglo de codigos (int)
	// crear variables con el nombre d elos archivos (argv[])
	
	  suma = padre(codigos, archivo_ped, archivo_disp);
	  printf("\n");
    //int buffer[20]={3,4,1,2,6,3,1,5,4,2};
    close(tuberia[0]); //Cerramos el lado de lectura del pipe
    //write(tuberia[1],codigos,sizeof(int)*100); //Escribimos en el pipe los datos
    write(tuberia[1],codigos,sizeof(codigos)); //Escribimos en el pipe los datos
    wait(NULL); //El padre espera a que termine el proceso hijo
    wait(NULL); //El padre espera a que termine el proceso hijo
    printf("\n");
    printf("El total recaudado es $%d\n", suma);
    //printf("Soy el padre, mi hijos eran el PID: %d y el PID: %d, yo soy el PID: %d\n",of1,of2,getpid());
	//imprimir suma despues de que os dos hijois terminen (wait x2)
    
    //printf("Que le vaya bn :3\n");
    return 0;  
}

