#include <cstring>
#include <fstream>
#include <iostream>

using namespace std;

void stdio() {
    char name[20];
    int n, i, j, len;

    cout << "Enter no of names: ";
    cin >> n;
    for (i = 0; i < n; i++) {
        cout << "Enter name: ";
        cin >> name;
        len = strlen(name);
        cout << "Reverse name is ";
        for (j = len - 1; j >= 0; j--) {
            cout << name[j];
        }
        cout << endl;
    }
}

void fileio() {
    fstream fin, fout;
    char name[20], infname[20], outfname[20];
    int len, i;

    cout << "Enter file name to read: ";
    cin >> infname;
    cout << "Enter file name to write: ";
    cin >> outfname;
    fin.open(infname, ios::in);
    fout.open(outfname, ios::out);
    while (true) {
        fin.getline(name, 20);
        if (fin.fail()) {
            break;
        }
        len = strlen(name);
        for (i = len - 1; i >= 0; i--) {
            fout << name[i];
        }
        fout << endl;
    }
    fin.close();
    fout.close();
}

int main(int argc, char const *argv[]) {
    int ch;

    cout << "1. Standard input\n2. File input" << endl;
    cout << "Enter your choice: ";
    cin >> ch;
    switch (ch) {
    case 1:
        stdio();
        break;
    case 2:
        fileio();
        break;
    default:
        cout << "Invalid choice." << endl;
        return 0;
    }
}
