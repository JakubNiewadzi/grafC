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
  FILE *out = argc > 5 ? fopen(argv[5], "w") : stdout;

  graf->kolumny = kol;
  graf->wiersze = wier;

  printf("Rozpoczynam test funkcji generującej graf.\nGenerowany graf ma wymiary %d x %d.\n", kol, wier);
  printf("Wagi połączeń między wierzchołkami mogą przyjmować wartości w przedziałe %lf - %lf.\n", wagMin, wagMax);

  wygenerujGraf(graf, tablice);

  printf("\nSprawdzam czy wygenerowny graf ma odpowiednią liczbę wierzchołków.\n");

  iloscWierzcholkow = tablice->iloscWezlow;

  if(iloscWierzcholkow != kol * wier) {
    fprintf(out, "Liczba wierzchołków nie zgadza się!\nProgram wygenerował %d zamiast %d wierzchołków.\nGenerator nie działa prawidłowo!\n", iloscWierzcholkow, kol * wier);
    return 0;
  } else {
    fprintf(out, "Liczba wierzchołków zgadza się!\n\n");
  }

  printf("Sprawdzam czy wygenerowny graf ma wagi połączeń w odpowiednim zakresie.\n");
  zleWagi = 0;

  for(int i = 0; i < kol * wier; i++) {
    for(int j = 0; j < kol * wier; j++) {
      if(graf->macierzSasiedztwa[i] [j] != DBL_MIN && graf->macierzSasiedztwa[i] [j] < wagMin) {
        fprintf(out, "Wartość wag nie są prawidłowe!\nGraf wygenerował wagę równą %lf. Nie znajduje się ona w wyznaczonym przedziale.\nGenerator nie działa prawidłowo!\n", graf->macierzSasiedztwa[i] [j]);
        return 0;
      }

      if(graf->macierzSasiedztwa[i] [j] > wagMax) {
        fprintf(out, "Wartość wag nie są prawidłowe!\nGraf wygenerował wagę równą %lf. Nie znajduje się ona w wyznaczonym przedziale.\nGenerator nie działa prawidłowo!\n", graf->macierzSasiedztwa[i] [j]);
        return 0;
      }
    }
  }

  fprintf(out, "Wagi znajdują się w odpowiednim zakresie!\n\nFunkcja generujaca graf działa prawidłowo!\n\n\n");

  free(tablice->sasiedzi);
  free(tablice);
  czyszczenieGrafu(graf);
  
  return 0;
}