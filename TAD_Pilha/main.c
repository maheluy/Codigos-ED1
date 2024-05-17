#include <stdio.h>
#include "tadpilha.h"
#include <string.h>

#define TRUE 1
#define FALSE 0

char* inverteString(char *s){
    Stack *stk;
    char* c;
    stk = stkCreate(10);
    int i;
    if (stk != NULL){
        for(i = 0; i < strlen(s); i++){
            c = &s[i];
            stkPush(stk, (void*)c);
        }
        for(i = 0; i < strlen(s); i++){
            c = (char*)stkPop(stk);
            s[i] = *c;
        }
        stkDestroy(stk);
        return s;
    }
    return NULL;
}

int verificaFormatoString(char *str, int n){
    Stack *stk;
    int i = 0;
    char* aux;
    stk = stkCreate(n);
    if (stk!=NULL){
        while(i <= (n/2)-1){
            stkPush(stk, (void*)&(str[i]));
            i++;
        }
        if (n%2 != 0){ // n eh impar
            i++; //pula o elm central
        }
        while (i<n){
            aux = (char*)stkPop(stk);
            if (*aux != str[i]){
                return FALSE;
            }
            i++;
        }
        return TRUE;
    }
    return FALSE;
}


int VerificaParenteses(char *str, int n){
    Stack *s;
    int i;
    s = stkCreate(n);
    for (i = 0; i < n; i++){
        if (str[i] == '('){
            stkPush(s, (void*)&str[i]);
        }
        if (str[i] == ')'){
            if (!stkIsEmpty(s)){
                stkPop(s);
            } else {
                return FALSE;
            }
        }
    }
    if (stkIsEmpty(s)){
        return TRUE;
    }
    return FALSE;
}








int main(void) {
    printf("Hello World!");
    return 0;
}
