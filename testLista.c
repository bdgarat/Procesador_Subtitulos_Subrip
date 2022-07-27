#include "list.h"
#include "tiempo.h"
#include <stdio.h>

int main(){
	t_list l;
	list_create(&l);
	
	printf("VACIA %d\n", list_is_empty(l));
	
	t_data d;
	d.indice = 1;
	convertirATiempo(&d.tiempoinicio, 3661999);
	convertirATiempo(&d.tiempofin, 3671999);
	d.texto=NULL; 
	
	t_data c;
	c.indice = 2;
	convertirATiempo(&c.tiempoinicio, 3661999);
	convertirATiempo(&c.tiempofin, 3671999);
	c.texto=NULL;
	
	t_data b;
	b.indice = 3;
	convertirATiempo(&b.tiempoinicio, 3661999);
	convertirATiempo(&b.tiempofin, 3671999);
	b.texto=NULL;

	list_add(&l,  c);
	list_add(&l,  d);
	
	t_list l1 = l;
	while (l1 != NULL){
		printf("	%d ",l1->data.indice);
		l1 = l1->next;
	}
	printf("\n");
	printf("\nFIND	%d \n" ,  list_find(l, c)); //ERROR EN LA COMPARACION PORQUE NO PREVEEN QUE SE PUEDEN TENER TODOS LOS DATOS CARGADOS.
	printf("\n");
	printf("DELETE	%d \n", list_delete(&l, d).indice); //ERROR PORQUE EN LA ITERACION SE USA *l Y SOLO LO ENCUENTRA SI ES EL PRIMERO.
	printf("\n");
	l1 = l;
	while (l1 != NULL){
		printf("	%d ",l1->data.indice);
		l1 = l1->next;
	}
	printf("VACIA %d\n", list_is_empty(l));	
	printf("\nDELETE	%d ", list_delete(&l, b).indice); //ERROR PORQUE NO CONTEMPLA QUE PUEDE NO EXISTIR.
	printf("\n");
	//l1 = l;
	//while (l1 != NULL){
	//	printf("	%d ",l1->data.indice);
	//	l1 = l1->next;
	//}
	list_add_pos(&l, b, 0); //NO FUNCIONA!!!
	l1 = l;
	while (l1 != NULL){
		printf("	%d ",l1->data.indice);
		l1 = l1->next;
	}
	printf("\n");
	list_free(&l);
	printf("\nVACIA %d\n", list_is_empty(l));
	return 0;
}