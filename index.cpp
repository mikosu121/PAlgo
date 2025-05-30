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
