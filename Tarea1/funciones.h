#ifndef __FUNCIONES__
#define __FUNCIONES__

struct producto{
  char descripcion[30];
  int precio;
  int codigo;
  int tiempo;
};

// Función de lectura del padre
struct producto lec_padre(char descrin[], char* file_disponible);

struct producto lec_hijo(int codin, char* file_disponible);

int padre(int codigos[], char* file_pedidos, char* file_disponible)

#endif // __FUNCIONES__
