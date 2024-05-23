#include "sll.h"
#include <malloc.h>

#define TRUE 1
#define FALSE 0


typedef struct slNode{ // definicao de struct de um nodo da lista
    void* data;        // contendo o dado "armazenado" e o endereço do nodo seguinte
    struct slNode *next;
}SLNode;

typedef struct slList{ //definicao de struct da SLL
    SLNode *first;     //contendo o endereço do primeiro nodo da lista
    SLNode *cur;
}SLList;



SLList* sllCreate(){ //criacao de uma lista encadeada
    SLList *l;
    l = (SLList*)malloc(sizeof(SLList));
    if (l!=NULL){
        l->first = NULL; // lista inicia vazia
        l->cur = NULL;
        return l;
    }
    return NULL;
}

int sllDestroy(SLList *l){ //remocao do espaço de memória onde a lista está alocada
    if (l!=NULL){
        if (l->first == NULL) {
            free(l);
            return TRUE;
        }
    }
    return FALSE;
}


int sllInsertAsFirst(SLList *l, void* data){ // Inserir um dado na lista, como primeiro elemento
    SLNode *newnode;
    if (l!=NULL){
        newnode = (SLNode*)malloc(sizeof(SLNode)); // criacao e alocação do novo nodo a ser adicionado
        if (newnode != NULL){
            newnode->data = data; // o nodo recebe o dado inserido
            newnode->next = l->first; // o nodo aponta para o antigo primeiro elemento, agora elemento seguinte
            l->first = newnode; // nodo é inserido na lista como primeiro elemento
            return TRUE;
        }
    }
    return FALSE;
}

int sllInsertAsLast(SLList *l, void* data) { // Inserir um dado na lista, como ultimo elemento
    SLNode *newnode, *last;
    if (l != NULL) {
        newnode = (SLNode *) malloc(sizeof(SLNode)); // criacao e alocação do novo nodo a ser adicionado
        if (newnode != NULL) {
            newnode->data = data; // nodo recebe dado inserido
            newnode->next = NULL; //nodo nao aponta, é o ultimo elemento
            if (l->first == NULL) {//lista vazia, adiciona como primeiro
                l->first = newnode;
            } else {
                last = l->first;
                while (last->next != NULL) { //busca o ultimo nodo da lista
                    last = last->next;
                }
                last->next = newnode; // nodo é inserido a lista como ultimo elemento
            }
            return TRUE;
        }
    }
    return FALSE;
}

void* sllRemoveFirst(SLList *l){ // remove da lista o primeiro elemento
    SLNode *del, *afterdel;
    void* data;
    if (l!=NULL){
        if (l->first != NULL){ // lista nao está vazia
            del = l->first; //del é o primeiro elemento da lista
            data = del->data; // dado a ser retirado
            afterdel = del->next; // nodo seguinte ao que se intende remover
            l->first = afterdel; // nodo seguinte agora é o primeiro e del está fora da lista
            free(del);
            return data; // dado removido é retornado
        }
    }
    return NULL;
}

void* sllRemoveLast(SLList *l){ //remove da lista o ultimo elemento
    SLNode *del, *prevDel;
    void* data;
    if (l != NULL){
        if (l->first != NULL){ //lista nao vazia
            del = l->first;
            prevDel = NULL;
            while(del->next != NULL){ // procura ultimo e penultimo elemento
                prevDel = del;
                del = del->next;
            }
            data = del->data; // recebe o dado armazenado
            if (prevDel != NULL){ // Há mais de um 1 nodo na lista
                prevDel->next = NULL; //retira del da lista
            } else { //Há apenas um nodo na lista
                l->first = NULL; //retira del da lista
            }
            free(del);
            return data;
        }
    }
    return NULL;
}



void* sllGetFirst(SLList *l){ //retorna o primeiro dado da lista, sem remover
    void* data;
    if (l!=NULL){
        if (l->first != NULL){ //lista nao vazia
            l->cur = l->first;
            data = l->first->data; // primeiro dado da lista
            return data; // retorna o dado
        }
    }
    return NULL;
}

void* sllGetNext(SLList *l){
    if (l!=NULL){
        if (l->first != NULL){
            l->cur = l->cur->next;
            if (l->cur != NULL){
                return l->cur->data;
            }
        }
    }
    return NULL;
}

void* sllGetLast(SLList *l){ // retorna o último dado da lista, sem remover
    SLNode *last;
    void* data;
    if (l != NULL){
        if (l->first != NULL){ //lista nao vazia
            last = l->first;
            while(last->next!=NULL){ //busca pelo ultimo elemento
                last = last->next;
            } //encontrado
            data = last->data; // ultimo dado da lista
            return data; // dado retornado
        }
    }
    return NULL;
}

int sllNumElms(SLList *l){ //retorna o número de nodos da lista
    int numElms = 0;
    SLNode* node;
    if (l != NULL){
        if (l->first != NULL){ // Lista nao vazia
            node = l->first; //primeiro nodo
            numElms++;
            while(node->next != NULL){ // percorre a lista ate o ultimo nodo contando
                node = node->next;
                numElms++;
            }
            return numElms;
        }
    }
    return FALSE;
}


void* sllQuery(SLList *l, void* key, int (*cmp)(void*, void*)){
    SLNode *cur;
    int status;
    if (l != NULL){
        if (l->first != NULL){
            cur = l->first;
            status = cmp(cur->data, key);
            while(status != TRUE && cur->next != NULL){ // Percorre enquanto nao encontra e nao chegou ao fim
                cur = cur->next;
                status = cmp(cur->data, key);
            }
            if (status == TRUE) {
                return cur->data;
            }
        }
    }
    return NULL;
}


void* sllRemoveSpec(SLList *l, void* key, int (*cmp)(void*, void*)){ // Procura na lista um dado recebido e o remove
    SLNode *spec, *prev;
    int status;
    void* data;
    if (l!=NULL){
        if (l->first != NULL){
            spec = l->first;
            prev = NULL;
            status = cmp(spec->data, key);
            while (status != TRUE && spec->next != NULL){ // procura dado
                prev = spec;
                spec = spec->next;
                status = cmp(spec->data, key);
            }
            if (status == TRUE){ //se encontrado, entao remove
                if (prev != NULL){ // Há mais de um nodo na lista
                    prev->next = spec->next;
                } else { // Há apenas um nodo na lista
                    l->first = spec->next;
                }
                data = spec->data;
                free(spec);
                return data;
            }
        }
    }
    return NULL;
}






