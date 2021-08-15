#include <fstream>
#include <iostream>

using namespace std;

void write_records() {
    fstream file;
    int n;
    string name;
}

void writerec() {
    fstream out1, out2;
    int i, m, n;
    char name[20];

    out1.open("file1.txt", ios::out);
    out2.open("file2.txt", ios::out);

    cout << "Enter the number of names you want to enter in file1\n";
    cin >> m;
    cout << "\nEnter the names in assending order \n";
    for (i = 0; i < m; i++) {
        cin >> name;
        out1 << name << "\n";
    }

    cout << "Enter the number of names you want to enter in file2\n";
    cin >> n;
    cout << "\nEnter the names in assending order \n";
    for (i = 0; i < n; i++) {
        cin >> name;
        out2 << name << "\n";
    }
    out1.close();
    out2.close();
}

int main() {
    char list1[100][20], list2[100][20];
    int i, j, m, n;
    fstream out1, out2, out3;

    writerec();

    out1.open("file1.txt", ios::in);
    out2.open("file2.txt", ios::in);
    out3.open("file3.txt", ios::out);
    m = 0;
    n = 0;
    while (!out1.eof()) {
        out1.getline(list1[m], 20, '\n');
        m++;
    }
    while (!out2.eof()) {
        out2.getline(list2[n], 20, '\n');
        n++;
    }
    m -= 2;
    n -= 2;
    i = 0;
    j = 0;

    while (i <= m && j <= n) {
        if (strcmp(list1[i], list2[j]) == 0) {
            cout << "\nElements common to both files are \n";
            out3 << list1[i] << "\n";
            cout << list1[i] << endl;
            i++;
            j++;
        }

        else if (strcmp(list1[i], list2[j]) < 0) {
            i++;
        } else {
            j++;
        }
    }

    out3.seekg(0, ios::end);
    int len = out3.tellg();
    if (len == 0) {
        cout << "no names are common\n";
    }

    return 0;
}
