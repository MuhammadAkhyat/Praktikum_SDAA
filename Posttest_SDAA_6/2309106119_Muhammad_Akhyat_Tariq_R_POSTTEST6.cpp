#include <iostream>
#include <string>
#include <cmath>
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

    Node* sortedMergeAscending(Node* a, Node* b) {
        if (a == nullptr)
            return b;
        if (b == nullptr)
            return a;

        Node* result = nullptr;
        if (a->data.harga <= b->data.harga) {
            result = a;
            result->next = sortedMergeAscending(a->next, b);
        } else {
            result = b;
            result->next = sortedMergeAscending(a, b->next);
        }
        return result;
    }

    Node* mergeSortAscending(Node* h) {
        if (h == nullptr || h->next == nullptr) {
            return h;
        }

        Node* middle = getMiddle(h);
        Node* nextToMiddle = middle->next;

        middle->next = nullptr;

        Node* left = mergeSortAscending(h);
        Node* right = mergeSortAscending(nextToMiddle);

        return sortedMergeAscending(left, right);
    }

    Node* getMiddle(Node* h) {
        if (h == nullptr) return h;

        Node* slow = h;
        Node* fast = h->next;

        while (fast != nullptr) {
            fast = fast->next;
            if (fast != nullptr) {
                slow = slow->next;
                fast = fast->next;
            }
        }
        return slow;
    }

    Node* partitionDescending(Node* low, Node* high) {
        float pivot = high->data.harga;
        Node* i = low->next;

        for (Node* j = low; j != high; j = j->next) {
            if (j->data.harga > pivot) {
                swap(i->data, j->data);
                i = (i == nullptr) ? low : i->next;
            }
        }
        swap(i->data, high->data);
        return i;
    }

    void quickSortDescending(Node* low, Node* high) {
        if (low != nullptr && high != nullptr && low != high && low != high->next) {
            Node* pivot = partitionDescending(low, high);
            quickSortDescending(low, pivot->next);
            quickSortDescending(pivot->next, high);
        }
    }

public:
    LinkedList() : head(nullptr) {}

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

    void sortAscending() {
        head = mergeSortAscending(head);
        cout << "Sparepart berhasil diurutkan secara ascending berdasarkan harga.\n";
    }

    void sortDescending() {
        quickSortDescending(head, getTail(head));
        cout << "Sparepart berhasil diurutkan secara descending berdasarkan harga.\n";
    }

    Node* getTail(Node* cur) {
        while (cur != nullptr && cur->next != nullptr)
            cur = cur->next;
        return cur;
    }

    int fibonacciSearch(int arr[], int x, int n) {
        int fib2 = 0;
        int fib1 = 1;
        int fibM = fib2 + fib1;

        while (fibM < n) {
            fib2 = fib1;
            fib1 = fibM;
            fibM = fib2 + fib1;
        }

        int offset = -1;

        while (fibM > 1) {
            int i = min(offset + fib2, n - 1);
            if (arr[i] < x) {
                fibM = fib1;
                fib1 = fib2;
                fib2 = fibM - fib1;
                offset = i;
            } else if (arr[i] > x) {
                fibM = fib2;
                fib1 = fib1 - fib2;
                fib2 = fibM - fib1;
            } else {
                return i;
            }
        }

        if (fib1 && arr[offset + 1] == x)
            return offset + 1;

        return -1;
    }

    int jumpSearch(int arr[], int x, int n) {
        int step = sqrt(n);
        int prev = 0;

        while (arr[min(step, n) - 1] < x) {
            prev = step;
            step += sqrt(n);
            if (prev >= n) return -1;
        }

        while (arr[prev] < x) {
            prev++;
            if (prev == min(step, n)) return -1;
        }

        if (arr[prev] == x) return prev;

        return -1;
    }

    int boyerMooreSearch(string text, string pattern) {
        int m = pattern.size();
        int n = text.size();
        int badChar[256];

        for (int i = 0; i < 256; i++) badChar[i] = -1;
        for (int i = 0; i < m; i++) badChar[(int)pattern[i]] = i;

        int s = 0;
        while (s <= (n - m)) {
            int j = m - 1;
            while (j >= 0 && pattern[j] == text[s + j]) j--;

            if (j < 0) {
                return s;
                s += (s + m < n) ? m - badChar[text[s + m]] : 1;
            } else {
                s += max(1, j - badChar[text[s + j]]);
            }
        }

        return -1;
    }

    void cariStok(int stokDicari) {
        Node* temp = head;
        int stokArray[100], index = 0;
        
        while (temp != nullptr) {
            stokArray[index++] = temp->data.stok;
            temp = temp->next;
        }
        
        int posisi = fibonacciSearch(stokArray, stokDicari, index);
        
        if (posisi != -1) {
            cout << "Sparepart dengan stok " << stokDicari << " ditemukan di posisi ke-" << posisi + 1 << ".\n";
        } else {
            cout << "Sparepart dengan stok " << stokDicari << " tidak ditemukan.\n";
        }
    }

    void cariHarga(int hargaDicari) {
        Node* temp = head;
        int hargaArray[100], index = 0;
        
        while (temp != nullptr) {
            hargaArray[index++] = temp->data.harga;
            temp = temp->next;
        }
        
        int posisi = jumpSearch(hargaArray, hargaDicari, index);
        
        if (posisi != -1) {
            cout << "Sparepart dengan harga " << hargaDicari << " ditemukan di posisi ke-" << posisi + 1 << ".\n";
        } else {
            cout << "Sparepart dengan harga " << hargaDicari << " tidak ditemukan.\n";
        }
    }

    void cariNama(string namaDicari) {
        Node* temp = head;
        bool ditemukan = false;
        int index = 1;

        while (temp != nullptr) {
            if (boyerMooreSearch(temp->data.nama, namaDicari) != -1) {
                cout << "Sparepart dengan nama: " << temp->data.nama << " ditemukan di posisi ke-" << index << ".\n";
                ditemukan = true;
            }
            temp = temp->next;
            index++;
        }

        if (!ditemukan) {
            cout << "Sparepart dengan nama " << namaDicari << " tidak ditemukan.\n";
        }
    }
};

int main() {
    LinkedList list;

    list.tambahSparepart(Sparepart("Busi", "Mesin", 100, 20000));
    list.tambahSparepart(Sparepart("Kampas Rem", "Rem", 50, 50000));
    list.tambahSparepart(Sparepart("Oli Mesin", "Pelumas", 75, 75000));
    list.tambahSparepart(Sparepart("Filter Udara", "Sistem Intake", 120, 30000));
    list.tambahSparepart(Sparepart("Aki", "Listrik", 30, 250000));

    int pilihan;
    do {
        cout << "\nMenu:\n";
        cout << "1. Tampilkan Sparepart\n";
        cout << "2. Tambah Sparepart\n";
        cout << "3. Urutkan Sparepart Ascending\n";
        cout << "4. Urutkan Sparepart Descending\n";
        cout << "5. Cari Sparepart berdasarkan Stok\n";
        cout << "6. Cari Sparepart berdasarkan Harga\n";
        cout << "7. Cari Sparepart berdasarkan Nama\n";
        cout << "8. Keluar\n";
        cout << "Pilih: ";
        cin >> pilihan;

        switch (pilihan) {
        case 1:
            list.tampilkanSparepart();
            break;
        case 2: {
            string nama, kategori;
            int stok;
            float harga;
            cout << "Masukkan Nama Sparepart: ";
            cin >> nama;
            cout << "Masukkan Kategori Sparepart: ";
            cin >> kategori;
            cout << "Masukkan Stok Sparepart: ";
            cin >> stok;
            cout << "Masukkan Harga Sparepart: ";
            cin >> harga;
            list.tambahSparepart(Sparepart(nama, kategori, stok, harga));
            break;
        }
        case 3:
            list.sortAscending();
            break;
        case 4:
            list.sortDescending();
            break;
        case 5: {
            int stokDicari;
            cout << "Masukkan Stok yang dicari: ";
            cin >> stokDicari;
            list.cariStok(stokDicari);
            break;
        }
        case 6: {
            int hargaDicari;
            cout << "Masukkan Harga yang dicari: ";
            cin >> hargaDicari;
            list.cariHarga(hargaDicari);
            break;
        }
        case 7: {
            string namaDicari;
            cout << "Masukkan Nama yang dicari: ";
            cin >> namaDicari;
            list.cariNama(namaDicari);
            break;
        }
        case 8:
            cout << "Terima kasih! Program selesai.\n";
            break;
        default:
            cout << "Pilihan tidak valid. Silakan coba lagi.\n";
        }
    } while (pilihan != 8);

    return 0;
}
