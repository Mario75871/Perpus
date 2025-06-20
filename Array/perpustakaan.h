#ifndef PERPUSTAKAAN_H
#define PERPUSTAKAAN_H

#include "models.h"

// --- Deklarasi Fungsi (Antarmuka ADT Perpustakaan) ---

void initPerpustakaan(Perpustakaan* perpus);
void tambahBuku(Perpustakaan* perpus, const char* judul, int stok);
void daftarPinjam(Perpustakaan* perpus, const char* judulBuku, const char* namaPeminjam, TipeAnggota tipe);
void prosesPeminjaman(Perpustakaan* perpus, const char* judulBuku);
void prosesPengembalian(Perpustakaan* perpus, const char* judulBuku, const char* namaPeminjam);
void batalAktivitasTerakhir(Perpustakaan* perpus);
void tampilkanStatusAntrian(Perpustakaan* perpus, const char* judulBuku);

// Fungsi baru untuk menampilkan status semua buku dan antriannya
void tampilkanStatusPerpustakaan(Perpustakaan* perpus);

#endif // PERPUSTAKAAN_H
