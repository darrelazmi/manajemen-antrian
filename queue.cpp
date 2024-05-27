#include <iostream>
#include <string>
#include <vector>
#include <utility>
using namespace std;

struct Node {
    Node* next;
    int nomor;
    string nama;
    int waktu; // Waktu layanan
};

class Queue {
private:
    vector<pair<Node, string>> riwayat;
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

    void front()
    {
        if(head==NULL) return;
        cout << "Pelanggan Sekarang:";
        cout << "\n\nNomor Antrian\t: " << head->nomor;
        cout << "\nNama\t\t: " << head->nama;
        cout << "\nWaktu Layanan\t: " << head->waktu;
        cout << "\n===========================================\n";
    }

    void push() {
        if (isi < kapasitas) 
        {
            string nama; int waktu;
            cout << "Masukkan nama untuk mendaftar ke dalam antrian: ";
            cin >> nama;
            cout << "Masukkan waktu layanan yang diperkirakan (dalam menit): ";
            cin >> waktu;
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

    void callNext(bool cek) {
        string kondisi;
        if(cek)
            kondisi = "Selesai";
        else
            kondisi = "Batal";
        if (isi == 0) {
            cout << "Antrian Kosong\n";
        } else {
            cout << "Memanggil Nomor: " << head->nomor << ", Nama: " << head->nama << "\n";
            Node simpan;
            simpan.nomor = head->nomor;
            simpan.nama = head->nama;
            simpan.waktu = head->waktu;
            riwayat.push_back(make_pair(simpan, kondisi));
            pop();
        }
    }

    void history()
    {
        cout << "Riwayat Antrian:\n";
        for (int i = 0; i < riwayat.size(); i++) {
            cout << "Nomor: " << riwayat[i].first.nomor << ", Nama: " << riwayat[i].first.nama << ", Waktu Layanan: " << riwayat[i].first.waktu << " menit" << ", Status: " << riwayat[i].second << endl;
        }
    }

    void search()
    {
        int angka;
        cout << "Masukkan Nomor Antrian: ";
        cin >> angka;
        for (int i = 0; i < riwayat.size(); i++)
        {
            if(angka == riwayat[i].first.nomor)
            {
                cout << "\nNomor: " << riwayat[i].first.nomor << ", Nama: " << riwayat[i].first.nama << ", Waktu Layanan: " << riwayat[i].first.waktu << " menit, Status: "<< riwayat[i].second << endl;
                return;
            }
        }
        Node * telusur = head;
        while(telusur!=NULL)
        {
            if(telusur->nomor == angka)
            {
                cout << "\nNomor: " << telusur->nomor << ", Nama: " << telusur->nama << ", Waktu Layanan: " << telusur->waktu << " menit, Status: Mengantri\n";
                return;
            }
        }
        cout << "\nPelanggan Tidak Ditemukan!\n";
        
    }
};

int main(int argc, char const *argv[]) {
    int choice;
    int kapasitas;
    
    cout << "Masukkan kapasitas antrian: ";
    cin >> kapasitas;

    Queue q(kapasitas);
    
    while (1) {
        cout << "----------QUEUE MANAGEMENT SYSTEM----------\n";
        cout << "Daftar Operasi:" << endl;
        cout << "===========================================\n";
        cout << "1. Seluruh Antrian" << endl;
        cout << "2. Pelanggan berikutnya" << endl;
        cout << "3. Daftar Antrian" << endl;
        cout << "4. Status Antrian" << endl;
        cout << "5. Lewati Pelanggan" << endl;
        cout << "6. Riwayat Pelanggan" << endl;
        cout << "7. Cari Pelanggan" << endl;
        cout << "8. Keluar" << endl;
        cout << "===========================================\n";
        q.front();
        cout << "Pilih operasi untuk antrian: ";
        cin >> choice;
        cout << "===========================================\n";
        switch (choice) {
            case 1:
                q.display();
                break;
            case 2:
                q.callNext(1);
                break;
            case 3:
                q.push();
                break;
            case 4:
                q.monitorStatus();
                break;
            case 5:
                q.callNext(0);
                break;
            case 6:
                q.history();
                break;
            case 7:
                q.search();
                break;
            case 8:
                cout << "Keluar dari program....\n";
                exit(0);
            default:
                cout << "Pilihan tidak valid. Silakan coba lagi.\n";
        }
        
    }

    return 0;
}
