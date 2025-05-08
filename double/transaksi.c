
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "transaksi.h"

Stack undoStack;

void InisialisasiTransaksi() {
    CreateStack(&undoStack, TYPE_STRING);
}

void SimpanUndo(string aksi, string nama, string judul, int prioritas) {
    char buffer[256];
    sprintf(buffer, "%s|%s|%s|%d", aksi, nama, judul, prioritas);
    Push(&undoStack, &((string){buffer}));
}

void TambahPeminjam(string nama, string judulBuku, int prioritas) {
    Buku *buku = CariBuku(judulBuku);
    if (!buku) return;
    Enqueue(&buku->antrean[prioritas], &nama);
    SimpanUndo("tambah", nama, judulBuku, prioritas);
}

void ProsesPeminjaman(string judulBuku) {
    Buku *buku = CariBuku(judulBuku);
    if (!buku || buku->stok <= 0) return;
    for (int i = 0; i < 3; i++) {
        if (!IsQueueEmpty(buku->antrean[i])) {
            string nama;
            Dequeue(&buku->antrean[i], &nama);
            buku->stok--;
            SimpanUndo("pinjam", nama, judulBuku, i);
            printf("%s meminjam buku '%s'\n", nama, judulBuku);
            return;
        }
    }
}

void KembalikanBuku(string judulBuku) {
    Buku *buku = CariBuku(judulBuku);
    if (!buku) return;
    buku->stok++;
    SimpanUndo("kembali", "", judulBuku, -1);
}

void TampilkanAntrean(string judulBuku) {
    Buku *buku = CariBuku(judulBuku);
    if (!buku) return;
    for (int i = 0; i < 3; i++) {
        printf("Prioritas %d: ", i);
        PrintQueue(buku->antrean[i]);
    }
}

void Undo() {
    if (IsStackEmpty(undoStack)) return;

    string aksiStr;
    Pop(&undoStack, &aksiStr);

    char *token = strtok(aksiStr, "|");
    string aksi = token;
    string nama = strtok(NULL, "|");
    string judul = strtok(NULL, "|");
    int prioritas = atoi(strtok(NULL, "|"));

    Buku *buku = CariBuku(judul);
    if (!buku) return;

    if (strcmp(aksi, "pinjam") == 0) {
        buku->stok++;
        Enqueue(&buku->antrean[prioritas], &nama);
    } else if (strcmp(aksi, "tambah") == 0) {
        Queue *Q = &buku->antrean[prioritas];
        Queue temp; CreateQueue(&temp, TYPE_STRING);
        string tempNama;
        while (!IsQueueEmpty(*Q)) {
            Dequeue(Q, &tempNama);
            if (strcmp(tempNama, nama) != 0) {
                Enqueue(&temp, &tempNama);
            }
        }
        *Q = temp;
    } else if (strcmp(aksi, "kembali") == 0) {
        buku->stok--;
    }
}
