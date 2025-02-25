#include <iostream>
#include <string>
using namespace std;

const int MAX_CONTACTS = 100; 

struct Contact {
    string name;
    string phoneNumber;
};


void addContact(Contact contacts[], int& count);
void displayContacts(const Contact contacts[], int count);
int searchContact(const Contact contacts[], int count, const string& name);
void deleteContact(Contact contacts[], int& count, const string& name);

int main() {
    Contact contacts[MAX_CONTACTS];
    int count = 0; // Current number of contacts
    int choice;

    do {
        cout << "\n--- Contact Management System ---\n";
        cout << "1. Add Contact\n";
        cout << "2. Display Contacts\n";
        cout << "3. Search Contact\n";
        cout << "4. Delete Contact\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addContact(contacts, count);
                break;
            case 2:
                displayContacts(contacts, count);
                break;
            case 3: {
                string name;
                cout << "Enter the name to search: ";
                cin.ignore();
                getline(cin, name);
                int index = searchContact(contacts, count, name);
                if (index != -1) {
                    cout << "Contact found: " << contacts[index].name << " - " << contacts[index].phoneNumber << endl;
                } else {
                    cout << "Contact not found." << endl;
                }
                break;
            }
            case 4: {
                string name;
                cout << "Enter the name to delete: ";
                cin.ignore();
                getline(cin, name);
                deleteContact(contacts, count, name);
                break;
            }
            case 5:
                cout << "Exiting the program." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 5);

    return 0;
}

// Function to add a contact
void addContact(Contact contacts[], int& count) {
    if (count < MAX_CONTACTS) {
        cout << "Enter name: ";
        cin.ignore();
        getline(cin, contacts[count].name);
        cout << "Enter phone number: ";
        getline(cin, contacts[count].phoneNumber);
        count++;
        cout << "Contact added successfully!" << endl;
    } else {
        cout << "Contact list is full!" << endl;
    }
}
void displayContacts(const Contact contacts[], int count) {
    if (count == 0) {
        cout << "No contacts to display." << endl;
        return;
    }
    cout << "\nContacts List:\n";
    for (int i = 0; i < count; i++) {
        cout << i + 1 << ". " << contacts[i].name << " - " << contacts[i].phoneNumber << endl;
    }
}
int searchContact(const Contact contacts[], int count, const string& name) {
    for (int i = 0; i < count; i++) {
        if (contacts[i].name == name) {
            return i; 
        }
    }
    return -1; 
}
void deleteContact(Contact contacts[], int& count, const string& name) {
    int index = searchContact(contacts, count, name);
    if (index != -1) {
        // Shift contacts to fill the gap
        for (int i = index; i < count - 1; i++) {
            contacts[i] = contacts[i + 1];
        }
        count--; 
        cout << "Contact deleted successfully!" << endl;
    } else {
        cout << "Contact not found." << endl;
    }
}
