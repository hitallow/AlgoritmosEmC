#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <sys/time.h>
int* preenche(int tam);
void merge(int* v,int s,int m,int e);
void mergeSort(int* v, int s,int e);
double calc(struct timeval *t) ;


int main (){
	struct timeval start,end;
	double t =0;
	int *v;
	for(int n=100;n<5000;n+=100){
			t =0;
			
			for(int i =0; i<100;i++){
				v =preenche(n);
				
				gettimeofday(&start,NULL);
				
				mergeSort(v, 0, n-1);
				
				gettimeofday(&end,NULL);
				t += calc(&end) - calc(&start);
				
				free(v);
				}
		 printf("%d %.10lf\n",n,t/100); 
		
	}
	return 0;}


void merge(int* v,int s,int m,int e){
	int i = s;
	int j = m+1;
	int k = 0;
	
	int* w = (int*)malloc((e-s+1)*sizeof(int));
	
	while(k<e-s+1){
		if((v[i]<v[j] )&& (i<=m || j>e)){
				w[k] = v[i];
				i++;
		}else{
			w[k] = v[j];
			j++;
	}
	k++;
	}
	k =0;
	while(k<e-s+1){
		v[s+k] = w[k];
		k++;}
	
	free(w);
}	
void mergeSort(int* v, int s,int e){
	
	if(s<e){
		int m = (s+e)/2;
		mergeSort(v,s,m);
		mergeSort(v,m+1,e);
		merge(v,s,m,e);
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