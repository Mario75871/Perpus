
#ifndef TRANSAKSI_H
#define TRANSAKSI_H

#include "buku.h"
#include "stack.h"

void InisialisasiTransaksi();
void TambahPeminjam(string nama, string judulBuku, int prioritas);
void ProsesPeminjaman(string judulBuku);
void KembalikanBuku(string judulBuku);
void TampilkanAntrean(string judulBuku);
void Undo();

#endif
