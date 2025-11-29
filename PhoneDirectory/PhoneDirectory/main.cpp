#include <iostream>
#include <vector>
#include "C:\Users\krssa\Desktop\PhoneDirectory\PhoneDirectory\Core\Contact.h"
#include "C:\Users\krssa\Desktop\PhoneDirectory\PhoneDirectory\Validation\Validator.h"
#include "C:\Users\krssa\Desktop\PhoneDirectory\PhoneDirectory\Storage\FileStorage.h"

using namespace std;

// Function prototypes
void addContact(vector<Contact>& contacts, FileStorage& storage);
void showAllContacts(const vector<Contact>& contacts);
void searchContacts(const vector<Contact>& contacts);
void deleteContact(vector<Contact>& contacts, FileStorage& storage); // NOUVEAU

int main() {
    FileStorage storage("contacts.txt");
    vector<Contact> contacts = storage.loadContacts();
    int choice;
    
    cout << "=== PHONE DIRECTORY MANAGEMENT ===" << endl;
    cout << "Contacts file: contacts.txt" << endl;
    
    do {
        cout << "\n=== MAIN MENU ===" << endl;
        cout << "1. Add Contact" << endl;
        cout << "2. Show All Contacts" << endl;
        cout << "3. Search Contacts" << endl;
        cout << "4. Delete Contact" << endl; // NOUVEAU
        cout << "5. Save and Exit" << endl;
        cout << "6. Exit without Saving" << endl;
        cout << "Choose option: ";
        cin >> choice;
        cin.ignore(); // Important pour les entrées suivantes
        
        switch(choice) {
            case 1:
                addContact(contacts, storage);
                break;
            case 2:
                showAllContacts(contacts);
                break;
            case 3:
                searchContacts(contacts);
                break;
            case 4: // NOUVEAU
                deleteContact(contacts, storage);
                break;
            case 5:
                storage.saveContacts(contacts);
                cout << "Contacts saved successfully! Goodbye!" << endl;
                return 0;
            case 6:
                cout << "Exiting without saving. Goodbye!" << endl;
                return 0;
            default:
                cout << "Invalid option! Please try again." << endl;
        }
        
    } while(true);
    
    return 0;
}

// FONCTION DE SUPPRESSION AJOUTÉE
void deleteContact(vector<Contact>& contacts, FileStorage& storage) {
    if(contacts.empty()) {
        cout << "No contacts to delete." << endl;
        return;
    }
    
    cout << "\n--- Delete Contact ---" << endl;
    showAllContacts(contacts);
    
    int index;
    cout << "Enter contact number to delete: ";
    cin >> index;
    cin.ignore();
    
    if(index >= 1 && index <= contacts.size()) {
        contacts.erase(contacts.begin() + (index - 1));
        storage.saveContacts(contacts); // Sauvegarde automatique
        cout << "Contact deleted successfully!" << endl;
    } else {
        cout << "Invalid contact number!" << endl;
    }
}

void addContact(vector<Contact>& contacts, FileStorage& storage) {
    string first, last, middle, email, phone, address, birthDate;
    
    cout << "\n--- Add New Contact ---" << endl;
    
    cout << "First Name: ";
    cin >> first;
    cout << "Last Name: ";
    cin >> last;
    
    cout << "Middle Name (optional): ";
    cin.ignore();
    getline(cin, middle);
    
    cout << "Email: ";
    cin >> email;
    
    cout << "Phone Number: ";
    cin >> phone;
    
    cout << "Address (optional): ";
    cin.ignore();
    getline(cin, address);
    
    cout << "Birth Date (optional - format YYYY-MM-DD): ";
    getline(cin, birthDate);
    
    // VALIDATION AVEC REGEX (AJOUT)
    if(!Validator::checkName(first) || !Validator::checkName(last)) {
        cout << "Error: Invalid name format!" << endl;
        return;
    }
    if(!Validator::checkEmail(email)) {
        cout << "Error: Invalid email format!" << endl;
        return;
    }
    if(!Validator::checkPhone(phone)) {
        cout << "Error: Invalid phone format!" << endl;
        return;
    }
    
    // Create new contact
    Contact newContact(first, last, email, phone);
    
    // Set optional fields
    if(!middle.empty()) newContact.setMiddleName(middle);
    if(!address.empty()) newContact.setAddress(address);
    if(!birthDate.empty()) newContact.setBirthDate(birthDate);
    
    // Add additional phone numbers
    char addMorePhones;
    cout << "Add another phone number? (y/n): ";
    cin >> addMorePhones;
    
    while(addMorePhones == 'y' || addMorePhones == 'Y') {
        string additionalPhone;
        cout << "Additional phone number: ";
        cin >> additionalPhone;
        
        if(Validator::checkPhone(additionalPhone)) {
            newContact.addPhone(additionalPhone);
        } else {
            cout << "Invalid phone format! Not added." << endl;
        }
        
        cout << "Add another phone number? (y/n): ";
        cin >> addMorePhones;
    }
    
    // Add to contacts list
    contacts.push_back(newContact);
    
    // Auto-save after adding
    storage.saveContacts(contacts);
    
    cout << "Contact added successfully!" << endl;
}

void showAllContacts(const vector<Contact>& contacts) {
    cout << "\n--- All Contacts ---" << endl;
    if(contacts.empty()) {
        cout << "No contacts found." << endl;
        return;
    }
    
    for(size_t i = 0; i < contacts.size(); i++) {
        cout << i + 1 << ". " << contacts[i].toString() << endl;
    }
    cout << "-------------------" << endl;
    cout << "Total contacts: " << contacts.size() << endl;
}

void searchContacts(const vector<Contact>& contacts) {
    if(contacts.empty()) {
        cout << "No contacts to search." << endl;
        return;
    }
    
    string searchTerm;
    cout << "Enter name or email to search: ";
    cin >> searchTerm;
    
    cout << "\n--- Search Results ---" << endl;
    bool found = false;
    
    for(size_t i = 0; i < contacts.size(); i++) {
        const Contact& contact = contacts[i];
        string fullName = contact.getFirstName() + " " + contact.getLastName();
        
        // Search in first name, last name, full name, and email
        if(contact.getFirstName().find(searchTerm) != string::npos ||
           contact.getLastName().find(searchTerm) != string::npos ||
           fullName.find(searchTerm) != string::npos ||
           contact.getEmail().find(searchTerm) != string::npos) {
            
            cout << i + 1 << ". " << contact.toString() << endl;
            found = true;
        }
    }
    
    if(!found) {
        cout << "No contacts found matching '" << searchTerm << "'" << endl;
    }
    cout << "----------------------" << endl;
    // Tâche 1 - Version console complète
}