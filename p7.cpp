#include <algorithm>
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

void writerec() {
    fstream file;
    int n;
    string name;

    cout << "Enter the number of names: ";
    cin >> n;
    cin.ignore();
    cout << "Enter the names:" << endl;
    file.open("file1.txt", ios::out);
    for (int i = 0; i < n; i++) {
        getline(cin, name);
        file << name << endl;
    }
    file.close();

    cout << "Enter the number of names: ";
    cin >> n;
    cin.ignore();
    cout << "Enter the names:" << endl;
    file.open("file2.txt", ios::out);
    for (int i = 0; i < n; i++) {
        getline(cin, name);
        file << name << endl;
    }
    file.close();
}

int main(int argc, char const *argv[]) {
    fstream file;
    string *n1, *n2;
    int m = 0, n = 0;

    writerec();

    file.open("file1.txt", ios::in);
    while (!file.eof()) {
        string temp;
        getline(file, temp, '\n');
        if (temp.empty()) {
            continue;
        }
        m++;
    }
    n1 = new string[m];
    file.seekg(0);
    for (int i = 0; i < m; i++) {
        getline(file, n1[i], '\n');
    }
    file.close();

    file.open("file2.txt", ios::in);
    while (!file.eof()) {
        string temp;
        getline(file, temp, '\n');
        if (temp.empty()) {
            continue;
        }
        n++;
    }
    n2 = new string[n];
    file.seekg(0);
    for (int i = 0; i < n; i++) {
        getline(file, n2[i], '\n');
    }
    file.close();

    file.open("output.txt", ios::out);
    int i = 0, j = 0;
    bool found = false;
    cout << m << n << endl;
    sort(n1, n1 + m);
    sort(n2, n2 + n);
    while (i < m && j < n) {
        if (n1[i].compare(n2[j]) < 0) {
            i++;
        } else if (n1[i].compare(n2[j]) > 0) {
            j++;
        } else {
            found = true;
            cout << n1[i].c_str() << endl;
            file << n1[i].c_str() << "\n";
            i++;
            j++;
        }
    }
    file.close();
    if (!found) {
        cout << "No common names :\\" << endl;
    }

    delete[] n1;
    delete[] n2;

    return 0;
}
