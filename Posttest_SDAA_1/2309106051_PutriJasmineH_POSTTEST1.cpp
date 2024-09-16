#include <iostream>
using namespace std;

int langkah = 1;

void MenaraHanoi(int n, char asal, char sementara, char tujuan) {
    if (n == 1) {
        cout << "Langkah " << langkah << ": Pindahkan piringan atas dari menara " << asal << " ke menara " << tujuan << endl;
        langkah++;
    } else {
        MenaraHanoi(n - 1, asal, tujuan, sementara);
        MenaraHanoi(1, asal, sementara, tujuan);
        MenaraHanoi(n - 1, sementara, asal, tujuan);
    }
}

int main() {
    int piringan = 3;

    cout << "===== Algoritma penyelesaian menara hanoi =====" << endl;
    cout << "========== dengan jumlah " << piringan << " piringan ===========" << endl;

    MenaraHanoi(piringan, 'A', 'B', 'C');

    cout << "Selesai" << endl;

    return 0;
}
