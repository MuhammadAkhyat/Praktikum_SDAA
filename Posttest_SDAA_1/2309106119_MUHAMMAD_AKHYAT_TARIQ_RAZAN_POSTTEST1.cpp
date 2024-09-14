#include <iostream>
using namespace std;

void hanoi(int jumlah, const string asal, const string tujuan, const string sementara) {
    if (jumlah == 1) {
        cout << "Pindahkan piringan 1 dari " << asal << " ke " << tujuan << endl;
        return;
    }
    hanoi(jumlah - 1, asal, sementara, tujuan);  
    cout << "Pindahkan piringan " << jumlah << " dari " << asal << " ke " << tujuan << endl;
    hanoi(jumlah - 1, sementara, tujuan, asal);  
}

int main() {
    int jumlah_piringan;
    char lanjut;

    do {
        cout << "Masukkan jumlah piringan: ";
        cin >> jumlah_piringan;
        cout << endl;
        if (jumlah_piringan <= 0) {
            cout << "Jumlah piringan harus lebih besar dari 0." << endl;
        } else {
            hanoi(jumlah_piringan, "Menara Asal", "Menara Tujuan", "Menara Sementara"); 
        }
        cout << endl;
        cout << "Apakah Anda ingin menginput jumlah piringan lain? y/n: ";
        cout << endl;
        cin >> lanjut;
    } while (lanjut == 'y' || lanjut == 'Y');

    return 0;
}
