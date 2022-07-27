#include "archivo.h"
#include "tiempo.h"
#include <stdio.h>
#include <stdlib.h>

void descargarLista(FILE *f, t_list *lista) {
  t_iterator it = list_iterator_init(*lista);
  Formato fact;
  while(!list_iterator_end(it)){
    fact = list_iterator_data(it);
  	fprintf(f, "%d\n", fact.indice);
  	fprintf(f, "%d:%.2d:%.2d,%.3d --> %.2d:%.2d:%.2d,%.3d\n", fact.tiempoinicio.horas, fact.tiempoinicio.minutos, fact.tiempoinicio.segundos, fact.tiempoinicio.milesimas, fact.tiempofin.horas, fact.tiempofin.minutos, fact.tiempofin.segundos, fact.tiempofin.milesimas);
  	fprintf(f, "%s", fact.texto);
    list_iterator_next(&it);
  }
  list_free(lista);
}

Formato cargarDesdeArchivo(FILE *f){
  Formato faux;
  int check = fscanf(f, "%d\n", &faux.indice);
  if (check != 1){
  	faux.indice = -1;
  	return faux;
  }
  if (!feof(f)) {
		check = fscanf(f,"%d:%d:%d,%d --> %d:%d:%d,%d\n", &faux.tiempoinicio.horas, &faux.tiempoinicio.minutos, &faux.tiempoinicio.segundos, &faux.tiempoinicio.milesimas, &faux.tiempofin.horas, &faux.tiempofin.minutos, &faux.tiempofin.segundos, &faux.tiempofin.milesimas);
		if (check != 8){
  			faux.indice = -1;
  			return faux;
  		}
		size_t cantaux = 0;
		size_t canttotal= 0;
		size_t cantidad = 10;
		char *buffer;
		char *ptr;
		buffer = malloc(cantidad * sizeof(char));
		cantaux = getline(&buffer, &cantidad, f);
		if (cantaux == -1) {
			faux.indice = -1;
  			return faux;
  		}		
		canttotal = canttotal + cantaux;
		faux.texto = malloc(sizeof(char) * canttotal);
		strcpy(faux.texto, buffer);
		if (cantaux != 1) {
			cantaux = getline(&buffer, &cantidad, f);
			canttotal = canttotal + cantaux;
			while (cantaux != 1 && cantaux != -1) {
				ptr = realloc(faux.texto, canttotal);
				if (ptr != NULL) {
					faux.texto = ptr;
				}
				strcat(faux.texto, buffer);
				cantaux = getline(&buffer, &cantidad, f);
				canttotal = canttotal + cantaux;
			}
		}
		ptr = realloc(faux.texto, canttotal+1);
		if (ptr != NULL) {
			faux.texto = ptr;
		}
		strcat(faux.texto, buffer);
		free(buffer);
  }
	return faux; 
}

int CrearListaFormato (FILE *f, t_list *lista){
  list_create(lista);
  Formato faux = cargarDesdeArchivo(f);
  while (!feof(f)){
  		if (faux.indice == -1){
			return 1;
  		}
		list_add(lista, faux);
		faux = cargarDesdeArchivo(f);
  }
  return 0;
}

void agregarEnOrden (t_list *lista, Formato ins){
	char * fintexto = malloc(sizeof(char)*3);
	fintexto[0] = '\n';
	fintexto[1] = '\n';
	fintexto[2] = '\0';
	strcat(ins.texto, fintexto);
	t_list laux = *lista;
	t_list lant = *lista;
	Formato faux = laux->data;
  	int fauxmilis = convertirAMilis(faux.tiempoinicio);
  	int insmilis = convertirAMilis(ins.tiempoinicio);
	while (fauxmilis < insmilis && laux){
	  lant = laux;
	  laux = laux->next;
	  if (laux){
  	  	faux = laux->data;
       	  	fauxmilis = convertirAMilis(faux.tiempoinicio);
	  }
	}
	if (laux) {
 		ins.indice = faux.indice;
	} else {
		ins.indice = faux.indice + 1;
	}
  	t_list nuevo;
  	list_create(&nuevo);
  	list_add(&nuevo, ins);
  	if (laux == *lista) {
    	  nuevo->next = *lista;
	  *lista = nuevo;
	} else {
	  nuevo->next = laux;
	  lant->next = nuevo;
	}
    	while (nuevo->next){
          nuevo->next->data.indice++;
          nuevo = nuevo->next;
     	} 
    }

void quitar (t_list *lista, int inddel) {
	t_list laux = *lista;
	t_list lant = *lista;
	Formato faux = laux->data;
	while (laux && faux.indice != inddel){
	  lant = laux;
	  laux = laux->next;
	  if (laux) {
	    faux = laux->data;
	  }
	}
	if (!laux){
	  printf("No se encontro el indice %d en el archivo\n", inddel);
	} else {
	  free(faux.texto);
	  if (laux == *lista){
	    *lista = laux->next;
	  } else {
	    lant->next = laux->next;
	  }
	  while (laux){
	    laux->data.indice--;
	    laux = laux->next;
	  }
	}
	free(laux);
}

