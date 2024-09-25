#include <iostream>
#include <string>
using namespace std;

const int MAX_PARFUM = 100;
const int MAX_REVIEW = 100;
const int MAX_USERS = 100;

struct Parfum {
    string brand;
    string nama;
};

struct Review {
    string user;
    string isiReview;
    string namaParfum;
};

struct User {
    string username;
    string password;
    char role;
};

Parfum daftarParfum[MAX_PARFUM];
int jumlahParfum = 0;

Review daftarReview[MAX_REVIEW];
int jumlahReview = 0;

User daftarUser[MAX_USERS];
int jumlahUser = 0;

void clearInputBuffer() {
    cin.clear();
    cin.ignore();
}

int inputAngka() {
    int angka;
    while (true) {
        if (cin >> angka) {
            clearInputBuffer();
            return angka;
        } else {
            cout << "Input tidak valid. Harap masukkan angka: ";
            clearInputBuffer();
        }
    }
}

void tampilkanDaftarParfum() {
    if (jumlahParfum == 0) {
        cout << "Belum ada parfum yang terdaftar.\n";
        return;
    }
    
    cout << "Daftar Parfum:\n";
    for (int i = 0; i < jumlahParfum; i++) {
        cout << i + 1 << ". Brand: " << daftarParfum[i].brand << ", Nama Parfum: " << daftarParfum[i].nama << endl;
    }
}

void tambahParfum() {
    if (jumlahParfum >= MAX_PARFUM) {
        cout << "Kapasitas parfum penuh.\n";
        return;
    }

    Parfum* pParfum = &daftarParfum[jumlahParfum];
    string namabrand, namaparfum;

    do {
        cout << "Masukkan nama brand: ";
        clearInputBuffer();
        getline(cin, namabrand);
        if (namabrand.empty()) {
            cout << "Nama brand tidak boleh kosong!\n";
        }
    } while (namabrand.empty());

    do {
        cout << "Masukkan nama parfum: ";
        getline(cin, namaparfum);
        if (namaparfum.empty()) {
            cout << "Nama parfum tidak boleh kosong!\n";
        }
    } while (namaparfum.empty());

    pParfum->brand = namabrand;
    pParfum->nama = namaparfum;

    jumlahParfum++;
    cout << "Parfum berhasil ditambahkan.\n";
}

void editParfum() {
    tampilkanDaftarParfum();

    if (jumlahParfum == 0) return;

    int nomor;
    cout << "Masukkan Nomor Parfum yang ingin diedit: ";
    nomor = inputAngka();

    if (nomor > 0 && nomor <= jumlahParfum) {
        Parfum* pParfum = &daftarParfum[nomor - 1];
        string namabaru, brandbaru;

        do {
            cout << "Masukkan nama baru brand: ";
            getline(cin, brandbaru);
            if (brandbaru.empty()) {
                cout << "Nama Brand tidak boleh kosong!\n";
            }
        } while (brandbaru.empty());

        do {
            cout << "Masukkan nama baru parfum: ";
            getline(cin, namabaru);
            if (namabaru.empty()) {
                cout << "Nama Parfum tidak boleh kosong!\n";
            }
        } while (namabaru.empty());

        pParfum->brand = brandbaru;
        pParfum->nama = namabaru;
        cout << "Parfum berhasil diedit.\n";
    } else {
        cout << "Pilihan tidak valid.\n";
    }
}

void hapusParfum() {
    if (jumlahParfum <= 0) {
        cout << "Tidak ada data parfum yang bisa dihapus.\n";
        return;
    }

    tampilkanDaftarParfum();
    int nomor;

    cout << "Pilih Parfum yang ingin dihapus (0 jika tidak jadi): ";
    nomor = inputAngka();

    if (nomor > 0 && nomor <= jumlahParfum) {
        for (int i = nomor - 1; i < jumlahParfum - 1; i++) {
            daftarParfum[i] = daftarParfum[i + 1];
        }
        jumlahParfum--;
        cout << "Parfum berhasil dihapus.\n";
    } else if (nomor != 0) {
        cout << "Pilihan tidak valid.\n";
    }
}

void tambahReview(const string& username) {
    if (jumlahReview >= MAX_REVIEW) {
        cout << "Kapasitas review penuh.\n";
        return;
    }
    tampilkanDaftarParfum();
   
    if (jumlahParfum == 0) {
        return;
    }
    
    Review* pReview = &daftarReview[jumlahReview];
    int nomor;
    cout << "Pilih parfum untuk direview (nomor): ";
    nomor = inputAngka();
    
    if (nomor > 0 && nomor <= jumlahParfum) {
        pReview->namaParfum = daftarParfum[nomor - 1].nama;
        pReview->user = username;
       
        string review;
        do {
            cout << "Masukkan review: ";
            clearInputBuffer();
            getline(cin, review);
            
            if (review.empty()) {
                cout << "Review tidak boleh kosong! Silakan coba lagi.\n";
            } else {
                pReview->isiReview = review;
                break;
            }
        } while (true);
        
        jumlahReview++;
        cout << "Review berhasil ditambahkan.\n";
    } else {
        cout << "Pilihan tidak valid.\n";
    }
}

void tampilkanReviewParfum(const string& namaParfum) {
    bool reviewDitemukan = false;
    cout << "Review untuk parfum " << namaParfum << ":\n";
    for (int i = 0; i < jumlahReview; i++) {
        if (daftarReview[i].namaParfum == namaParfum) {
            cout << "User: " << daftarReview[i].user << "\nReview: " << daftarReview[i].isiReview << "\n\n";
            reviewDitemukan = true;
        }
    }
    if (!reviewDitemukan) {
        cout << "Belum ada review untuk parfum ini.\n";
    }
}

void tampilkanReviewUser(const string& username) {
    bool reviewDitemukan = false;
    cout << "Review oleh " << username << ":\n";
    int index = 1;

    for (int i = 0; i < jumlahReview; i++) {
        if (daftarReview[i].user == username) {
            cout << index << ". Parfum: " << daftarReview[i].namaParfum << "\nReview: " << daftarReview[i].isiReview << "\n\n";
            reviewDitemukan = true;
            index++;
        }
    }

    if (!reviewDitemukan) {
        cout << "Anda belum membuat review.\n";
    }
}


void editReview(const string& username) {
    tampilkanReviewUser(username);

    bool reviewDitemukan = false;
    int indexReview = -1;
    string review;

    for (int i = 0; i < jumlahReview; i++) {
        if (daftarReview[i].user == username) {
            reviewDitemukan = true;
            break;
        }
    }

    if (!reviewDitemukan) {
        return;
    }

    cout << "Pilih nomor review yang ingin diedit (0 untuk batal): ";
    indexReview = inputAngka();

    if (indexReview > 0 && indexReview <= jumlahReview) {
        Review* rReview = &daftarReview[indexReview-1];
        if (rReview->user== username) {
            do{
                cout << "Masukkan review baru: ";
                clearInputBuffer();
                getline(cin, review);
                if (review.empty()){
                    cout << "review tidak boleh kosong\n";
                }
                else{
                    rReview ->isiReview = review;
                    cout << "Review berhasil diperbarui.\n";
                    break;
                }
            
            }while(true);
        } else {
            cout << "Anda hanya bisa mengedit review yang Anda buat.\n";
        }
    } else if (indexReview == 0) {
        cout << "Batal mengedit review.\n";
    } else {
        cout << "Pilihan tidak valid.\n";
    }
}

void hapusReviewUser(const string& username) {
    tampilkanReviewUser(username);

    bool reviewDitemukan = false;
    int indexReview = -1;

    for (int i = 0; i < jumlahReview; i++) {
        if (daftarReview[i].user == username) {
            reviewDitemukan = true;
            break;
        }
    }

    if (!reviewDitemukan) {
        cout << "Anda belum membuat review.\n";
        return;
    }

    cout << "Pilih nomor review yang ingin dihapus (0 untuk batal): ";
    indexReview = inputAngka();

    if (indexReview > 0 && indexReview <= jumlahReview) {
        for (int i = indexReview - 1; i < jumlahReview - 1; i++) {
            daftarReview[i] = daftarReview[i + 1];
        }
        jumlahReview--;
        cout << "Review berhasil dihapus.\n";
    } else if (indexReview == 0) {
        cout << "Batal menghapus review.\n";
    } else {
        cout << "Pilihan tidak valid.\n";
    }
}


bool cekUsername(const string& username) {
    for (int i = 0; i < jumlahUser; i++) {
        if (daftarUser[i].username == username) {
            return true;
        }
    }
    return false;
}

void registrasi() {
    if (jumlahUser >= MAX_USERS) {
        cout << "Kapasitas user penuh.\n";
        return;
    }

    string username;
    cout << "==== Registrasi User ====\n";
    do {
        cout << "Masukkan username: ";
        cin >> username;
        if (cekUsername(username)) {
            cout << "Username sudah terpakai. Coba username lain.\n";
        }
    } while (cekUsername(username));

    cout << "Masukkan password: ";
    cin >> daftarUser[jumlahUser].password;
    daftarUser[jumlahUser].username = username;
    daftarUser[jumlahUser].role = 'u';
    jumlahUser++;
    cout << "Registrasi berhasil.\n";
}


User* login() {
    string username, password;
    int coba = 0;

    do {
        cout << "==== Login ====\n";
        cout << "Masukkan username: ";
        cin >> username;
        cout << "Masukkan password: ";
        cin >> password;

        for (int i = 0; i < jumlahUser; i++) {
            if (daftarUser[i].username == username && daftarUser[i].password == password) {
                cout << "Login berhasil!\n";
                return &daftarUser[i];
            }
        }
        cout << "Login gagal. Username atau password salah.\n";
        coba++;
    } while (coba < 3);
    cout << "Anda telah gagal login 3 kali, program akan berhenti!\n";
    return nullptr; 
}

void menuAdmin() {
    int pilihan;
    do {
        cout << "=== Menu Admin ===\n";
        cout << "1. Tambah Parfum\n";
        cout << "2. Edit Parfum\n";
        cout << "3. Hapus Parfum\n";
        cout << "4. Lihat Daftar Parfum\n";
        cout << "5. Lihat Review\n";
        cout << "0. Logout\n";
        cout << "Pilih menu: ";
        pilihan = inputAngka();

        switch (pilihan) {
            case 1:
                tambahParfum();
                break;
            case 2:
                editParfum();
                break;
            case 3:
                hapusParfum();
                break;
            case 4:
                tampilkanDaftarParfum();
                break;
            case 5:
                if (jumlahParfum == 0) {
                    cout << "Belum ada parfum yang terdaftar.\n";
                } else {
                    int nomor;
                    tampilkanDaftarParfum();
                    cout << "Pilih nomor parfum untuk melihat review: ";
                    nomor = inputAngka();
                    
                    if (nomor > 0 && nomor <= jumlahParfum) {
                        tampilkanReviewParfum(daftarParfum[nomor - 1].nama);
                    } else {
                        cout << "Pilihan tidak valid.\n";
                    }
                }
                break;
            case 0:
                cout << "Logout berhasil.\n";
                break;
            default:
                cout << "Pilihan tidak valid.\n";
        }
    } while (pilihan != 0);
}

void menuUser(User* user) {
    int pilihan;
    do {
        cout << "=== Menu User ===\n";
        cout << "1. Lihat Daftar Parfum\n";
        cout << "2. Lihat Review Parfum\n";
        cout << "3. Tambah Review\n";
        cout << "4. Lihat Review Saya\n";
        cout << "5. Edit Review Saya\n";
        cout << "6. Hapus Review Saya\n";
        cout << "0. Logout\n";
        cout << "Pilih menu: ";
        pilihan = inputAngka();

        switch (pilihan) {
            case 1:
                tampilkanDaftarParfum();
                break;
            case 2: {
                if (jumlahParfum == 0) {
                    cout << "Belum ada parfum yang terdaftar.\n";
                } else {
                    int nomor;
                    tampilkanDaftarParfum();
                    cout << "Pilih nomor parfum untuk melihat review: ";
                    nomor = inputAngka();
                    
                    if (nomor > 0 && nomor <= jumlahParfum) {
                        tampilkanReviewParfum(daftarParfum[nomor - 1].nama);
                    } else {
                        cout << "Pilihan tidak valid.\n";
                    }
                }
                break;
            }
            case 3:
                tambahReview(user->username);
                break;
            case 4:
                tampilkanReviewUser(user->username);
                break;
            case 5:
                editReview(user->username);
                break;
            case 6:
                hapusReviewUser(user->username);
                break;
            case 0:
                cout << "Logout berhasil.\n";
                break;
            default:
                cout << "Pilihan tidak valid.\n";
        }
    } while (pilihan != 0);
}


int main() {
    int pilihan;
    User* user;

    daftarUser[jumlahUser++] = {"admin", "admin123", 'a'};
    daftarParfum[jumlahParfum++] = {"Hmns", "Unrosed"};

    do {
        cout << "=== Sistem Review Parfum ===\n";
        cout << "1. Registrasi\n";
        cout << "2. Login\n";
        cout << "3. Keluar\n";
        cout << "Pilih menu: ";
        pilihan = inputAngka();

        switch (pilihan) {
            case 1:
                registrasi();
                break;
            case 2:
                user = login();
                if (user != nullptr) {
                    if (user->role == 'a') {
                        menuAdmin();
                    } else {
                        menuUser(user);
                    }
                }
                break;
            case 3:
                cout << "Keluar dari program.\n";
                break;
            default:
                cout << "Pilihan tidak valid.\n";
        }
    } while (pilihan != 3);

    return 0;
}
