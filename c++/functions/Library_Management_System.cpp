#include <iostream>
#include <string>
#include <iomanip> // For std::setw
using namespace std;

const int MAX_BOOKS = 100; 

// Function prototypes
void addBook(string titles[], string authors[], string isbns[], bool availability[], int& count);
void displayBooks(const string titles[], const string authors[], const string isbns[], const bool availability[], int count);
int searchBook(const string isbns[], int count, const string& isbn);
void deleteBook(string titles[], string authors[], string isbns[], bool availability[], int& count, const string& isbn);
void checkOutBook(bool availability[], int count, const string& isbn);
void returnBook(bool availability[], int count, const string& isbn);

int main() {
    string titles[MAX_BOOKS];
    string authors[MAX_BOOKS];
    string isbns[MAX_BOOKS];
    bool availability[MAX_BOOKS]; // true if available, false if checked out
    int count = 0; // Current number of books
    int choice;

    do {
        cout << "\n--- Library Management System ---\n";
        cout << "1. Add Book\n";
        cout << "2. Display Books\n";
        cout << "3. Search Book by ISBN\n";
        cout << "4. Delete Book\n";
        cout << "5. Check Out Book\n";
        cout << "6. Return Book\n";
        cout << "7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addBook(titles, authors, isbns, availability, count);
                break;
            case 2:
                displayBooks(titles, authors, isbns, availability, count);
                break;
            case 3: {
                string isbn;
                cout << "Enter ISBN to search: ";
                cin.ignore();
                getline(cin, isbn);
                int index = searchBook(isbns, count, isbn);
                if (index != -1) {
                    cout << "Book found: " << titles[index] << " by " << authors[index] 
                         << " (ISBN: " << isbns[index] << ") - "
                         << (availability[index] ? "Available" : "Checked Out") << endl;
                } else {
                    cout << "Book not found." << endl;
                }
                break;
            }
            case 4: {
                string isbn;
                cout << "Enter ISBN to delete: ";
                cin.ignore();
                getline(cin, isbn);
                deleteBook(titles, authors, isbns, availability, count, isbn);
                break;
            }
            case 5: {
                string isbn;
                cout << "Enter ISBN to check out: ";
                cin.ignore();
                getline(cin, isbn);
                checkOutBook(availability, count, isbn);
                break;
            }
            case 6: {
                string isbn;
                cout << "Enter ISBN to return: ";
                cin.ignore();
                getline(cin, isbn);
                returnBook(availability, count, isbn);
                break;
            }
            case 7:
                cout << "Exiting the program." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 7);

    return 0;
}

// Function to add a book
void addBook(string titles[], string authors[], string isbns[], bool availability[], int& count) {
    if (count < MAX_BOOKS) {
        cout << "Enter title: ";
        cin.ignore();
        getline(cin, titles[count]);
        cout << "Enter author: ";
        getline(cin, authors[count]);
        cout << "Enter ISBN: ";
        getline(cin, isbns[count]);
        availability[count] = true; // New book is available by default
        count++;
        cout << "Book added successfully!" << endl;
    } else {
        cout << "Library is full!" << endl;
    }
}

// Function to display all books
void displayBooks(const string titles[], const string authors[], const string isbns[], const bool availability[], int count) {
    if (count == 0) {
        cout << "No books to display." << endl;
        return;
    }
    cout << "\nBooks List:\n";
    cout << left << setw(30) << "Title" 
         << setw(20) << "Author" 
         << setw(15) << "ISBN" 
         << setw(10) << "Status" << endl;

    for (int i = 0; i < count; i++) {
        cout << left << setw(30) << titles[i] 
             << setw(20) << authors[i] 
             << setw(15) << isbns[i] 
             << setw(10) << (availability[i] ? "Available" : "Checked Out") 
             << endl;
    }
}

// Function to search for a book by ISBN
int searchBook(const string isbns[], int count, const string& isbn) {
    for (int i = 0; i < count; i++) {
        if (isbns[i] == isbn) {
            return i; // Return the index of the found book
        }
    }
    return -1; // Return -1 if not found
}

// Function to delete a book by ISBN
void deleteBook(string titles[], string authors[], string isbns[], bool availability[], int& count, const string& isbn) {
    int index = searchBook(isbns, count, isbn);
    if (index != -1) {
        // Shift books to fill the gap
        for (int i = index; i < count - 1; i++) {
            titles[i] = titles[i + 1];
            authors[i] = authors[i + 1];
            isbns[i] = isbns[i + 1];
            availability[i] = availability[i + 1];
        }
        count--; // Decrease the book count
        cout << "Book deleted successfully!" << endl;
    } else {
        cout << "Book not found." << endl;
    }
}

// Function to check out a book by ISBN
void checkOutBook(bool availability[], int count, const string& isbn) {
    int index = searchBook(isbns, count, isbn);
    if (index != -1 && availability[index]) {
        availability[index] = false; // Mark as checked out
        cout << "You have checked out the book." << endl;
    } else if (index != -1) {
        cout << "This book is already checked out." << endl;
    } else {
        cout << "Book not found." << endl;
    }
}

// Function to return a book by ISBN
void returnBook(bool availability[], int count, const string& isbn) {
    int index = searchBook(isbns, count, isbn);
    if (index != -1 && !availability[index]) {
        availability[index] = true; // Mark as available
        cout << "You have returned the book." << endl;
    } else if (index != -1) {
        cout << "This book was not checked out." << endl;
    } else {
        cout << "Book not found." << endl;
    }
}
