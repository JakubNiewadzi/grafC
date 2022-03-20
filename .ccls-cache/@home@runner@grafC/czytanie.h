#ifndef _CZYTANIE_H_
#define _CZYTANIE_H_
#include <stdio.h>

typedef struct graf {
  int kolumny;
  int wiersze;
  int wagaMin;
  int wagaMax;
  double **macierzSasiedztwa;
} graf_t;

typedef struct tablice {
  int **grafBFS;
  double **grafD;
  int *sasiedzi; 
} tablice_t;


int grafWTablice (graf_t *g, tablice_t *t, char *plik );

#endif