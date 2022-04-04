#ifndef _CZYTANIE_H_
#define _CZYTANIE_H_
#include <stdio.h>

typedef struct graf {
  int kolumny;
  int wiersze;
  double wagaMin;
  double wagaMax;
  double **macierzSasiedztwa;
} graf_t;

typedef struct tablice {
  int **grafBFS;
  //double **grafD;
  int *sasiedzi;
  int iloscWezlow;
} tablice_t;


int grafWTablice (graf_t *g, tablice_t *t, char *plik );
void czyszczenieTablic(tablice_t *tablice);
void czyszczenieGrafu(graf_t *graf);

#endif