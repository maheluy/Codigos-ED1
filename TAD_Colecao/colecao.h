
#ifndef TAD_COLECAO_COLECAO_H
#define TAD_COLECAO_COLECAO_H

typedef struct colecao Colecao;

Colecao *cCreate( int maxItens );

int cDestroy(Colecao *c);

int cInsert(Colecao *c, void *item);

void* cRemove(Colecao *c, void* key );

void * cGetFirst(Colecao *c);

void * cGetNext(Colecao *c);

void * cQuery(Colecao *c, void* key, int (*cmp)(void*, void*));


#endif //TAD_COLECAO_COLECAO_H
