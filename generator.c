#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include "czytanie.h"

double losuj(double min, double max) {
  double zakres = (max - min); 
  double dzielnik = RAND_MAX / zakres;
  return min + (rand() / dzielnik);
}

void wygenerujGraf (graf_t *g, tablice_t *t, FILE *p) {
  
  int aktualnyWierzcholek, sasiad, iloscSasiadow;
  double wagaMinimalna, wagaMaxymalna, waga;

  /*
  if(p == NULL) {
    p = stdout;
  } */

  if(g->wagaMax == 0) {
    wagaMaxymalna = 10;
    wagaMinimalna = 0;
  } else {
    wagaMaxymalna = g->wagaMax;
    wagaMinimalna = g->wagaMin;
  }

  fprintf(p,"%d %d\n", g->kolumny, g->wiersze);

  g->macierzSasiedztwa = malloc(g->kolumny * g->wiersze * sizeof *g->macierzSasiedztwa);
  for(int i = 0; i < g->kolumny * g->wiersze; i++) {
    g->macierzSasiedztwa [i] = malloc(g->kolumny * g->wiersze * sizeof *g->macierzSasiedztwa);
  }

  for(int i = 0; i < g->kolumny * g->wiersze; i++) {
    for(int j = 0; j < g->kolumny * g->wiersze; j++) {
      g->macierzSasiedztwa [i] [j] = DBL_MIN;
    }
  }

  /*t->grafD = malloc(g->kolumny * g->wiersze * sizeof *t->grafD);
  for(int i = 0; i < g->kolumny * g->wiersze; i++) {
    t->grafD [i] = malloc(4 * sizeof *t->grafD[i]);
  }*/

  t->grafBFS = malloc(g->kolumny * g->wiersze * sizeof *t->grafBFS);
  for(int i = 0; i < g->kolumny * g->wiersze; i++) {
    t->grafBFS [i] = malloc(g->kolumny * g->wiersze * sizeof *t->grafBFS[i]);
  }

  t->sasiedzi = malloc(g->kolumny * g->wiersze * sizeof *t->sasiedzi);

  
  for(aktualnyWierzcholek = 0; aktualnyWierzcholek < (g->kolumny * g->wiersze); aktualnyWierzcholek++ ) {
    iloscSasiadow = 0;
    t->sasiedzi [aktualnyWierzcholek] = 0;

    sasiad = aktualnyWierzcholek - 1;

    /*printf("Wierzchołek %d ma sąsiadów z wagami:\n\t", aktualnyWierzcholek);*/

    
    if(sasiad >= 0 && sasiad < g->kolumny * g->wiersze && aktualnyWierzcholek % g->wiersze != 0) {
      t->sasiedzi [aktualnyWierzcholek] ++;

      t->grafBFS [aktualnyWierzcholek] [iloscSasiadow] = sasiad;
      iloscSasiadow ++;

      waga = losuj(wagaMinimalna, wagaMaxymalna);
      //t->F [aktualnyWierzcholek] [0] = waga;

      g->macierzSasiedztwa [aktualnyWierzcholek] [sasiad] = waga;

      /*printf("\tt->grafBFS [%d] [%d] = %d\n", aktualnyWierzcholek, iloscSasiadow, sasiad);*/

      fprintf(p,"%d :%lf   ", sasiad, waga);
    }
  

    sasiad = aktualnyWierzcholek + g->wiersze;

    if(sasiad >= 0 && sasiad < g->kolumny * g->wiersze ) {
      t->sasiedzi [aktualnyWierzcholek] ++;

      t->grafBFS [aktualnyWierzcholek] [iloscSasiadow] = sasiad;
      iloscSasiadow ++;

      waga = losuj(wagaMinimalna, wagaMaxymalna);
     // t->grafD [aktualnyWierzcholek] [1] = waga;

      g->macierzSasiedztwa [aktualnyWierzcholek] [sasiad] = waga;

      /*printf("\tt->grafBFS [%d] [%d] = %d\n", aktualnyWierzcholek, iloscSasiadow, sasiad);*/

      fprintf(p,"%d :%lf   ", sasiad, waga);
    }


    sasiad = aktualnyWierzcholek + 1;

    if(sasiad >= 0 && sasiad < g->kolumny * g->wiersze && (aktualnyWierzcholek + 1) % g->wiersze != 0) {
      t->sasiedzi [aktualnyWierzcholek] ++;

      t->grafBFS [aktualnyWierzcholek] [iloscSasiadow] = sasiad;
      iloscSasiadow ++;

      waga = losuj(wagaMinimalna, wagaMaxymalna);
      //t->grafD [aktualnyWierzcholek] [2] = waga;

      g->macierzSasiedztwa [aktualnyWierzcholek] [sasiad] = waga;

      /*printf("\tt->grafBFS [%d] [%d] = %d\n", aktualnyWierzcholek, iloscSasiadow, sasiad);*/

      fprintf(p,"%d :%lf   ", sasiad, waga);
    }


    sasiad = aktualnyWierzcholek - g->wiersze;
    
    if(sasiad >= 0 && sasiad < g->kolumny * g->wiersze) {
      t->sasiedzi [aktualnyWierzcholek] ++;

      t->grafBFS [aktualnyWierzcholek] [iloscSasiadow] = sasiad;
      iloscSasiadow ++;

      waga = losuj(wagaMinimalna, wagaMaxymalna);
     // t->grafD [aktualnyWierzcholek] [0] = waga;

      g->macierzSasiedztwa [aktualnyWierzcholek] [sasiad] = waga;

      /*printf("\tt->grafBFS [%d] [%d] = %d\n", aktualnyWierzcholek, iloscSasiadow, sasiad);*/

      fprintf(p,"%d :%lf   ", sasiad, waga);
    }
    fprintf(p, "\n");

    /*printf("\n\tIlość sąsiadów %d\n\n", t->sasiedzi[aktualnyWierzcholek-1]);*/
  }

  t->iloscWezlow = aktualnyWierzcholek++;
  /*if( p != stdout )
    fclose(p); */
}