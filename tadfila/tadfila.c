#include <malloc.h>
#include "tadfila.h"

#define TRUE 1
#define FALSE 0


typedef struct queue {
    int front;
    int rear;
    int maxItens;
    void **item;
    int numItens;
} Queue;



int qIncCircular(int n, int max){
    return ((n+1)%max);
}

Queue *qCreate(int size){
    if (size > 0){
        Queue *q;
        q = (Queue*)malloc(sizeof(Queue));
        if (q!=NULL){
            q->item = (void**)malloc(sizeof(void*)*size);
            if (q->item !=NULL){
                q->front = 0;
                q->rear = -1;
                q->maxItens = size;
                q->numItens = 0;
                return q;
            }
        }
    }
    return NULL;
}

int qDestroy(Queue *q){
    if (q!=NULL){
        if (q->numItens<=0){
            free(q->item);
            free(q);
            return TRUE;
        }
    }
    return FALSE;
}

int qEnqueue(Queue *q, void *elm){
    if (q!=NULL){
        if (q->numItens >= 0 && q->numItens < q->maxItens){
            q->rear = qIncCircular(q->rear, q->maxItens);
            q->item[q->rear] = elm;
            q->numItens++;
            return TRUE;
        }
    }
    return FALSE;
}

void *qDequeue(Queue *q){
    if (q!=NULL){
        if (q->numItens > 0){
            void *aux;
            aux = q->item[q->front];
            q->front = qIncCircular(q->front, q->maxItens);
            q->numItens--;
            return aux;
        }
    }
    return NULL;
}

int qIsEmpty(Queue *q){
    if (q!=NULL){
        if (q->numItens <= 0){
            return TRUE;
        }
    }
    return FALSE;
}

//-----------------------------------------------------------------------

void *qGetLast(Queue *q){
    if (q!=NULL){
        if (q->numItens > 0){
            void* aux;
            aux = q->item[q->front];
            return aux;
        }
    }
    return NULL;
}

int qEnqueueN(Queue *q, int n, void **elms){
    if (q!=NULL){
        if (q->numItens >= 0 && (q->numItens + n-1) < q->maxItens){
            for (int i = 0; i < n; i++){
                q->rear = qIncCircular(q->rear, q->maxItens);
                q->item[q->rear] = elms[i];
                q->numItens++;
            }
            return TRUE;
        }
    }
    return FALSE;
}

void **qDequeueN(Queue *q, int n){
    void* aux;
    void**elms;
    if (q!=NULL){
        if (q->numItens >= n) {
            elms = (void**)malloc(sizeof(void*)*n);
            if (elms !=NULL){
                for (int i = 0; i < n; i++){
                    aux = q->item[q->front];
                    q->front = qIncCircular(q->front, q->maxItens);
                    q->numItens--;
                    elms[i] = aux;
                }
                return elms;
            }
        }
    }
    return NULL;
}

void *qDequeueSpecified(Queue *q, void *key, int (*cmp(void *, void *))){
    if (q!=NULL){
        if (q->numItens > 0){
            void* aux;
            for (int i = 0; i < q->numItens; i++){
                if (cmp(q->item[i], key)){
                    aux = qDequeue(q);
                    return aux;
                }
            }
        }
    }
    return NULL;
}



int qReorganizaFila(Queue *q){
    int i;
    if (q!= NULL){
        if (!qIsEmpty(q)){
            if (q->front == q->maxItens-1){
                return TRUE;
            }
            if (q->numItens < q->maxItens) { //nao cheia
                while (q->front != q->maxItens -1){
                    for (i = q->front; i <= q->rear; i--){
                        q->item[i+1] = q->item[i];
                    }
                    q->front++;
                    q->rear++;
                }
                return TRUE;
            } else { //fila cheia
                void* aux;
                while (q->front != q->maxItens -1){
                    aux = q->item[q->rear];
                    for (i = q->front; i <= q->rear; i--){
                        q->item[i+1] = q->item[i];
                    }
                    q->rear++;
                    q->item[q->rear] = aux;
                    q->front++;
                }
                return TRUE;
            }
        }
    }
    return FALSE;
}









