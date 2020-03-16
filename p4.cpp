#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

const string filename = "abc.txt";

class student
{
private:
    char usn[10], name[10], sem[10], dept[10];

public:
    char rrn[10], buffer[50];

    void read()
    {
        cout << "Enter usn, name, sem, dept: ";
        cin >> usn >> name >> sem >> dept;
    }

    void pack(int *count)
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
        (*count)++;
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

void write(int *count)
{
    student s;
    ofstream file;

    file.open(filename, ios::app | ios::out);
    s.read();
    s.pack(count);
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

void search(int *count)
{
    student s;
    ifstream file;
    char rrn[10];
    int n = 1;

    file.open(filename, ios::in);
    cout << "Enter rrn to search: ";
    cin >> rrn;
    while (n <= *count)
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
    int ch, count = 0;

    while (true)
    {
        cout << "1. Insert\n2. Search\n3. Display" << endl;
        cout << "Enter your choice: ";
        cin >> ch;
        switch (ch)
        {
        case 1:
            write(&count);
            break;
        case 2:
            search(&count);
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
