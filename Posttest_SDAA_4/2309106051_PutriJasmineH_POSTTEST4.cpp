#include <iostream>
#include <string>
using namespace std;

struct Parfum {
    string brand;
    string nama;
    Parfum* next;
};

struct Review {
    string user;
    string isiReview;
    string namaParfum;
    Review* next;
};

struct User {
    string username;
    string password;
    char role;
    User* next;
};

// Queue PArfum
Parfum* front = nullptr;
Parfum* rear = nullptr;

// Stack Review
Review* topReview;

// LInked List User
User* HeadUser = nullptr;



void clearInputBuffer() {
    cin.clear();
    cin.ignore();
}

int inputAngka() {
    int angka;
    while (true) {
        if(cin >> angka) {
            clearInputBuffer();
            return angka;
        } 
        else {
            cout << "Input tidak valid. Harap masukkan angka: ";
            clearInputBuffer();
        }
    }
}

bool inputKosong(const string& input) {
    return !input.empty() && input.find_first_not_of(" \t\n\r\f\v") != string::npos;
}



// QUEUE PARFUM
Parfum* createParfum() {
    Parfum* newNode = new Parfum();
    string brand, nama;

    do {
        cout << "Masukan Nama Brand: ";
        getline(cin, brand);
        if (!inputKosong(brand)) {
            cout << "Nama Brand tidak boleh kosong atau hanya berisi spasi! Silahkan coba lagi\n";
        } else {
            newNode->brand = brand;
        }
    } while (!inputKosong(brand));

    do {
        cout << "Masukan Nama Parfum: ";
        getline(cin, nama);
        if (!inputKosong(nama)) {
            cout << "Nama Parfum tidak boleh kosong atau hanya berisi spasi! Silahkan coba lagi\n";
        } else {
            newNode->nama = nama;
        }
    } while (!inputKosong(nama));

    newNode->next = NULL;
    return newNode;
}


void enqueue(Parfum** front, Parfum** rear){
    Parfum* parfumBaru = createParfum();
    if(!*front){
        *front = parfumBaru;
    }
    else{
        (*rear)->next = parfumBaru;
    }
    *rear = parfumBaru;
    cout << "Parfum berhasil ditambahkan." << endl;
}

void dequeue(Parfum** front){
    if(!*front){
        cout << "Antrian Kosong!\n";
        return;
    }
    Parfum* temp = *front;
    *front = (*front)->next;
    if(!front){
        rear = nullptr;
    }
    delete temp;
    cout << "Penghapusan front queue berhasil." << endl;
}

void tampilkanDaftarParfum(){
    if(!front){
        cout << "Antrian Kosong!\n";
        return;
    }

    int i = 1;
    Parfum* temp = front;
    while (temp) {
        cout << i << ". Brand: " << temp->brand << "\n";
        cout << "Nama Parfum: " << temp->nama << "\n";
        temp = temp->next;
        i++;
    }
}

Parfum* frontQueue() {
    if (front == nullptr) {
        cout << "Queue parfum kosong.\n";
        return nullptr;
    }
    return front;
}

Parfum* rearQueue() {
    if (rear == nullptr) {
        cout << "Queue parfum kosong.\n";
        return nullptr;
    }
    return rear; 
}

void tampilkanFrontRear() {
    Parfum* parfumDepan = frontQueue();
    Parfum* parfumBelakang = rearQueue();

    if (parfumDepan) {
        cout << "Parfum di depan: " << parfumDepan->brand << " - " << parfumDepan->nama << endl;
    }
    if (parfumBelakang) {
        cout << "Parfum di belakang: " << parfumBelakang->brand << " - " << parfumBelakang->nama << endl;
    }
}



// STACK REVIEW
Review* createReview(const string& username) {
    tampilkanDaftarParfum();
    Review* newReview = new Review();
    int nomor;
    cout << "Masukkan Nomor Parfum yang ingin direview: ";
    nomor = inputAngka();

    Parfum* temp = front;
    int i = 1;
    while (temp && i < nomor) {
        temp = temp->next;
        i++;
    }
    
    if (!temp) {
        cout << "Parfum tidak ditemukan!\n";
        delete newReview;
        return nullptr;
    }

    newReview->namaParfum = temp->nama;
    newReview->user = username;

    string review;
    do {
        cout << "Masukkan review: ";
        getline(cin, review);
        if (!inputKosong(review)) {
            cout << "Review tidak boleh kosong! Silahkan coba lagi\n";
        } else {
            newReview->isiReview = review;
            break;
        }
    } while (true);

    newReview->next = topReview;
    return newReview;
}

void peekReview() {
    if (topReview) {
        cout << "Review Teratas:\n";
        cout << "User: " << topReview->user << ", Nama Parfum: " << topReview->namaParfum << ", Review: " << topReview->isiReview << endl;
    } else {
        cout << "Stack review kosong.\n";
    }
}

void pushReview(const string& user, const string& isiReview, const string& namaParfum) {
    Review* newReview = new Review{user, isiReview, namaParfum, topReview};
    topReview = newReview;
    cout << "Review berhasil ditambahkan.\n";
}

void popReview() {
    if (topReview) {
        Review* temp = topReview;
        topReview = topReview->next;
        delete temp;
        cout << "Review berhasil dihapus.\n";
    } else {
        cout << "Stack review kosong.\n";
    }
}

void tampilkanReview() {
    if (!topReview) {
        cout << "Belum ada review yang terdaftar.\n";
        return;
    }
    cout << "Daftar Review:\n";
    Review* temp = topReview;
    while (temp) {
        cout << "User: " << temp->user << ", Nama Parfum: " << temp->namaParfum << ", Review: " << temp->isiReview << endl;
        temp = temp->next;
    }
}

bool cekUsername(const string& username) {
    User* temp = HeadUser;
    while (temp != nullptr) { 
        if (temp->username == username) {
            return true;
        }
        temp = temp->next;
    }
    return false;
}

void registrasi() {
    User* newUser = new User();
    string username, password;
    cout << "==== Registrasi User ====\n";
    
    do {
        cout << "Masukkan Username: ";
        getline(cin, username);
        if (!inputKosong(username)) {
            cout << "Username tidak boleh kosong atau hanya berisi spasi!\n";
        } else if (cekUsername(username)) {
            cout << "Username sudah terpakai. Coba Username lain.\n";
        }
    } while (!inputKosong(username) || cekUsername(username));
    
    do {
        cout << "Masukkan Password: ";
        getline(cin, password);
        if (!inputKosong(password)) {
            cout << "Password tidak boleh kosong atau hanya berisi spasi!\n";
        }
    } while (!inputKosong(password));
    
    newUser->username = username;
    newUser->password = password;
    newUser->role = 'u';
    newUser->next = nullptr;
    
    if (HeadUser == nullptr) {
        HeadUser = newUser;
    } else {
        User* temp = HeadUser;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = newUser;
    }
    
    cout << "Registrasi berhasil!\n";
}

User* login() {
    string username, password;
    int coba = 0;

    do {
        cout << "==== Login ====\n";
        cout << "Masukkan username: ";
        getline(cin, username);
        cout << "Masukkan password: ";
        getline(cin, password);

        User* temp = HeadUser;
        while (temp != nullptr) {
            if (temp->username == username && temp->password == password) {
                cout << "Login berhasil!\n";
                return temp;
            }
            temp = temp->next;
        }
        cout << "Login gagal. Username atau password salah.\n";
        coba++;
    } while (coba < 3);
    cout << "Anda telah gagal login 3 kali, program akan berhenti!\n";
    exit(0);
}

void menuAdmin() {
    int pilihan;
    do {
        cout << "1. Enqueue \n";
        cout << "2. Dequeue \n";
        cout << "3. Lihat Data Parfum \n";
        cout << "4. Tampilkan Front dan Rear Queue Parfum \n";
        cout << "5. Tampilkan Review Teratas\n";
        cout << "6. Tampilkan Review user\n";
        cout << "7. Hapus Review Teratas\n";
        cout << "0. Logout\n";
        cout << "Pilih Menu: ";
        pilihan = inputAngka();
        clearInputBuffer();

        switch (pilihan) {
            case 1:
                enqueue(&front, &rear);
                tampilkanDaftarParfum();
                break;
            case 2:
                dequeue(&front);
                tampilkanDaftarParfum();
                break;
            case 3:
                tampilkanDaftarParfum();
                break;
            case 4:
                tampilkanFrontRear();
                break;
            case 5:
                peekReview();
                break;
            case 6:
                tampilkanReview();
                break;
            case 7:
                popReview();
                tampilkanReview();
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
        cout << "2. Tambah Review\n";
        cout << "3. Tampilkan Review Teratas\n";
        cout << "4. Tampilkan Review\n";
        cout << "0. Logout\n";
        cout << "Pilih menu: ";
        pilihan = inputAngka();

        switch (pilihan) {
            case 1:
                tampilkanDaftarParfum();
                break;
            case 2: {
                Review* reviewBaru = createReview(user->username);
                if (reviewBaru) {
                    pushReview(user->username, reviewBaru->isiReview, reviewBaru->namaParfum);
                }
                break;
            }
            case 3:
                peekReview();
                break;
            case 4:
                tampilkanReview();
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

    User* admin = new User();
    admin->username = "admin";
    admin->password = "admin123";
    admin->role = 'a';
    admin->next = HeadUser;
    HeadUser = admin;

    Parfum* firstParfum = new Parfum();
    firstParfum->brand = "Hmns";
    firstParfum->nama = "Unrosed";
    firstParfum->next = nullptr;
    front = firstParfum;
    rear = firstParfum;


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