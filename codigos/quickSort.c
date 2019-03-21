#include <stdio.h>
#include <math.h>
#include <sys/time.h>
#include <time.h>
#include <stdlib.h>
void fill(int *v,int s, int e);
int partitionps(int *v,int s, int e);
int partition(int *v,int s, int e);
void quickSort(int* v,int s,int e);
double calc(struct timeval *t);
int* preenchevetorOrdenado(int tam);
int* preenchevetorIntercalado(int tam);
int testa(int *v, int x, int tam);
int* preencheAleatorio(int tam);
/*
	Para o pior caso desta função, é necessário na linha 37, trocar a função 
	que preenche o vetor pela função "prenchevetorOrdenado(n);"

	Para o caso médio desta função, é necessário na linha 37 , trocar a função
	que preenhe o vetor pela função, "preencheAleatorio(n);"
*/


int main()
{
	
	
      struct timeval start,end;
      double t = 0;
      unsigned i,n;
      int *v;
      int a = 0;
      for(n =100;n<=900;n+=100){
            t = 0;
            
            for(i = 0;i<10;i++){
                  v = preencheAleatorio(n);
                  gettimeofday(&start,NULL);
                  quickSort(v,0,n-1);
                  gettimeofday(&end,NULL);
                  t+= calc(&end)-calc(&start);
                  free(v);
                  }
            printf("%d %.10lf\n",n,t/10);  
          }

		

	
}
int partitionps(int *v,int s, int e){
	int l = s,i;
	int aux =0;
	for(i=s+1;i<=e;i++){
		if(v[i]<v[s]){
			l++;
			aux = v[i];		
			v[i] = v[l];
			v[l] = aux;
			
	}}
	aux = v[s];
	v[s]= v[l] ;
	v[l]= aux;
	 
	return l;}


int partition(int *v,int s, int e){
	int l = s;
	int aux =0,i;
	for(i=s;i<e;i++){
		if(v[i]<v[e]){
			
			aux = v[i];		
			v[i] = v[l];
			v[l] = aux;
			l++;
	}}
	aux = v[e];
	v[e]= v[l] ;
	v[l]= aux;
	 
	return l;}


void quickSort(int* v,int s,int e){
	
	if (s<e) {
		int p = partition(v,s,e);
		
		quickSort(v,s,p-1);
		quickSort(v,p+1,e);
	}
}
double calc(struct timeval *t) {
      return (double) t->tv_sec + t->tv_usec/(double)1e6;
}
int* preenchevetorOrdenado(int tam){
	int *v =(int*) malloc(tam*sizeof(int));
	int i = 0;
     while(i<=tam)
      {
		  v[i]= tam-i;
		  i++;
	
      }
      return v;
}
int* preenchevetorIntercalado(int tam){
	int *v = (int*) malloc(tam*sizeof(int));
	fill(v,0,tam-1);
	return v;
}

void fill(int *v,int s, int e){
	int m = (s+e)/2;
	if(e-s+1==3){
		v[e]=m+1;
		v[s]=m;
		v[s+1]=m+2;
	}else if (e-s+1){
		fill(v,s,m-1);
		fill(v,m+1,e);
		v[m]=v[e];
		v[e]=m+1;
	}
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
