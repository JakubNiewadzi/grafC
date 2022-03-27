#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>

#include "czytanie.h"
#include "generator.h"

int main (int argc, char** argv) {
  int kol, wier, iloscWierzcholkow, zleWagi;
  double wagMin, wagMax;
  char *p;

  graf_t *graf = malloc(sizeof (*graf));
  tablice_t *tablice = malloc(sizeof (*tablice));

  kol = argc > 1 ? atoi(argv[1]) : 10;
  wier = argc > 2 ? atoi(argv[2]) : 10;
  wagMin = argc > 3 ? atof(argv[3]) : 0;
  wagMax = argc > 4 ? atof(argv[4]) : 10;
  p = argc > 5 ? argv[5] : NULL;

  graf->kolumny = kol;
  graf->wiersze = wier;

  printf("Rozpoczynam test funkcji generującej graf.\nGenerowany graf ma wymiary %d x %d.\n", kol, wier);
  printf("Wagi połączeń między wierzchołkami mogą przyjmować wartości w przedziałe %lf - %lf.\n", wagMin, wagMax);

  if(p == NULL) {
    printf("Wygenerowany plik zostanie wypisany na wyjsciu głównym\n\n");
  } else {
    printf("Wygenerowany plik zostanie zapisany w pliku o nazwie %s.\n", argv[5]);
  }

  wygenerujGraf(graf, tablice, p);

  printf("\nSprawdzam czy wygenerowny graf ma odpowiednią liczbę wierzchołków.\n");

  iloscWierzcholkow = tablice->iloscWezlow;

  if(iloscWierzcholkow != kol * wier) {
    printf("Liczba wierzchołków nie zgadza się!\nProgram wygenerował %d zamiast %d wierzchołków.\nGenerator nie działa prawidłowo!\n", iloscWierzcholkow, kol * wier);
    return 1;
  } else {
    printf("Liczba wierzchołków zgadza się!\n\n");
  }

  printf("Sprawdzam czy wygenerowny graf ma wagi połączeń w odpowiednim zakresie.\n");
  zleWagi = 0;

  for(int i = 0; i < kol * wier; i++) {
    for(int j = 0; j < kol * wier; j++) {
      if(graf->macierzSasiedztwa[i] [j] != DBL_MIN && graf->macierzSasiedztwa[i] [j] < wagMin) {
        printf("Wartość wag nie są prawidłowe!\nGraf wygenerował wagę równą %lf. Nie znajduje się ona w wyznaczonym przedziale.\nGenerator nie działa prawidłowo!\n", graf->macierzSasiedztwa[i] [j]);
        return 1;
      }

      if(graf->macierzSasiedztwa[i] [j] > wagMax) {
        printf("Wartość wag nie są prawidłowe!\nGraf wygenerował wagę równą %lf. Nie znajduje się ona w wyznaczonym przedziale.\nGenerator nie działa prawidłowo!\n", graf->macierzSasiedztwa[i] [j]);
        return 1;
      }
    }
  }

  printf("Wagi znajdują się w odpowiednim zakresie!\n\nFunkcja generujaca graf działa prawidłowo!\n");

  czyszczenieTablic(tablice);
  czyszczenieGrafu(graf);
  
  return 0;
}