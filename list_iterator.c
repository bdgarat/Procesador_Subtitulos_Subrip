#include "list_iterator.h"
#include <stdio.h>

t_iterator list_iterator_init(t_list l){
  t_iterator i;
  i.list = l;
  i.current = l;
  i.prev = l;
  i.pos = 0;
  return i;
}

void list_iterator_next(t_iterator *i){
  i->prev = i->current;
  i->current = i->current->next;
  ++i->pos;
}

t_data list_iterator_data(t_iterator i){
  return i.current->data;
}

short list_iterator_end(t_iterator i){
  return i.current == NULL;
}

int list_iterator_pos(t_iterator i){
	return i.pos;
}

t_list_index list_iterator_current(t_iterator i){
  return  i.current;
}

t_list_index list_iterator_previous(t_iterator i){
  return i.prev;
}
