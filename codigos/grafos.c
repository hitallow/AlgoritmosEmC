#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

/*
	Código para avaliação da terceira unidade da Disciplina de ED
	Ministrada por João Paulo.
	Aluno : Hítallo William

	O nome do rquivo TXT deve ser alterado para que o código funcione bem
*/


struct adj
{
	int v;
	struct adj* p;
};
struct no
{
	int v;
	int tadjs;
	struct adj* adjs;
	
};
struct grafo
{
	int tam;
	int alocados;
	struct no** nos;
};

struct grafo* newGrafo(int tam){
	struct grafo* g = (struct grafo*)malloc(sizeof(struct grafo));
	g->tam = tam;
	g->alocados = -1;
	g->nos = (struct no**) malloc (tam* sizeof(struct no));
	for(int i = 0 ; i < tam; i++)
	{
		g->nos[i] = NULL;
	}
	return g;
}
struct no* newNo(int v)
{
	struct no* aux =(struct no*) malloc(sizeof(struct no));
	aux->v = v;
	aux->tadjs = 0;
	aux->adjs = NULL;
	return aux;
}
void destructG(struct grafo* grafo){

	for(int i = 0 ; i< grafo->alocados+1; i++)
	{
		struct no* auxNo = grafo->nos[i];
		struct adj* auxAdj = grafo->nos[i]->adjs,*auxAdjFree;
		while( auxAdj!=NULL)
		{
			auxAdjFree = auxAdj->p;
			free(auxAdj);
			auxAdj = auxAdjFree;
		}
		free(grafo->nos[i]);

	}
	grafo->tam = 0;
	grafo->alocados = 0;
	free(grafo);
}
void atualizaGrafo(struct grafo** grafo)
{
	
	struct grafo* auxGrafo = newGrafo(((*grafo)->tam)*2);
	if(auxGrafo == NULL)
	{
		exit(1);
	}
	auxGrafo->alocados = (*grafo)->alocados;

	for(int i=0;i<(*grafo)->tam ; i++)
	{
		auxGrafo->nos[i] = (*grafo)->nos[i];
		
	}
	(*grafo)->tam = auxGrafo->tam;
	(*grafo)->nos = auxGrafo->nos;
	(*grafo)->alocados = auxGrafo->alocados;

}
int confereNo(struct grafo* grafo, int v)
{
	for (int i = 0; i < grafo->alocados+1; i++)
	{
		if (grafo->nos[i]->v == v)
		{
			return 1;
		}
	}
	return 0;
}
void insereNo(struct grafo** grafo, int v)
{
	
	if((*grafo) == NULL)
		return;
	if(!(confereNo(*grafo , v))){
		if((*grafo)->tam <= (*grafo)->alocados +1)
			atualizaGrafo(grafo);
		struct no* aux = newNo(v);
		(*grafo)->nos[(*grafo)->alocados+1] = aux;
		(*grafo)->alocados+=1;
	}


}
struct adj* newAdj(int v){
	struct adj* aux = (struct adj*) malloc(sizeof(struct adj));
	aux->v = v;
	aux->p= NULL;

}

void insertAdj(struct grafo** grafo, int v, int adj)
{

	if((*grafo) == NULL)
		return;
	
	if(confereNo(*grafo , adj)){
		for(int i = 0; i <= ((*grafo)->alocados); i++)
		{
			struct adj* auxAdj = newAdj(adj);
			if((*grafo)->nos[i]->v == v)
			{
			
				if((*grafo)->nos[i]->adjs == NULL)
				{
					(*grafo)->nos[i]->adjs = auxAdj;
				}
				else{
					auxAdj->p = (*grafo)->nos[i]->adjs;
					(*grafo)->nos[i]->adjs = auxAdj;
				}
				(*grafo)->nos[i]->tadjs+=1;
			break;
			}
		}
	}

}
void printGrafo(struct grafo* grafo)
{
	printf("\nPRINTANDO GRAFO\n");

	for(int i = 0; i < grafo->alocados+1 ; i++){
		struct no* aux = grafo->nos[i];
		struct adj* auxAdj = grafo->nos[i]->adjs;
		int j = 0;
		printf("Nó: %d > ", aux->v);
		while( auxAdj != NULL){
			printf(" | %d |",auxAdj->v );
			auxAdj = auxAdj->p;
		}
		printf("\n");
	}
}

void recoveryGrafo(struct grafo** grafo)
	{
	FILE * arquivo = fopen("t.txt" , "r");
	char t[3],numS[10], adjS[10] ; 
	int num , adj;
	fscanf(arquivo , "%s",  t);
	while(strcmp(t, "#") != 0){
		num = atoi(t);
		insereNo(grafo,num);
		fscanf(arquivo , "%s",  t);
	}
	while(fscanf(arquivo, "%s %s",numS, adjS)!=EOF){
		num = atoi(numS);
		adj = atoi(adjS);
		insertAdj(grafo , num , adj);
		
	}
	fclose(arquivo);

}
int main(int argc, char const *argv[])
{
	struct grafo* i = newGrafo(1);
	recoveryGrafo(&i);
	printGrafo(i);
	destructG(i);
	
	
	return 0;
}