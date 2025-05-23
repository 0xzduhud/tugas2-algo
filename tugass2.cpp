#include <iostream>
using namespace std;


struct Pesanan {
    string namaPelanggan;
    string rotiPilihan;
    int hargaTotal;
};

// Struktur Node untuk Queue
struct queue {
    Pesanan data;
    queue *berikutnya;
};

// Struktur Node untuk Stack
struct stack {
    Pesanan data;
    stack *berikutnya;
};


queue *antrianDepan = nullptr, *antrianBelakang = nullptr;
stack *riwayatAwal = nullptr, *riwayatAkhir = nullptr;

// cek queuekosong
bool antrianKosong() {
    return antrianDepan == nullptr;
}

// nambah anteran
void tambahKeAntrian(Pesanan pesanan) {
    queue *baru = new queue{pesanan, nullptr};
    if (antrianKosong()) {
        antrianDepan = antrianBelakang = baru;
    } else {
        antrianBelakang->berikutnya = baru;
        antrianBelakang = baru;
    }
    cout << "Pesanan atas nama " << pesanan.namaPelanggan << " telah ditambahkan ke antrian.\n";
}


Pesanan prosesAntrian() {
    if (antrianKosong()) {
        cout << "Antrian kosong.\n";
        return {};
    }
    queue *hapus = antrianDepan;
    Pesanan diambil = hapus->data;
    antrianDepan = antrianDepan->berikutnya;
    if (antrianDepan == nullptr) antrianBelakang = nullptr;
    delete hapus;
    return diambil;
}

// daftar antrian
void tampilkanAntrian() {
    if (antrianKosong()) {
        cout << "Antrian kosong.\n";
        return;
    }
    queue *penunjuk = antrianDepan;
    int nomor = 1;
    cout << "\n--- Daftar Antrian ---\n";
    while (penunjuk) {
        cout << nomor++ << ". " << penunjuk->data.namaPelanggan
             << " | Roti: " << penunjuk->data.rotiPilihan
             << " | Harga: " << penunjuk->data.hargaTotal << endl;
        penunjuk = penunjuk->berikutnya;
    }
}


bool riwayatKosong() {
    return riwayatAwal == nullptr;
}


void push(Pesanan pesanan) {
    stack *baru = new stack{pesanan, nullptr};
    if (riwayatKosong()) {
        riwayatAwal = riwayatAkhir = baru;
    } else {
        riwayatAkhir->berikutnya = baru;
        riwayatAkhir = baru;
    }
}



void tampilkanRiwayat() {
    if (riwayatKosong()) {
        cout << "Belum ada riwayat pesanan.\n";
        return;
    }
    stack *penunjuk = riwayatAwal;
    int nomor = 1;
    cout << "\n--- Riwayat Pesanan Dilayani ---\n";
    while (penunjuk) {
        cout << nomor++ << ". " << penunjuk->data.namaPelanggan
             << " | Roti: " << penunjuk->data.rotiPilihan
             << " | Harga: " << penunjuk->data.hargaTotal << endl;
        penunjuk = penunjuk->berikutnya;
    }
}

// batal pesanan
void batalkanTerakhir() {
    if (antrianKosong()) {
        cout << "Tidak ada pesanan yang bisa dibatalkan.\n";
        return;
    }
    cout << "Pesanan atas nama " << antrianBelakang->data.namaPelanggan << " akan dibatalkan.\n";
    char konfirmasi;
    cout << "Yakin? (y/n): ";
    cin >> konfirmasi;
    cin.ignore();
    if (konfirmasi != 'y' && konfirmasi != 'Y') {
        cout << "Pembatalan dibatalkan.\n";
        return;
    }
    if (antrianDepan == antrianBelakang) {
        delete antrianDepan;
        antrianDepan = antrianBelakang = nullptr;
    } else {
        queue *sebelum = antrianDepan;
        while (sebelum->berikutnya != antrianBelakang)
            sebelum = sebelum->berikutnya;
        delete antrianBelakang;
        antrianBelakang = sebelum;
        antrianBelakang->berikutnya = nullptr;
    }
    cout << "Pesanan dibatalkan.\n";
}

// input pesana
void inputPesanan() {
    Pesanan p;
    cout << "Nama Pelanggan: ";
    getline(cin, p.namaPelanggan);
    cout << "Jenis Roti: ";
    getline(cin, p.rotiPilihan);
    cout << "Total Harga: ";
    cin >> p.hargaTotal;
    cin.ignore();
    tambahKeAntrian(p);
}

// melayani pesanan
void layaniPesanan() {
    if (antrianKosong()) {
        cout << "Tidak ada pesanan yang menunggu.\n";
    } else {
        Pesanan p = prosesAntrian();
        push(p);
        cout << "Pesanan untuk " << p.namaPelanggan << " sedang diproses.\n";
    }
}


int main() {
    int pilihan;
    char menuKembali;
    do {
        cout << "\n=========================\n";
        cout << "TOKO ROTI" << endl;
        cout << "=========================\n";
        cout << "1. Tambah Pesanan\n";
        cout << "2. Proses Pesanan\n";
        cout << "3. Tampilkan Antrian\n";
        cout << "4. Batalkan Pesanan Terakhir\n";
        cout << "5. Riwayat\n";
        cout << "6. Keluar\n";
        cout << "Pilihan Anda: ";
        cin >> pilihan;
        cin.ignore();
        switch (pilihan) {
            case 1: inputPesanan(); break;
            case 2: layaniPesanan(); break;
            case 3: tampilkanAntrian(); break;
            case 4: batalkanTerakhir(); break;
            case 5: tampilkanRiwayat(); break;
            case 6: return 0;
            default: cout << "Pilihan tidak valid!\n";
            break;
        }
        cout << "Kembali ke menu? (y/n) : ";
        cin >> menuKembali;
        cin.ignore();

    } 
    while (menuKembali == 'y' || menuKembali == 'Y');
    return 0;
}
