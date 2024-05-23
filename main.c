#include <stdio.h>
#include "sll.h"
#include <malloc.h>
#include <string.h>

#define TRUE 1
#define FALSE 0


typedef struct musica{
    char* titulo;
    int ano;
    float nOuvintes; //em milhao
} Musica;

//funcoes cmp
//int cmpStr(void *elm, void *key){ // (struct, char*)
//    char *keystr, *elmstr = NULL;
//    Musica *elmMusica = (Musica*)elm;
//    //elmstr = elmMusica->titulo; // recebe da struct o char*
//    strcpy(elmstr, elmMusica->titulo);
//    keystr = (char*)key; // transforma o void* em char*
//    if (!strcmp(elmstr, keystr)) { //comparacao
//        return TRUE;
//    }
//    return FALSE;
//}
int cmpStr(void *elm, void *key){
    char *keystr, *elmstr;
    Musica *elmMusica;
    elmMusica = (Musica*)elm;
    elmstr = elmMusica->titulo;
    keystr = (char*)key;
    if (!strcmp(elmstr, keystr)) {
        return TRUE;
    }
    return FALSE;
}

int cmpInt(void *elm, void *key){ //(struct, int*)
    int *keyInt, *elmInt;
    Musica *elmMusica = (Musica*)elm;
    elmInt = &(elmMusica->ano); // recebe da struct o int*
    keyInt = (int*)key; // transforma o void* em int*
    if (*keyInt == *elmInt){ //comparacao
        return TRUE;
    }
    return FALSE;
}
int cmpFloat(void *elm, void* key) { //(struct, float*)
    float *keyFloat, *elmFloat;
    Musica *elmMusica = (Musica*)elm;
    elmFloat = &(elmMusica->nOuvintes); // recebe da struct o float*
    keyFloat = (float*)key; // transforma o void* em float*
    if (*keyFloat == *elmFloat){ //comparacao
        return TRUE;
    }
    return FALSE;
}


int receberMusica(SLList *list, int local){
    Musica *m;
    m = (Musica*)malloc(sizeof(Musica));
    m->titulo = (char*)malloc(sizeof(char)*20);

    printf("Nome da musica: "); // criacao de uma musica
    scanf("%s", m->titulo);
    getchar();
    printf("Ano da musica: ");
    scanf("%d", &(m->ano));
    printf("Numero de ouvintes da musica (em milhao): ");
    scanf("%f", &(m->nOuvintes));

    if (local == 1){ //insercao a partir do local pedido
        sllInsertAsFirst(list, m);
        return TRUE;
    } else if (local >= 2){
        sllInsertAsLast(list, m);
        return TRUE;
    }
    return FALSE;

}

int removerMusica(SLList *list, int local){
    void* m = NULL;
    char key[20];
    if (local == 1){ //remocao a partir do local pedido
        m = sllRemoveFirst(list);
    } else if (local == 2){
        printf("\nTitulo da musica a ser removida: ");
        scanf(" %s", key);
        m = sllRemoveSpec(list, key, cmpStr);
    } else if (local == 3){
        m = sllRemoveLast(list);
    }
    if (m != NULL){
        return TRUE;
    } else {
        return FALSE;
    }
}

int consultarLista(SLList *list, int local){
    Musica *elm = NULL;
    int keyInt = 0;
    char keyStr[20];
    float keyFloat = 0.0f;
    if (local == 1){
        printf("\nDigite o titulo procurado: "); //pede o valor a procurar
        scanf(" %s", keyStr);
        elm = sllQuery(list, (void*)keyStr, cmpStr); //busca
    } else if (local == 2){
        printf("\nDigite o ano procurado: "); // pede o valor a procurar
        scanf(" %d", &keyInt);
        elm = sllQuery(list, (void*)(&keyInt), cmpInt); //busca
    } else if (local == 3){
        printf("\nDigite o numero de ouvintes procurado: "); // pede o valor a procurar
        scanf(" %f", &keyFloat);
        elm = sllQuery(list, (void*)(&keyFloat), cmpFloat); //busca
    }

    if (elm != NULL){ // se encontrado, entao TRUE
        return TRUE;
    }
    return FALSE;
}

int listar(SLList *list){
    Musica *elm;
    int vazia = TRUE;
    elm = (Musica*)sllGetFirst(list);
    while (elm != NULL){
        vazia = FALSE;
        printf("\n %s: Ano- %d; Numero de ouvintes- %f", elm->titulo, elm->ano, elm->nOuvintes);
        elm = (Musica*)sllGetNext(list);
    }
    return vazia;
}

void esvaziarLista(SLList *list){
    void* removido;
    removido = sllRemoveFirst(list);
    while (removido != NULL) {
        removido = sllRemoveFirst(list);
    }
}


int main(void) {
    int op, haLista = FALSE, working = TRUE;
    SLList *l = NULL;

    while(working){
        printf("\n....................\n1-Criar lista\n2-Inserir Musica\n3-Remover Musica\n4-Consultar Musica\n");
        printf("5-Listar\n6-Esvaziar a lista\n7-Esvaziar, Destruir a lista e Sair\n....................\n");
        printf("Digite a operacao desejada: ");
        scanf("%d", &op);
        switch (op){
            case 1:
                if (!haLista){
                    l = sllCreate();
                    if (l!=NULL){
                        printf("Criada");
                        haLista = TRUE;
                    } else {
                        return -1;
                    }
                } else {
                    printf("Ja existe uma lista");
                }
                break;
            case 2:
                if (haLista){
                    printf("\n++++++++++\n1-Inserir no inicio\n2-Inserir no Fim\n++++++++++\n");
                    printf("Digite a operacao desejada: ");
                    scanf(" %d", &op);
                    if (!receberMusica(l, op)){
                        printf("Erro!");
                        return -2;
                    } else {
                        printf("Inserido!");
                    }
                } else {
                    printf("\nCrie uma lista primeiro!");
                }
                break;
            case 3:
                if (haLista){
                    printf("\n----------\n1-Remover o primeiro\n2-Remover especificado\n3-Remover o ultimo\n----------\n");
                    printf("Digite a operacao desejada: ");
                    scanf(" %d", &op);
                    if (removerMusica(l, op)){
                        printf("Removido\n");
                    } else {
                        printf("Erro!\n");
                        //return -3;
                    }
                } else {
                    printf("\nCrie uma lista primeiro!");
                }
                break;
            case 4:
                if (haLista){
                    printf("\n----------\n1-Consultar por titulo\n2-Consultar por ano\n3-Consultar por numero de Ouvintes\n----------\n");
                    printf("Digite a operacao desejada: ");
                    scanf(" %d", &op);
                    if (consultarLista(l, op)){
                        printf("Encontrado na lista!\n");
                    } else {
                        printf("Nao ha na lista");
                    }
                } else {
                    printf("\nCrie uma lista primeiro!");
                }
                break;
            case 5:
                if(haLista){
                    if(listar(l)){
                        printf("A lista esta vazia");
                    }
                } else {
                    printf("\nCrie uma lista primeiro!");
                }
                break;
            case 6:
                if (haLista){
                    esvaziarLista(l);
                    printf("Esvaziada!");
                } else {
                    printf("\nCrie uma lista primeiro!");
                }
                break;
            case 7:
                if (haLista){
                    esvaziarLista(l);
                    sllDestroy(l);
                    working = FALSE;
                } else {
                    printf("\nCrie uma lista primeiro!");
                }
                break;
            default:
                working = FALSE;
                break;
        }
    }

    return 0;
}
