#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

const string filename = "abc.txt";

class student
{
private:
    char usn[10];
    char name[10];
    char sem[10];
    char dept[10];

public:
    static int count;
    char rrn[10];
    char buffer[50];

    void read()
    {
        cout << "Enter usn, name, sem, dept: ";
        cin >> usn >> name >> sem >> dept;
    }

    void pack()
    {
        char buffer[50];
        char str[10];

        sprintf(str, "%d", count);
        strcpy(buffer, str);
        strcat(buffer, "|");
        strcpy(buffer, usn);
        strcat(buffer, "|");
        strcpy(buffer, name);
        strcat(buffer, "|");
        strcpy(buffer, sem);
        strcat(buffer, "|");
        strcpy(buffer, dept);
        strcat(buffer, "\n");
        count++;
    }

    void unpack(ifstream &file)
    {
        file.getline(rrn, 10, '|');
        file.getline(usn, 10, '|');
        file.getline(name, 10, '|');
        file.getline(sem, 10, '|');
        file.getline(dept, 10, '\n');
    }

    void print()
    {
        cout << rrn << "\t" << usn << "\t" << name << "\t" << sem << "\t" << dept << endl;
    }
};

void write()
{
    student s;
    ofstream file;

    file.open(filename, ios::app | ios::out);
    s.read();
    s.pack();
    file << s.buffer;
    file.close();
}

void display()
{
    student s;
    ifstream file;

    file.open(filename, ios::in);
    cout << "RRN\tUSN\tName\tSem\tDept" << endl;
    while (!file.eof())
    {
        s.unpack(file);
        s.print();
    }
    file.close();
}

void search()
{
    student s;
    ifstream file;
    char rrn[10];
    int n = 1;

    file.open(filename, ios::in);
    cout << "Enter rrn to search: ";
    cin >> rrn;
    while (n <= student::count)
    {
        s.unpack(file);
        if (strcmp(rrn, s.rrn) == 0)
        {
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

int main()
{
    int ch;

    while (true)
    {
        cout << "1. Insert\n2. Search\n3. Display" << endl;
        cout << "Enter your choice: ";
        cin >> ch;
        switch (ch)
        {
        case 1:
            write();
            break;
        case 2:
            search();
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
