#ifndef _T_LIST_ITERATOR_H
#define _T_LIST_ITERATOR_H

/* El tipo de la lista */
#include "list.h"
typedef t_list_node * t_list_index;

typedef struct {
  t_list list;
  t_list_index current;
  t_list_index prev;
  int pos;
} t_iterator;

/* Inicializa un iterador */
t_iterator    list_iterator_init(t_list);

/* Avanza un elmento en la lista (debe checkear si no se esta en NULL) */
void          list_iterator_next(t_iterator*);

/* Retorna el elemento actual en la lista (debe checkear si no se esta en NULL) */
t_data        list_iterator_data(t_iterator);

/* Indica si termino el recorrido */
short         list_iterator_end(t_iterator);

/* Indica la cant de avances en el iterador */
int           list_iterator_pos(t_iterator);

/* Retorna el puntero de la posicion actual de la lista */
t_list_index list_iterator_current(t_iterator i);

/* Retorna el puntero de la posicion anterior de la lista */
t_list_index list_iterator_previous(t_iterator i);

#endif

