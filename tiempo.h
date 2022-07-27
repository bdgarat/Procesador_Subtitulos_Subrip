#include <stdio.h>
#ifndef _T_TIEMPO_H
#define _T_TIEMPO_H

typedef struct {
	int horas;
	int minutos;
	int segundos;
	int milesimas;
} Tiempo;

int convertirAMilis(Tiempo taux);
void convertirATiempo(Tiempo *taux, int milis);
#endif
