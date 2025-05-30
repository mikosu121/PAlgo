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
