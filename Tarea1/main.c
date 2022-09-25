#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define DISPONIBLE "disponible.txt"
#define PEDIDOS "pedidos.txt"

struct producto{
  char descripcion[30];
  int precio;
  int codigo;
  int tiempo;
};

int main(){
	/*PADRE:
		1. lee archivo de pedidos y crea array
		2. suma el precio de todos los pedidos y los guarda
		3. imprime por pantalla cada producto con su precio
		4. leer e imprimir todos los productos disponibles
	*/
	//extraer datos de argc y argv
	
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
        int codigo1; //Variable para lectura
        close(tuberia[1]); //Cerramos el lado de escritura del pipe
        int i = 0;
		struct producto prod; //creear variable struct
        int r=0;//return read
        while(1){
            r = read(tuberia[0],&codigo1,sizeof(int)); //Leemos datos del pipe
            //printf("el codigo es %d\n",codigo1);
            i++;
            if (r==0){ //Queremos leer 9 veces
                break;
            }
            //printf("hijo1: n1: %d y n2: %d, i= %d\n",buffer[0],buffer[1],i);
			prod = lec_hijo(codigo1,DISPONIBLE);
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
        int codigo2; //Variable para lectura
        close(tuberia[1]); //Cerramos el lado de escritura del pipe
        int i = 0;
		struct producto prod; //creear variable struct
        int r=0;//return read
        while(1){
            r = read(tuberia[0],&codigo2,sizeof(int)); //Leemos datos del pipe
            //printf("el codigo es %d\n",codigo2);
            i++;
            printf("%d\n",r);
            if (r==0){ //Queremos leer 9 veces
                printf("bi");
                break;
            }
            //printf("hijo1: n1: %d y n2: %d, i= %d\n",buffer[0],buffer[1],i);
			prod = lec_hijo(codigo2,DISPONIBLE);
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
    int buffer[20]={3,4,1,2,6,3,1,5,4,2};
    close(tuberia[0]); //Cerramos el lado de lectura del pipe
    write(tuberia[1],buffer,sizeof(int)*20); //Escribimos en el pipe los datos
    wait(NULL); //El padre espera a que termine el proceso hijo
    wait(NULL); //El padre espera a que termine el proceso hijo
    printf("Soy el padre, mi hijos eran el PID: %d y el PID: %d, yo soy el PID: %d\n",of1,of2,getpid());
	//imprimir suma despues de que os dos hijois terminen (wait x2)
    return 0;    
}