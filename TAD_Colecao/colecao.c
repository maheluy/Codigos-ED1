#include "colecao.h"


#include <malloc.h>
#include "colecao.h"
#define TRUE 1
#define FALSE 0


typedef struct colecao {
    int maxItens;
    int numItens;
    int cur;
    void** item;
} Colecao;


Colecao *cCreate( int maxItens ) {
    Colecao *c;
    c = (Colecao*)malloc(sizeof (Colecao));
    if (c -> maxItens > 0) {
        if (c != NULL) {
            c->item = (void **) malloc (sizeof(void *)*c -> maxItens);
            if ( c->item != NULL) {
                c->numItens = 0;
                c->maxItens = maxItens;
                c-> cur = -1;
                return c;
            }
            free(c);
        }
    }
    return NULL;
}



int cDestroy(Colecao *c){
    if ( c != NULL ) {
        if ( c->numItens == 0 ) {
            free(c->item);
            free(c);
            return TRUE;
        }
    }
    return FALSE;
}



int cInsert(Colecao *c, void *elm){
    if ( c != NULL ) {
        if ( c->numItens < c->maxItens) {
            c->item[c->numItens] = elm;
            c->numItens++;
            return TRUE;
        }
    }
    return FALSE;
}



void* cRemove(Colecao *c, void* key ){
    int i, j, status;
    void* aux;
    if ( c != NULL ) {
        if ( c->numItens > 0) {
            i=0; status = FALSE;
            while ( i < c->numItens && status != TRUE ) {
                if ( c->item[i] == key) {
                    status = TRUE;
                } else {
                    i++;
                }
            }
            if ( status == TRUE ) {
                aux = c->item[i];
                for( j=i; j < c->numItens-1; j++) {
                    c->item[j] = c->item[j+1];
                }
                c->numItens--;
                return aux;
            }
        }
    }
    return NULL;
}



void * cGetFirst(Colecao *c) {
    if ( c!= NULL ) {
        if ( c->numItens > 0 ) {
            c->cur = 0;
            return c->item[c->cur];
        }
    }
    return NULL;
}





void * cGetNext(Colecao *c){
    if ( c!= NULL ) {
        if ( c->cur < c->numItens -1) {
            c->cur++;
            return c->item[c->cur];
        }
    }
    return NULL;
}



void * cQuery(Colecao *c, void* key, int (*cmp)(void*, void*)){
    int stat, i = 0;
    if (c != NULL){
        if (c->numItens > 0){
            stat = cmp(c->item[0], key);
            while(stat != TRUE && i < c->numItens){
                i++;
                stat = cmp(c->item[i], key);
            }
            if (stat == TRUE){
                return c->item[i];
            }
        }
    }
    return NULL;
}