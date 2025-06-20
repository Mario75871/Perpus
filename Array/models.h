#ifndef MODELS_H
#define MODELS_H

// --- Konstanta untuk ukuran array ---
#define MAX_JUDUL 50
#define MAX_NAMA 50
#define MAX_BUKU 10
#define MAX_ANTRIAN 50
#define MAX_AKSI 100

// --- Definisi Tipe Data (ADT) ---

// Enum untuk level prioritas
typedef enum {
    DOSEN = 1,
    MAHASISWA = 2,
    UMUM = 3
} TipeAnggota;

// Struktur untuk data peminjam
typedef struct {
    char nama[MAX_NAMA];
    int prioritas;
} Peminjam;

// Struktur untuk mencatat riwayat aksi (untuk fitur undo/pembatalan)
typedef struct {
    char namaPeminjam[MAX_NAMA];
    char judulBuku[MAX_JUDUL];
} Aksi;

// Struktur untuk data buku
typedef struct {
    char judul[MAX_JUDUL];
    int stok; [cite_start]// Stok buku bervariasi antara 1 sampai N [cite: 1]
    char dipinjamOleh[MAX_NAMA];
    
    // Antrian peminjam diimplementasikan dengan array
    Peminjam antrian[MAX_ANTRIAN];
    int jumlahAntrian;
} Buku;

// Struktur utama yang merepresentasikan perpustakaan
typedef struct {
    Buku daftarBuku[MAX_BUKU];
    int jumlahBuku;
    
    [cite_start]// Tumpukan (Stack) diimplementasikan dengan array untuk fitur undo [cite: 7]
    Aksi tumpukanAksi[MAX_AKSI];
    int topAksi; // Indeks teratas dari stack, -1 jika kosong
} Perpustakaan;

#endif // MODELS_H
