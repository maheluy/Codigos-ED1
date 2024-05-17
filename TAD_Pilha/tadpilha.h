#ifndef TAD_PILHA_TADPILHA_H
#define TAD_PILHA_TADPILHA_H

typedef struct stack Stack;


Stack *stkCreate(int max);

int stkDestroy(Stack *s);

int stkPush(Stack *s, void *elm);

void *stkPop(Stack *s);

int stkIsEmpty(Stack *s);

int stkIsFull(Stack *s);


#endif //TAD_PILHA_TADPILHA_H
