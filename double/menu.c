
#include <stdio.h>
#include <string.h>
#include "menu.h"
#include "buku.h"
#include "transaksi.h"

void Menu() {
    InisialisasiTransaksi();
    int pilihan;
    char judul[100], nama[100];
    int stok, prioritas;
    Buku b;

    while (1) {
        printf("\n=== MENU PERPUSTAKAAN ===\n");
        printf("1. Tambah Buku\n");
        printf("2. Tambah Peminjam\n");
        printf("3. Proses Peminjaman\n");
        printf("4. Kembalikan Buku\n");
        printf("5. Tampilkan Antrean\n");
        printf("6. Undo\n");
        printf("0. Keluar\n");
        printf("Pilih: ");
        scanf("%d", &pilihan); getchar();

        switch (pilihan) {
            case 1:
                printf("Judul buku: "); fgets(judul, sizeof(judul), stdin); judul[strcspn(judul, "\n")] = 0;
                printf("Jumlah stok: "); scanf("%d", &stok); getchar();
                InisialisasiBuku(&b, judul, stok);
                break;
            case 2:
                printf("Nama: "); fgets(nama, sizeof(nama), stdin); nama[strcspn(nama, "\n")] = 0;
                printf("Judul buku: "); fgets(judul, sizeof(judul), stdin); judul[strcspn(judul, "\n")] = 0;
                printf("Prioritas (0=dosen,1=mahasiswa,2=masyarakat): "); scanf("%d", &prioritas); getchar();
                TambahPeminjam(nama, judul, prioritas);
                break;
            case 3:
                printf("Judul buku: "); fgets(judul, sizeof(judul), stdin); judul[strcspn(judul, "\n")] = 0;
                ProsesPeminjaman(judul);
                break;
            case 4:
                printf("Judul buku: "); fgets(judul, sizeof(judul), stdin); judul[strcspn(judul, "\n")] = 0;
                KembalikanBuku(judul);
                break;
            case 5:
                printf("Judul buku: "); fgets(judul, sizeof(judul), stdin); judul[strcspn(judul, "\n")] = 0;
                TampilkanAntrean(judul);
                break;
            case 6:
                Undo();
                break;
            case 0:
                return;
            default:
                printf("Pilihan tidak valid.\n");
        }
    }
}
