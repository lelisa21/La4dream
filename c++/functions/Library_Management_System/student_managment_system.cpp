#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <algorithm>

using namespace std;

const int MAX_STUDENTS = 100; // Maximum number of students

struct Student {
    int id;
    string name;
    float gpa;
};

Student students[MAX_STUDENTS]; // Array to hold student records
int studentCount = 0; // Current number of students

// Function prototypes
void addStudent();
void deleteStudent(int id);
void updateStudent(int id);
void displayStudents();
int searchStudentByName(const string& name);
void loadStudentsFromFile();
void saveStudentsToFile();
void sortStudentsByName();
void sortStudentsByGPA();

int main() {
    loadStudentsFromFile(); // Load existing students from file

    int choice;
    do {
        cout << "\n--- Student Management System ---\n";
        cout << "1. Add Student\n";
        cout << "2. Delete Student\n";
        cout << "3. Update Student\n";
        cout << "4. Display Students\n";
        cout << "5. Search Student by Name\n";
        cout << "6. Sort Students by Name\n";
        cout << "7. Sort Students by GPA\n";
        cout << "8. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addStudent();
                break;
            case 2: {
                int id;
                cout << "Enter Student ID to delete: ";
                cin >> id;
                deleteStudent(id);
                break;
            }
            case 3: {
                int id;
                cout << "Enter Student ID to update: ";
                cin >> id;
                updateStudent(id);
                break;
            }
            case 4:
                displayStudents();
                break;
            case 5: {
                string name;
                cout << "Enter Student Name to search: ";
                cin.ignore(); // Clear the newline character from the input buffer
                getline(cin, name);
                int index = searchStudentByName(name);
                if (index != -1) {
                    cout << "Student found: ID: " << students[index].id 
                         << ", Name: " << students[index].name 
                         << ", GPA: " << students[index].gpa << endl;
                } else {
                    cout << "Student not found." << endl;
                }
                break;
            }
            case 6:
                sortStudentsByName();
                break;
            case 7:
                sortStudentsByGPA();
                break;
            case 8:
                saveStudentsToFile(); // Save students before exiting
                cout << "Exiting the program." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 8);

    return 0;
}

// Function to load students from a file
void loadStudentsFromFile() {
    ifstream infile("students.txt");
    if (infile.is_open()) {
        while (infile >> students[studentCount].id >> ws &&
               getline(infile, students[studentCount].name) &&
               infile >> students[studentCount].gpa) {
            studentCount++;
        }
        infile.close();
    }
}

// Function to save students to a file
void saveStudentsToFile() {
    ofstream outfile("students.txt");
    for (int i = 0; i < studentCount; i++) {
        outfile << students[i].id << endl
                << students[i].name << endl
                << students[i].gpa << endl;
    }
    outfile.close();
}

// Function to add a new student
void addStudent() {
    if (studentCount >= MAX_STUDENTS) {
        cout << "Cannot add more students. Maximum limit reached." << endl;
        return;
    }

    Student newStudent;

    // Input validation for ID
    cout << "Enter Student ID: ";
    while (!(cin >> newStudent.id)) {
        cout << "Invalid input. Please enter a valid integer for ID: ";
        cin.clear(); // Clear the error flag
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
    }

    cin.ignore(); // Clear the newline character from the input buffer
    cout << "Enter Student Name: ";
    getline(cin, newStudent.name);

    // Input validation for GPA
    cout << "Enter Student GPA: ";
    while (!(cin >> newStudent.gpa) || newStudent.gpa < 0.0 || newStudent.gpa > 4.0) {
        cout << "Invalid input. Please enter a valid GPA (0.0 - 4.0): ";
        cin.clear(); // Clear the error flag
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
    }

    students[studentCount] = newStudent; // Add the new student to the array
    studentCount++; // Increment the student count
    cout << "Student added successfully!" << endl;
}

// Function to delete a student by ID
void deleteStudent(int id) {
    for (int i = 0; i < studentCount; i++) {
        if (students[i].id == id) {
            // Shift all subsequent students one position up
            for (int j = i; j < studentCount - 1; j++) {
                students[j] = students[j + 1];
            }
            studentCount--; // Decrement the student count
            cout << "Student deleted successfully!" << endl;
            return;
        }
    }
    cout << "Student with ID " << id << " not found." << endl;
}

// Function to update a student's information
void updateStudent(int id) {
    for (int i = 0; i < studentCount; i++) {
        if (students[i].id == id) {
            cout << "Updating details for Student ID: " << id << endl;

            cin.ignore(); // Clear the newline character from the input buffer
            cout << "Enter new name: ";
            getline(cin, students[i].name);

            // Input validation for GPA
            cout << "Enter new GPA: ";
            while (!(cin >> students[i].gpa) || students[i].gpa < 0.0 || students[i].gpa > 4.0) {
                cout << "Invalid input. Please enter a valid GPA (0.0 - 4.0): ";
                cin.clear(); // Clear the error flag
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
            }

            cout << "Student updated successfully!" << endl;
            return;
        }
    }
    cout << "Student with ID " << id << " not found." << endl;
}

// Function to display all students
void displayStudents() {
    if (studentCount == 0) {
        cout << "No students to display." << endl;
        return;
    }

    cout << "\n--- Student List ---\n";
    cout << left << setw(10) << "ID" 
         << setw(30) << "Name" 
         << setw(10) << "GPA" << endl;

    for (int i = 0; i < studentCount; i++) {
        cout << left << setw(10) << students[i].id 
             << setw(30) << students[i].name 
             << setw(10) << fixed << setprecision(2) 
             << students[i].gpa 
             << endl;
    }
}

// Function to search for a student by name (partial match)
int searchStudentByName(const string& name) {
    for (int i = 0; i < studentCount; i++) {
        if (students[i].name.find(name) != string::npos) { // Partial match search
            return i; // Return the index of the found student
        }
    }
    return -1; // Return -1 if not found
}

// Function to sort students by name
void sortStudentsByName() {
    sort(students, students + studentCount, [](const Student &a, const Student &b) {
        return a.name < b.name; // Sort in ascending order by name
    });
    cout << "Students sorted by name." << endl;
}
// Function to sort students by GPA
void sortStudentsByGPA() {
    sort(students, students + studentCount, [](const Student &a, const Student &b) {
        return a.gpa < b.gpa; // Sort in ascending order by GPA
    });
    cout << "Students sorted by GPA." << endl;
}
