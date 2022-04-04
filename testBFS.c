#include <stdio.h>
#include <stdlib.h>

#include "czytanie.h"
#include "BFS.h"

int main (int argc, char **argv) {
  int czySpojny, czyBlad;
  int wynikBFS = 0;
  char *p;

  if(argc < 3) {
    printf("Podano za mało argumentów wywołania!\n\n");
    printf("Program testujący przyjmuje 2 argumenty.\n");
    printf("Pierwszym z nich jest nazwa pliku zawierającego zapis grafu. Drugim jest liczba 0 lub 1.\n");
    printf("0 oznacza, że w pliku jest zapisany garaf spójny, 1 zaś oznacza, że graf nie jest spójny.\n");
    return 1;
  }

  p = argv [1];
  czySpojny = atoi(argv [2]);

  printf("Rozpoczynam test funkcji sprawdzającej spójność grafu za pomocą algorytmu BFS\n");
  printf("Analizie zostannie poddany graf zapisany w pliku o nazwie %s.\n", p);

  if(czySpojny == 0) {
    printf("Zapisany tam graf jest spójny.\n");
  } else {
    printf("Zapisany tam graf nie jest spójny.\n");
  }

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
  
  int ile_elementow = graf->kolumny*graf->wiersze;
    
  bfs_t *output = malloc(sizeof(*output));
  output->odleglosc = malloc(ile_elementow*sizeof(*output->odleglosc));
  output->rodzic = malloc(ile_elementow*sizeof(*output->rodzic));
  output->kolor = malloc(ile_elementow*sizeof(*output->kolor));

  printf("\nRozpoczynam analizę grafu algorytmem BFS.\n");
  
  BFS(tablice->grafBFS, 0, ile_elementow, tablice->sasiedzi, output);
    
  for(int i=0;i<ile_elementow;i++){
    if(output->odleglosc[i]==-1){
      wynikBFS = 1;
      break;
    }     
  }
  
  if(wynikBFS == czySpojny) {
    printf("Funkcja analizująca graf pod względem spójności wykorzystując algorytm BFS wykazała ");
    if(wynikBFS == 0) {
      printf("spójność grafu!\n\nFunkcja działa prawidłowo!\n");
    } else {
      printf("nie spójność grafu!\n\nFunkcja działa prawidłowo!\n");
    }
  } else {
    printf("Funkcja analizująca graf pod względem spójności wykorzystując algorytm BFS zwróciła inny wynik niż przewidywano.\n\n");
    printf("Funkcja nie działa prawidłowo.\n");
  }

  czyszczenieTablic(tablice);
  czyszczenieGrafu(graf);
  return 0;
}