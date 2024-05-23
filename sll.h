#ifndef TAD_SLL_SLL_H
#define TAD_SLL_SLL_H


typedef struct slNode SLNode;

typedef struct slList SLList;

SLList* sllCreate();

int sllDestroy(SLList *l);

int sllInsertAsFirst(SLList *l, void* data);

int sllInsertAsLast(SLList *l, void* data);

void* sllRemoveFirst(SLList *l);

void* sllRemoveLast(SLList *l);

void* sllGetFirst(SLList *l);

void* sllGetNext(SLList *l);

void* sllGetLast(SLList *l);

int sllNumElms(SLList *l);

void* sllQuery(SLList *l, void* key, int (*cmp)(void*, void*));

void* sllRemoveSpec(SLList *l, void* key, int (*cmp)(void*, void*));

#endif //TAD_SLL_SLL_H
