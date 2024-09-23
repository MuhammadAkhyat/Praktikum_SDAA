#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

class Sparepart {
public:
    string nama;
    string kategori;
    int stok;
    float harga;

    Sparepart(string n, string k, int s, float h)
        : nama(n), kategori(k), stok(s), harga(h) {}
};

vector<Sparepart> daftarSparepart;

void tambahSparepart() {
    string nama, kategori;
    int stok;
    float harga;

    cout << "Masukkan nama sparepart: ";
    cin.ignore();
    getline(cin, nama);

    cout << "Masukkan kategori sparepart: ";
    getline(cin, kategori);

    cout << "Masukkan jumlah stok: ";
    cin >> stok;

    cout << "Masukkan harga: ";
    cin >> harga;

    daftarSparepart.emplace_back(nama, kategori, stok, harga);
    cout << "Sparepart berhasil ditambahkan.\n";
}

void tampilkanSparepart() {
    if (daftarSparepart.empty()) {
        cout << "Belum ada sparepart yang ditambahkan.\n";
        return;
    }

    cout << "\n_____Daftar Sparepart _____\n";
    for (size_t i = 0; i < daftarSparepart.size(); ++i) {
        cout << i+1 << ". Nama: " << daftarSparepart[i].nama << "\n"
                << "   Kategori: " << daftarSparepart[i].kategori << "\n"
                << "   Stok: " << daftarSparepart[i].stok << "\n"
                << "   Harga: Rp" << daftarSparepart[i].harga << "\n\n";
    }
}

void updateSparepart() {
    tampilkanSparepart();

    if (daftarSparepart.empty()) return;

    size_t index;
    cout << "Masukkan nomor sparepart yang akan diupdate: ";
    cin >> index;

    if (index > 0 && index <= daftarSparepart.size()) {
        Sparepart& updateSparepart = daftarSparepart[index-1];
        string newNama, newKategori;
        int newStok;
        float newHarga;

        cin.ignore();
        cout << "Masukkan nama baru (atau enter untuk tidak mengubah): ";
        getline(cin, newNama);
        if (!newNama.empty()) updateSparepart.nama = newNama;

        cout << "Masukkan kategori baru (atau enter untuk tidak mengubah): ";
        getline(cin, newKategori);
        if (!newKategori.empty()) updateSparepart.kategori = newKategori;

        cout << "Masukkan jumlah stok baru (atau -1 untuk tidak mengubah): ";
        cin >> newStok;
        if (newStok != -1) updateSparepart.stok = newStok;

        cout << "Masukkan harga baru (atau -1 untuk tidak mengubah): ";
        cin >> newHarga;
        if (newHarga != -1) updateSparepart.harga = newHarga;

        cout << "Sparepart berhasil diupdate.\n";
    } else {
        cout << "Nomor sparepart tidak valid.\n";
    }
}

void hapusSparepart() {
    tampilkanSparepart();

    if (daftarSparepart.empty()) return;

    size_t index;
    cout << "Masukkan nomor sparepart yang akan dihapus: ";
    cin >> index;

    if (index > 0 && index <= daftarSparepart.size()) {
        daftarSparepart.erase(daftarSparepart.begin() + index - 1);
        cout << "Sparepart berhasil dihapus.\n";
    } else {
        cout << "Nomor sparepart tidak valid.\n";
    }
}

void cariSparepart() {
    string keyword;
    bool ditemukan = false;

    cout << "Masukkan kata kunci pencarian: ";
    cin.ignore();
    getline(cin, keyword);

    cout << "\n===== Hasil Pencarian =====\n";
    for (size_t i = 0; i < daftarSparepart.size(); ++i) {
        if (daftarSparepart[i].nama.find(keyword) != string::npos ||
            daftarSparepart[i].kategori.find(keyword) != string::npos) {
            cout << i+1 << ". Nama: " << daftarSparepart[i].nama << "\n"
                    << "   Kategori: " << daftarSparepart[i].kategori << "\n"
                    << "   Stok: " << daftarSparepart[i].stok << "\n"
                    << "   Harga: Rp" << daftarSparepart[i].harga << "\n\n";
            ditemukan = true;
        }
    }

    if (!ditemukan) {
        cout << "Tidak ada sparepart yang cocok dengan kata kunci tersebut.\n";
    }
}

int main() {
    int pilihan;

    do {
        cout << "\n_____ Program List Sparepart Komputer _____\n";
        cout << endl;
        cout << "1. Tambah Sparepart\n";
        cout << "2. Tampilkan Semua Sparepart\n";
        cout << "3. Update Sparepart\n";
        cout << "4. Hapus Sparepart\n";
        cout << "5. Cari Sparepart\n";
        cout << "0. Keluar\n";
        cout << endl;
        cout << "Pilihan Anda: ";
        cin >> pilihan;

        switch(pilihan) {
            case 1: tambahSparepart(); break;
            case 2: tampilkanSparepart(); break;
            case 3: updateSparepart(); break;
            case 4: hapusSparepart(); break;
            case 5: cariSparepart(); break;
            case 0: cout << "Terima kasih telah menggunakan program ini.\n"; break;
            default: cout << "Pilihan tidak valid. Silakan coba lagi.\n";
        }
    } while (pilihan != 0);

    return 0;
}