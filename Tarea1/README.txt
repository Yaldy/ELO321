Tarea 1 ELO321 2022-2

Natalia Vega Quinteros ROL: 201904501-6
Oscar Villarroel Quezada ROL: 201804615-9

El programa se debe compilar y ejecutar de la siguiente forma

	gcc main.c funciones.c -o Tarea1

	./Tarea1 disponible.txt pedidos.txt

Si el nombre de los archivos .txt son distintos, modificar al momento de ejecutar

Suposiciones:
	- los código de los productos son todos numeros mayores a cero.
	- el archivo de productos disponibles no tiene ningún salto de linea extra.
	- no hay espacio entre las comas y las palabra en ninguno de los das archivos.
	- case sensitive (mayusculas y minusculas se consideran letras distintas).

Fuentes:
	- split: https://cplusplus.com/reference/cstring/strtok/
	- strcpy: https://www.tutorialspoint.com/c_standard_library/c_function_strcpy.htm
	- estructura general en el uso de pipe y fork: código ejemplo Miguel Andrade (Ayudante ELO321)