/* 
    File name    : stack.h
    Made by      : Nauval Khairiyan from Muhammad Nabil Syauqi Rasyiq
    Date         : 30 March 2025
    Description  : Header file for stack implementation using linked list
*/

#ifndef STACK_H
#define STACK_H

#include "linked.h"

typedef List Stack;

/*=======================================================*/
/*==================== MAIN FUNCTIONS ===================*/
/*=======================================================*/

// I.S : Stack sembarang, mungkin kosong
// F.S : Stack diinisialisasi dengan type yang sesuai
void CreateStack(Stack *S, DataType type);

// I.S : Stack terdefinisi
// F.S : Mengembalikan true jika stack kosong
boolean IsStackEmpty(Stack S);

// I.S : Stack terdefinisi, mungkin kosong
// F.S : Menambahkan elemen baru ke bagian atas stack
void Push(Stack *S, void *value);

// I.S : Stack tidak kosong
// F.S : Menghapus dan mengembalikan elemen dari bagian atas stack
void Pop(Stack *S, void *output);

// I.S : Stack tidak kosong
// F.S : Mengembalikan elemen dari bagian atas stack tanpa menghapus
void *Top(Stack S);

// I.S : Stack terdefinisi
// F.S : Menghapus semua elemen stack
void ClearStack(Stack *S);

// I.S : Stack terdefinisi
// F.S : Mengembalikan jumlah elemen dalam stack
int StackSize(Stack S);

// I.S : Stack terdefinisi
// F.S : Menampilkan isi stack
void PrintStack(Stack S);

#endif /* STACK_H */
