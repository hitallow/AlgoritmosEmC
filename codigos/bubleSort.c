#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <sys/time.h>
void bublesort(int* v, int n);
int* preenche(int tam);
double calc(struct timeval *t);
int main (){
	struct timeval start,end;
	double t =0;
	int *v;
	for(int n=100;n<1000;n+=100){
			t =0;
			for(int i =0; i<n;i++){
				v =preenche(n);
				gettimeofday(&start,NULL);
				bublesort(v,n);
				gettimeofday(&end,NULL);
				t += calc(&end) - calc(&start);
				free(v);
				}
		 printf("%d %.10lf\n",n,t/n); 
		
	}
	return 0;}
void bublesort(int* v, int n){
	int aux =0;
	for(int i = 0; i<n;i++){
		for(int j=0;j-i-1;j++){
			if(v[j]>v[j+1]){
				aux =v[j];
				v[j+1] = v[j];
				v[j] = aux; 
			}}
		}
	}
int* preenche(int tam){
	int *v;
	v = (int*)malloc(tam*sizeof(int));
	int i=0;
	while(tam)
		v[i] = tam--;
	return v;
	}
double calc(struct timeval *t) {
      return (double) t->tv_sec + t->tv_usec/(double)1e6;}