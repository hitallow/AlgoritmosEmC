#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include <inttypes.h>
/* Codigos referentes a tabela de disperção */
struct info
{
	int v;
	struct info *p;
};
struct table
{
	int qtd;
	int m;
	struct info** itens;
};


struct table* newTable(int tam)
{
	struct table* aux = (struct table*) malloc(sizeof(struct table));
	if(aux == NULL)
		return NULL;
	aux->m = tam;
	aux->qtd = 0;
	aux->itens = (struct info**) malloc(aux->m*sizeof(struct info*));
	if(aux->itens == NULL){
		free(aux);
		return NULL;
	}
	for(int i=0;i<aux->m;i++)
		aux->itens[i] = NULL;
	return aux;
}


struct info* newInfo(int v){
	struct info* aux =(struct info*) malloc(sizeof(struct info));
	aux->v = v;
	aux->p = NULL;
	return aux;
}

int keyDivisao(int v , int tam){
	return (v%tam);
}
void destructTable(struct table* tabela){
	for(int i= 0; i < tabela->m ; i++)
	{
		struct info* aux = tabela->itens[i], *prox;
		while(aux != NULL)
		{
			prox = aux->p;
			free(aux);
			aux = prox;
		}
		// free(tabela->itens[i]);
		
	}

	 free(tabela);
}
void printTable(struct table* tabela)
{
	printf("Itens inseridos: %d \n",tabela->m);
	for(int i = 0 ; i< tabela->m; i++)
	{	
		printf("i = %d ->",i);
		struct info* aux = tabela->itens[i];
		while(aux != NULL)
		{
			printf(" %d ",aux->v );
			aux = aux->p;
		}
		printf("\n");
	}
}
struct info* searchTable(struct table* tabela, int x)
{
	int key = keyDivisao(x , tabela->m);
	for(struct info* aux = tabela->itens[key] ; aux!= NULL ; aux = aux->p)
	{
		if(aux->v == x)
			return aux;
	}
	return NULL;
}

void atualiza(struct table** tabela){
	
	struct table* auxTable = newTable(2*((*tabela)->m));
	for(int i = 0; i < (*tabela)->m ; i++)
	{
		struct info* aux = (*tabela)->itens[i];
		while(aux!= NULL)
		{
			unsigned int pos = keyDivisao(aux->v , auxTable->m);
			struct info* auxInfo = newInfo(aux->v);
			if(auxTable->itens[pos] == NULL)
				auxTable->itens[pos] = auxInfo;
			else
			{
				auxInfo->p = auxTable->itens[pos];
				auxTable->itens[pos] = auxInfo;
			}
			aux = aux->p;
			auxTable->qtd++;
		}
	}
	(*tabela)->itens = auxTable->itens;
	(*tabela)->m = auxTable->m;
	(*tabela)->qtd = auxTable->qtd;
	

}
void insertTable(struct table** tabela , int v)
{
	if((*tabela)->m == (*tabela)->qtd)
	{
		atualiza(tabela);
		
	}
	unsigned int pos = keyDivisao( v , (*tabela)->m);

	struct info* novo = (struct info*) malloc(sizeof(struct info));
	novo->v = v;
	if( (*tabela)->itens[pos] == NULL)
	{
		
		(*tabela)->itens[pos] = novo;
	}else{
		novo->p = (*tabela)->itens[pos] ;
		(*tabela)->itens[pos] = novo; 	
	}
	(*tabela)->qtd++;	

}

/*


Códigos referentes a AVL


*/
struct tnode{
	int v;
	int h;
	struct tnode * l;
	struct tnode* r;
	struct tnode* p;
	
	};

struct tnode* newtnode(int v){
	struct tnode* n = (struct tnode*) malloc(sizeof(struct tnode));
	if (n == NULL)
	{
		exit(1);
	}
	n->v = v;
	n->h = 1;
	n->l = NULL;
	n->r = NULL;
	return n;
}



int max(int a, int b)
{
	if(a>=b)
		return a;
	return b;
}
int altura (struct tnode* n)
{
	if(n == NULL)
		return 0;
	return n->h;
}



void atualizaAlt(struct tnode* n)
{
	if(n == NULL)
		return;
	if(altura(n->l) > altura(n->r))
		n->h = altura(n->l)+1;
	else 
		n->h = altura(n->r)+1;	
}
void re(struct tnode *x)
{
	struct tnode *y = x->r;
	struct tnode *b = y->l;
	if(x->p != NULL)
	{
		if(x->p->r == x)
			x->p->r = y;
		else
			x->p->l = y;
	}
	if(x->p != NULL)
		y->p = x->p;
	else 
		y->p = NULL;
	x->p = y;
	y->l = x;
	if(b!=NULL)
	{
		b->p = x;
		x->r = b;
	}
	else
		x->r = NULL;
}  
void rd(struct tnode *x)
{
	struct tnode *y = x->l;
	struct tnode *b = y->r;
	if (x->p != NULL)
	{
		if(x->p->l == x)
			x->p->l = y;
		else
			x->p->r = y;	
	}
	if (x->p != NULL)
	{
		y->p = x->p;
	}else
		y->p = NULL;
	x->p = y;
	y->r =x;
	if(b!=NULL)
	{	
		b->p = x;
		x->l = b;	
	}
	else
		x->l = NULL;
}


void updatet(struct tnode *n,struct tnode **r)
{
	unsigned int h = (max(altura(n->r), altura(n->l))+1);

	if(n->h != h)
	{
		n->h = h;
		if(abs(altura(n->r)- altura(n->l))>1)
		{
			
			if(altura(n->r) > altura(n->l))
			{
				if(altura(n->r->r)> altura(n->r->l))
				{
					//printf("Caso1 em %d %p\n\n",n->v,n);
					re(n);
					atualizaAlt(n);
					atualizaAlt(n->p);
				}else
				{
					//printf("Caso3 em %d %p\n\n",n->v,n);
					rd(n->r);
					re(n);
					atualizaAlt(n);
					atualizaAlt(n->p->r);
					atualizaAlt(n->p);
				}	
			}else if(altura(n->l) > altura(n->r))
				{
					if(altura(n->l->l) > altura(n->l->r))
					{
						//printf("Caso2 em %d %p\n\n",n->v,n);
						rd(n);
						atualizaAlt(n);
						atualizaAlt(n->p);
						
					}else{
						//printf("Caso4 em %d %p\n\n",n->v,n);
						re(n->l);

						rd(n);
						atualizaAlt(n);
						atualizaAlt(n->p->l);
						atualizaAlt(n->p);
					}	
				}	
				
			if(n == (*r))
				*r = n->p;
		}
	}	
	if(n->p != NULL)
	{
		updatet(n->p,r);
	}
	
	}

void tinsert(struct tnode **R, int v){
	struct tnode *f,*p, *w = newtnode(v);
	if((*R) == NULL)
		(*R) = w;
	else
	{	
		p = *R;
		while(p!=NULL)
		{ 
			f = p;
			if(p->v > w->v)
				p = p->l;
			else
				p = p->r;
		}
	
		w->p = f;
		if (w->v == f->v)
			return;
		if(w->v < f->v)
			f->l = w;
		else 
			f->r = w;
		updatet(w->p,R);
	}		
}

struct tnode* tsearch(struct tnode* R, int x){
	if (R!=NULL){
		if(R->v == x)
			return R;
		else if(R->v < x)
			return tsearch(R->r,x);
		else 
			return tsearch(R->l,x);
	}
	return NULL;
}

void tprint(struct tnode *r){
	if (r!=NULL){
		tprint(r->l);
		printf("%p || %d h=%d p=%p || L = %p R =%p\n",r,r->v,r->h,r->p,r->l,r->r);
		tprint(r->r);
	}
}


void tremove(struct tnode* r)
{
	if(r!=NULL)
	{
		tremove(r->l);
		tremove(r->r);
		free(r);
	}
	
}	
double calc(struct timeval *t)
{
    return (double) t->tv_sec + t->tv_usec/(double)1e6;
}

void preenche(struct tnode **r, int n)
{	
	srand(time(NULL));
	int a,i =0;
	while(i < n)
	{
		a = rand()%(10*n);
		if(tsearch(*r,a)==NULL)
		{
			//printf("\nInserindo: %d\n",a );
			//getchar();
			tinsert(r,a);
			
			//tprint(*r);
			i++;
		}
	}
}

void removeAVLandInsertTable(struct table** tabela, struct tnode* AVL)
{
	if(AVL!=NULL)
	{
		removeAVLandInsertTable(tabela, AVL->l);
		removeAVLandInsertTable(tabela, AVL->r);
		insertTable(tabela,AVL->v );
	
		free(AVL);
	}
}
int main()
{

	struct table * aux = newTable(1);
	struct tnode* r = NULL;
	preenche(&r, 15);
	tprint(r);
	removeAVLandInsertTable(&aux,r);
	printTable(aux);
	destructTable(aux);
	printf("\n\n\n");
	printTable(aux);
	return 0;
}
