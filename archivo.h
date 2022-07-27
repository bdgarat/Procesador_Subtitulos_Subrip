#ifndef _T_ARCHIVO_H
#define _T_ARCHIVO_H
#include "list.h"
#include "list_iterator.h"
void descargarLista(FILE *f, t_list *lista);
Formato cargarDesdeArchivo(FILE *f);
int CrearListaFormato (FILE *f, t_list *lista);
void agregarEnOrden (t_list *lista, Formato ins);
void quitar (t_list *lista, int indice);
#endif