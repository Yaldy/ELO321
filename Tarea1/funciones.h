#ifndef __FUNCIONESH__
#define __FUNCIONESH__

void disponibles_print(char* file_disponible);

struct producto lec_hijo(int codin, char* file_disponible);

struct producto lec_padre(char descrin[], char* file_disponible);

int padre(int codigos[], char* file_pedidos, char* file_disponible);

#endif // __FUNCIONESH__
