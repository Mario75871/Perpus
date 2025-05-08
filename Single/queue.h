/* 
    File name    : queue.h
    Made by      : Nauval Khairiyan from Muhammad Nabil Syauqi
    Date         : 30 March 2025
    Description  : Header file for queue implementation using linked list
*/

#ifndef QUEUE_H
#define QUEUE_H

#include "linked.h"

typedef List Queue;

/*=======================================================*/
/*==================== MAIN FUNCTIONS ===================*/
/*=======================================================*/

// I.S : Queue sembarang, mungkin kosong
// F.S : Queue diinisialisasi dengan type yang sesuai
void CreateQueue(Queue *Q, DataType type);

// I.S : Queue terdefinisi
// F.S : Mengembalikan true jika queue kosong
boolean IsQueueEmpty(Queue Q);

// I.S : Queue terdefinisi, mungkin kosong
// F.S : Menambahkan elemen baru ke bagian belakang queue
void Enqueue(Queue *Q, void *value);

// I.S : Queue tidak kosong
// F.S : Menghapus dan mengembalikan elemen dari bagian depan queue
void Dequeue(Queue *Q, void *output);

// I.S : Queue tidak kosong
// F.S : Mengembalikan elemen dari bagian depan queue tanpa menghapus
void *Front(Queue Q);

// I.S : Queue tidak kosong
// F.S : Mengembalikan elemen dari bagian belakang queue tanpa menghapus
void *Rear(Queue Q);

// I.S : Queue terdefinisi
// F.S : Menghapus semua elemen queue
void ClearQueue(Queue *Q);

// I.S : Queue terdefinisi
// F.S : Mengembalikan jumlah elemen dalam queue
int QueueSize(Queue Q);

// I.S : Queue terdefinisi
// F.S : Menampilkan isi queue
void PrintQueue(Queue Q);

#endif /* QUEUE_H */
