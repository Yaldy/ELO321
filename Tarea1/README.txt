Tarea 1 ELO321 2022-2

Natalia Vega Quinteros ROL: 201904501-6
Oscar Villarroel Quezada ROL: 201804615-9

El programa consta de 3 archivos, main.c que contiene el código principal, funciones.c que contiene la implementación de las funciones utilizadas y funciones.h que contiene el prototipo de estas.

Se implementan 4 funciones además del main:
	1. lec_padre: lee el archivo "diponibles" y busca una descripción específica. Retorna struc con todos los datos del producto.
	2. padre: lee el archivo "pedidos", printea los pedidos con sus respectivos precios, crea array con codigos y suma el precio de todos los pedidos. Retorna int con la suma total.

	3. lec_hijo el archivo "diponibles" y busca un codigo específico. Retorna struc con todos los datos del producto encontrado.

	4. disponibles_print: printea productos disponibles.

La función main contiene la creación de los hijos con su códigio y la implementación del pipe.

Dentro de los archivos disponibles en la carpeta hay un makefile. La manera de ejecutarlo es:

	make

	make run

En caso de no funcionar el makefile, el programa se debe compilar y ejecutar de la siguiente forma

	gcc main.c funciones.c -o Tarea1

	./Tarea1 disponible.txt pedidos.txt

Si el nombre de los archivos .txt son distintos, modificar al momento de ejecutar

Suposiciones:
	- Los códigos de los productos son todos numeros mayores a cero.
	- El archivo de productos disponibles no tiene ningún salto de linea extra.
	- No hay espacio entre las comas y las palabra en ninguno de los dos archivos.
	- Case sensitive (mayusculas y minusculas se consideran letras distintas).
	- No se hacen más de 100 pedidos

Fuentes:
	- split: https://cplusplus.com/reference/cstring/strtok/
	- strcpy: https://www.tutorialspoint.com/c_standard_library/c_function_strcpy.htm
	- estructura general en el uso de pipe y fork: código ejemplo Miguel Andrade (Ayudante ELO321)