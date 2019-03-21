#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include <stdlib.h>

int* zeros(int n);
int* preenche(int n);
 int *coutingSort (int *v, int n);
 double calc(struct timeval *t) ;

int main()
{
	struct timeval start,end;
    double t = 0;
    unsigned i,n;
    int *v;
    int* newV;
    for(n =100;n<=1000;n+=100){
        t = 0;
        for(i = 0;i<n;i++){
            v = preenche(n);
            gettimeofday(&start,NULL);
            newV = coutingSort(v,n);
            gettimeofday(&end,NULL);
            t+= calc(&end)-calc(&start);
            free(v);
            free(newV);
                  }
        printf("%d %.10lf\n",n,t/n);  
          }
	return 0;
	
}
int* zeros(int n){
    int* v = (int*) malloc(n*sizeof(int));
    for(int i =0;i<n;i++)
        v[i] = 0;
    return v;
}


int* preenche(int n){
    int* v = (int*)malloc(n*sizeof(int));
    for(int i =0;i<n;i++)
        v[i] = n-i;
    return v;
}
 int *coutingSort (int *v, int n){
    int *w = zeros(n);
    int *c = zeros(n);

    for(int i = 0; i < n; i++){

        for(int j = 0; j < n; j++){

            if(v[j] < v[i]){

                c[i] = c[i]+1;

            }
        }

    }

    for(int k = 0; k < n; k++ ){

        w[c[k]] = v[k];
    }

    return w;

 }
 double calc(struct timeval *t) {
      return (double) t->tv_sec + t->tv_usec/(double)1e6;
}

