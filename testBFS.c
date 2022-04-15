#include <stdio.h>
#include <stdlib.h>
#include <float.h>

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
    printf("0 oznacza, że w pliku jest zapisany graf spójny, 1 zaś oznacza, że graf nie jest spójny.\n");
    return 1;
  }

  p = argv [1];
  czySpojny = atoi(argv [2]);
  FILE *out = argc>3 ? fopen(argv[3], "w"):stdout;
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
    free(tablice->sasiedzi);
    free(tablice);
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

  tablice->grafBFS = malloc(ile_elementow * sizeof *tablice->grafBFS);

  for(int i = 0; i < ile_elementow; i++) {
    tablice->grafBFS [i] = malloc(tablice->sasiedzi[i] * sizeof *tablice->grafBFS[i]);
  }

  int indeks_bfs;
    for(int i =0;i<ile_elementow;i++){
      indeks_bfs=0;
      for(int j=0;j<ile_elementow;j++){
        if(graf->macierzSasiedztwa[i][j]!=DBL_MIN){
          tablice->grafBFS[i][indeks_bfs]=j;
          indeks_bfs++;
        }
      }
    }
  
  BFS(tablice->grafBFS, 0, ile_elementow, tablice->sasiedzi, output);
    
  for(int i=0;i<ile_elementow;i++){
    if(output->odleglosc[i]==-1){
      wynikBFS = 1;
      break;
    }     
  }
  
  if(wynikBFS == czySpojny) {
    fprintf(out, "Funkcja analizująca graf pod względem spójności wykorzystując algorytm BFS wykazała ");
    if(wynikBFS == 0) {
      fprintf(out, "spójność grafu!\n\nFunkcja działa prawidłowo!\n");
    } else {
      fprintf(out, "nie spójność grafu!\n\nFunkcja działa prawidłowo!\n\n\n");
    }
  } else {
    fprintf(out, "Funkcja analizująca graf pod względem spójności wykorzystując algorytm BFS zwróciła inny wynik niż przewidywano.\n\n");
    fprintf(out, "Funkcja nie działa prawidłowo.\n\n\n");
  }

  czyszczenieTablic(tablice);
  czyszczenieGrafu(graf);
  fclose(out);
  return 0;
}