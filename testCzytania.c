#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>

#include "czytanie.h"

int main (int argc, char** argv) {
  int kol, wier, iloscWierzcholkow, zleWagi;
  double wagMin, wagMax;
  char *p;

  if(argc < 6) {
      printf("Podano za mało argumentów wywołania!\n\n");
      printf("\tPierwszym argumentem powinnna być nazwa pliku zawierającego zapis grafu.\nNa podstaiwe tego pliku będziem testować funkcję czytającą.\n");
      printf("\tKolejnymi 2 argumentami powinny być liczby kolumn i wierszy grafu zapisango we wcześniej podanym pliku.\nPowinny być to liczby naturalne.\n");
      printf("\tOstatnie 2 argumenty powinny być to wartości najmniejszej i największej wagi połączeń pomiędzy wierzchołkami grafu.\nMogą być to liczby zmiennoprzecinkowe.\n");
      return 1;
  }

  graf_t *graf = malloc(sizeof (*graf));
  tablice_t *tablice = malloc(sizeof (*tablice));

  p = argv[1];
  kol = atoi(argv[2]);
  wier = atoi(argv[3]);
  wagMin = atof(argv[4]);
  wagMax = atof(argv[5]);

  printf("Rozpoczynam test funkcji czytającej graf.\nGraf będzie odczytywany z pliku o nazwie: %s.\n", p);

  grafWTablice(graf, tablice, p);

  printf("\nSprawdzam czy odczytany graf ma odpowiednią liczbę wierzchołków.\n");

  iloscWierzcholkow = tablice->iloscWezlow;

  if(iloscWierzcholkow != kol * wier) {
    printf("Liczba wierzchołków nie zgadza się!\nProgram odczytał %d zamiast %d wierzchołków.\nFunkcja czytająca nie działa prawidłowo!\n", iloscWierzcholkow, kol * wier);
    return 1;
  } else {
    printf("Liczba wierzchołków zgadza się!\n\n");
  }

  printf("Sprawdzam czy program przypisał do tablicy sąsiedztwa wagi połączeń w odpowiednim zakresie.\n");
  zleWagi = 0;

  for(int i = 0; i < kol * wier; i++) {
    for(int j = 0; j < kol * wier; j++) {
      if(graf->macierzSasiedztwa[i] [j] != DBL_MIN && graf->macierzSasiedztwa[i] [j] < wagMin) {
        printf("Wartość wag nie są prawidłowe!\nGraf przypisał wagę równą %lf. Nie znajduje się ona w wyznaczonym przedziale.\nFunkcja czytająca nie działa prawidłowo!\n", graf->macierzSasiedztwa[i] [j]);
        return 1;
      }

      if(graf->macierzSasiedztwa[i] [j] > wagMax) {
        printf("Wartość wag nie są prawidłowe!\nGraf przypisał wagę równą %lf. Nie znajduje się ona w wyznaczonym przedziale.\nFunkcja czytająca nie działa prawidłowo!\n", graf->macierzSasiedztwa[i] [j]);
        return 1;
      }
    }
  }

  printf("Wagi znajdują się w odpowiednim zakresie!\n\nFunkcja czytająca graf z pliku działa prawidłowo!\n");

  free(tablice->sasiedzi);
  free(tablice);
  czyszczenieGrafu(graf);
  
  return 0;
}