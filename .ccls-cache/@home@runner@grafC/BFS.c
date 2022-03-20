#include <stdlib.h>
#include <stdio.h>

#include "czytanie.h"
#include "BFS.h"

int BFS(int ** graf, int wierz, int n, int * ile_sasiadow){
  //printf("zaczynamy!\n");
  int * kolor = malloc(n*sizeof(*kolor)); //0-biały, 1-szary, 2-czarny
  int * odleglosc = malloc(n*sizeof(*kolor));
  int * rodzic = malloc(n*sizeof(*kolor));
  int * kolejka =malloc(n*sizeof(*kolejka));
  int pocz=0;
  int kon=0;
  //printf("tyle wierzcholkow:%d\n", n);
  for(int i=0;i<n;i++){
    kolor[i]=0;
    odleglosc[i]=n+1;
    rodzic[i]=-1;
  }
  kolor[wierz] = 1;
  odleglosc[wierz] = 0;
  kolejka[0]=wierz;
  kon++;
  
  while(pocz!=kon){
    int u=kolejka[pocz];
    pocz++;
    //printf("sprawdzamy wierzcholek:%d\n\n", u);
    for(int i =1;i<ile_sasiadow[u]+1;i++){
      //printf("tyle sasiadow: %d\n\n", ile_sasiadow[u]);
      if (kolor[graf[u][i]]==0){
        kolor[graf[u][i]]=1;
        odleglosc[graf[u][i]]=odleglosc[u]+1;
        rodzic[graf[u][i]]=u;
        kolejka[kon]=graf[u][i];
        kon++;
      }
    }
    kolor[u]=2;
  }
  for(int i=0;i<n;i++){
    //printf("kolor:%d\n", kolor[i]);
    if(kolor[i]!=2){
      free(kolor);
      free(odleglosc);
      free(rodzic);
      free(kolejka);
      return 1;
    }
  }
  free(kolor);
  free(odleglosc);
  free(rodzic);
  free(kolejka);
  
  return 0; //0 - spójny, 1-niespójny
}

