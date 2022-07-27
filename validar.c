#include "validar.h"
#include "tiempo.h"
#include <stdio.h>
#include <string.h>

int tiempocorto (t_list lista) {
	int tiempoini = convertirAMilis(lista->data.tiempoinicio);
	int tiempofin = convertirAMilis(lista->data.tiempofin);
	if ((tiempofin - tiempoini) < 1000) {
		printf ("El subtitulo indice %d no dura mas de 1 segundo\n", lista->data.indice);
	}
	return (lista->data.tiempoinicio.segundos + lista->data.tiempofin.segundos);
}

int tiempolargo (t_list lista) {
	int tiempoini = convertirAMilis(lista->data.tiempoinicio);
	int tiempofin = convertirAMilis(lista->data.tiempofin);
	if ((tiempofin - tiempoini) > 7000) {
		printf ("El subtitulo indice %d dura mas de 7 segundos\n", lista->data.indice);
	}
	return (tiempofin - tiempoini);
}

int textolargo (t_list lista) {
	int tiempoini = convertirAMilis(lista->data.tiempoinicio);
	int tiempofin = convertirAMilis(lista->data.tiempofin);
	int totaltime = tiempofin - tiempoini;
	if (totaltime < 1000) {
		totaltime = 1;
	} else {
		totaltime = totaltime / 1000;
	}
	int cont = strlen(lista->data.texto) / totaltime;
	if (cont >= 25) {
		printf ("El subtitulo del indice %d tiene demasiados caracteres\n", lista->data.indice);
	}
	return (cont);
}

int demcar (t_list lista) { // Lineas demasiado largas
	int total = 0; int cant = 0; int seguir = 1;
	while (lista->data.texto[total] != '\0' && seguir) {
		while (lista->data.texto[total] != '\n') {
			cant++;
			total++;
		}
		if (cant > 36) {
			printf ("El subtitulo del indice %d tiene lineas demasiado largas\n", lista->data.indice);
			seguir = 0;
		}
		cant = 0;
		total++;
	}
	return (total);
}

int demlin (t_list lista) { // Tiene mas de dos lineas
	int cantlin = 0; int i = 0;
	while (cantlin < 2 && lista->data.texto[i] != '\0') {
		if (lista->data.texto[i] == '\n') {
			cantlin++;
		}
		i++;
	}
	if (cantlin > 2) {
		printf ("El subtitulo del indice %d tiene demasiadas lineas\n", lista->data.indice);
	}
	return (cantlin);
}

int pocaseparacion(t_list lista) { // Tiene menos de 75 milis entre final de sub1 y principio de sub2
	if (!lista->next){
		return -1;
	} else {
	    Formato fact = lista->data;
	    Formato fsig = lista->next->data;
	    int auxnext = convertirAMilis(fsig.tiempoinicio);
	    int auxact = convertirAMilis(fact.tiempofin);
	    if (auxnext - auxact < 75) {
	      printf("El subtitulo del indice %d tiene menos de 75 milisegudos entre el final del sub1 y el principio de sub2\n", fact.indice);
	    }
	    return(auxnext - auxact);
	}
}

int subsolapados(t_list lista) {
	if (!lista->next){
		return -1;
	} else {
	    Formato fact = lista->data;
	    Formato fsig = lista->next->data;
	    int auxnext = convertirAMilis(fsig.tiempoinicio);
	    int auxact = convertirAMilis(fact.tiempofin);
	    if (auxact >= auxnext) {
	      printf("Los Subtitulos del indice %d y %d se solapan\n", fact.indice, fsig.indice);
	    }
	    return (auxact);
	}
}

int inicioInvalido(t_list lista) {
  if (lista->data.indice != 1) {
    printf("No Empieza con 1 el indice\n");
  }
  return(lista->data.indice);
}

int numConsecutivos(t_list lista) {
	if (!lista->next){
		return -1;
	} else {
	    Formato fact = lista->data;
	    Formato fsig = lista->next->data;
	    if (fsig.indice != fact.indice + 1) {
	      printf("En el indice %d y %d Los numeros no son consecutivos\n", fact.indice, fsig.indice);
	    }
	    return (fsig.indice - fact.indice); 
	}
}

void validar(t_list lista) {
    printf("-o-o-o-INICIO VALIDAR-o-o-o-\n");  
    inicioInvalido(lista);
    while (lista){
    	tiempocorto(lista);
        tiempolargo(lista);
        textolargo(lista); 
        demcar(lista);
        demlin(lista);
        pocaseparacion(lista);
        subsolapados(lista);
        numConsecutivos(lista);
        lista = lista->next;
    }
    printf("-o-o-o-FIN VALIDAR-o-o-o-\n");  
}
