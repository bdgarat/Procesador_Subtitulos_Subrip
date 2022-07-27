#include "tiempo.h"
#include <stdio.h>

int main(){
	Tiempo t, a;
	t.horas = 1;
	t.minutos = 1;
	t.segundos = 1;
	t.milesimas = 999;
	
	int milisegundos = convertirAMilis(t);
	convertirATiempo(&a, milisegundos);
	
	printf("%d", milisegundos);
	printf("	%d %d %d %d ", a.horas, a.minutos, a.segundos, a.milesimas );
	
	printf("	%d %d %d %d", (t.horas*3600000), t.minutos*60000, t.segundos*1000, t.milesimas);
	return 0;
}