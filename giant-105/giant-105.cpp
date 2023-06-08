#include <iostream>
#include <string>
using namespace std;

class Node {
public:
    int rollNumber;
    string name;
    Node* next;
};

class CircularLinkedList {
private:
    Node* LAST;

public:
    CircularLinkedList() {
        LAST = NULL;
    }

    void addNode();                                                 //pemanggilan fungsi addNode dimana berguna untuk menambahkan data
    bool search(int rollno, Node** prakoso, Node** giant);          //pemanggilan fungsi search dimana berguna untuk mencari data
    bool listEmpty();
    bool delNode();
    void traverse();
};

void CircularLinkedList::addNode() {
    int rollNumber;
    string name;

    cout << "masukan roll number dari siswa : ";
    cin >> rollNumber;
    cout << "Masukkan nama siswa : ";
    cin.ignore();
    getline(cin, name);

    Node* newNode = new Node();
    newNode->rollNumber = rollNumber;
    newNode->name = name;

    if (LAST == NULL) {         // jika list kosong
        LAST = newNode;
        newNode->next = newNode;
    }

    else if (rollNumber <= LAST->rollNumber) {
        if (rollNumber == LAST->rollNumber) {
            cout << "Roll Number sudah ada" << endl;
            delete newNode;
            return;
        }
        newNode->next = LAST->next;
        LAST->next = newNode;
    }

    else {
        Node* giant = LAST->next;
        Node* prakoso = NULL;

        while (giant->rollNumber < rollNumber && giant != LAST) {
            prakoso = giant;
            giant = giant->next;
        }

        if (giant->rollNumber == rollNumber) {
            cout << "Roll number sudah ada" << endl;
            delete newNode;
            return;
        }

        newNode->next = giant;
        prakoso->next = newNode;

        if (giant == LAST) {
            LAST = newNode;
        }
    }
}

bool CircularLinkedList::search(int rollno, Node** prakoso, Node** giant) {
    if (LAST == NULL) {
        return false;
    }

    *prakoso = LAST->next;
    *giant = LAST->next;

    while (*giant != LAST) {
        if (rollno == (*giant)->rollNumber) {
            return true;
        }
        *prakoso = *giant;
        *giant = (*giant)->next;
    }

    if (rollno == LAST->rollNumber) {
        return true;
    }
    else {
        return false;
    }
}

bool CircularLinkedList::listEmpty() {
    return LAST == NULL;
}

bool CircularLinkedList::delNode() {
    if (listEmpty()) {
        cout << "List kosong" << endl;
        return false;
    }

    int rollNumber;
    cout << "masukkan roll number yang akan di hapus : ";
    cin >> rollNumber;

    Node* prakoso = NULL;
    Node* giant = NULL;

    if (search(rollNumber, &prakoso, &giant)) {
        if (giant == LAST) { // list terakhir
            prakoso->next = giant->next;
            LAST = prakoso;
        }
        else if (giant == LAST->next) { // list pertama (awal)
            LAST->next = giant->next;
        }
        else {
            prakoso->next = giant->next;
        }

        delete giant;
        return true;
    }
    else {
        cout << "Roll number tidak ditemukan" << endl;
        return false;
    }
}

void CircularLinkedList::traverse() {
    if (listEmpty()) {
        cout << "\nList is empty\n";
    }
    else {
        cout << "\nRecords in the list are:\n";
        Node* giantNode = LAST->next;
        while (giantNode != LAST) {
            cout << giantNode->rollNumber << " " << giantNode->name << endl;
            giantNode = giantNode->next;
        }
        cout << LAST->rollNumber << " " << LAST->name << endl;
    }
}

int main()
{
    CircularLinkedList object;

    while (true) {
        try {
            cout << "\nMenu" << endl;
            cout << "1. Masukkan data ke list" << endl;
            cout << "2. hapus data yang ada di list" << endl;
            cout << "3. tampilkan semua data" << endl;
            cout << "4. Exit" << endl;
            cout << "\nMasukkan pilihan(1-4): ";
            char ch;
            cin >> ch;

            switch (ch) {

            case '1': {
                object.addNode();
                break;
            }
            case '2': {
                object.delNode();
                break;
            }
            case '3': {
                object.traverse();
                break;
            }

            case '4': {
                return 0;
            }

            default: {
                cout << "Invalid option" << endl;
                break;
            }

            }
        }

        catch (exception& e) {
            cout << e.what() << endl;
        }
    }
    return 0;
}







































