#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include "czytanie.h"

double losuj(double min, double max) {
  double zakres = (max - min); 
  double dzielnik = RAND_MAX / zakres;
  return min + (rand() / dzielnik);
}

void wygenerujGraf (graf_t *g, tablice_t *t, char *plik) {
  
  int aktualnyWierzcholek, sasiad, iloscSasiadow, czyDoPliku;
  double wagaMinimalna, wagaMaxymalna, waga;
  FILE *p = fopen (plik, "w");

  if(p == NULL) {
    czyDoPliku = 0;
  } else {
    czyDoPliku = 1;
  }

  if(g->wagaMax == 0) {
    wagaMaxymalna = 10;
    wagaMinimalna = 0;
  } else {
    wagaMaxymalna = g->wagaMax;
    wagaMinimalna = g->wagaMin;
  }

  if(czyDoPliku == 1) {
    fprintf(p,"%d %d\n", g->kolumny, g->wiersze);
  }

  g->macierzSasiedztwa = malloc(g->kolumny * g->wiersze * sizeof *g->macierzSasiedztwa);
  for(int i = 0; i < g->kolumny * g->wiersze; i++) {
    g->macierzSasiedztwa [i] = malloc(g->kolumny * g->wiersze * sizeof *g->macierzSasiedztwa);
  }

  for(int i = 0; i < g->kolumny * g->wiersze; i++) {
    for(int j = 0; j < g->kolumny * g->wiersze; j++) {
      g->macierzSasiedztwa [i] [j] = DBL_MIN;
    }
  }

  t->grafD = malloc(g->kolumny * g->wiersze * sizeof *t->grafD);
  for(int i = 0; i < g->kolumny * g->wiersze; i++) {
    t->grafD [i] = malloc(4 * sizeof *t->grafD[i]);
  }

  t->grafBFS = malloc(g->kolumny * g->wiersze * sizeof *t->grafBFS);
  for(int i = 0; i < g->kolumny * g->wiersze; i++) {
    t->grafBFS [i] = malloc(g->kolumny * g->wiersze * sizeof *t->grafBFS[i]);
  }

  t->sasiedzi = malloc(g->kolumny * g->wiersze * sizeof *t->sasiedzi);

  aktualnyWierzcholek = 0;
  while(aktualnyWierzcholek != (g->kolumny * g->wiersze)) {
    iloscSasiadow = 0;
    t->sasiedzi [aktualnyWierzcholek] = 0;

    sasiad = aktualnyWierzcholek - 1;

    printf("Wierzchołek %d ma sąsiadów z wagami:\n\t", aktualnyWierzcholek);

    if(sasiad >= 0 && sasiad < g->kolumny * g->wiersze && aktualnyWierzcholek % g->wiersze != 0) {
      t->sasiedzi [aktualnyWierzcholek] ++;

      t->grafBFS [aktualnyWierzcholek] [iloscSasiadow] = sasiad;
      iloscSasiadow ++;

      waga = losuj(wagaMinimalna, wagaMaxymalna);
      t->grafD [aktualnyWierzcholek] [0] = waga;

      g->macierzSasiedztwa [aktualnyWierzcholek] [sasiad] = waga;

      printf("%d :%lf ", sasiad, waga);

      if(czyDoPliku == 1) {
        fprintf(p,"%d :%lf\t", sasiad, waga);
      }
    }

    sasiad = aktualnyWierzcholek + g->wiersze;

    if(sasiad >= 0 && sasiad < g->kolumny * g->wiersze ) {
      t->sasiedzi [aktualnyWierzcholek] ++;

      t->grafBFS [aktualnyWierzcholek] [iloscSasiadow] = sasiad;
      iloscSasiadow ++;

      waga = losuj(wagaMinimalna, wagaMaxymalna);
      t->grafD [aktualnyWierzcholek] [1] = waga;

      g->macierzSasiedztwa [aktualnyWierzcholek] [sasiad] = waga;

      printf("%d :%lf ", sasiad, waga);

      if(czyDoPliku == 1) {
        fprintf(p,"%d :%lf\t", sasiad, waga);
      }
    }

    sasiad = aktualnyWierzcholek + 1;

    if(sasiad >= 0 && sasiad < g->kolumny * g->wiersze && (aktualnyWierzcholek + 1) % g->wiersze != 0) {
      t->sasiedzi [aktualnyWierzcholek] ++;

      t->grafBFS [aktualnyWierzcholek] [iloscSasiadow] = sasiad;
      iloscSasiadow ++;

      waga = losuj(wagaMinimalna, wagaMaxymalna);
      t->grafD [aktualnyWierzcholek] [2] = waga;

      g->macierzSasiedztwa [aktualnyWierzcholek] [sasiad] = waga;

      printf("%d :%lf ", sasiad, waga);

      if(czyDoPliku == 1) {
        fprintf(p,"%d :%lf\t", sasiad, waga);
      }
    }

    sasiad = aktualnyWierzcholek - g->wiersze;

    if(sasiad >= 0 && sasiad < g->kolumny * g->wiersze) {
      t->sasiedzi [aktualnyWierzcholek] ++;

      t->grafBFS [aktualnyWierzcholek] [iloscSasiadow] = sasiad;
      iloscSasiadow ++;

      waga = losuj(wagaMinimalna, wagaMaxymalna);
      t->grafD [aktualnyWierzcholek] [0] = waga;

      g->macierzSasiedztwa [aktualnyWierzcholek] [sasiad] = waga;

      printf("%d :%lf ", sasiad, waga);

      if(czyDoPliku == 1) {
        fprintf(p,"%d :%lf\t", sasiad, waga);
      }
    }

    aktualnyWierzcholek++;

    if(czyDoPliku == 1) {
      fprintf(p, "\n");
    }

    printf("\n\tIlość sąsiadów %d\n\n", t->sasiedzi[aktualnyWierzcholek-1]);
  }
}