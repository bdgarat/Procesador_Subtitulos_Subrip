#ifndef _T_VALIDAR_H
#define _T_VALIDAR_H
#include "list.h"
#include "list_iterator.h"
int tiempocorto (t_list lista);
int tiempolargo (t_list lista);
int textolargo (t_list lista);
int demcar (t_list lista);
int demlin (t_list lista);
int pocaseparacion(t_list lista);
int subsolapados(t_list lista);
int inicioInvalido(t_list lista);
int numConsecutivos(t_list lista);
void validar(t_list lista);
#endif