#include <stdio.h>
#include <stdlib.h>

#include "czytanie.h"
#include "dijkstra.h"

int main (int argc, char **argv) {
  int poczatek, koniec, czyBlad;
  double trasa;
  char *p;

  if(argc < 5) {
    printf("Podano za mało argumentów wywołania!\n\n");
    printf("Program testujący przyjmuje 4 argumenty.\n");
    printf("Pierwszym z nich jest nazwa pliku zawierającego zapis grafu.\n"); 
    printf("Drugim jest początkowy wierzchołek od którego funkcja ma rozpocząć analizować graf.\n");
    printf("Trzecim argumentem jest wierzchołek końcowy do, kótrego funkcja ma wyznaczyć trasę.\n");
    printf("Czwartym argumentem jest długość najkrótrzej ścierzki z wierzchołka początkowego do końcowego.\n");
    return 1;
  }

  p = argv [1];
  poczatek = atoi(argv [2]);
  koniec = atoi(argv [3]);
  trasa = atof(argv [4]);

  printf("Rozpoczynam test funkcji analizującą grafu za pomocą algorytmu Dijkstry\n");
  printf("Analizie zostannie poddany graf zapisany w pliku o nazwie %s.\n", p);
  printf("Analiza rozpocznie sie od wierzchołka %d i zakończy na wierzchołku %d", poczatek, koniec);
  printf("Droga między tymi wierzchołkami wynosi %lf.\n", trasa);
  printf("Funkcja wykarze prawidłowe działanie jeżeli dowiedzie tego samego.\n");

  graf_t *graf=malloc(sizeof (*graf));
  tablice_t *tablice=malloc(sizeof (*tablice));

  printf("\nRozpoczynam czytanie pliku z grafem.\n");

  czyBlad = grafWTablice(graf,tablice,p);
  
  if(czyBlad == 1) {
    czyszczenieTablic(tablice);
    czyszczenieGrafu(graf);
    printf("Proces czytania nie przebiegł prawidłowo.\n");
    printf("Awaryjne zatrzymanie programu\n");
    return 1;
  }

  printf("Proces czytania przebiegł prawidłowo.\n");

  printf("\nRozpoczynam analizę grafu algorytmem Dijkstry.\n\n");
  
  double * droga = malloc(graf->kolumny * graf->wiersze * sizeof(*droga));
  dijkstra(graf, poczatek, graf->kolumny*graf->wiersze, droga);

  printf("\nDroga z wierzchołka %d do wierzchołka %d wynosi %lf\n",poczatek, koniec, droga[koniec]);

  if(droga[koniec] == trasa) {
    printf("Wyznaczona trasa zgadza się z podaną podczas kompilacji programu!\n\n");
    printf("Funkcja działa prawidłowo!\n");
  } else {
    printf("Wyznaczona trasa nie zgadza się z podaną podczas kompilacji programu!\n\n");
    printf("Funkcja nie działa prawidłowo.\n");
  }

  czyszczenieTablic(tablice);
  czyszczenieGrafu(graf);
  return 0;
}