#include "tiempo.h"

int convertirAMilis(Tiempo taux){
  int cantMilis = (taux.segundos * 1000) + taux.milesimas;
  cantMilis = (taux.minutos * 60000) + cantMilis;
  cantMilis = (taux.horas * 3600000) + cantMilis;
  return cantMilis;
}


void convertirATiempo(Tiempo *taux, int milis) {
  if (milis >= 3600000) {
  	(*taux).horas = milis / 3600000;
	milis = milis % 3600000;
  } else {
	 (*taux).horas = 0;
  }
  if (milis >= 60000) {
  	(*taux).minutos = milis / 60000;
	milis = milis % 60000;
  } else {
	 (*taux).minutos = 0;
  }
  if (milis >= 1000) {
  	(*taux).segundos = milis / 1000;
	 milis = milis % 1000;
  }	else {
	 (*taux).segundos = 0;
  }
  	(*taux).milesimas = milis;
}