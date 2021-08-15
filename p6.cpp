#include <cstring>
#include <fstream>
#include <iostream>

#define MAX_RECORD 20

using namespace std;

typedef struct {
  char name[20];
  char usn[20];
  char branch[5];
} student_t;

student_t students[MAX_RECORD];
int indices[MAX_RECORD];
int record_count = 0;

int get_index(char *key) {
  int low = 0;
  int high = record_count - 1;
  while (low <= high) {
    int mid = (low + high) / 2;
    if (strcmp(students[mid].usn, key) < 0) {
      low = mid + 1;
    } else if (strcmp(students[mid].usn, key) > 0) {
      high = mid - 1;
    } else {
      return mid;
    }
  }
  return -1;
}

void sort_insert(student_t *s) {
  int low = 0;
  int high = record_count - 1;
  while (low <= high) {
    int mid = (low + high) / 2;
    if (strcmp(students[mid].usn, s->usn) < 0) {
      low = mid + 1;
    } else if (strcmp(students[mid].usn, s->usn) > 0) {
      high = mid - 1;
    }
  }
  for (int i = record_count - 1; i >= low; i--) {
    students[i + 1] = students[i];
  }
  students[low] = *s;
  record_count++;
}

void search_student(char *name) {
  int found = 0;
  for (int i = 0; i < record_count; i++) {
    if (strcmp(students[i].name, name) == 0) {
      indices[found++] = i;
    }
  }
  if (found == 0) {
    cout << "No records found." << endl;
    return;
  }

  cout << "Matching records:" << endl;
  cout << "USN\tName\tBranch" << endl;
  for (int i = 0; i < found; i++) {
    cout << students[indices[i]].usn << "\t" << students[indices[i]].name
         << "\t" << students[indices[i]].branch << endl;
  }
}

void write_to_file() {
  fstream file;
  file.open("students.txt", ios::out);
  for (int i = 0; i < record_count; i++) {
    file << students[i].usn << "|" << students[i].name << "|"
         << students[i].branch << endl;
  }
  file.close();
}

void delete_student(char *name) {
  int found = 0;
  for (int i = 0; i < record_count; i++) {
    if (strcmp(students[i].name, name) == 0) {
      indices[found++] = i;
    }
  }
  if (found == 0) {
    cout << "No records found." << endl;
    return;
  }

  for (int i = 0; i < found; i++) {
    cout << "Record deleted." << endl;
    cout << "USN: " << students[indices[i]].usn << endl;
    for (int j = indices[i]; i < record_count - 1; j++) {
      students[j] = students[j + 1];
    }
    record_count--;
  }

  write_to_file();
}

void new_student() {
  if (record_count == MAX_RECORD) {
    cout << "Memory full." << endl;
    return;
  }

  student_t s;
  cout << "Enter name: ";
  cin >> s.name;
  cout << "Enter usn: ";
  cin >> s.usn;
  int pos = get_index(s.usn);
  if (pos != -1) {
    cout << "Student with USN already exists." << endl;
    return;
  }
  cout << "Enter branch: ";
  cin >> s.branch;

  sort_insert(&s);
  write_to_file();
  cout << "Record inserted." << endl;
}

int main(int argc, const char **argv) {
  int ch;
  char name[20];

  while (true) {
    cout << "1. Add\n2. Search\n3. Delete\n4. Exit" << endl;
    cout << "Enter your choice: ";
    cin >> ch;

    switch (ch) {
    case 1:
      new_student();
      break;
    case 2:
      cout << "Enter name: ";
      cin >> name;
      search_student(name);
      break;
    case 3:
      cout << "Enter name: ";
      cin >> name;
      delete_student(name);
      break;
    case 4:
      return 0;
    default:
      cout << "Invalid choice." << endl;
      break;
    }
  }
}
