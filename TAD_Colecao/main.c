#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include "colecao.h"
//struct Livro
typedef struct livro{
    char titulo[30];
    int ano;
    float preco;
}Livro;

int cmpStr(void *elm, void *key){ //funcao de comparacao entre strings para a funcao cQuery
    char *keystr, *elmstr;
    Livro *elmLivro;
    elmLivro = (Livro*)elm;
    elmstr = elmLivro->titulo;
    keystr = (char*)key;
    if (!strcmp(elmstr, keystr)) {
        return 1;
    }
    return 0;
}

Colecao *criarColecao(){ //cria uma Colecao usando tamanho dado pelo usuario
    int max;
    printf("\nDigite o numero total de livros na colecao: ");
    scanf("%d", &max);
    return cCreate(max);
}

void inserirLivro(Colecao *cofo){ //pede dados do Livro ao usuario e o adiciona na colecao
    Livro *book = (Livro*)malloc(sizeof(Livro));
    printf("\nNome do livro: ");
    scanf("%s", book->titulo);
    printf("\nAno de lancamento do livro: ");
    scanf("%d", &book->ano);
    printf("\nPreco do livro: ");
    scanf("%f", &book->preco);
    cInsert(cofo, book);
}

void removerLivro(Colecao *cofo) { //pede os dados ao usuario e remove o livro com esses dados
    char nome[30];
    int n;
    float p;
    Livro *removido, *remover;
    printf("\nTitulo do livro a ser removido: ");
    scanf("%s", nome);
    printf("\nAno do livro a ser removido: ");
    scanf("%d", &n);
    printf("\nPreco do livro a ser removido: ");
    scanf("%f", &p);
    remover = cQuery(cofo, (void*)nome, cmpStr);
    if (remover->ano == n && remover->preco == p) {
        removido = (Livro*)cRemove(cofo, remover);
        if (removido != NULL){
            printf("%s Removido", removido->titulo);
        }
    } else {
        printf("Dados incorretos");
    }
}

void consultarLivro(Colecao *cofo){ // pede o livro ao usuario para informar se esta ou nao dentro da colecao
    char nome[30];
    Livro *procurado;
    printf("\nTitulo do livro procurado: ");
    scanf("%s", nome);
    procurado = cQuery(cofo, nome, cmpStr);
    if (!strcmp(procurado->titulo, nome)) {
        printf("%s Esta na colecao", nome);
    } else {
        printf("Nao encontrado");
    }
}

void listarColecao(Colecao *cofo){ // lista todos os elementos presentes na colecao
    Livro *atual = NULL;
    atual = cGetFirst(cofo);
    if (atual == NULL){
        printf("Colecao esta vazia");
    }
    printf("\nLivros na colecao:");
    while(atual != NULL){
        printf("\nTitulo: %s; ", atual->titulo);
        printf("Ano: %d; ", atual->ano);
        printf("Preco: %f; ", atual->preco);
        atual = cGetNext(cofo);
    }
}

void esvaziarColecao(Colecao *cofo){ //considerando o retorno NULL de cGetFirst como uma colecao vazia, esvazia a colecao ate essa condicao
    Livro *atual = NULL;
    atual = cGetFirst(cofo);
    while(atual != NULL) {
        cRemove(cofo, atual);
        atual = cGetFirst(cofo);
    }
}



int main(void) {
    int op, haColecao = 0, working = 1;
    Colecao *c = NULL;
    while(working){
        printf("\n-------------------\n1-Criar colecao\n2-Inserir um Livro\n3-Remover Livro\n4-Consultar um Livro\n");
        printf("5-Listar a colecao\n6-Esvaziar a colecao\n7-Destruir a colecao e Sair\n-----------------\n");
        printf("Digite a operacao desejada: ");
        scanf("%d", &op);
        switch(op){
            case 1:
                if (!haColecao) {
                    c = criarColecao();
                    haColecao = 1;
                    if (c == NULL){
                        free(c);
                        working = 0;
                    } else {
                        printf("Criado");
                    }
                } else {
                    printf("Ja existe uma colecao em uso");
                }
                break;
            case 2:
                if (haColecao) {
                    inserirLivro(c);
                    printf("Inserido");
                } else {
                    printf("Crie uma colecao primeiro");
                }
                break;
            case 3:
                if (haColecao){
                    removerLivro(c);
                } else {
                    printf("Crie uma colecao primeiro");
                }

                break;
            case 4:
                if (haColecao){
                    consultarLivro(c);
                } else {
                    printf("Crie uma colecao primeiro");
                }
                break;
            case 5:
                if (haColecao){
                    listarColecao(c);
                } else {
                    printf("Crie uma colecao primeiro");
                }
                break;
            case 6:
                if (haColecao){
                    esvaziarColecao(c);
                } else {
                    printf("Crie uma colecao primeiro");
                }
                break;
            case 7:
                if (haColecao){
                    esvaziarColecao(c);
                    cDestroy(c);
                }
                working = 0;
                break;
        }
    }
    return 0;
}
