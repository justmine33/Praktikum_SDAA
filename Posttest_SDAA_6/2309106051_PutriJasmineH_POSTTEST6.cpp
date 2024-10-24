#include <iostream>
#include <string>
#include <bits/stdc++.h>
using namespace std;

struct Parfum {
    int id_parfum;
    string brand;
    string nama;
    Parfum* next;
};

struct Review {
    int id_parfum;
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


Parfum* HeadParfum = nullptr;
Review* HeadReview = nullptr;
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

void tampilkanDaftarParfum() {
    if(HeadParfum == nullptr) {
        cout << "Belum ada parfum yang terdaftar.\n";
        return;
    }
    
    cout << "Daftar Parfum:\n";
    Parfum* temp = HeadParfum;
    while(temp != nullptr) {
        cout << "ID Parfum: " << temp->id_parfum << "\n";
        cout << "Brand: " << temp->brand << "\n";
        cout << "Nama Parfum: " << temp->nama << "\n\n";
        temp = temp->next;
    }
}

int last_id_parfum = 0; 
void tambahParfum() {
    Parfum* newParfum = new Parfum();
    string namabrand, namaparfum;

    newParfum->id_parfum = ++last_id_parfum;

    do{
        cout << "Masukkan Nama Brand: ";
        getline(cin, namabrand);
        clearInputBuffer();
        if (!inputKosong(namabrand)){
            cout << "Nama Brand Tidak Boleh Kosong!\n";
        }
        else{
            newParfum->brand = namabrand;
            break;
        }
    }while(true);

    do{
        cout << "Masukkan Nama Parfum: ";
        getline(cin, namaparfum);
        clearInputBuffer();
        if (!inputKosong(namaparfum)){
            cout << "Nama Parfum Tidak Boleh Kosong!\n";
        }
        else{
            newParfum->nama = namaparfum;
            break;
        }
    }while(true);

    newParfum->next = nullptr;

    if (HeadParfum == nullptr){
        HeadParfum = newParfum;
    }
    else{
        Parfum* temp = HeadParfum;
        while(temp->next != nullptr){
            temp = temp->next;
        }
        temp->next = newParfum;
    }
    cout << "Parfum Berhasil ditambahkan dengan ID " << newParfum->id_parfum << "." << endl;
}


void editParfum() {
    tampilkanDaftarParfum();

    if (HeadParfum == nullptr){
        cout << "Tidak ada data parfum yang bisa diedit.\n";
        return;
    }

    int id;
    cout << "Masukkan ID Parfum yang ingin diedit: ";
    id = inputAngka();

    Parfum* temp = HeadParfum;
    while(temp != nullptr && temp->id_parfum != id){
        temp = temp->next;
    }

    if(temp != nullptr){
        string namabaru, brandbaru;

        do{
            cout << "Masukkan Nama Baru untuk Brand: ";
            clearInputBuffer();
            getline(cin, brandbaru);
            clearInputBuffer();
            if(!inputKosong(brandbaru)){
                cout << "Nama Brand Tidak Boleh Kosong!\n";
            }
            else{
                temp->brand = brandbaru;
                break;
            }
        }while(true);

        do{
            cout << "Masukkan Nama Baru Parfum: ";
            clearInputBuffer();
            getline(cin , namabaru);
            clearInputBuffer();
            if(!inputKosong(namabaru)){
                cout << "Nama Parfum Tidak Boleh Kosong!\n";
            }
            else{
                temp->nama = namabaru;
                break;
            }
        }while(true);
        cout << "Parfum dengan ID " << temp->id_parfum << " berhasil diedit.\n";
    }
    else{
        cout << "ID Parfum tidak valid!.\n";
    }
}

void hapusParfum() {
    if (HeadParfum == nullptr) {
        cout << "Tidak ada data parfum yang bisa dihapus.\n";
        return;
    }

    tampilkanDaftarParfum();
    int id;

    cout << "Masukkan ID Parfum yang ingin dihapus (0 jika tidak jadi): ";
    id = inputAngka();

    if (id == 0) {
        cout << "Penghapusan dibatalkan.\n";
        return;
    }

    if (HeadParfum->id_parfum == id) {
        Parfum* temp = HeadParfum;
        HeadParfum = HeadParfum->next;
        delete temp;
        cout << "Parfum dengan ID " << id << " berhasil dihapus.\n";
    } else { 
        Parfum* prev = HeadParfum;
        Parfum* curr = HeadParfum->next;
        while (curr != nullptr && curr->id_parfum != id) {
            prev = curr;
            curr = curr->next;
        }
        if (curr != nullptr) {
            prev->next = curr->next;
            delete curr;
            cout << "Parfum dengan ID " << id << " berhasil dihapus.\n";
        } else {
            cout << "ID Parfum tidak valid.\n";
        }
    }
}


void tambahReview(const string& username) {
    tampilkanDaftarParfum();
   
    if (HeadParfum == nullptr) {
        cout << "Belum ada parfum yang terdaftar.\n";
        return;
    }
    
    Review* newReview = new Review();
    int nomor;
    cout << "Pilih parfum untuk direview (nomor): ";
    nomor = inputAngka();
    
    Parfum* tempParfum = HeadParfum;
    for (int i = 1; i < nomor && tempParfum != nullptr; i++) {
        tempParfum = tempParfum->next;
    }
    
    if (tempParfum != nullptr) {
        newReview->id_parfum = tempParfum->id_parfum;
        newReview->namaParfum = tempParfum->nama;
        newReview->user = username;
       
        string review;
        do {
            cout << "Masukkan review: ";
            getline(cin, review);
            if (inputKosong(review)) {
                cout << "Review tidak boleh kosong! Silakan coba lagi.\n";
            } else {
                newReview->isiReview = review;
                break;
            }
        } while (true);
        
        newReview->next = nullptr;
        if (HeadReview == nullptr) {
            HeadReview = newReview;
        } else {
            Review* tempReview = HeadReview;
            while (tempReview->next != nullptr) {
                tempReview = tempReview->next;
            }
            tempReview->next = newReview;
        }
        cout << "Review berhasil ditambahkan.\n";
    } else {
        cout << "Pilihan tidak valid.\n";
        delete newReview; 
    }
}

void tampilkanReviewParfum(int idParfum) {
    bool reviewDitemukan = false;
    cout << "Review untuk parfum ID " << idParfum << ":\n";
    Review* temp = HeadReview;
    while(temp != nullptr){
        if(temp->id_parfum == idParfum) {
            cout << "User: " << temp->user << "\nReview: " << temp->isiReview << "\n";
            reviewDitemukan = true;
        }
        temp = temp->next;
    }
    if(!reviewDitemukan){
        cout << "Belum Ada Review untuk Parfum ini.\n";
    }
}

void tampilkanReviewUser(const string& username) {
    bool reviewDitemukan = false;
    cout << "Review oleh " << username << ":\n";
    int index = 1;

    Review* temp = HeadReview;
    while(temp != nullptr){
        if(temp->user == username){
            cout << index << ". Parfum ID: " << temp->id_parfum << "\n";
            cout << "Nama Parfum: " << temp->namaParfum << "\nReview: " << temp->isiReview << "\n";
            reviewDitemukan = true;
            index++;
        }
        temp = temp->next;
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

    Review* temp = HeadReview;
    while (temp != nullptr) {
        if (temp->user == username) {
            reviewDitemukan = true;
            break;
        }
        temp = temp->next;
    }

    if (!reviewDitemukan) {
        cout << "Anda belum membuat review.\n";
        return;
    }

    cout << "Pilih nomor review yang ingin diedit (0 untuk batal): ";
    indexReview = inputAngka();

    if (indexReview == 0) {
        cout << "Batal mengedit review.\n";
        return;
    }

    temp = HeadReview;
    for (int i = 1; i < indexReview && temp != nullptr; i++) {
        temp = temp->next;
    }

    if (temp != nullptr && temp->user == username) {
        do {
            cout << "Masukkan review baru: ";
            clearInputBuffer();
            getline(cin, review);
            if (inputKosong(review)) {
                cout << "Review tidak boleh kosong\n";
            } else {
                temp->isiReview = review;
                cout << "Review berhasil diperbarui.\n";
                break;
            }
        } while (true);
    } else {
        cout << "Pilihan tidak valid.\n";
    }
}


void hapusReviewUser(const string& username) {
    tampilkanReviewUser(username);

    bool reviewDitemukan = false;
    int indexReview = -1;

    Review* temp = HeadReview;
    Review* prev = nullptr;
    while (temp != nullptr) {
        if (temp->user == username) {
            reviewDitemukan = true;
            break;
        }
        prev = temp;
        temp = temp->next;
    }

    if (!reviewDitemukan) {
        cout << "Anda belum membuat review.\n";
        return;
    }

    cout << "Pilih nomor review yang ingin dihapus (0 untuk batal): ";
    indexReview = inputAngka();

    if (indexReview == 1 && HeadReview->user == username) {
        Review* temp = HeadReview;
        HeadReview = HeadReview->next;
        delete temp;
        cout << "Review berhasil dihapus.\n";
    } else if (indexReview > 1) {
        prev = HeadReview;
        temp = HeadReview->next;
        for (int i = 2; i < indexReview && temp != nullptr; i++) {
            prev = temp;
            temp = temp->next;
        }
        if (temp != nullptr && temp->user == username) {
            prev->next = temp->next;
            delete temp;
            cout << "Review berhasil dihapus.\n";
        } else {
            cout << "Pilihan tidak valid.\n";
        }
    } else if (indexReview == 0) {
        cout << "Batal menghapus review.\n";
    } else {
        cout << "Pilihan tidak valid.\n";
    }
}


int length(Parfum* Head) {
    int panjang = 0;
    Parfum* temp = Head;
    while (temp != NULL) {
        temp = temp->next;
        panjang++;
    }
    return panjang;
}

void linkedListArray(Parfum* Head, Parfum* arr[]) {
    int panjang = length(Head);
    for (int i = 0; i < panjang; i++) {
        arr[i] = Head;
        Head = Head->next;
    }
}

void arrayLinkedList(Parfum* Head, Parfum* arr[]) {
    int panjang = length(Head);
    for (int i = 0; i < panjang; i++) {
        Head->brand = arr[i]->brand;
        Head->nama = arr[i]->nama;
        Head = Head->next;
    }
}

void shellSort(Parfum* arr[], int n) {
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            Parfum* temp = arr[i];
            int j;
            for (j = i; j >= gap && arr[j - gap]->nama < temp->nama; j -= gap) {
                arr[j] = arr[j - gap];
            }
            arr[j] = temp;
        }
    }
}

void daftarParfumDesc() {
    int n = length(HeadParfum);
    if (n == 0) {
        cout << "Belum ada parfum yang terdaftar.\n";
        return;
    }

    Parfum** arr = new Parfum*[n];
    linkedListArray(HeadParfum, arr);
    shellSort(arr, n);
    arrayLinkedList(HeadParfum, arr);
    tampilkanDaftarParfum();

    delete[] arr; 
}

void FrontBackSplit(Parfum *source, Parfum **frontRef, Parfum **backRef){
    Parfum *fast;
    Parfum *slow;
    slow = source;
    fast = source->next;

    while (fast != NULL){
        fast = fast->next;
        if (fast != NULL){
            slow = slow->next;
            fast = fast->next;
        }
    }
    *frontRef = source;
    *backRef = slow->next;
    slow->next = NULL;
}

Parfum* SortedMerge(Parfum* a, Parfum* b) {
    Parfum* result = nullptr;

    if (a == nullptr)
        return b;
    else if (b == nullptr)
        return a;

    if (a->nama <= b->nama) {
        result = a;
        result->next = SortedMerge(a->next, b);
    } else {
        result = b;
        result->next = SortedMerge(a, b->next);
    }
    return result;
}

void MergeSort(Parfum **headRef){
    Parfum *head = *headRef;
    Parfum *a;
    Parfum *b;

    if ((head == NULL) || (head->next == NULL)){
        return;
    }

    FrontBackSplit(head, &a, &b);

    MergeSort(&a);
    MergeSort(&b);
    *headRef = SortedMerge(a, b);
}

void daftarParfumAsc(){
    MergeSort(&HeadParfum);
    tampilkanDaftarParfum();
}

Parfum* getNodeAtIndex(Parfum* head, int index) {
    Parfum* current = head;
    for (int i = 0; i < index && current != nullptr; i++) {
        current = current->next;
    }
    return current;
}

// FIBONACCI SEARCH
int min(int x, int y) { return (x <= y) ? x : y; }
int fibMonaccianSearchParfumById(Parfum* head, int id, int n) {
    int fibMMm2 = 0;
    int fibMMm1 = 1;
    int fibM = fibMMm2 + fibMMm1;

    while (fibM < n) {
        fibMMm2 = fibMMm1;
        fibMMm1 = fibM;
        fibM = fibMMm2 + fibMMm1;
    }

    int offset = -1;

    while (fibM > 1) {
        int i = min(offset + fibMMm2, n - 1);
        Parfum* current = getNodeAtIndex(head, i);
        
        if (current == nullptr) {
            return -1;
        }

        if (current->id_parfum < id) {
            fibM = fibMMm1;
            fibMMm1 = fibMMm2;
            fibMMm2 = fibM - fibMMm1;
            offset = i;
        }
        else if (current->id_parfum > id) {
            fibM = fibMMm2;
            fibMMm1 = fibMMm1 - fibMMm2;
            fibMMm2 = fibM - fibMMm1;
        }
        else {
            cout << "Parfum dengan ID '" << id << "' ditemukan pada indeks: " << i + 1 << "\n";
            return i;
        }
    }

    Parfum* lastElement = getNodeAtIndex(head, offset + 1);
    if (fibMMm1 && lastElement != nullptr && lastElement->id_parfum == id) {
        cout << "Parfum dengan ID '" << id << "' ditemukan pada indeks: " << offset + 2 << "\n";
        return offset + 1;
    }

    cout << "Parfum dengan ID '" << id << "' tidak ditemukan.\n";
    return -1;
}

// JUMP SEARCH
int jumpSearchParfumById(Parfum* head, int id, int n) {
    if (head == nullptr || n == 0) {
        cout << "Data parfum kosong.\n";
        return -1;
    }

    int step = sqrt(n);
    Parfum* current = head;
    Parfum* prev = head;
    int currentIndex = 0;

    while (current != nullptr && current->id_parfum < id) {
        prev = current;
        for (int i = 0; i < step && current != nullptr; i++) {
            current = current->next;
            currentIndex++;
        }

        if (current == nullptr) break;
    }

    current = prev;
    currentIndex = max(0, currentIndex - step);

    while (current != nullptr && currentIndex < n) {
        if (current->id_parfum == id) {
            cout << "Parfum dengan ID '" << id << "' ditemukan pada indeks: " << currentIndex + 1 << "\n";
            return currentIndex;
        }
        current = current->next;
        currentIndex++;
    }

    cout << "Parfum dengan ID '" << id << "' tidak ditemukan.\n";
    return -1;
}

// BOYER MOORE SEARCH
#define NO_OF_CHARS 256

void badCharHeuristic(string str, int size, int badChar[NO_OF_CHARS]) {
    for (int i = 0; i < NO_OF_CHARS; i++) {
        badChar[i] = -1;
    }

    for (int i = 0; i < size; i++) {
        badChar[(int)str[i]] = i;
    }
}

void boyerMooreSearchParfumByNama(Parfum* head, string keyword) {
    if (head == nullptr) {
        cout << "Data parfum kosong.\n";
        return;
    }

    int m = keyword.length();
    int badChar[NO_OF_CHARS];
    bool found = false;
    
    badCharHeuristic(keyword, m, badChar);
    
    Parfum* temp = head;
    int indeks = 0;
    
    while (temp != nullptr) {
        if (temp->nama.find(keyword) != string::npos) {
            cout << "Parfum dengan nama '" << keyword << "' ditemukan pada indeks: " << indeks + 1 << "\n";
            found = true;
            break;
        }
        temp = temp->next;
        indeks++;
    }
    
    if (!found) {
        cout << "Parfum dengan nama '" << keyword << "' tidak ditemukan.\n";
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
    int pilihan, pilih, pilihcari, cari;
    string caristring;
    do {
        cout << "=== Menu Admin ===\n";
        cout << "1. Tambah Parfum\n";
        cout << "2. Edit Parfum\n";
        cout << "3. Hapus Parfum\n";
        cout << "4. Cari Parfum\n";
        cout << "5. Lihat Daftar Parfum\n";
        cout << "6. Lihat Daftar Parfum Terurut\n";
        cout << "7. Lihat Review\n";
        cout << "0. Logout\n";
        cout << "Pilih menu: ";
        pilihan = inputAngka();
        clearInputBuffer();

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
                cout << "Pilih metode pencarian:\n";
                cout << "1. Fibonacci Search\n";
                cout << "2. Jump Search\n";
                cout << "3. Boyer-Moore Search\n";
                cout << "Pilih: ";
                pilihcari = inputAngka();

                switch (pilihcari) {
                    case 1:
                        cout << "Masukkan id parfum yang ingin dicari: ";
                        cari = inputAngka();
                        fibMonaccianSearchParfumById(HeadParfum, cari, length(HeadParfum));
                        break;
                    case 2:
                        cout << "Masukkan id parfum yang ingin dicari: ";
                        cari = inputAngka(); 
                        jumpSearchParfumById(HeadParfum, cari, length(HeadParfum));
                        break;
                    case 3:
                        cout << "Masukkan nama parfum yang ingin dicari: ";
                        getline(cin, caristring);
                        if(!inputKosong(caristring)){
                            cout << "Input Tidak Boleh Kosong!\n";
                        }
                        else{
                            boyerMooreSearchParfumByNama(HeadParfum, caristring);
                            break;
                        }
                        break;
                    default:
                        cout << "Pilihan tidak valid.\n";
                        break;
                }
                break;
            case 5:
                tampilkanDaftarParfum();
                break;
            case 6:
                cout << "1. Terurut Ascending\n";
                cout << "2. Terurut Descending\n";
                cout << "Pilih: ";
                pilih = inputAngka();
                if (pilih == 1){
                    cout << "=== Daftar Parfum Terurut Secara Ascending ===\n";
                    daftarParfumAsc();
                }
                else if (pilih == 2){
                    cout << "=== Daftar Parfum Terurut Secara Descending ===\n";
                    daftarParfumDesc();
                }
                else{
                    cout << "Pilihan tidak valid.\n";
                }
                break;
            case 7:
                if (HeadParfum == nullptr) {
                    cout << "Belum ada parfum yang terdaftar.\n";
                } else {
                    int nomor;
                    tampilkanDaftarParfum();
                    cout << "Pilih nomor parfum untuk melihat review: ";
                    nomor = inputAngka();
                    
                    Parfum* temp = HeadParfum;
                    for (int i = 1; i < nomor && temp != nullptr; i++) {
                        temp = temp->next;
                    }
                    
                    if (temp != nullptr) {
                        tampilkanReviewParfum(temp->id_parfum);
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
        clearInputBuffer();

        switch (pilihan) {
            case 1:
                tampilkanDaftarParfum();
                break;
            case 2: {
                if (HeadParfum == nullptr) {
                    cout << "Belum ada parfum yang terdaftar.\n";
                } else {
                    tampilkanDaftarParfum(); 
                    int idParfum;
                    cout << "Masukkan ID parfum untuk melihat review: ";
                    idParfum = inputAngka(); 
                    tampilkanReviewParfum(idParfum);
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

    User* admin = new User();
    admin->username = "admin";
    admin->password = "admin123";
    admin->role = 'a';
    admin->next = HeadUser;
    HeadUser = admin;

    // Parfum* firstParfum = new Parfum();
    // firstParfum->brand = "Hmns";
    // firstParfum->nama = "Unrosed";
    // firstParfum->next = nullptr;
    // HeadParfum = firstParfum;

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