#include <iostream>
#include <vector>
using namespace std;

struct Node
{
    Node* next;
    int nomor;
    string nama;
    int waktu;
};


class Queue
{
    private:

    Node* head;
    Node* tail;
    int antrian;
    int kapasitas;
    int isi;

    public:

    Queue(int kapasitas)
    {
        head = NULL;
        tail = NULL;
        antrian = 1;
        this->kapasitas = kapasitas;
        isi = 0;
    }

    void push(string nama)
    {
        if(isi<kapasitas)
        {
            Node* nodeBaru = new Node;
            nodeBaru->nama = nama;
            nodeBaru->nomor = antrian++;
            tail=nodeBaru;
            nodeBaru->next = NULL;
            isi++;
        }
        else cout << "Kapasitas Antrian Penuh\n";
    }

    void pop()
    {
        if(isi==0)
        {
            cout << "Antrian Kosong\n";
        }
        else
        {
            Node* temp = head;
            head = head->next;
            delete temp;
            isi--;
        }   
    }

    void display()
    {
        
    }
}

int main(int argc, char const *argv[])
{
    
    return 0;
}
