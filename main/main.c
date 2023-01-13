#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<stdbool.h>

#include"../headers/arn.h"

#define SETA_IN 175
#define SETA_OUT 174

void pause();
void screenClr();

int main(){
	int opt;
	
	TArvore arvore;
	inicializa(&arvore);
	
	do{
		fflush(stdin);
		screenClr();
		printf(" %c Arvore Rubro-Negra - Demo %c\n\n", SETA_IN, SETA_OUT);
		printf(" 1. Inserir\n");
		printf(" 2. Deletar\n");
		printf(" 3. Pesquisar\n");
		printf(" 4. Pre Ordem\n");
		printf(" 5. Pos Ordem\n");
		printf(" 6. In Ordem\n");
		printf(" 0. Encerrar\n");
		printf(" %c ", SETA_IN);
		scanf("%d", &opt);
			
		switch(opt){
			case 1:{
				screenClr();
				printf(" %c Inserir %c\n\n", SETA_IN, SETA_OUT);
				
				long chave;
				fflush(stdin);
				printf(" - Digite o valor a ser inserido: ");
				scanf("%ld", &chave);
				
				insere(&arvore, chave);
				
				printf("\n %c Valor inserido com sucesso!", SETA_IN);
				pause();
				break;
			}
		
			case 2:{
				screenClr();
				printf(" %c Deletar %c\n\n", SETA_IN, SETA_OUT);
				
				long chave;
				fflush(stdin);
				printf(" - Digite o valor a ser deletado: ");
				scanf("%ld", &chave);
				
				TNo *ret = pesquisa(&arvore, chave);
				
				if(ret != NULL){
					deleta(&arvore, chave);
					printf("\n %c Valor deletado com sucesso!", SETA_IN);
				}
				else 
					printf("\n %c Valor inexistente!", SETA_IN);
				
				pause();
				break;
			}
				
			case 3:{
				screenClr();
				printf(" %c Pesquisar %c\n\n", SETA_IN, SETA_OUT);
				
				long chave;
				fflush(stdin);
				printf(" - Digite o valor a ser pesquisado: ");
				scanf("%ld", &chave);
				
				TNo *ret = pesquisa(&arvore, chave);
				
				if(ret != NULL){
					printf("\n %c Valor encontrado! ", SETA_IN);
					exibeChave(ret);
				}else 
					printf("\n %c Valor nao encontrado!", SETA_IN);
				
				pause();
				break;
			}
				
			case 4:{
				screenClr();
				printf(" %c Pre Ordem %c\n\n", SETA_IN, SETA_OUT);
				
				if(arvore.raiz != NULL)
					printf(" %c ", SETA_IN);
					
				preOrdem(arvore.raiz);
				
				pause();
				break;
			}
				
			case 5:{
				screenClr();
				printf(" %c Pos Ordem %c\n\n", SETA_IN, SETA_OUT);
				
				if(arvore.raiz != NULL)
					printf(" %c ", SETA_IN);
					
				posOrdem(arvore.raiz);
				
				pause();
				break;
			}
			
			case 6:{
				screenClr();
				printf(" %c In Ordem %c\n\n", SETA_IN, SETA_OUT);
				
				if(arvore.raiz != NULL)
					printf(" %c ", SETA_IN);
					
				inOrdem(arvore.raiz);
				
				pause();
				break;
			}
		}
	}while(opt);
	
	printf("\n %c Programa encerrado.\n", SETA_IN);
	return 0;
}

void pause(){
	printf("\n\n %c Pressione qualquer tecla para continuar...", SETA_IN);
	getch();
}

void screenClr(){
	system("cls");
}