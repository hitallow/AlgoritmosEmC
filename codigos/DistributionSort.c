#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include <stdlib.h>

int* zeros(int tam);
int max(int* v,int tam);
int min(int* v,int tam);
void distributionSort(int *v,int n);
int* preenchevetor(int n){;
double calc(struct timeval *t);

int main(){
	struct timeval start,end ;
	double t =0 ;
	int* v;

	for(int n =100;n<5000;n+=100){
		t =0;
		for(int i =0;i<n;i++){
			v = preenchevetor(n);
			gettimeofday(&start,NULL);
			distributionSort(v,n);
			gettimeofday(&end,NULL);
			t+= calc(&end) - calc(&start);
			free(v);
	}
	printf("%d %.10lf\n", n, t/n );
}
}
int* zeros(int tam){
	int* v = (int*) malloc(tam*sizeof(int));
	for(int i = 0;i<tam;i++)
		v[i] =0;
	return v;
}
int max(int* v,int tam){
	int aux = v[0];
	for(int i = 1;i<tam;i++){
		if(aux<v[i]){
			aux = v[i];}}
	return aux;
}
int min(int* v,int tam){
	int aux = v[0];
	for(int i = 1;i<tam;i++){
		if(v[i]<aux){
			aux = v[i];
		}
	}
	return aux;
}
void distributionSort(int *v,int n){
	int l = min(v,n);
	int b = max(v,n);
	int k = b-l+1;
	int* w = zeros(k);
	int* y = zeros(n);
	for(int i=0;i<n;i++){
		w[v[i]-l+1]++;	
	}
	for(int i = 0;i<k;i++){
		w[i] = w[i]+ w[i-1];
		}
	int j = 0;
	for(int i = 0; i<n;i++){
		j = v[i]-l;
		y[w[j]] = v[i];
		w[j]--;
	}
	for(int i =0;i<n;i++)
		v[i] = y [i];
	free(y);
	free(w);

}
int* preenchevetor(int n){
	int* v = (int*)malloc(n*sizeof(int));

	
	for(int i = 0;i<n;i++)
		v[i] =n-i;
	return v;
}
double calc(struct timeval *t) {
      return (double) t->tv_sec + t->tv_usec/(double)1e6;
}
