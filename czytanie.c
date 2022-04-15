#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <float.h>
#include "czytanie.h"


int grafWTablice (graf_t *g, tablice_t *t, char *plik ) {  /*pobieram wskaźnik na plik, wskaźnik na strókturę oraz nazwę pliku z którego czytam dane */
    
  char c;
  char poprzedniZnak;
  int aktualnyWezel, aktualnySasiad, licznikSasiadow;
  double waga;
  char* linijka;
  FILE *p = fopen (plik, "r");

  if(p == NULL) {
    printf("Program nie ma dostępu do pliku z którego chcesz pobrać dane na temat opisu grafu, spróbuj podać inny plik.\n");
    return 1;
  }

  if(fscanf(p,"%d %d", &(g->wiersze), &(g->kolumny)) != 2) {
    printf("Nieodpowiedni format lub ilość liczb w pierwszym wierszu pliku!\nPowinny być to 2 liczby naturalne określające liczbę wierszy i kolumn grafu\n");
    return 1;        /*błąd związany z nie podaniem odpowiedniej ilości wierszy i kolumn*/
  }

  linijka = malloc(14 * (g->kolumny * g->wiersze) * sizeof *linijka);

  g->macierzSasiedztwa = malloc(g->kolumny * g->wiersze * sizeof *g->macierzSasiedztwa);

  for(int i = 0; i < g->kolumny * g->wiersze; i++) {
    g->macierzSasiedztwa [i] = malloc(g->kolumny * g->wiersze * sizeof *g->macierzSasiedztwa);
  }

  for(int i = 0; i < g->kolumny * g->wiersze; i++) {
    for(int j = 0; j < g->kolumny * g->wiersze; j++) {
      g->macierzSasiedztwa [i] [j] = DBL_MIN;
    }
  }

  t->sasiedzi = malloc(g->kolumny * g->wiersze * sizeof *t->sasiedzi);

  /* printf("Zaalokowano pamięć na sasiedzi\n"); */

  for(int i = 0; i < g->kolumny * g->wiersze; i++) {
    t->sasiedzi [i] = 0;
  }
  
  int koniec, iterator, dwukropek;
  aktualnyWezel = 0;
  fgets(linijka, 11, p);

  while(fgets(linijka, 14 * (g->kolumny * g->wiersze), p) != NULL) {    /* główna pętla zapisująca odpowiednie dane w tablicach grafD i grafBFS */
    /*printf("\t%s\n", linijka);*/
    licznikSasiadow = 0;
    while(sscanf(linijka, "%d :%lf", &aktualnySasiad, &waga) == 2) {
      /*printf("\t%d , waga %lf\n", aktualnySasiad, waga);*/

      iterator = 0;
      dwukropek = 0;
      koniec = 0;
      while(koniec == 0) {
        if(dwukropek == 0) {
          if(linijka [iterator] == '\n' || iterator > 14 * (g->kolumny * g->wiersze) ) {
            koniec = 1;
          }

          if(linijka [iterator] == ':') {
            linijka [iterator] = ' ';
            iterator++;
            dwukropek = 1;
          } else {
            linijka [iterator] = ' ';
            iterator++;
          }
        } else {
          if(linijka [iterator] == '\n' || iterator > 14 * (g->kolumny * g->wiersze) ) {
            koniec = 1;
          }

          if(isalnum(linijka [iterator]) != 0 && linijka [iterator + 1] == ' ') {
            linijka [iterator] = ' ';
            koniec = 1;
          } else {
            linijka [iterator] = ' ';
            iterator++;
          }
        }
      }

      licznikSasiadow++;
    
      if(aktualnySasiad>=g->wiersze*g->kolumny || aktualnySasiad<0){
        printf("W pliku znajduje się wierzchołek, który wychodzi poza podany zakres.\nProgram kończy działanie.\n");
       return 1;
      }
    
      g->macierzSasiedztwa [aktualnyWezel] [aktualnySasiad] = waga;
      t->sasiedzi [aktualnyWezel] ++;

      /*
      printf("\nsasiedzi [%d] = %d", aktualnyWezel, t->sasiedzi [aktualnyWezel]);
      printf("\nmacierzSasiedztwa [%d] [%d] = %lf\n\n", aktualnyWezel, aktualnySasiad, waga);
      */
      
    }

    aktualnyWezel++;
  }


  /*printf("\n");*/

  t->iloscWezlow = aktualnyWezel;

  fclose(p);
  free(linijka);
  /*fclose(kp);*/
  return 0;
}

void czyszczenieTablic(tablice_t *tablice) {
  free(tablice->sasiedzi);
  /*for(int i = 0; i < tablice->iloscWezlow; i++) {
    free(tablice->grafBFS [i]);
    //free(tablice->grafD [i]);
  }*/
  //free(tablice->grafBFS);
  //free(tablice->grafD);
  free(tablice);
}

void czyszczenieGrafu(graf_t *graf) {
  for(int i = 0; i < graf->kolumny * graf->wiersze; i++) {
    free(graf->macierzSasiedztwa [i]);
  }
  free(graf->macierzSasiedztwa);
  free(graf);
} 