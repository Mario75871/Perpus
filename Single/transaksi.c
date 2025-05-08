
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "transaksi.h"

List undoStack;

void InisialisasiTransaksi() {
    CreateList(&undoStack);
}

void SimpanUndo(string aksi, string nama, string judul, int prioritas) {
    char buffer[256];
    sprintf(buffer, "%s|%s|%s|%d", aksi, nama, judul, prioritas);
    InsVFirst(&undoStack, (int)strdup(buffer));
}

void TambahPeminjam(string nama, string judulBuku, int prioritas) {
    Buku *buku = CariBuku(judulBuku);
    if (!buku) return;
    InsVLast(&buku->antrean[prioritas], (int)strdup(nama));
    SimpanUndo("tambah", nama, judulBuku, prioritas);
}

void ProsesPeminjaman(string judulBuku) {
    Buku *buku = CariBuku(judulBuku);
    if (!buku || buku->stok <= 0) return;
    for (int i = 0; i < 3; i++) {
        if (!ListEmpty(buku->antrean[i])) {
            string nama;
            DelVFirst(&buku->antrean[i], (int*)&nama);
            buku->stok--;
            SimpanUndo("pinjam", nama, judulBuku, i);
            printf("%s meminjam buku '%s'
", nama, judulBuku);
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
        PrintInfo(buku->antrean[i]);
    }
}

void Undo() {
    if (ListEmpty(undoStack)) return;

    int temp;
    DelVFirst(&undoStack, &temp);
    string aksiStr = (string)temp;

    char *token = strtok(aksiStr, "|");
    string aksi = token;
    string nama = strtok(NULL, "|");
    string judul = strtok(NULL, "|");
    int prioritas = atoi(strtok(NULL, "|"));

    Buku *buku = CariBuku(judul);
    if (!buku) return;

    if (strcmp(aksi, "pinjam") == 0) {
        buku->stok++;
        InsVLast(&buku->antrean[prioritas], (int)strdup(nama));
    } else if (strcmp(aksi, "tambah") == 0) {
        List *Q = &buku->antrean[prioritas];
        List tempList;
        CreateList(&tempList);
        int tempNamaInt; string tempNama;

        while (!ListEmpty(*Q)) {
            DelVFirst(Q, &tempNamaInt);
            tempNama = (string)tempNamaInt;
            if (strcmp(tempNama, nama) != 0) {
                InsVLast(&tempList, (int)strdup(tempNama));
            }
        }
        *Q = tempList;
    } else if (strcmp(aksi, "kembali") == 0) {
        buku->stok--;
    }
}
