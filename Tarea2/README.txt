Tarea 2 ELO321
Natalia Vega Quinteros ROL: 201904501-6
Oscar Villarroel Quezada ROL: 201804615-9

Para compilar:
	$ gcc -pthread tarea2.c

Para ejecutar programa
	$ ./a.out <file>

donde <file> es el nombre del archivo que contiene los pedidos.

Ej:
	$ gcc -pthread tarea2.c
	$ ./a.out "pedidos.txt"
	

CONSIDERACIONES:
- Archivo de pedidos no debe terminar con un salto de linea.

- Impresora parte apagada.

- Para prender impresora se disminuyen la espera de 3seg a 3ms.