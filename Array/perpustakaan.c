#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "perpustakaan.h"

// --- Fungsi Helper (Private) ---

// Fungsi pembanding untuk qsort, mengurutkan berdasarkan prioritas
static int bandingkanPrioritas(const void* a, const void* b) {
    Peminjam* p1 = (Peminjam*)a;
    Peminjam* p2 = (Peminjam*)b;
    return p1->prioritas - p2->prioritas;
}

// Mencari buku berdasarkan judul, mengembalikan pointer ke buku
static Buku* cariBuku(Perpustakaan* perpus, const char* judul) {
    for (int i = 0; i < perpus->jumlahBuku; i++) {
        if (strcmp(perpus->daftarBuku[i].judul, judul) == 0) {
            return &perpus->daftarBuku[i];
        }
    }
    return NULL;
}

// --- Implementasi Fungsi Publik ---

void initPerpustakaan(Perpustakaan* perpus) {
    perpus->jumlahBuku = 0;
    perpus->topAksi = -1; // Stack kosong
}

void tambahBuku(Perpustakaan* perpus, const char* judul, int stok) {
    if (perpus->jumlahBuku < MAX_BUKU) {
        Buku* bukuBaru = &perpus->daftarBuku[perpus->jumlahBuku];
        strcpy(bukuBaru->judul, judul);
        bukuBaru->stok = stok;
        bukuBaru->jumlahAntrian = 0;
        strcpy(bukuBaru->dipinjamOleh, "");
        perpus->jumlahBuku++;
        printf("[INFO] Buku '%s' dengan stok %d berhasil ditambahkan.\n", judul, stok);
    } else {
        printf("[ERROR] Daftar buku sudah penuh.\n");
    }
}

void daftarPinjam(Perpustakaan* perpus, const char* judulBuku, const char* namaPeminjam, TipeAnggota tipe) {
    Buku* buku = cariBuku(perpus, judulBuku);
    if (buku) {
        if (buku->jumlahAntrian < MAX_ANTRIAN) {
            // Tambahkan peminjam ke antrian
            Peminjam* peminjamBaru = &buku->antrian[buku->jumlahAntrian];
            strcpy(peminjamBaru->nama, namaPeminjam);
            peminjamBaru->prioritas = tipe;
            buku->jumlahAntrian++;

            [cite_start]// Urutkan antrian untuk menjaga prioritas [cite: 2]
            qsort(buku->antrian, buku->jumlahAntrian, sizeof(Peminjam), bandingkanPrioritas);

            // Push aksi ke stack untuk fitur undo
            if (perpus->topAksi < MAX_AKSI - 1) {
                perpus->topAksi++;
                Aksi* aksiBaru = &perpus->tumpukanAksi[perpus->topAksi];
                strcpy(aksiBaru->namaPeminjam, namaPeminjam);
                strcpy(aksiBaru->judulBuku, judulBuku);
            }
            printf("[INFO] '%s' masuk ke antrian peminjaman '%s'.\n", namaPeminjam, judulBuku);
        } else {
            printf("[ERROR] Antrian untuk buku '%s' sudah penuh.\n", judulBuku);
        }
    } else {
        printf("[ERROR] Buku '%s' tidak ditemukan.\n", judulBuku);
    }
}

void prosesPeminjaman(Perpustakaan* perpus, const char* judulBuku) {
    printf("\n--- Memproses Peminjaman Buku '%s' ---\n", judulBuku);
    Buku* buku = cariBuku(perpus, judulBuku);
    if (buku) {
        if (buku->stok > 0) {
            if (buku->jumlahAntrian > 0) {
                [cite_start]// Ambil peminjam dengan prioritas tertinggi (indeks 0) [cite: 2, 3]
                Peminjam peminjam = buku->antrian[0];
                buku->stok--;
                strcpy(buku->dipinjamOleh, peminjam.nama);
                
                printf("[SUKSES] Buku '%s' berhasil dipinjam oleh '%s' (Prioritas: %d).\n", judulBuku, peminjam.nama, peminjam.prioritas);

                // Geser antrian ke kiri
                for (int i = 0; i < buku->jumlahAntrian - 1; i++) {
                    buku->antrian[i] = buku->antrian[i + 1];
                }
                buku->jumlahAntrian--;
            } else {
                printf("[INFO] Tidak ada antrian untuk buku '%s'.\n", judulBuku);
            }
        } else {
            printf("[GAGAL] Stok buku '%s' habis.\n", judulBuku);
        }
    } else {
        printf("[ERROR] Buku '%s' tidak ditemukan.\n", judulBuku);
    }
}

void prosesPengembalian(Perpustakaan* perpus, const char* judulBuku, const char* namaPeminjam) {
    printf("\n--- Memproses Pengembalian Buku '%s' oleh '%s' ---\n", judulBuku, namaPeminjam);
    Buku* buku = cariBuku(perpus, judulBuku);
    if (buku) {
        if (strcmp(buku->dipinjamOleh, namaPeminjam) == 0) {
            buku->stok++;
            strcpy(buku->dipinjamOleh, "");
            printf("[SUKSES] Buku '%s' telah dikembalikan.\n", judulBuku);

            [cite_start]// Sistem akan cek antrian peminjaman buku dengan prioritas tertinggi [cite: 4]
            if (buku->jumlahAntrian > 0) {
                printf("[INFO] Potensi peminjam selanjutnya adalah '%s'.\n", buku->antrian[0].nama);
            } else {
                printf("[INFO] Antrian untuk buku '%s' kosong.\n", judulBuku);
            }
        } else {
            printf("[GAGAL] '%s' tidak tercatat meminjam buku ini.\n", namaPeminjam);
        }
    } else {
        printf("[ERROR] Buku '%s' tidak ditemukan.\n", judulBuku);
    }
}

void batalAktivitasTerakhir(Perpustakaan* perpus) {
    printf("\n--- Memproses Pembatalan Aktivitas Terakhir ---\n");
    if (perpus->topAksi > -1) {
        // Pop aksi dari stack
        Aksi aksiTerakhir = perpus->tumpukanAksi[perpus->topAksi];
        perpus->topAksi--;
        
        printf("[INFO] Aksi yang dibatalkan: Pendaftaran '%s' untuk buku '%s'.\n", aksiTerakhir.namaPeminjam, aksiTerakhir.judulBuku);

        Buku* buku = cariBuku(perpus, aksiTerakhir.judulBuku);
        if (buku) {
            int indexHapus = -1;
            // Cari peminjam di antrian
            for (int i = 0; i < buku->jumlahAntrian; i++) {
                if (strcmp(buku->antrian[i].nama, aksiTerakhir.namaPeminjam) == 0) {
                    indexHapus = i;
                    break;
                }
            }
            
            if (indexHapus != -1) {
                // Geser elemen untuk menghapus
                for (int i = indexHapus; i < buku->jumlahAntrian - 1; i++) {
                    buku->antrian[i] = buku->antrian[i + 1];
                }
                buku->jumlahAntrian--;
                printf("[SUKSES] '%s' berhasil dihapus dari antrian '%s'.\n", aksiTerakhir.namaPeminjam, aksiTerakhir.judulBuku);
            }
        }
    } else {
        printf("[INFO] Tidak ada aktivitas yang bisa dibatalkan.\n");
    }
}

void tampilkanStatusAntrian(Perpustakaan* perpus, const char* judulBuku) {
    Buku* buku = cariBuku(perpus, judulBuku);
    if (buku) {
        printf("Status Antrian '%s': ", buku->judul);
        if (buku->jumlahAntrian == 0) {
            printf("[Kosong]\n");
        } else {
            for (int i = 0; i < buku->jumlahAntrian; i++) {
                printf("%d. %s (Prio: %d) ", i + 1, buku->antrian[i].nama, buku->antrian[i].prioritas);
            }
            printf("\n");
        }
    }
}
// --- Implementasi Fungsi Baru ---
void tampilkanStatusPerpustakaan(Perpustakaan* perpus) {
    printf("=========================================================\n");
    printf("                  STATUS PERPUSTAKAAN\n");
    printf("=========================================================\n");
    if (perpus->jumlahBuku == 0) {
        printf("Belum ada buku di dalam perpustakaan.\n");
    }

    for (int i = 0; i < perpus->jumlahBuku; i++) {
        Buku* buku = &perpus->daftarBuku[i];
        printf("Judul Buku    : %s\n", buku->judul);
        printf("Stok Tersedia : %d\n", buku->stok);
        printf("Dipinjam Oleh : %s\n", strlen(buku->dipinjamOleh) > 0 ? buku->dipinjamOleh : "[Tidak ada]");
        tampilkanStatusAntrian(perpus, buku->judul);
        printf("---------------------------------------------------------\n");
    }
}
