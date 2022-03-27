#include "dijkstra.h"


void dijkstra(graf_t * g, int wierz, int n, double * droga){

  int u;
  
  int * poprzednik = malloc(n*sizeof(*poprzednik));
  int * kolejka = malloc(n*sizeof(*kolejka));

  
  for(int i=0;i<n;i++){
    droga[i]=DBL_MAX;
    poprzednik[i]=-1;
  }


  droga[wierz]=0;

  int pocz=0;
  int kon=0;
  
  
  for(int i =0;i<n;i++){
    if (g->macierzSasiedztwa[wierz][i]!=DBL_MIN){
      kolejka[kon++]=i;
      droga[i]=g->macierzSasiedztwa[wierz][i];
      poprzednik[i]=wierz;
    }
  }
  

  double min = droga[0];
  int i_min;
  int tmp;
  
  while(pocz!=kon){
    for(int i=pocz;i<kon;i++){
      if (droga[i]<=min){
        min=droga[i];
        i_min=i;
      }
    }
    tmp=kolejka[pocz];
    kolejka[pocz]=kolejka[i_min];
    kolejka[i_min]=tmp;
    for(int i =0;i<n;i++){
      if(g->macierzSasiedztwa[kolejka[pocz]][i]!=DBL_MIN && droga[i]>g->macierzSasiedztwa[kolejka[pocz]][i]+droga[kolejka[pocz]]){
        kolejka[kon++]=i;
        droga[i]=g->macierzSasiedztwa[kolejka[pocz]][i]+droga[kolejka[pocz]];
        poprzednik[i]=kolejka[pocz];
      }
    }
    pocz++;
  }
  for(int i =0;i<n;i++){
    printf("Droga do wierzchołka %d wynosi %lf \n", i, droga[i]);
  }

}