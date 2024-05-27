#include <iostream>
#include <string>
using namespace std;

struct Node {
    Node* next;
    int nomor;
    string nama;
    int waktu; // Waktu layanan
};

class Queue {
private:
    Node* head;
    Node* tail;
    int antrian;
    int kapasitas;
    int isi;

public:
    Queue(int kapasitas) {
        head = NULL;
        tail = NULL;
        antrian = 1;
        this->kapasitas = kapasitas;
        isi = 0;
    }

    void push(string nama, int waktu) {
        if (isi < kapasitas) {
            Node* nodeBaru = new Node;
            nodeBaru->nama = nama;
            nodeBaru->nomor = antrian++;
            nodeBaru->waktu = waktu;
            nodeBaru->next = NULL;
            
            if (tail) {
                tail->next = nodeBaru;
            } else {
                head = nodeBaru;
            }
            
            tail = nodeBaru;
            isi++;
        } else {
            cout << "Kapasitas Antrian Penuh\n";
        }
    }

    void pop() {
        if (isi == 0) {
            cout << "Antrian Kosong\n";
        } else {
            Node* temp = head;
            head = head->next;
            if (!head) {
                tail = NULL;
            }
            delete temp;
            isi--;
        }
    }

    void display() {
        if (isi == 0) {
            cout << "Antrian Kosong\n";
        } else {
            Node* temp = head;
            while (temp) {
                cout << "Nomor: " << temp->nomor << ", Nama: " << temp->nama << ", Waktu Layanan: " << temp->waktu << " menit\n";
                temp = temp->next;
            }
        }
    }

    void daftarAntrian() {
        string nama;
        int waktu;
        cout << "Masukkan nama untuk mendaftar ke dalam antrian: ";
        cin >> nama;
        cout << "Masukkan waktu layanan yang diperkirakan (dalam menit): ";
        cin >> waktu;
        push(nama, waktu);
    }

    void monitorStatus() {
        if (isi == 0) {
            cout << "Antrian Kosong\n";
        } else {
            cout << "Jumlah orang dalam antrian: " << isi << "\n";
            cout << "Perkiraan total waktu tunggu: " << getTotalWaktuTunggu() << " menit\n";
        }
    }

    int getTotalWaktuTunggu() {
        int totalWaktu = 0;
        Node* temp = head;
        while (temp) {
            totalWaktu += temp->waktu;
            temp = temp->next;
        }
        return totalWaktu;
    }

    void callNext() {
        if (isi == 0) {
            cout << "Antrian Kosong\n";
        } else {
            cout << "Memanggil Nomor: " << head->nomor << ", Nama: " << head->nama << "\n";
            pop();
        }
    }

    void continueQueue() {
        while (isi > 0) {
            callNext();
        }
        cout << "Semua pelanggan dalam antrian telah dipanggil.\n";
    }
};

int main(int argc, char const *argv[]) {
    int choice;
    int kapasitas;
    
    cout << "Masukkan kapasitas antrian: ";
    cin >> kapasitas;

    Queue q(kapasitas);
    
    while (1) {
        cout << "\nOperasi pada Queue" << endl;
        cout << "1. Cetak Antrian" << endl;
        cout << "2. Hapus dari Antrian" << endl;
        cout << "3. Masukkan ke Antrian" << endl;
        cout << "4. Monitor Status Antrian" << endl;
        cout << "5. Panggil Pelanggan Berikutnya" << endl;
        cout << "6. Lanjutkan Pemanggilan Antrian" << endl;
        cout << "7. Keluar" << endl;
        cout << "Ketik angka yang akan anda pilih: ";
        cin >> choice;

        switch (choice) {
            case 1:
                q.display();
                break;
            case 2:
                q.pop();
                break;
            case 3:
                q.daftarAntrian();
                break;
            case 4:
                q.monitorStatus();
                break;
            case 5:
                q.callNext();
                break;
            case 6:
                q.continueQueue();
                break;
            case 7:
                cout << "Keluar dari program.\n";
                exit(0);
            default:
                cout << "Pilihan tidak valid. Silakan coba lagi.\n";
        }
    }

    return 0;
}
