#include <malloc.h>
#include "tadpilha.h"

#define TRUE 1
#define FALSE 0


typedef struct stack {
    int maxItens;
    int top;
    void **item;
} Stack;


Stack *stkCreate(int max){
    Stack *s;
    if (max > 0){
        s = (Stack*)malloc(sizeof(Stack));
        if (s!=NULL){
            s->item = (void**)malloc(sizeof(void*)*max);
            if (s->item != NULL){
                s->maxItens = max;
                s->top = -1;
                return s;
            }
        }
    }
    return NULL;
}

int stkDestroy(Stack *s){
    if (s!=NULL){
        if(s->top < 0){
            free(s->item);
            free(s);
            return TRUE;
        }
    }
    return FALSE;
}

int stkPush(Stack *s, void *elm){
    if (s!=NULL){
        if (s->top < s->maxItens-1){
            s->top++;
            s->item[s->top] = elm;
            return TRUE;
        }
    }
    return FALSE;
}


void *stkPop(Stack *s){
    void *aux;
    if (s != NULL){
        if (s->top >= 0){
            aux = s->item[s->top];
            s->top--;
            return aux;
        }
    }
    return NULL;
}

int stkIsEmpty(Stack *s){
    if (s!=NULL){
        if (s->top < 0){
            return TRUE;
        }
    }
    return FALSE;
}

int stkIsFull(Stack *s){
    if (s!=NULL){
        if (s->top >= s->maxItens-1){
            return TRUE;
        }
    }
    return FALSE;
}

void **stkMultiPop ( Stack *s, int k){
    void* aux;
    void** elmspop;
    int i;
    if (s!=NULL){
        if (s->top >= 0){
            if (k < s->maxItens){
                elmspop = (void**)malloc(sizeof(void*)*(k));
                for (i = 0; i < k; i++){
                    elmspop[i] = stkPop(s);
                }
                return elmspop;
            } else {
                elmspop = (void**)malloc(sizeof(void*)*(s->top + 1));
                aux = stkPop(s);
                i = 0;
                while (aux != NULL){
                    elmspop[i] = aux;
                    i++;
                    aux = stkPop(s);
                }
                return elmspop;
            }
        }
    }
    return NULL;
}