#include <iostream>
#include <string>
#include <iomanip>
#include <vector>

using namespace std;


// this include:

// • User authentication (login/logout).

// • Different roles (Admin and Member).

// • Admin can add/delete books and manage users.

// • Members can check out and return books.

// • A simple menu-driven interface.

const int MAX_BOOKS = 100; // Maximum number of books
const int MAX_USERS = 50; // Maximum number of users

enum Role { ADMIN, MEMBER }; // User roles

struct User {
    string username;
    string password;
    Role role;
};

struct Book {
    string title;
    string author;
    string isbn;
    bool availability; // true if available, false if checked out
};

vector<User> users; // List of users
vector<Book> books; // List of books
User* currentUser = nullptr; // Pointer to the currently logged-in user

// Function prototypes
void addBook();
void displayBooks();
int searchBook(const string& isbn);
void deleteBook(const string& isbn);
void checkOutBook(const string& isbn);
void returnBook(const string& isbn);
void registerUser();
bool loginUser();
void adminMenu();
void memberMenu();
void mainMenu();

int main() {
    // Predefined admin user
    users.push_back({"admin", "admin123", ADMIN});
    
    mainMenu();
    return 0;
}

// Function to display the main menu
void mainMenu() {
    int choice;
    do {
        cout << "\n--- Library Management System ---\n";
        cout << "1. Login\n";
        cout << "2. Register\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                if (loginUser()) {
                    if (currentUser->role == ADMIN) {
                        adminMenu();
                    } else {
                        memberMenu();
                    }
                }
                break;
            case 2:
                registerUser();
                break;
            case 3:
                cout << "Exiting the program." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 3);
}

// Function to register a new user
void registerUser() {
    User newUser;
    cout << "Enter username: ";
    cin >> newUser.username;
    cout << "Enter password: ";
    cin >> newUser.password;
    newUser.role = MEMBER; // Default role is MEMBER
    users.push_back(newUser);
    cout << "User registered successfully!" << endl;
}

// Function to log in a user
bool loginUser() {
    string username, password;
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;

    for (auto& user : users) {
        if (user.username == username && user.password == password) {
            currentUser = &user; // Set the current user
            cout << "Login successful! Welcome, " << username << "!" << endl;
            return true;
        }
    }
    
    cout << "Invalid username or password." << endl;
    return false;
}

// Function for admin menu
void adminMenu() {
    int choice;
    do {
        cout << "\n--- Admin Menu ---\n";
        cout << "1. Add Book\n";
        cout << "2. Display Books\n";
        cout << "3. Delete Book\n";
        cout << "4. Logout\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addBook();
                break;
            case 2:
                displayBooks();
                break;
            case 3: {
                string isbn;
                cout << "Enter ISBN to delete: ";
                cin.ignore();
                getline(cin, isbn);
                deleteBook(isbn);
                break;
            }
            case 4:
                currentUser = nullptr; // Log out
                cout << "Logged out successfully!" << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 4);
}

// Function for member menu
void memberMenu() {
    int choice;
    do {
        cout << "\n--- Member Menu ---\n";
        cout << "1. Display Books\n";
        cout << "2. Check Out Book\n";
        cout << "3. Return Book\n";
        cout << "4. Logout\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                displayBooks();
                break;
            case 2: {
                string isbn;
                cout << "Enter ISBN to check out: ";
                cin.ignore();
                getline(cin, isbn);
                checkOutBook(isbn);
                break;
            }
            case 3: {
                string isbn;
                cout << "Enter ISBN to return: ";
                cin.ignore();
                getline(cin, isbn);
                returnBook(isbn);
                break;
            }
            case 4:
                currentUser = nullptr; // Log out
                cout << "Logged out successfully!" << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 4);
}

// Function to add a book
void addBook() {
    Book newBook;
    cout << "Enter title: ";
    cin.ignore();
    getline(cin, newBook.title);
    cout << "Enter author: ";
    getline(cin, newBook.author);
    cout << "Enter ISBN: ";
    getline(cin, newBook.isbn);
    newBook.availability = true; // New book is available by default
    books.push_back(newBook);
    cout << "Book added successfully!" << endl;
}

// Function to display all books
void displayBooks() {
    if (books.empty()) {
        cout << "No books to display." << endl;
        return;
    }
    
    cout << "\nBooks List:\n";
    cout << left << setw(30) << "Title" 
         << setw(20) << "Author" 
         << setw(15) << "ISBN" 
         << setw(10) << "Status" << endl;

    for (const auto& book : books) {
        cout << left << setw(30) << book.title 
             << setw(20) << book.author 
             << setw(15) << book.isbn 
             << setw(10) << (book.availability ? "Available" : "Checked Out") 
             << endl;
    }
}

// Function to search for a book by ISBN
int searchBook(const string& isbn) {
    for (size_t i = 0; i < books.size(); i++) {
        if (books[i].isbn == isbn) {
            return i; // Return the index of the found book
        }
    }
    return -1; // Return -1 if not found
}

// Function to delete a book by ISBN
void deleteBook(const string& isbn) {
    int index = searchBook(isbn);
    if (index != -1) {
        books.erase(books.begin() + index); // Remove the book from vector
        cout << "Book deleted successfully!" << endl;
    } else {
        cout << "Book not found." << endl;
    }
}

// Function to check out a book by ISBN
void checkOutBook(const string& isbn) {
    int index = searchBook(isbn);
    if (index != -1 && books[index].availability) {
        books[index].availability = false; // Mark as checked out
        cout << "You have checked out the book." << endl;
    } else if (index != -1) {
        cout << "This book is already checked out." << endl;
    } else {
        cout << "Book not found." << endl;
    }
}

// Function to return a book by ISBN
void returnBook(const string& isbn) {
    int index = searchBook(isbn);
    if (index != -1 && !books[index].availability) {
        books[index].availability = true; // Mark as available
        cout << "You have returned the book." << endl;
    } else if (index != -1) {
        cout << "This book was not checked out." << endl;
    } else {
        cout << "Book not found." << endl;
    }
}
