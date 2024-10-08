#include <iostream>
#include <string>
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

class Node {
public:
    Sparepart data;
    Node* next;

    Node(Sparepart sparepart)
        : data(sparepart), next(nullptr) {}
};

class LinkedList {
private:
    Node* head;

public:
    LinkedList() : head(nullptr) {}

    Node* getHead() const {
        return head;
    }

    void setHead(Node* newHead) {
        head = newHead;
    }

    void tambahSparepart(Sparepart sparepart) {
        Node* newNode = new Node(sparepart);
        if (head == nullptr) {
            head = newNode;
        } else {
            Node* temp = head;
            while (temp->next != nullptr) {
                temp = temp->next;
            }
            temp->next = newNode;
        }
        cout << "Sparepart berhasil ditambahkan.\n";
    }

    void tampilkanSparepart() {
        if (head == nullptr) {
            cout << endl;
            cout << "Belum ada sparepart yang ditambahkan.\n";
            return;
        }

        cout << "\n_____ Daftar Sparepart _____\n";
        Node* temp = head;
        int index = 1;
        while (temp != nullptr) {
            cout << index << ". Nama: " << temp->data.nama << "\n"
                << "   Kategori: " << temp->data.kategori << "\n"
                << "   Stok: " << temp->data.stok << "\n"
                << "   Harga: Rp" << temp->data.harga << "\n\n";
            temp = temp->next;
            index++;
        }
    }

    void updateSparepart(int index) {
        if (head == nullptr) {
            cout << "Belum ada sparepart yang ditambahkan.\n";
            return;
        }

        Node* temp = head;
        int currentIndex = 1;
        while (temp != nullptr && currentIndex < index) {
            temp = temp->next;
            currentIndex++;
        }

        if (temp == nullptr) {
            cout << "Nomor sparepart tidak valid.\n";
            return;
        }

        string newNama, newKategori;
        int newStok;
        float newHarga;

        cin.ignore();
        cout << "Masukkan nama baru (atau enter untuk tidak mengubah): ";
        getline(cin, newNama);
        if (!newNama.empty()) temp->data.nama = newNama;

        cout << "Masukkan kategori baru (atau enter untuk tidak mengubah): ";
        getline(cin, newKategori);
        if (!newKategori.empty()) temp->data.kategori = newKategori;

        cout << "Masukkan jumlah stok baru (atau -1 untuk tidak mengubah): ";
        cin >> newStok;
        if (newStok != -1) temp->data.stok = newStok;

        cout << "Masukkan harga baru (atau -1 untuk tidak mengubah): ";
        cin >> newHarga;
        if (newHarga != -1) temp->data.harga = newHarga;

        cout << "Sparepart berhasil diupdate.\n";
    }

    void hapusSparepart(int index) {
        if (head == nullptr) {
            cout << "Belum ada sparepart yang ditambahkan.\n";
            return;
        }

        Node* temp = head;
        if (index == 1) {
            head = head->next;
            delete temp;
            cout << "Sparepart berhasil dihapus.\n";
            return;
        }

        Node* prev = nullptr;
        int currentIndex = 1;
        while (temp != nullptr && currentIndex < index) {
            prev = temp;
            temp = temp->next;
            currentIndex++;
        }

        if (temp == nullptr) {
            cout << "Nomor sparepart tidak valid.\n";
            return;
        }

        prev->next = temp->next;
        delete temp;
        cout << "Sparepart berhasil dihapus.\n";
    }

    void cariSparepart(string keyword) {
        if (head == nullptr) {
            cout << "Belum ada sparepart yang ditambahkan.\n";
            return;
        }

        Node* temp = head;
        bool ditemukan = false;
        int index = 1;
        cout << "\n===== Hasil Pencarian =====\n";
        while (temp != nullptr) {
            if (temp->data.nama.find(keyword) != string::npos || 
                temp->data.kategori.find(keyword) != string::npos) {
                cout << index << ". Nama: " << temp->data.nama << "\n"
                    << "   Kategori: " << temp->data.kategori << "\n"
                    << "   Stok: " << temp->data.stok << "\n"
                    << "   Harga: Rp" << temp->data.harga << "\n\n";
                ditemukan = true;
            }
            temp = temp->next;
            index++;
        }

        if (!ditemukan) {
            cout << "Tidak ada sparepart yang cocok dengan kata kunci tersebut.\n";
        }
    }
};

class Stack {
private:
    LinkedList list;
    
public:
    void push(Sparepart sparepart) {
        list.tambahSparepart(sparepart);
    }

    void pop() {
        Node* head = list.getHead();
        if (head == nullptr) {
            cout << "Stack kosong, tidak ada sparepart yang bisa dihapus.\n";
            return;
        }

        Node* temp = head;
        if (temp->next == nullptr) {
            delete temp;
            list.setHead(nullptr);
            cout << "Sparepart terakhir berhasil dihapus.\n";
            return;
        }

        while (temp->next->next != nullptr) {
            temp = temp->next;
        }

        delete temp->next;
        temp->next = nullptr;
        cout << "Sparepart terakhir berhasil dihapus.\n";
    }

    void tampilkanStack() {
        cout << "\n_____ Daftar Sparepart dalam Stack _____\n";
        list.tampilkanSparepart();
    }
};

class Queue {
private:
    LinkedList list;

public:
    void enqueue(Sparepart sparepart) {
        list.tambahSparepart(sparepart);
    }

    void dequeue() {
        Node* head = list.getHead();
        if (head == nullptr) {
            cout << "Queue kosong, tidak ada sparepart yang bisa dihapus.\n";
            return;
        }

        Node* temp = head;
        list.setHead(head->next);
        delete temp;
        cout << "Sparepart pertama berhasil dihapus dari queue.\n";
    }

    void tampilkanQueue() {
        cout << "\n_____ Daftar Sparepart dalam Queue _____\n";
        cout << endl;
        list.tampilkanSparepart();
    }
};

int main() {
    LinkedList listSparepart;
    Stack stackSparepart;
    Queue queueSparepart;
    int pilihan;

    do {
        cout << "\n_____ Program List Sparepart Komputer _____\n";
        cout << endl;
        cout << "1. Tambah Sparepart\n";
        cout << "2. Tampilkan Semua Sparepart\n";
        cout << "3. Update Sparepart\n";
        cout << "4. Hapus Sparepart\n";
        cout << "5. Cari Sparepart\n";
        cout << "6. Tambah Sparepart ke Stack\n";
        cout << "7. Hapus Sparepart dari Stack\n";
        cout << "8. Tampilkan Sparepart dalam Stack\n";
        cout << "9. Tambah Sparepart ke Queue\n";
        cout << "10. Hapus Sparepart dari Queue\n";
        cout << "11. Tampilkan Sparepart dalam Queue\n";
        cout << "0. Keluar\n";
        cout << endl;
        cout << "Pilihan Anda: ";
        cin >> pilihan;

        switch(pilihan) {
            case 1: {
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

                listSparepart.tambahSparepart(Sparepart(nama, kategori, stok, harga));
                break;
            }
            case 2: 
                listSparepart.tampilkanSparepart(); 
                break;
            case 3: {
                int index;
                cout << "Masukkan nomor sparepart yang akan diupdate: ";
                cin >> index;
                listSparepart.updateSparepart(index);
                break;
            }
            case 4: {
                int index;
                cout << "Masukkan nomor sparepart yang akan dihapus: ";
                cin >> index;
                listSparepart.hapusSparepart(index);
                break;
            }
            case 5: {
                string keyword;
                cout << "Masukkan kata kunci pencarian: ";
                cin.ignore();
                getline(cin, keyword);
                listSparepart.cariSparepart(keyword);
                break;
            }
            case 6: {
                string nama, kategori;
                int stok;
                float harga;

                cout << "Masukkan nama sparepart untuk stack: ";
                cin.ignore();
                getline(cin, nama);

                cout << "Masukkan kategori sparepart untuk stack: ";
                getline(cin, kategori);

                cout << "Masukkan jumlah stok untuk stack: ";
                cin >> stok;

                cout << "Masukkan harga untuk stack: ";
                cin >> harga;

                stackSparepart.push(Sparepart(nama, kategori, stok, harga));
                break;
            }
            case 7:
                stackSparepart.pop();
                break;
            case 8:
                stackSparepart.tampilkanStack();
                break;
            case 9: {
                string nama, kategori;
                int stok;
                float harga;

                cout << "Masukkan nama sparepart untuk queue: ";
                cin.ignore();
                getline(cin, nama);

                cout << "Masukkan kategori sparepart untuk queue: ";
                getline(cin, kategori);

                cout << "Masukkan jumlah stok untuk queue: ";
                cin >> stok;

                cout << "Masukkan harga untuk queue: ";
                cin >> harga;

                queueSparepart.enqueue(Sparepart(nama, kategori, stok, harga));
                break;
            }
            case 10:
                queueSparepart.dequeue();
                break;
            case 11:
                queueSparepart.tampilkanQueue();
                break;
            case 0: 
                cout << "Terima kasih telah menggunakan program ini.\n"; 
                break;
            default: 
                cout << "Pilihan tidak valid. Silakan coba lagi.\n";
        }
    } while (pilihan != 0);

    return 0;
}
