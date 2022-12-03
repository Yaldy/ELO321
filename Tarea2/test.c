#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

typedef struct impresion{
	char type;
	int pages;
	char urgent;
}impresion;


int usr_srv[2];
int srv_imp[2];
int imp_srv[2];	


sem_t scons; //escribir en consola
sem_t sem1; //pipe user server
sem_t sem2; //pipe server impresora
sem_t sem3; // pipe imp server

void queue_init(impresion queue[]){
	int i=0;
	for(i;i<3;i++){
		queue[i].pages=-2;
	}
}

void *user(void* arg) // pagina 170 OS_Concepts
{   
	printf("Entra al user\n");
	int *arr = (int*) arg;
	//close(arr[0]);
	impresion prnt;
	FILE* ptr; // se declara puntero para arreglo donde se guarda lo que esta en el .txt
	char ch;
	char texto[20]; // array para guardar linea
	int a = 0;
	int i = 0;
	ptr = fopen("test.txt", "r");
	if (NULL == ptr) {
		printf("file can't be opened \n");
	}
	while(!feof(ptr)){
		ch = fgetc(ptr); // lee un caracter del archivo de texto
		texto[a] = ch;
		//if(texto[a] == '\n' || feof(ptr)){ // no funciona en aragorn
		if((ch > 47 && ch < 58) || (ch > 64 && ch < 90) || ch == ','){
			//printf("%c",ch);
		}
		else{
			// se guardan los datos ordenados en un struct

			prnt.type = strtok(texto,",")[0];
			prnt.pages = atoi(strtok(NULL,","));
			prnt.urgent = strtok(NULL,",")[0];
			
			//sem_wait(&scons);
			if(prnt.type == 'B' && prnt.urgent == 'N'){
				sem_wait(&scons);
				printf("User: Blanco y Negro, %d paginas, no urgente, tiempo de envio %d [us]\n",prnt.pages, 100*prnt.pages);
				sem_post(&scons);
				fflush(stdout);	
				usleep(100*prnt.pages);
			}
			else if(prnt.type == 'B' && prnt.urgent == 'S'){
				sem_wait(&scons);
				printf("User: Blanco y Negro, %d paginas, urgente, tiempo de envio %d [us]\n",prnt.pages, 100*prnt.pages);
				sem_post(&scons);
				fflush(stdout);	
				usleep(100*prnt.pages);
			}
			else if (prnt.type == 'C' && prnt.urgent == 'N'){
				sem_wait(&scons);
				printf("User: Color, %d paginas, no urgente, tiempo de envio %d [us]\n",prnt.pages, 200*prnt.pages);
				sem_post(&scons);
				fflush(stdout);	
				usleep(200*prnt.pages);
			}
			else if (prnt.type == 'C' && prnt.urgent == 'S'){
				sem_wait(&scons);
				printf("User: Color, %d paginas, urgente, tiempo de envio %d [us]\n",prnt.pages, 200*prnt.pages);
				sem_post(&scons);	
				fflush(stdout);	
				usleep(200*prnt.pages);
			}
			//sem_post(&scons);
			
			memset(texto, '\0', sizeof(texto));
			a = -1;
			
			//sem_wait(&mutex);

			write(arr[1], &prnt, sizeof(impresion));
			sem_post(&sem1);
			//printf("user :%d\n", prnt.pages);
			//usleep(1000);
    	}
		a++;
	}
	prnt.pages =-1;

	//wait
    //sem_wait(&mutex);
    //critical section
    write(arr[1], &prnt, sizeof(impresion));
    sem_post(&sem1);
	//signal
	
    //printf("Just Exiting...\n");
    
    
}

void *printer(void* arg) // pagina 170 OS_Concepts
{  
	int *arr = (int*) arg;
	//close(arr[1]);
	impresion prnt[3];
	
	
	printf("thread creado..\n");
	//wait
    
    printf("Entered printer\n");
    
    do{
    	
    	int cprim = 0; //contador para ver si entra por primera vez
    	int sem2Val;
    	sem_getvalue(&sem2,&sem2Val);
    	printf("%d\n",sem2Val);
    	if(sem2Val==0)
	    	while(1){
	    		if(cprim==0){
	    			sem_wait(&scons);
					printf("Apagada\n");
					sem_post(&scons);
					
				}
				usleep(50);
				cprim++;
				sem_getvalue(&sem2,&sem2Val);
				if(sem2Val>0){
					int o = 3;
					
					for(o;o>0;o--){
						usleep(100);
						sem_wait(&scons);
						printf(" impresora prendiendo en: %d\n",o);	
						sem_post(&scons);	
						fflush(stdout);					
					}
					break;
				}
				
			}
		cprim=0;
		
		
    	sem_wait(&sem2);
		read(arr[0], prnt, 3*sizeof(impresion));
		//printf("%d\n",a);
		
		//sem_post(&mutex);
		if(prnt[0].pages !=-1 ){
			int i=0;
			//?? aca o solo en printf
			for(i;i<3;i++){
				if (prnt[i].pages!=-2){
					usleep(150*prnt[i].pages);
					sem_wait(&scons);
					printf("Impresora: Finalizado, el pedido tardo %d us\n",150*prnt[i].pages);
					sem_post(&scons);
					fflush(stdout);
				//	write(imp_srv[1], &prnt[i], sizeof(impresion));
				}
			}
			
			
		}
	}while(prnt[0].pages !=-1);
    
	
    //critical section
	
    //signal
    printf("Just Exiting...\n");
    
    
}

int main()
{
	/*
	int usr_srv[2];
	int srv_imp[2];
	int imp_srv[2];	
	*/
	
	pipe(usr_srv);
	pipe(srv_imp);
	pipe(imp_srv);
	
	impresion arg;
	impresion plisto;
	sem_init(&scons, 0, 1);
    sem_init(&sem1, 0, 0);
	sem_init(&sem2, 0, 0);
	//sem_init(&mutex, 0, 0);


	

	pthread_t t1,t2;
	
	
    pthread_create(&t1,NULL,user,(void*) &usr_srv);
    usleep(100);
    pthread_create(&t2,NULL,printer,(void*) &srv_imp);
    


	//close(usr_srv[1]);
	//close(srv_imp[0]);
	impresion queue[3];
	queue_init(queue);
	int i =0;
	do{
		sem_wait(&sem1);
		read(usr_srv[0], &arg, sizeof(impresion));
		
		//sem_post(&mutex);
		if(arg.pages >0 ){
			/*if(arg.type=='B'){
				ByN++;
			}
			else if(arg.type=='C'){
				CLR++;
			}*/
			queue[i]=arg;
			if (i==2 || arg.urgent=='S'){
				//mandar cola a impresora
				//sem_wait(&mutex);
				write(srv_imp[1], queue, 3*sizeof(impresion));
				sem_post(&sem2);
				i=0;
				queue_init(queue);
			}
			//else if(){}
			else{
				i++;
			}
			sem_wait(&scons);
			printf("server: %d\n", arg.pages);
			sem_post(&scons);
		}
		else{
			//sem_wait(&mutex);
			write(srv_imp[1], queue, 3*sizeof(impresion));
			sem_post(&sem2);
			//sem_post(&mutex);
		}
		/*
		read(imp_srv[0], &plisto, sizeof(impresion));
		
		/*
		if(plisto.pages==-1){
			break;
		}
		if(plisto.type == 'B'){
			sem_wait(&scons);
			printf("Server: Pediodo blanco y negro, %d paginas esta listo. Monto a pagar:%d\n",plisto.pages, 10*plisto.pages);
			sem_post(&scons);
			fflush(stdout);	
		}
		else if (plisto.type == 'C'){
			sem_wait(&scons);
			printf("Server: Pedidio color, %d paginas esta listo. Monto a pagar: %d\n",plisto.pages, 20*plisto.pages);
			sem_post(&scons);
			fflush(stdout);	
		}*/

	}while(arg.pages >0 );
	queue[0].pages=-1;
	write(srv_imp[1], queue, 3*sizeof(impresion));
	sem_post(&sem2);
	
    pthread_join(t1,NULL);
    pthread_join(t2,NULL);
    sem_destroy(&scons);
    sem_destroy(&sem1);
    sem_destroy(&sem2);
    //sem_destroy(&sem3);
	
/*	
	while(imprimir = 1)
		pthread_create(printer) // se crea thread para una porcion de la cola de impresion
		
		pthread_join // espera a que termine la impresion
		if(ultimo elemento = 1)	// si es el ultimo elemento se sale
			break
*/

	//printf("%d\n", arg[1].pages);
    return 0;
}
