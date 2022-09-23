#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>

int main(){
	/*PADRE:
		1. lee archivo de pedidos y crea array
		2. suma el precio de todos los pedidos y los guarda
		3. imprime por pantalla cada producto con su precio
		4. leer e imprimir todos los productos disponibles
	*/
    pid_t of1,of2; //Creamos el pid para guardar el retorno del fork
    int tuberia[2];	//Creamos la variable para el pipe  
    pipe(tuberia);  //Creamos el pipe
    of1 = fork(); //Hacemos fork para crear el proceso hijo 1
	
    if (of1 < 0){ //Ocurrio un error
        printf("Fallo el fork");
        return 1;
    }
    else if (of1 == 0){ //Este es el proceso hijo 1
        //printf("Soy el proceso hijo 1, mi PID es %d\n",getpid());
        int buffer[2]; //Variable para lectura
        close(tuberia[1]); //Cerramos el lado de escritura del pipe
        int i = 0;
        while(1){
            read(tuberia[0],buffer,2*sizeof(int)); //Leemos datos del pipe, dos int cada vez
            i++;
            if (buffer[0]==0){ //Queremos leer 9 veces
                break;
            }
            //printf("hijo1: n1: %d y n2: %d, i= %d\n",buffer[0],buffer[1],i);
            usleep(5);
			// por aca tiene que decir quien es y que está entregando
        }
        return 0;
    }
	
    of2 = fork(); //Hacemos fork para crear el proceso hijo 2
    if (of2 < 0){ //Ocurrio un error
        printf("Fallo el fork");
        return 1;
    }
    else if (of2 == 0){ //Este es el proceso hijo 2
        //printf("Soy el proceso hijo 2, mi PID es %d\n",getpid());
        int buffer[2]; //Variable para lectura
        close(tuberia[1]); //Cerramos el lado de escritura del pipe
        int i = 0;
        while(1){
            read(tuberia[0],buffer,2*sizeof(int)); //Leemos datos del pipe, dos int cada vez
            i++;
            if (buffer[0]==0){ //Queremos leer 9 veces
                break;
            }
            //printf("hijo2: n1: %d y n2: %d, i= %d\n",buffer[0],buffer[1],i);
            usleep(5);
        }
        return 0;
    }
    //Proceso padre
	/*	manda array por el pipe
		espera a que los hijos terminen
		imprime suma
		*/
    int buffer[100]={1,10,1,30,2,10,5,1,5,1,4,2,5,10,0,10,0,11};		
    close(tuberia[0]); //Cerramos el lado de lectura del pipe
    write(tuberia[1],buffer,sizeof(int)*100); //Escribimos en el pipe los datos
    wait(NULL); //El padre espera a que termine el proceso hijo
    wait(NULL); //El padre espera a que termine el proceso hijo
    printf("Soy el padre, mi hijos eran el PID: %d y el PID: %d, yo soy el PID: %d\n",of1,of2,getpid());
	//imprimir suma
    return 0;    
}