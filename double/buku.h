
#ifndef BUKU_H
#define BUKU_H

#include "queue.h"

#define MAX_BOOKS 100

typedef struct {
    string judul;
    int stok;
    Queue antrean[3]; // 0=dosen, 1=mahasiswa, 2=masyarakat
} Buku;

void InisialisasiBuku(Buku *buku, string judul, int stok);
Buku* CariBuku(string judul);
extern Buku daftarBuku[MAX_BOOKS];
extern int jumlahBuku;

#endif
