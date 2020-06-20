#include <cstring>
#include <fstream>
#include <iostream>

#define FILENAME "abc.txt"

using namespace std;

class student {
private:
    char usn[10];
    char name[10];
    char sem[10];
    char dept[10];

public:
    char rrn[10];
    char buffer[50];

    void read() {
        cout << "Enter usn, name, sem, dept: ";
        cin >> usn >> name >> sem >> dept;
    }

    void pack(int &count) {
        char str[10];

        sprintf(str, "%d", count);
        strcpy(buffer, str);
        strcat(buffer, "|");
        strcat(buffer, usn);
        strcat(buffer, "|");
        strcat(buffer, name);
        strcat(buffer, "|");
        strcat(buffer, sem);
        strcat(buffer, "|");
        strcat(buffer, dept);
        strcat(buffer, "\n");
        count++;
    }

    void unpack(ifstream &file) {
        file.getline(rrn, 10, '|');
        file.getline(usn, 10, '|');
        file.getline(name, 10, '|');
        file.getline(sem, 10, '|');
        file.getline(dept, 10, '\n');
    }

    void print() {
        cout << rrn << "\t" << usn << "\t" << name << "\t" << sem << "\t"
             << dept << endl;
    }
};

void write(int &count) {
    student s;
    ofstream file;

    file.open(FILENAME, ios::app | ios::out);
    s.read();
    s.pack(count);
    file << s.buffer;
    file.close();
}

void display() {
    student s;
    ifstream file;

    file.open(FILENAME, ios::in);
    cout << "RRN\tUSN\tName\tSem\tDept" << endl;
    while (!file.eof()) {
        s.unpack(file);
        s.print();
    }
    file.close();
}

void search(int &count) {
    student s;
    ifstream file;
    char rrn[10];
    int n = 1;

    file.open(FILENAME, ios::in);
    cout << "Enter rrn to search: ";
    cin >> rrn;
    while (n <= count) {
        s.unpack(file);
        if (strcmp(rrn, s.rrn) == 0) {
            cout << "Record found." << endl;
            s.print();
            file.close();
            return;
        }
        n++;
    }
    cout << "Incorrect rrn." << endl;
    file.close();
}

int main() {
    int ch, count = 0;

    while (true) {
        cout << "1. Insert\n2. Search\n3. Display" << endl;
        cout << "Enter your choice: ";
        cin >> ch;
        switch (ch) {
        case 1:
            write(count);
            break;
        case 2:
            search(count);
            break;
        case 3:
            display();
            break;
        default:
            cout << "Invalid choice." << endl;
            return 0;
        }
    }
}
