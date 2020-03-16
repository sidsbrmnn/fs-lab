#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

const string filename = "student.txt";

class student
{
public:
    char name[15];
    char usn[15];
    char age[5];
    char sem[5];
    char branch[15];
    char buffer[45];

    void read()
    {
        cout << "Enter student name: ";
        cin >> name;
        cout << "Enter student usn: ";
        cin >> usn;
        cout << "Enter student age: ";
        cin >> age;
        cout << "Enter student sem: ";
        cin >> sem;
        cout << "Enter student branch: ";
        cin >> branch;
    }

    void pack()
    {
        strcpy(buffer, name);
        strcat(buffer, "|");
        strcat(buffer, usn);
        strcat(buffer, "|");
        strcat(buffer, age);
        strcat(buffer, "|");
        strcat(buffer, sem);
        strcat(buffer, "|");
        strcat(buffer, branch);
        strcat(buffer, "\n");
    }

    void print()
    {
        cout << name << "\t" << usn << "\t" << age << "\t" << sem << "\t" << branch << endl;
    }

    void unpack(fstream &file)
    {
        file.getline(name, 15, '|');
        file.getline(usn, 15, '|');
        file.getline(age, 5, '|');
        file.getline(sem, 5, '|');
        file.getline(branch, 15, '\n');
    }
};

void nofile()
{
    cout << "Could not open the file." << endl;
    exit(1);
}

void write()
{
    fstream file;
    student s;

    file.open(filename, ios::app | ios::out);
    if (!file)
        nofile();
    s.read();
    s.pack();
    file << s.buffer;
    file.close();
}

void search()
{
    fstream file;
    student s;
    char usn[15];

    file.open(filename, ios::in);
    if (!file)
        nofile();
    cout << "Enter usn to search: ";
    cin >> usn;
    while (!file.eof())
    {
        s.unpack(file);
        if (strcmp(s.usn, usn) == 0)
        {
            cout << "Record found." << endl;
            s.print();
            file.close();
            return;
        }
    }

    cout << "Record not found." << endl;
    file.close();
}

void display()
{
    fstream file;
    student s;

    file.open(filename, ios::in);
    if (!file)
        nofile();
    cout << "NAME\t\tUSN\t\tAGE\t\tSEM\t\tBRANCH" << endl;
    cout << "----\t\t---\t\t---\t\t---\t\t------" << endl;
    while (!file.eof())
    {
        s.unpack(file);
        s.print();
    }

    file.close();
}

void modify()
{
    fstream file;
    student s[100];
    char usn[15];
    int i, count = 0;

    file.open(filename, ios::in);
    if (!file)
        nofile();
    cout << "Enter usn: ";
    cin >> usn;
    while (!file.eof())
    {
        s[count].unpack(file);
        count++;
    }
    file.close();
    count--;

    for (i = 0; i < count; i++)
    {
        if (strcmp(usn, s[i].usn) == 0)
        {
            s[i].print();
            cout << "Enter new values: " << endl;
            s[i].read();
            break;
        }
    }

    if (i == count)
    {
        cout << "Record not found." << endl;
        return;
    }

    file.open(filename, ios::out);
    if (!file)
        nofile();
    for (i = 0; i < count; i++)
    {
        s[i].pack();
        file << s[i].buffer;
    }
    file.close();
}

int main()
{
    int ch;

    while (true)
    {
        cout << "1. Insert\n2. Search\n3. Display\n4. Modify" << endl;
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
        case 4:
            modify();
            break;
        default:
            cout << "Invalid choice." << endl;
            return 0;
        }
    }
}
