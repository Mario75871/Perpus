/* 
    File name    : queue.c
    Made by      : Nauval Khairiyan from Muhammad Nabil Syauqi Rasyiq
    Date         : 30 March 2025
    Description  : Implementation of queue using linked list
*/

#include "queue.h"
#include <stdlib.h>

/*=======================================================*/
/*==================== MAIN FUNCTIONS ===================*/
/*=======================================================*/

void CreateQueue(Queue *Q, DataType type) {
    CreateList(Q, type);
}

boolean IsQueueEmpty(Queue Q) {
    return ListEmpty(Q);
}

void Enqueue(Queue *Q, void *value) {
    address newNode;
    
    if (Q->type == TYPE_INT) {
        int intValue = *((int *)value);
        newNode = AlokasiInt(intValue);
    } else {
        char *strValue = *((char **)value);
        newNode = AlokasiCharS(strValue);
    }
    
    if (newNode != Nil) {
        InsertLast(&(First(*Q)), newNode);
    }
}

void Dequeue(Queue *Q, void *output) {
    if (!IsQueueEmpty(*Q)) {
        if (Q->type == TYPE_INT) {
            DeleteFirstInt(Q, (int *)output);
        } else {
            DeleteFirstCharS(Q, (char **)output);
        }
    }
}

void *Front(Queue Q) {
    if (IsQueueEmpty(Q)) {
        return NULL;
    }
    
    if (Q.type == TYPE_INT) {
        int *value = malloc(sizeof(int));
        *value = infoInt(First(Q));
        return value;
    } else {
        return infoStr(First(Q));
    }
}

void *Rear(Queue Q) {
    if (IsQueueEmpty(Q)) {
        return NULL;
    }
    
    address P = First(Q);
    while (next(P) != Nil) {
        P = next(P);
    }
    
    if (Q.type == TYPE_INT) {
        int *value = malloc(sizeof(int));
        *value = infoInt(P);
        return value;
    } else {
        return infoStr(P);
    }
}

void ClearQueue(Queue *Q) {
    ClearList(Q);
}

int QueueSize(Queue Q) {
    return CountList(Q);
}

void PrintQueue(Queue Q) {
    PrintList(Q);
}
