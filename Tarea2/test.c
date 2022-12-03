/*ya tiene while1, algo queda abierto*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

/*Estructura con información de pedido*/
typedef struct impresion{
	char type;
	int pages;
	char urgent;
}impresion;

/*Declaración de variables para pipes*/
int usr_srv[2];
int srv_imp[2];
int imp_srv[2];	

/*Declaración de semáforos*/
sem_t scons; //para escribir en consola
sem_t sem1; //para pipe user server
sem_t sem2; //para pipe server impresora
sem_t sem3; //para pipe imp server

/*Función para llenar cola con valores inválidos*/
void queue_init(impresion queue[]){
	int i=0;
	for(i;i<3;i++){
		queue[i].pages=-2;
	}
}

/*Función de thread que lee archivo de pedidios y los envia a proceso servidor (main)*/
void *user(void* arg) 
{   
	printf("Entra al thread user...\n");
	int *arr = (int*) arg; //casteo de argumento de entrada para pipe
	
	//close(arr[0]);
	
	impresion prnt;//estructura para guardar datos extraidos de archivo
	
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
			//Para no tener problemas con editor de texto
		}
		else{
			// se guardan los datos ordenados en un struct
			prnt.type = strtok(texto,",")[0];
			prnt.pages = atoi(strtok(NULL,","));
			prnt.urgent = strtok(NULL,",")[0];
			
			//Impresión por pantalla del pedido
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
			
			//rellena variable texto de '\0'
			memset(texto, '\0', sizeof(texto));
			a = -1;
			
			//manda estructura con pedido recibido
			write(arr[1], &prnt, sizeof(impresion));
			sem_post(&sem1);
			
    	}
		a++;
	}
	
	
	prnt.pages =-1;//valor invalido para avisar fin de los pedidos

	//envia estructura indicando el final de los pedidos
    write(arr[1], &prnt, sizeof(impresion)); //escribe en pipe user-server
    sem_post(&sem1);//libera semaforo para que se pueda leer el pipe
	
    printf("Thread User termino...\n");
    
    
}

/*Función de thread que lee la cola de pedidos desde el servidor e imprime por pantalla tiempo de impresión*/
void *printer(void* arg)
{  
	printf("Entra al thread Printer...\n");
	int *arr = (int*) arg; //casteo de argumento de entrada para pipe
	
	//close(arr[1]);
	impresion prnt[3];//estructura para guardar datos extraidos de archivo
	impresion fin;

    do{
    	int cprim = 0; //contador para ver si entra por primera vez
    	int sem2Val; //variable con valor del semaforo
    	int sem3Val; //variable con valor del semaforo
		sem_getvalue(&sem2,&sem2Val);//guarda valor del semaforo
    	//printf("%d\n",sem2Val);
    	if(sem2Val==0)
	    	while(1){//espera ocupada
	    		if(cprim==0){//si recién entró al while(1) informa que se apagó
	    			sem_wait(&scons);
					printf("Impresora: Apagada\n");
					sem_post(&scons);
					
				}
				usleep(50);
				cprim++;
				sem_getvalue(&sem2,&sem2Val);
				if(sem2Val>0){ //para prender impresora
					int o = 3;
					
					for(o;o>0;o--){
						usleep(1000);//1 seg es mucha espera
						sem_wait(&scons);
						printf("impresora prendiendo en: %d\n",o);	
						sem_post(&scons);	
						fflush(stdout);					
					}
					break;//sale de espera ocupada
				}
				
			}
		cprim=0;
		
		
    	sem_wait(&sem2);//blolquea semaforo hasta que pueda leer el pipe
		read(arr[0], prnt, 3*sizeof(impresion)); //lee pipe server-printer
		//printf("%d\n",a);
		
		//sem_post(&mutex);
		if(prnt[0].pages !=-1 ){ //si no es estructura final,entra
			int i=0;
			//?? aca o solo en printf
			for(i;i<3;i++){
				if (prnt[i].pages!=-2){//si no es entructura de relleno, entra
					usleep(150*prnt[i].pages);
					sem_wait(&scons);
					printf("Impresora: Finalizado, el pedido tardo %d us\n",150*prnt[i].pages);
					sem_post(&scons);
					fflush(stdout);
					write(imp_srv[1], &prnt[i], sizeof(impresion));
					sem_post(&sem3);
					sem_getvalue(&sem3,&sem3Val);//guarda valor del semaforo
					//printf("%d\n",sem3Val);
				}
			}
			
			
		}
	}while(prnt[0].pages !=-1);
    
    /*envia estructura indicando el final de los pedidos*/
    fin.pages =-1;//valor invalido para avisar fin de los pedidos
	write(imp_srv[1], &fin, sizeof(impresion));
	sem_post(&sem3);
    printf("Thread Printer termino...\n");
    
    
}

int main()
{
	/*
	int usr_srv[2];
	int srv_imp[2];
	int imp_srv[2];	
	*/
	int flags1=1;
	/*inicialización de pipes*/
	pipe(usr_srv);
	pipe(srv_imp);
	pipe(imp_srv);
	
	impresion arg; //para guadar lo que recibe del user
	impresion plisto; //para guardar lo que recibe de la impresora
	
	/*inicialización de semáforos*/
	sem_init(&scons, 0, 1);
    sem_init(&sem1, 0, 0);
	sem_init(&sem2, 0, 0);
	sem_init(&sem3, 0, 0);
	
	int sem3Val;

	
	/*variables para los threads*/
	pthread_t t1,t2;
	
	/*crea los threads*/
    pthread_create(&t1,NULL,user,(void*) &usr_srv);
    usleep(100);
    pthread_create(&t2,NULL,printer,(void*) &srv_imp);
    


	//close(usr_srv[1]);
	//close(srv_imp[0]);
	//close(imp_srv[1]);
	
	impresion queue[3];//cola para enviar a impresora
	queue_init(queue); //rellena cola de valores no validos
	
	int i =0;
	while(1){
		if (flags1){
			sem_wait(&sem1);
			read(usr_srv[0], &arg, sizeof(impresion)); //lee pipe usr_srv
			
			if(arg.pages >0 ){
			
				queue[i]=arg;
				if (i==2 || arg.urgent=='S'){
					/*mandar cola a impresora*/
					write(srv_imp[1], queue, 3*sizeof(impresion));// escribe en pipe srv-imp
					sem_post(&sem2);
					i=0;
					queue_init(queue);
				}
				//else if(){}
				else{
					i++;
				}
				
			}
			else{
				write(srv_imp[1], queue, 3*sizeof(impresion));
				sem_post(&sem2);
				/*envia estructura indicando el final de los pedidos*/
				queue[0].pages=-1;
				write(srv_imp[1], queue, 3*sizeof(impresion));
				sem_post(&sem2);
				flags1=0;
			}
		}
		sem_getvalue(&sem3,&sem3Val);
		//printf("%d\n",sem3Val);
		if(sem3Val>0){
			read(imp_srv[0], &plisto, sizeof(impresion));
			
			if(plisto.pages==-1){
				break;
			}
			
			if(plisto.type == 'B'){
				sem_wait(&scons);
				printf("Server: Pedido blanco y negro, %d paginas esta listo. Monto a pagar:%d\n",plisto.pages, 10*plisto.pages);
				sem_post(&scons);
				fflush(stdout);	
			}
			else if (plisto.type == 'C'){
				sem_wait(&scons);
				printf("Server: Pedido color, %d paginas esta listo. Monto a pagar: %d\n",plisto.pages, 20*plisto.pages);
				sem_post(&scons);
				fflush(stdout);	
			}
			sem_trywait(&sem3);
			//printf("pasa\n");
		}

	}
	
	/*envia estructura indicando el final de los pedidos
	queue[0].pages=-1;
	write(srv_imp[1], queue, 3*sizeof(impresion));
	sem_post(&sem2);*/
	
	/*termina los threads*/
    pthread_join(t1,NULL);
    pthread_join(t2,NULL);
    
    /*elimina los semaforos*/
    sem_destroy(&scons);
    sem_destroy(&sem1);
    sem_destroy(&sem2);
    //sem_destroy(&sem3);
	printf("Proceso servidor termino\n");
    return 0;
}
