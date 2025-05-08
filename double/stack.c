/* 
    File name    : stack.c
    Made by      : Nauval Khairiyan from Muhammad Nabil Syauqi Rasyiq
    Date         : 30 March 2025
    Description  : Implementation of stack using linked list
*/

#include "stack.h"
#include <stdlib.h>

/*=======================================================*/
/*==================== MAIN FUNCTIONS ===================*/
/*=======================================================*/

void CreateStack(Stack *S, DataType type) {
    CreateList(S, type);
}

boolean IsStackEmpty(Stack S) {
    return ListEmpty(S);
}

void Push(Stack *S, void *value) {
    address newNode;
    
    if (S->type == TYPE_INT) {
        int intValue = *((int *)value);
        newNode = AlokasiInt(intValue);
    } else {
        char *strValue = *((char **)value);
        newNode = AlokasiCharS(strValue);
    }
    
    if (newNode != Nil) {
        InsertFirst(&(First(*S)), newNode);
    }
}

void Pop(Stack *S, void *output) {
    if (!IsStackEmpty(*S)) {
        if (S->type == TYPE_INT) {
            DeleteFirstInt(S, (int *)output);
        } else {
            DeleteFirstCharS(S, (char **)output);
        }
    }
}

void *Top(Stack S) {
    if (IsStackEmpty(S)) {
        return NULL;
    }
    
    if (S.type == TYPE_INT) {
        int *value = malloc(sizeof(int));
        *value = infoInt(First(S));
        return value;
    } else {
        return infoStr(First(S));
    }
}

void ClearStack(Stack *S) {
    ClearList(S);
}

int StackSize(Stack S) {
    return CountList(S);
}

void PrintStack(Stack S) {
    PrintList(S);
}
