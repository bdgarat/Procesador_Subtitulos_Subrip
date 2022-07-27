#include "list.h"
#include "tiempo.h"
#include <stdlib.h>


short compararFormato (Formato fcomp1, Formato fcomp2){
  short cmpindice = fcomp1.indice == fcomp2.indice;
  short cmptiempoinicio = convertirAMilis(fcomp1.tiempoinicio) == convertirAMilis(fcomp2.tiempoinicio);
  short cmptiempofin = convertirAMilis(fcomp1.tiempofin) == convertirAMilis(fcomp2.tiempofin);
  short cmptexto = 0;
  if (fcomp1.texto != NULL && fcomp2.texto != NULL){
    cmptexto = strcmp(fcomp1.texto, fcomp2.texto);
  }
  return (cmpindice && cmptiempoinicio && cmptiempofin && !cmptexto);
}


void list_create(t_list *l){
  *l = NULL;
}

short list_find(t_list l, t_data e){
  while(l)
  {
    if (compararFormato(l->data, e)) return 1;
    l = l->next;
  }
  return 0;
}

short list_is_empty(t_list l){
  return l == NULL;
}

t_data list_add(t_list *l, t_data e){
  t_list_node *node = malloc(sizeof(t_list_node));
  node->data = e;
  node->next = NULL;
  if (*l == NULL) {
    *l = node;
    (*l)->ult = node;
  } else {
    (*l)->ult->next = node;
    (*l)->ult = (*l)->ult->next;
  }
  return e;
}

t_data  list_delete(t_list *l, t_data e){
  t_list_node *prev = NULL, *node = *l;
  while(node != NULL && !compararFormato(node->data, e)) {
    prev = node;
    node = node->next;
  }
  if (node == NULL){
    Formato faux;
    faux.indice = -1;
    return faux;
  } else {
    if (prev == NULL) *l = node->next;
    else
    {
      prev->next = node->next;
    }
    free(node);
  }
  return e;
}

/* Libera las estructuras internas usadas por este tipo de dato */
void list_free(t_list *l) {
t_list_node *node = *l;
  while(node) {
    t_list_node *aux;
    aux = node;
    node = node->next;
    free(aux->data.texto);
    free(aux);
  }
  *l=NULL;
}

void list_add_pos(t_list *l, t_data e, int pos){
  t_list_node *node = malloc(sizeof(t_list_node));
  node->data = e;
  node->next = NULL;
  if (*l == NULL) *l = node;
  else {
    t_list_node *ant = *l;
    t_list_node *act = *l;
    int aux = 0;
    while (act && aux < pos){
      ++aux;
      ant = act;
      act = act->next;
    }
    if (aux == 0){
      node->next = *l;
      *l = node;
    } else {
      ant->next = node;
      node->next = act;
    }
  }
}


