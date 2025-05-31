#include <iostream>
#include <string>
#include <cstdio>
using namespace std;

struct Mahasiswa {
    string nim;
    string nama;
    string jurusan;
    float ipk;
};

struct Node {
    Mahasiswa data;
    Node* next;
};

Node* head = nullptr;

// Fungsi untuk menambah mahasiswa ke linked list
void tambahMahasiswa(const Mahasiswa& mhs) {
    Node* baru = new Node{mhs, nullptr};
    if (!head) {
        head = baru;
    } else {
        Node* temp = head;
        while (temp->next) {
            temp = temp->next;
        }
        temp->next = baru;
    }
}

// Fungsi untuk menampilkan semua data mahasiswa
void tampilkanData() {
    if (!head) {
        cout << "Belum ada data mahasiswa.\n";
        return;
    }

    Node* temp = head;
    while (temp) {
        cout << "NIM: " << temp->data.nim
             << ", Nama: " << temp->data.nama
             << ", Jurusan: " << temp->data.jurusan
             << ", IPK: " << temp->data.ipk << endl;
        temp = temp->next;
    }
}

// Fungsi untuk mencari mahasiswa berdasarkan NIM
Mahasiswa* cariMahasiswa(const string& nim) {
    Node* temp = head;
    while (temp) {
        if (temp->data.nim == nim) {
            return &temp->data;
        }
        temp = temp->next;
    }
    return nullptr;
}

// Fungsi untuk mengurutkan mahasiswa berdasarkan IPK (descending)
void urutkanIPK() {
    if (!head) return;

    bool swapped;
    do {
        swapped = false;
        Node* temp = head;
        while (temp->next) {
            if (temp->data.ipk < temp->next->data.ipk) {
                swap(temp->data, temp->next->data);
                swapped = true;
            }
            temp = temp->next;
        }
    } while (swapped);

    cout << "Data telah diurutkan berdasarkan IPK (descending).\n";
}

// Fungsi untuk menghapus mahasiswa berdasarkan NIM
void hapusMahasiswa(const string& nim) {
    Node* temp = head;
    Node* prev = nullptr;

    while (temp) {
        if (temp->data.nim == nim) {
            if (!prev) {
                head = temp->next;
            } else {
                prev->next = temp->next;
            }
            delete temp;
            cout << "Data berhasil dihapus.\n";
            return;
        }
        prev = temp;
        temp = temp->next;
    }
    cout << "Data tidak ditemukan.\n";
}

// Fungsi untuk menyimpan data mahasiswa ke file
void simpanKeFile(const char* filename) {
    FILE* file = fopen(filename, "w");
    if (!file) {
        cout << "Gagal membuka file.\n";
        return;
    }

    Node* temp = head;
    while (temp) {
        fprintf(file, "%s;%s;%s;%.2f\n",
                temp->data.nim.c_str(),
                temp->data.nama.c_str(),
                temp->data.jurusan.c_str(),
                temp->data.ipk);
        temp = temp->next;
    }

    fclose(file);
    cout << "Data berhasil disimpan ke \"" << filename << "\".\n";
}

// Fungsi untuk menampilkan menu
void menu() {
    int pilihan;
    string nim;
    Mahasiswa mhs;

    do {
        cout << "\n--- MENU MAHASISWA ---\n";
        cout << "1. Tampilkan Data\n";
        cout << "2. Tambah Mahasiswa\n";
        cout << "3. Cari Mahasiswa\n";
        cout << "4. Urutkan IPK\n";
        cout << "5. Hapus Mahasiswa\n";
        cout << "6. Simpan ke File\n";
        cout << "7. Keluar\n";
        cout << "Pilih menu: "; cin >> pilihan; cin.ignore();

        switch (pilihan) {
            case 1:
                tampilkanData();
                break;
            case 2:
                cout << "NIM: "; getline(cin, mhs.nim);
                cout << "Nama: "; getline(cin, mhs.nama);
                cout << "Jurusan: "; getline(cin, mhs.jurusan);
                cout << "IPK: "; cin >> mhs.ipk; cin.ignore();
                tambahMahasiswa(mhs);
                break;
            case 3:
                cout << "Masukkan NIM: "; getline(cin, nim);
                {
                    Mahasiswa* hasil = cariMahasiswa(nim);
                    if (hasil)
                        cout << "Ditemukan: " << hasil->nama << ", IPK: " << hasil->ipk << endl;
                    else
                        cout << "Data tidak ditemukan.\n";
                }
                break;
            case 4:
                urutkanIPK();
                break;
            case 5:
                cout << "Masukkan NIM: "; getline(cin, nim);
                hapusMahasiswa(nim);
                break;
            case 6:
                simpanKeFile("data_mahasiswa.txt");
                break;
            case 7:
                cout << "Terima kasih!\n";
                break;
            default:
                cout << "Pilihan tidak valid.\n";
        }
    } while (pilihan != 7);
}

int main() {
    menu();
    return 0;
}
