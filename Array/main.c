#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "perpustakaan.h"

// Fungsi untuk membersihkan layar konsol
void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// Fungsi untuk membersihkan buffer input (setelah scanf)
void cleanInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Fungsi untuk mengambil input string dengan aman
void getString(char* buffer, int size) {
    fgets(buffer, size, stdin);
    // Menghapus karakter newline di akhir string
    buffer[strcspn(buffer, "\n")] = 0;
}

void pressEnterToContinue() {
    printf("\nTekan Enter untuk melanjutkan...");
    cleanInputBuffer();
}

void menuPinjamBuku(Perpustakaan* perpus) {
    char nama[MAX_NAMA];
    char judul[MAX_JUDUL];
    int pilihanTipe;
    TipeAnggota tipe;

    printf("--- Menu Pinjam Buku ---\n");
    printf("Masukkan Nama Anda: ");
    getString(nama, MAX_NAMA);

    printf("Masukkan Judul Buku yang ingin dipinjam: ");
    getString(judul, MAX_JUDUL);

    printf("Pilih Tipe Keanggotaan:\n");
    printf("1. Dosen\n");
    printf("2. Mahasiswa\n");
    printf("3. Masyarakat Umum\n");
    printf("Pilihan Anda: ");
    scanf("%d", &pilihanTipe);
    cleanInputBuffer();

    switch(pilihanTipe) {
        case 1: tipe = DOSEN; break;
        case 2: tipe = MAHASISWA; break;
        case 3: tipe = UMUM; break;
        default:
            printf("Tipe tidak valid! Aksi dibatalkan.\n");
            return;
    }
    // Memanggil fungsi ADT untuk mendaftarkan pinjaman
    daftarPinjam(perpus, judul, nama, tipe);
}

int main() {
    Perpustakaan perpus;
    initPerpustakaan(&perpus);

    // Pra-inisialisasi data buku agar menu bisa langsung digunakan
    tambahBuku(&perpus, "Buku1", 1);
    tambahBuku(&perpus, "Buku2", 1);
    printf("Data buku awal telah di-load.\n");
    pressEnterToContinue();

    int pilihan = -1;
    do {
        clearScreen();
        printf("========= SISTEM PERPUSTAKAAN PERGURUAN TINGGI =========\n\n");
        printf("Menu:\n");
        printf("1. Pinjam Buku\n");
        printf("2. Lihat Status Perpustakaan\n");
        printf("3. Proses Antrian Peminjaman (Manual oleh Admin)\n");
        printf("0. Keluar\n\n");
        printf(">> Pilihan Anda: ");
        scanf("%d", &pilihan);
        cleanInputBuffer();

        switch (pilihan) {
            case 1:
                clearScreen();
                menuPinjamBuku(&perpus);
                pressEnterToContinue();
                break;
            case 2:
                clearScreen();
                tampilkanStatusPerpustakaan(&perpus);
                pressEnterToContinue();
                break;
            case 3:
                {
                    char judul[MAX_JUDUL];
                    clearScreen();
                    printf("--- Proses Peminjaman Buku dari Antrian ---\n");
                    printf("Masukkan Judul Buku yang akan diproses antriannya: ");
                    getString(judul, MAX_JUDUL);
                    prosesPeminjaman(&perpus, judul);
                    pressEnterToContinue();
                }
                break;
            case 0:
                printf("\nTerima kasih telah menggunakan sistem ini!\n");
                break;
            default:
                printf("\nPilihan tidak valid. Silakan coba lagi.\n");
                pressEnterToContinue();
                break;
        }

    } while (pilihan != 0);

    return 0;
}
