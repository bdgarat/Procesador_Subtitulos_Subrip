#ifndef _T_LIST_H
#define _T_LIST_H
#include "tiempo.h"
#include <string.h>


typedef struct {
	int indice;
	Tiempo tiempoinicio;
	Tiempo tiempofin;
	char *texto;
} Formato;

typedef Formato t_data;

typedef struct t_list_node {
  struct t_list_node *next;
  struct t_list_node *ult;
  t_data data;
} * t_list;

typedef struct t_list_node t_list_node;

/* Compara si los 2 parametros de Formato (fcomp1 y fcomp2) son iguales */
short compararFormato (Formato fcomp1, Formato fcomp2);

/* Crea una nueva lista, que puede usarse de inmediato */
void    list_create(t_list *);

/* Busca eun elemento en la lista y retorna verdadero si existe */
short   list_find(t_list, t_data);

/* Devuelve verdadero si la lista está vacía */
short   list_is_empty(t_list);

/* Agrega un elemento a la lista. Luego lo retorna */
t_data  list_add(t_list *, t_data );

/* Elimina un elemento de la lista y luego lo retorna */
t_data  list_delete(t_list *, t_data);

/* Libera las estructuras internas usadas por este tipo de dato */
void    list_free(t_list *);

/* Agrega un elemento a la lista en una posicion y luego retorna la posicion en la que se agrego */
void    list_add_pos(t_list *, t_data, int);

#endif

