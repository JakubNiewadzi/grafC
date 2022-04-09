#include "dijkstra.h"


void dijkstra(graf_t * g, int wierz, int n, double * droga){

  int u;
  
  int *poprzednik=malloc(n*sizeof(*poprzednik));
  int *kolejka=malloc(5*n*sizeof(*kolejka));

  
  for(int i=0;i<n;i++){
    droga[i]=DBL_MAX;
    poprzednik[i]=-1;
  }


  droga[wierz]=0;

  int pocz=0;
  int kon=0;
  

  for(int i =0;i<n;i++){
    if (g->macierzSasiedztwa[wierz][i]!=DBL_MIN){
      kolejka[kon]=i;
      kon++;
      droga[i]=g->macierzSasiedztwa[wierz][i];
      poprzednik[i]=wierz;
    }
  }
  

  double min = droga[0];
  int i_min=0;
  int tmp=0;
  
  while(pocz!=kon){
  

    for(int i=pocz;i<kon;i++){
      if (droga[kolejka[i]]<=min){
        min=droga[kolejka[i]];
        i_min=i;
      }
    }
    tmp=kolejka[pocz];
    kolejka[pocz]=kolejka[i_min];
    kolejka[i_min]=tmp;

    for(int i =0;i<n;i++){
      if(g->macierzSasiedztwa[kolejka[pocz]][i]!=DBL_MIN && droga[i]>g->macierzSasiedztwa[kolejka[pocz]][i]+droga[kolejka[pocz]]){
        kolejka[kon]=i;
        kon++;
        droga[i]=g->macierzSasiedztwa[kolejka[pocz]][i]+droga[kolejka[pocz]];
        poprzednik[i]=kolejka[pocz];
        g->macierzSasiedztwa[kolejka[pocz]][i]=DBL_MIN;
      }
    }
  
    pocz++;
  }
  
  for(int i =0;i<n;i++){
    if(droga[i] == DBL_MAX) {
      droga[i] = -1;  
    }
  }
  free(kolejka);
  free(poprzednik);
}