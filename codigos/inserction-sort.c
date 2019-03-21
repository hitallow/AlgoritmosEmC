#include <stdio.h>
#include <math.h>
#include <sys/time.h>
#include <time.h>
#include <stdlib.h>

void insertionSortC(int* v, int tamanho) ;
int* preenchevetorDecrescente(int tam);
int* preenchevetorOrdenado(int tam);
double calc(struct timeval *t);
int testa(int *v, int x, int tam);
int* preencheAleatorio(int tam);

int main()
{
      struct timeval start,end;
      double t = 0;
      unsigned i,n;
      int *v;
      for(n =100;n<=10000;n+=100){
            t = 0;
            for(i = 0;i<10;i++){
                  v = preencheAleatorio(n);
                  gettimeofday(&start,NULL);
                  insertionSortC(v,n);
                  gettimeofday(&end,NULL);
                  t+= calc(&end)-calc(&start);
                  free(v);
                  }
            printf("%d %.10lf\n",n,t/10);  
          }

	
	return 0;
}
void insertionSortC(int* v, int tamanho) 
{
      int i, j, aux;
      for (i = 1; i < tamanho; i++) 
      {
            j = i;
            while (j > 0 && v[j - 1] > v[j]) 
            {
                  aux= v[j];
                  v[j] = v[j - 1];
                  v[j - 1] = aux;
                  j--;
                  }
      }
}
int* preenchevetorOrdenado(int tam){
      int *v =(int*) malloc(tam*sizeof(int));
      int i = 0;
     while(i<=tam)
      {
           v[i] = i++;
               //v[i]= tam-i++;
      }
      return v;
}
int* preenchevetorDecrescente(int tam){
      int *v =(int*) malloc(tam*sizeof(int));
      int i = 0;
     while(i<=tam)
               v[i]= tam-i++;
      
      return v;
}
double calc(struct timeval *t) {
      return (double) t->tv_sec + t->tv_usec/(double)1e6;
}
int testa(int *v, int x, int tam){
   if (tam == 0)
      return 1;
   for(int i =0; i< tam; i++){
      if(x == v[i])
         return 0;
   }
   return 1;
   }


int* preencheAleatorio(int tam){
   int* v = (int*) malloc(tam*sizeof(int));
   int i = 0, a;
   srand(time(NULL));
   while(i<tam){
      a= rand()%tam+1;     
      if(testa(v,a,i))
         v[i] = a;
      i+=testa(v,a,i);
   }
   return v;
}
