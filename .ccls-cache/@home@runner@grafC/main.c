#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>

#include "BFS.h"
#include "czytanie.h"
#include "generator.h"
#include "dijkstra.h"

int main(int argc, char** argv) {
  int opt;
  int elementWywolania = 1;
  int czy_wywolany=0;
  int czy_wlasne_wagi = 0;
  int poczatek;
  int koniec=-1;
  int czy_dijkstra=0;
  
  char* gprzedzial=NULL;
  char* wprzedzial=NULL;
  char* input=NULL;
  char* output=NULL;

  char* k = NULL;
  char* w = NULL;
  char* wmin = NULL;
  char* wmax = NULL;

  while((opt = getopt(argc, argv, "f:bdgwz:h")) != -1) {
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
        czy_dijkstra=1;
        elementWywolania ++;
        if(elementWywolania < argc && argv[elementWywolania] [0] != '-') {
          poczatek = atoi(argv[elementWywolania]);
          elementWywolania ++;
        } else {
          printf("Podczas wywoływania argumentu -d wymagane jest podanie początkowego wierzchołka wymaganego do analizy grafu za pomocą algorytmu Dijkstry.\nNie można wywołać argumentu bez tego parametru\n");
          return 1;
        }
        if(elementWywolania < argc && argv[elementWywolania] [0] != '-') {
          koniec = atoi(argv[elementWywolania]);
          elementWywolania++;
        }
        break;
      case 'g':
        elementWywolania ++;
        if(elementWywolania < argc && argv[elementWywolania] [0] != '-') {
          k = argv[elementWywolania];
          elementWywolania ++;
        }
        if(elementWywolania < argc && argv[elementWywolania] [0] != '-') {
          w = argv[elementWywolania];
          elementWywolania ++;
        }
        break;
      case 'w':
        czy_wlasne_wagi = 1;
        elementWywolania ++;
        if(elementWywolania < argc && argv[elementWywolania] [0] != '-') {
          wmin = argv[elementWywolania];
          elementWywolania ++;
        } else {
          printf("Podczas wywoływania argumentu -w należy podać dwa parametry: wage minimalną i wagę maksymalną.\nNie można wywołać argumentu bez tych parametrów\n");
          return 1;
        }
        if(elementWywolania < argc && argv[elementWywolania] [0] != '-') {
          wmax = argv[elementWywolania];
          elementWywolania ++;
        } else {
          printf("Podczas wywoływania argumentu -w należy podać dwa parametry: wage minimalną i wagę maksymalną.\nNie można wywołać argumentu bez tych parametrów\n");
          return 1;
        }
        break;
      case 'z':
        output=optarg;
        elementWywolania += 2;
        break;
      case 'h':
        printf("Wywołano help do pragramu grafC.\n");
        printf("grafC to program do analizy grafów za pomocą algorytmów BFS i Dijkstry.\n");
        printf("Oto lista akcptowanych przez program argumentów wywołania:\n\n");
        printf("-f plik -> podajemy plik, w którym zapisane są wierzchołki naszego grafu i wagi połączeń między nimi.\n\tZ tego pliku będzeię on czytany i przekonwertowywany na tablicę sąsiedztwa.\n\n");
        printf("-g k w -> generacja grafu o podanej ilości kolumn i wierszy, gdzie k - liczba kolumn, a w liczba wierszy\n\toba paramentry muszą być liczbami naturalnymi.\n\tParametry nie są obowiązkowe i przy braku ich podania zostanie wygenerowany graf 10 x 10.\n\n");
        printf("-b -> program zastosuje algorytm BFS do analizy grafu pod kątem jego zbierzności.\n\n");
        printf("-d a b -> program zastosuje algorytm Dijkstry do analizy grafu pod kątem wyznaczania najkrótszych tras.\n\tParametr a to wierzchołek od którego algorytm zostanie zatosowany.\n\tParametr b natomiast to ewentualny punkt końcowy wyznaczanej drogi z punktu a. Jest to parametr nie obowiązkowy.\n\tOba paramentry muszą być liczbami naturalnymi.\n\n");
        printf("-w min max -> Ustalenie przedziału wag, gdzie min to najniższa waga, a max maksymalna.\n\tOba parametry mogą być liczbami zmiennoprzecinkowymi.\n\tW przypadku nie wybrania tego argumentu generowany graf będzia miał wagi zawarte w przedziale 0 - 10\n\n");
        printf("-z plik -> pozwala zapisać wyniki wykonania programu i ewentualnie wygenerowany graf do pliku o podanej nazwie.\n\n");
        printf("\tDo prawidłowego działania programu wymagane jest podanie argumentów wywołujących działanie algorytmu BFS lub Dijkstry lub obu.\nReszta argumentów jest opcjonalna.\n\tW przypadku nie podania pliku z którego program mógłby odczytać graf lub w przypadku nie sprecyzowania generacji takowego pliku\nprogram wygeneruje graf 10 x 10 z wagami z zakresu 0 - 10.\n");
        return 0;
        break;
      default:
        fprintf(stderr, "podano złą opcję :<\n");
    }
  }

  if(czy_wywolany == 0 && czy_dijkstra == 0) {
    printf("Podczas wywoływania programu nie podano rzadnej metody analizy grafu!\n");
    printf("Jednym z argumentów wywołania powinien być -b lub -d lub oba.\n");
    return 0;
  }
  
  graf_t *graf=malloc(sizeof (*graf));
  tablice_t *tablice=malloc(sizeof (*tablice));

  if(czy_wlasne_wagi != 0) {
    graf->wagaMin = atof(wmin);
    graf->wagaMax = atof(wmax);

    if(graf->wagaMin > graf->wagaMax) {
      printf("Podana przez użytkownika waga minimalna jest wieksza od wagi maksymalnej!\nPodczas wywoływania argumentu -w pierwszą zmienną powinna być waga minimalna, a potem maksymalna.\nNie odwrotnie!\nProszę poprawić kolejność wag lub podać inne ich wartości.\n");
      return 1;
    }
  }
  
  if(input != NULL){
    int a = grafWTablice(graf,tablice,input);
    if(a==1){
      return 1;
    }
    printf("Udało się prawidłowo odczytać podany przez użytkownika plik.\n");
  } else{
    if(k != NULL) {
      graf->kolumny = atoi(k);
      graf->wiersze = atoi(w);
    }
    
    if(graf->kolumny == 0 || graf->wiersze == 0) {
      graf->kolumny = 10;
      graf->wiersze = 10;
    }
    printf("Program grafC rozpoczyna generacje grafu o wymiarach %d x %d.\n", graf->kolumny, graf->wiersze);
    wygenerujGraf(graf, tablice, output);
    
    }

  if(czy_wywolany==1){
    int czy_spojny=0;
    printf("Program rozpoczyna analizę grafu algorytmem BFS.\n\n");

    int ile_elementow = graf->kolumny*graf->wiersze;
    
    bfs_t *output = malloc(sizeof(*output));
    output->odleglosc = malloc(ile_elementow*sizeof(*output->odleglosc));
    output->rodzic = malloc(ile_elementow*sizeof(*output->rodzic));
    output->kolor = malloc(ile_elementow*sizeof(*output->kolor));
    
    BFS(tablice->grafBFS, 0, ile_elementow, tablice->sasiedzi, output);
    
    /*for(int i=0;i<ile_elementow;i++){
      printf("zawartość tablicy z rodzicami: %d\n", output->rodzic[i]);
    }
    printf("\n");
    for(int i=0;i<ile_elementow;i++){
      printf("zawartość tablicy z kolorami: %d\n", output->kolor[i]);
    }
      printf("\n");*/
    for(int i=0;i<ile_elementow;i++){
      printf("Zawartość tablicy z odleglosciami: %d\n", output->odleglosc[i]);
      if(output->odleglosc[i]==-1){
        czy_spojny=1;
        break;
      }     
    }
    if(czy_spojny==0){
      printf("\nGraf jest spójny.\n");
    }else{
      printf("\nGraf nie jest spójny.\n");
    }
  }

  if(czy_dijkstra==1){
    if(poczatek > graf->kolumny * graf->wiersze - 1 || poczatek < 0) {
      printf("\nPoczątkowy węzeł podany przez użytkownika do analizy grafu algorytmem Dijkstry nie zawiera się w grafie!\nProszę podać wierzchołek znajdujący się w przedziale od 0 do %d\n", graf->wiersze * graf->kolumny - 1);
      return 1;
    }
    
    if(koniec > graf->kolumny * graf->wiersze - 1) {
      printf("\nKońcowy węzeł podany przez użytkownika do analizy grafu algorytmem Dijkstry nie zawiera się w grafie!\nProszę podać wierzchołek znajdujący się w przedziale od 0 do %d\n", graf->wiersze * graf->kolumny - 1);
      return 1;
    }
    printf("\nProgram rozpoczyna analizę grafu algorytmem Dijkstry.\n\n");
    /*for(int i=0;i<graf->kolumny*graf->wiersze;i++){
      for(int j=0;j<graf->kolumny*graf->wiersze;j++)
        printf("%lf\t", graf->macierzSasiedztwa[i][j]);
      printf("\n");
    }*/
    double * droga = malloc(graf->kolumny * graf->wiersze * sizeof(*droga));
    dijkstra(graf, poczatek, graf->kolumny*graf->wiersze, droga);

    if(koniec > 0) {
      printf("\nNajkrótsza droga z wierzchołka %d do wierzchołka %d wynosi %lf\n",poczatek, koniec, droga[koniec]);
    }
  }

  czyszczenieTablic(tablice);
  czyszczenieGrafu(graf);
  
  return 0;
}