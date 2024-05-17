#ifndef TADFILA_TADFILA_H
#define TADFILA_TADFILA_H


typedef struct queue Queue;

int qIncCircular(int n, int max);

Queue *qCreate(int size);

int qDestroy(Queue *q);

int qEnqueue(Queue *q, void *elm);

void *qDequeue(Queue *q);

int qIsEmpty(Queue *q);
//-------------------------------------------
void *qGetLast(Queue *q);

int cqEnqueueN(Queue *q, int n, void **elms);

void **qDequeueN (Queue *q, int n);

void *qDequeueSpecified(Queue *q, void *key, int (*cmp(void *, void *)));

int qReorganizaFila(Queue *q);







#endif //TADFILA_TADFILA_H
