#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <time.h>
#include "czytanie.h"

double losuj(double min, double max) {
  double zakres = (max - min); 
  double dzielnik = RAND_MAX / zakres;
  return min + (rand() / dzielnik);
}

void druk (FILE * plik, graf_t *g) {
  fprintf(plik,"%d %d\n", g->kolumny, g->wiersze);

  for(int i = 0; i < g->kolumny * g->wiersze; i++) {
    for(int j = 0; j < g->kolumny * g->wiersze; j++) {
      if(g->macierzSasiedztwa [i] [j] != DBL_MIN) {
        fprintf(plik,"%d :%lf    ", j, g->macierzSasiedztwa [i] [j]);
      }
    }

    fprintf(plik,"\n");
  }
}

void wygenerujGraf (graf_t *g, tablice_t *t) {

  srand(time(NULL));
  int aktualnyWierzcholek, sasiad, iloscSasiadow;
  double wagaMinimalna, wagaMaxymalna, waga;

  if(g->wagaMax == 0) {
    wagaMaxymalna = 10;
    wagaMinimalna = 0;
  } else {
    wagaMaxymalna = g->wagaMax;
    wagaMinimalna = g->wagaMin;
  }

  g->macierzSasiedztwa = malloc(g->kolumny * g->wiersze * sizeof *g->macierzSasiedztwa);
  for(int i = 0; i < g->kolumny * g->wiersze; i++) {
    g->macierzSasiedztwa [i] = malloc(g->kolumny * g->wiersze * sizeof **g->macierzSasiedztwa);
  }

  for(int i = 0; i < g->kolumny * g->wiersze; i++) {
    for(int j = 0; j < g->kolumny * g->wiersze; j++) {
      g->macierzSasiedztwa [i] [j] = DBL_MIN;
      //printf("%lf",g->macierzSasiedztwa [i] [j]);
    }
  }


  t->sasiedzi = malloc(g->kolumny * g->wiersze * sizeof *t->sasiedzi);

  iloscSasiadow = 0;

  for(int i = 0; i <= (g->kolumny - 1) * g->wiersze; i = i + g->wiersze) {
    if(i + g->wiersze >= 0 && i + g->wiersze < g->kolumny * g->wiersze) {
      waga = losuj(wagaMinimalna, wagaMaxymalna);
      g->macierzSasiedztwa [i] [i + g->wiersze] = waga;
      iloscSasiadow++;
    }

    if(i + 1 >= 0 && i + 1 < g->kolumny * g->wiersze) {
      waga = losuj(wagaMinimalna, wagaMaxymalna);
      g->macierzSasiedztwa [i] [i + 1] = waga;
      iloscSasiadow++;
    }

    if(i - g->wiersze >= 0 && i - g->wiersze < g->kolumny * g->wiersze) {
      waga = losuj(wagaMinimalna, wagaMaxymalna);
      g->macierzSasiedztwa [i] [i - g->wiersze] = waga;
      iloscSasiadow++;
    }

    t->sasiedzi [i] = iloscSasiadow;
    iloscSasiadow = 0;
  }

  for(int i = 2; i < g->wiersze; i++) {
    for(int j = i - 1; j <= (g->kolumny - 1) * g->wiersze + (i - 1); j = j + g->wiersze) {
      if(j - 1 >= 0 && j - 1 < g->kolumny * g->wiersze) {
        waga = losuj(wagaMinimalna, wagaMaxymalna);
        g->macierzSasiedztwa [j] [j - 1] = waga;
        iloscSasiadow++;
      }

      if(j + g->wiersze >= 0 && j + g->wiersze < g->kolumny * g->wiersze) {
        waga = losuj(wagaMinimalna, wagaMaxymalna);
        g->macierzSasiedztwa [j] [j + g->wiersze] = waga;
        iloscSasiadow++;
      }

      if(j + 1 >= 0 && j + 1 < g->kolumny * g->wiersze) {
        waga = losuj(wagaMinimalna, wagaMaxymalna);
        g->macierzSasiedztwa [j] [j + 1] = waga;
        iloscSasiadow++;
      }

      if(j - g->wiersze >= 0 && j - g->wiersze < g->kolumny * g->wiersze) {
        waga = losuj(wagaMinimalna, wagaMaxymalna);
        g->macierzSasiedztwa [j] [j - g->wiersze] = waga;
        iloscSasiadow++;
      }

      t->sasiedzi [j] = iloscSasiadow;
      iloscSasiadow = 0;
    }
  }


  for(int i = g->wiersze - 1; i < g->kolumny * g->wiersze; i = i + g->wiersze) {
    if(i + g->wiersze >= 0 && i + g->wiersze < g->kolumny * g->wiersze) {
      waga = losuj(wagaMinimalna, wagaMaxymalna);
      g->macierzSasiedztwa [i] [i + g->wiersze] = waga;
      iloscSasiadow++;
    }

    if(i - 1 >= 0 && i - 1 < g->kolumny * g->wiersze) {
      waga = losuj(wagaMinimalna, wagaMaxymalna);
      g->macierzSasiedztwa [i] [i - 1] = waga;
      iloscSasiadow++;
    }

    if(i - g->wiersze >= 0 && i - g->wiersze < g->kolumny * g->wiersze) {
      waga = losuj(wagaMinimalna, wagaMaxymalna);
      g->macierzSasiedztwa [i] [i - g->wiersze] = waga;
      iloscSasiadow++;
    }

    t->sasiedzi [i] = iloscSasiadow;
    iloscSasiadow = 0;
  }
  t->iloscWezlow=g->wiersze*g->kolumny;
}