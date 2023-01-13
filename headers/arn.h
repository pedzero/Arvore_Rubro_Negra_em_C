#ifndef ARB_H
#define ARB_H

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<windows.h>

#define RED 4
#define BLACK 7

typedef struct No TNo;

typedef struct No{
	TNo *esq, *dir, *pai;
	bool cor;
	long chave;
}TNo;

typedef struct Arvore{
	TNo *raiz;
}TArvore;

void rotacaoEsq(TArvore *arvore, TNo *no){
	TNo *p = no, *q = no->dir, *pai = p->pai;
	
	if(pai != NULL){
		if(pai->esq == p) 
			pai->esq = q;
		else 
			pai->dir = q;
	}else{
		arvore->raiz = q;
	}
	
	q->pai = pai;
	p->pai = q;
	p->dir = q->esq;
	if(p->dir != NULL)
		p->dir->pai = p;
	
	q->esq = p;
}

void rotacaoDir(TArvore *arvore, TNo *no){
	TNo *p = no, *q = no->esq, *pai = p->pai;
	
	if(pai != NULL){
		if(pai->esq == p)
			pai->esq = q;
		else 
			pai->dir = q;
	}else{
		arvore->raiz = q;
	}
	
	q->pai = pai;
	p->pai = q;
	p->esq = q->dir;
	if(p->esq)
		p->esq->pai = p;
	
	q->dir = p;
}

void inicializa(TArvore *arvore){
	arvore->raiz = NULL;
}

void inicializaNo(TNo *no){
	memset(no, 0, sizeof(no)); 
	no->dir = NULL;
	no->esq = NULL;
	no->pai = NULL;
}

int insereNo(TArvore *arvore, TNo *no, long chave){
	TNo *pai, *avo, *tio;
	
	pai = arvore->raiz;
	if(pai != NULL){ 
		while(1){ 
			if(chave < pai->chave){
				if(pai->esq != NULL){
					pai = pai->esq;
				}else{
					pai->esq = no;
					break;
				}
			}else{
				if(chave > pai->chave){
					if(pai->dir != NULL){
						pai = pai->dir;
					}else{
						pai->dir = no;
						break;
					}
				}else{
					return -1; 
				}
			}
		}
	}else{
		arvore->raiz = no;
	}
	no->chave = chave;
	no->esq = no->dir = NULL;
	no->pai = pai;
	no->cor = true;
	
	while(pai != NULL && pai->cor){
		avo = pai->pai;
		if(pai == avo->esq){ 
			tio = avo->dir;
			if(tio != NULL && tio->cor){ 
				pai->cor = tio->cor = false;
				avo->cor = true;
				no = avo;
			}else{
				if(no == pai->dir){ 
					rotacaoEsq(arvore, pai);
					no = pai;
					pai = no->pai;
				}
				pai->cor = false; 
				avo->cor = true;
				rotacaoDir(arvore, avo);
			}
		}else{ 
			tio = avo->esq;
			if(tio != NULL && tio->cor){ 
				pai->cor = tio->cor = false;
				avo->cor = true;
				no = avo;
			}else{
				if(no == pai->esq){ 
					rotacaoDir(arvore, pai);
					no = pai;
					pai = no->pai;
				}
				pai->cor = false; 
				avo->cor = true;
				rotacaoEsq(arvore, avo);
			}
		}
		pai = no->pai;
	}
	arvore->raiz->cor = false;
	return 0;
}

void deletaNo(TArvore *arvore, TNo *no){
	TNo *pai = no->pai, *esq = no->esq, *dir = no->dir;
	TNo *prox, *irmao;
	bool cor;
	
	if(esq == NULL){
		prox = dir;
	}else 
		if(dir == NULL){
			prox = esq;
		}else{
			prox = dir;
			while(prox->esq != NULL)
				prox = prox->esq;
		}
	
	if(pai != NULL){
		if(pai->esq == no)
			pai->esq = prox;
		else
			pai->dir = prox;
	}else{
		arvore->raiz = prox;
	}
	
	if(esq != NULL && dir != NULL){
		cor = prox->cor;
		prox->cor = no->cor;
		prox->esq = esq;
		esq->pai = prox;
		if(prox != dir){ 
			pai = prox->pai; 
			prox->pai = no->pai;
			no = prox->dir;
			pai->esq = no;
			prox->dir = dir;
			dir->pai = prox;
		}else{ 
			prox->pai = pai;
			pai = prox;
			no = prox->dir;
		}
	}else{ 
		cor = no->cor;
		no = prox;
	}
	
	if(no != NULL)
		no->pai = pai;
	if(cor) 
		return;
	if(no != NULL && no->cor){
		no->cor = false;
		return;
	}
	
	do{ 
		if(no == arvore->raiz)
			break;
		if(no == pai->esq){ 
			irmao = pai->dir;
			if(irmao->cor){ 
				irmao->cor = false;
				pai->cor = true;
				rotacaoEsq(arvore, pai);
				irmao = pai->dir;
			}
			if((irmao->esq != NULL && irmao->esq->cor) || (irmao->dir != NULL && irmao->dir->cor)){ 
				if(irmao->dir == NULL || !irmao->dir->cor){
					irmao->esq->cor = false;
					irmao->cor = true;
					rotacaoDir(arvore, irmao);
					irmao = pai->dir;
				}
				irmao->cor = pai->cor;
				pai->cor = irmao->dir->cor = false;
				rotacaoEsq(arvore, pai);
				no = arvore->raiz;
				break;
			}
		}else{
			irmao = pai->esq; 
			if(irmao->cor){
				irmao->cor = false;
				pai->cor = true;
				rotacaoDir(arvore, pai);
				irmao = pai->esq;
			}
			if((irmao->esq != NULL && irmao->esq->cor) || (irmao->dir != NULL && irmao->dir->cor)){
				if(irmao->esq == NULL || !irmao->esq->cor){
					irmao->dir->cor = false;
					irmao->cor = true;
					rotacaoEsq(arvore, irmao);
					irmao = pai->esq;
				}
				irmao->cor = pai->cor;
				pai->cor = irmao->esq->cor = false;
				rotacaoDir(arvore, pai);
				no = arvore->raiz;
				break;
			}
		}
		irmao->cor = true;
		no = pai;
		pai = pai->pai;
	}while(!no->cor);
	
	if(no != NULL)
		no->cor = false;
}

TNo *pesquisa(TArvore *arvore, long chave){
	TNo *no = arvore->raiz; 
	while(no != NULL){ 
		if(chave < no->chave)
			no = no->esq;
		else
			if(chave > no->chave)
				no = no->dir;
			else
				return no;
	}
	return NULL; 
}

void insere(TArvore *arvore, long chave){
	TNo *no;
	
	no = (TNo*) malloc(sizeof (*no)); 
	inicializaNo(no);
	insereNo(arvore, no, chave); 
}

void deleta(TArvore *arvore, long chave){
	TNo *no;
	
	no = pesquisa(arvore, chave); 
	deletaNo(arvore, no); 
	free(no); 
}

void textcolor(int color){ 
    static int __BACKGROUND;

    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
     
    GetConsoleScreenBufferInfo(h, &csbiInfo);

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color + (__BACKGROUND << 4));
}

void exibeChave(TNo *no){ 
	if(no->cor)
		textcolor(RED);
	 
	printf("%d ", no->chave);
	textcolor(BLACK);
}

void inOrdem(TNo *no){
	if(no != NULL){
		inOrdem(no->esq);
		exibeChave(no);
		inOrdem(no->dir);
	}
}

void preOrdem(TNo *no){
	if(no != NULL){
		exibeChave(no);
		inOrdem(no->esq);
		inOrdem(no->dir);
	}
}

void posOrdem(TNo *no){
	if(no != NULL){
		inOrdem(no->esq);
		inOrdem(no->dir);
		exibeChave(no);
	}
}
#endif