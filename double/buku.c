
#include <string.h>
#include <stdlib.h>
#include "buku.h"

Buku daftarBuku[MAX_BOOKS];
int jumlahBuku = 0;

void InisialisasiBuku(Buku *buku, string judul, int stok) {
    buku->judul = strdup(judul);
    buku->stok = stok;
    for (int i = 0; i < 3; i++) {
        CreateQueue(&buku->antrean[i], TYPE_STRING);
    }
    daftarBuku[jumlahBuku++] = *buku;
}

Buku* CariBuku(string judul) {
    for (int i = 0; i < jumlahBuku; i++) {
        if (strcmp(daftarBuku[i].judul, judul) == 0)
            return &daftarBuku[i];
    }
    return NULL;
}
