#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

#include "BFS.h"
#include "czytanie.h"
#include "generator.h"

int main(int argc, char** argv) {
  int opt;
  int elementWywolania = 1;
  int czy_spojny=-1;
  int czy_wywolany=0;
  int czy_wlasne_wagi = 0;

  char* dprzedzial=NULL;
  char* gprzedzial=NULL;
  char* wprzedzial=NULL;
  char* input=NULL;
  char* output=NULL;

  char* k = NULL;
  char* w = NULL;
  char* wmin = NULL;
  char* wmax = NULL;

  while((opt = getopt(argc, argv, "f:bd:gwz:")) != -1) {
    switch(opt){
      case 'f':
        input=optarg;
        elementWywolania += 2;
        break;
      case 'b':
        czy_wywolany=1;
        elementWywolania ++;
        break;
      case 'd':
        dprzedzial=optarg;
        elementWywolania ++;
        break;
      case 'g':
        elementWywolania ++;
        k = argv[elementWywolania];
        elementWywolania ++;
        w = argv[elementWywolania];
        elementWywolania ++;
        break;
      case 'w':
        czy_wlasne_wagi = 1;
        elementWywolania ++;
        wmin = argv[elementWywolania];
        elementWywolania ++;
        wmax = argv[elementWywolania];
        elementWywolania ++;
        break;
      case 'z':
        output=optarg;
        elementWywolania += 2;
        break;
      default:
        fprintf(stderr, "podano złą opcję :<\n");
    }
  }
  graf_t *graf=malloc(sizeof (*graf));
  tablice_t *tablice=malloc(sizeof (*tablice));

  if(czy_wlasne_wagi != 0) {
    graf->wagaMin = atoi(wmin);
    graf->wagaMax = atoi(wmax);
  }
  
  if(input != NULL){
    int a = grafWTablice(graf,tablice,input);
    if(a==1){
      return 1;
    }
    printf("udało się przeczytać plik :>\n");
  } else{
    if(k != NULL) {
      graf->kolumny = atoi(k);
      graf->wiersze = atoi(w);
    } else {
      graf->kolumny = 10;
      graf->wiersze = 10;
    }
    printf("Program grafC rozpoczyna generacje grafu o wymiarach %d x %d.\n", graf->kolumny, graf->wiersze);
    wygenerujGraf(graf, tablice, output);
    
  }

  if(czy_wywolany==1){
    printf("argument b został wywołany\n");
    czy_spojny=BFS(tablice->grafBFS, 0, graf->kolumny*graf->wiersze, tablice->sasiedzi);
    if(czy_spojny==0){
      printf("Graf jest spójny\n");
    }else{
      printf("Graf nie jest spójny\n");
    }
  }
  
  return 0;
}