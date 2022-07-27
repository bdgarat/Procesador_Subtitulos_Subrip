#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "list_iterator.h"
#include "archivo.h"
#include "validar.h"


void ayuda(){
  printf ("Parametros validos:\n");
  printf ("-f <filein> : filein es el archivo a procesar(Solo invocable 1 vez)\n");
  printf ("-o <fileout> : fileout es el archivo donde se guardaran los cambios(Solo invocable 1 vez)\n");
  printf ("-b <indice> : borra el subtitulo numero indice\n");
  printf ("-i <startmilis> <endmillis> : texto inserta el subtitulo texto en startmilis con duracion hasta\n");
  printf ("    endmillis , corrige todos los indices de los subtitulos siguientes\n");
  printf ("-v : valida el subtitulo buscando los siguientes errores:\n");
  printf ("    Los numeros de indice dentro del archivo no son numeros consecutivos ordenados\n");
  printf ("    Los numeros de indice no arrancan en 1\n");
  printf ("    Los  subtitulos  estan  solapados  (el  tiempo  de  fin  del  subtitulo  i  es  mayor  o igual al\n");
  printf ("    tiempo de inicio del subtitulo i + 1)\n");
  printf ("    Dura menos de 1 segundo\n");
  printf ("    Dura mas de 7 segundos\n");
  printf ("    Tiene lineas demasiado largas (mas de 36 caracteres)\n");
  printf ("    Tiene demasiados caracteres por segundo (mas de 25)\n");
  printf ("    Tiene mas de 2 lineas\n");
  printf ("    Hay menos de 75 milisegundos entre el final del subtitulo i y el principio del i + 1.\n");
}

int main(int argc, char *argv[]) {
  int contf = 0;
  int conto = 0;
  int i;
  char filenameIn[255];
  char filenameOut[255];
  t_list lista;
  FILE *fIn;
  FILE *fOut;
  int editFalse = 1;
  Formato faux;
	for (i = 1; i < argc; i++) {
    if (strcmp(argv[i], "-f") == 0) {
		contf++;
		if((argc-1) != i) {
		strcpy(filenameIn, argv[i+1]);
	  }
    }
    if (strcmp(argv[i], "-o") == 0) {
	conto++;
	  if ((argc-1) != i) {
		strcpy(filenameOut, argv[i+1]);
	  }
    }
    if (((strcmp(argv[i], "-b") == 0) || (strcmp(argv[i], "-i") == 0)) && editFalse) {
      editFalse = 0;
    } 
  }
  if (contf > 1 || conto > 1) {
    ayuda();
    return 1;
  }
  if (contf == 0 || (conto == 0 && editFalse == 0)) {
    ayuda();
    return 2;
  }
  fIn = fopen(filenameIn, "r");
  if (fIn == NULL) {
    printf("No se pudo abrir el archivo %s", filenameIn);
    return 4;
  }
  if(!editFalse) {
  	fOut = fopen(filenameOut, "w");
  	if(fOut == NULL ) {
    	printf("No se pudo abrir el archivo %s", filenameOut);
    	return 4;    
  	}
  }
  int check = CrearListaFormato(fIn, &lista);
  if (check) {
	  printf("Formato Invalido del archivo %s\n", filenameIn);
	  return 5;
  }
  for (i = 1; i < argc; i++) {
    if (strcmp(argv[i], "-f") == 0) {
      i++;
    } else {
      if (strcmp(argv[i], "-o") == 0) {
        i++;
      } else {
        if (strcmp(argv[i], "-i") == 0) {
          i++;
          Tiempo taux;
      	  convertirATiempo(&taux, atoi(argv[i]));
          faux.tiempoinicio.horas = taux.horas;
          faux.tiempoinicio.minutos = taux.minutos;
          faux.tiempoinicio.segundos = taux.segundos;
          faux.tiempoinicio.milesimas = taux.milesimas;
          i++;
          convertirATiempo(&taux, atoi(argv[i]));
          faux.tiempofin.horas = taux.horas;
          faux.tiempofin.minutos = taux.minutos;
          faux.tiempofin.segundos = taux.segundos;
          faux.tiempofin.milesimas = taux.milesimas;
          i++;
          faux.texto = malloc(strlen(argv[i])+1);
          strcpy(faux.texto, argv[i]);
          agregarEnOrden(&lista, faux);
        } else {
          if (strcmp(argv[i], "-b") == 0) {
             i++;
            quitar(&lista ,atoi(argv[i]));
          } else {
            if (strcmp(argv[i], "-v") == 0) {
              validar(lista);
            } else {
              ayuda();
              return 3;
            }
          } 
        }
      }
    }
  }
  fclose(fIn);
  if(!editFalse) {
	descargarLista(fOut, &lista);
  	fclose(fOut);
  }
  return 0;
}
