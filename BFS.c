#include <stdlib.h>
#include <stdio.h>

#include "czytanie.h"
#include "BFS.h"

void BFS(int ** graf, int wierz, int n, int * ile_sasiadow, bfs_t * output){
  //printf("zaczynamy!\n");
  int * kolejka =malloc(n*sizeof(*kolejka));
  int pocz=0;
  int kon=0;
  //printf("tyle wierzcholkow:%d\n", n);
  for(int i=0;i<n;i++){
    output->kolor[i]=0;
    output->odleglosc[i]=-1;
    output->rodzic[i]=-1;
  }
  output->kolor[wierz] = 1;
  output->odleglosc[wierz] = 0;
  kolejka[0]=wierz;
  kon++;
  
  while(pocz!=kon){
    int u=kolejka[pocz];
    pocz++;
    //printf("sprawdzamy wierzcholek:%d\n\n", u);
    
    for(int i =0;i<ile_sasiadow[u];i++){
      //printf("tyle sasiadow: %d\n\n", ile_sasiadow[u]);
      if (output->kolor[graf[u][i]]==0){
        output->kolor[graf[u][i]]=1;
        output->odleglosc[graf[u][i]]=output->odleglosc[u]+1;
        output->rodzic[graf[u][i]]=u;
        kolejka[kon]=graf[u][i];
        kon++;
      }
    }
    output->kolor[u]=2;
  }
  free(kolejka);
}

void czyszczenieBFS(bfs_t *bfs){
  free(bfs->kolor);
  free(bfs->rodzic);
  free(bfs->odleglosc);
  free(bfs);
}