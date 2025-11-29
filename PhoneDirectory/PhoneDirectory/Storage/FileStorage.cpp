#include "FileStorage.h"
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

FileStorage::FileStorage(string file) : filename(file) {}

void FileStorage::saveContacts(const vector<Contact>& contacts) {
    ofstream file(filename);
    
    if (!file.is_open()) {
        cout << "Error: Cannot open file " << filename << " for writing!" << endl;
        return;
    }
    
    for (const auto& contact : contacts) {
        file << contact.toFileString() << endl;
    }
    
    file.close();
    cout << "Contacts saved to " << filename << " successfully!" << endl;
}

vector<Contact> FileStorage::loadContacts() {
    vector<Contact> contacts;
    ifstream file(filename);
    
    if (!file.is_open()) {
        cout << "No existing contacts file found. Starting with empty directory." << endl;
        return contacts;
    }
    
    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;
        
        stringstream ss(line);
        string first, last, middle, email, address, birthDate, phonesStr;
        
        // Read fields separated by |
        getline(ss, first, '|');
        getline(ss, last, '|');
        getline(ss, middle, '|');
        getline(ss, email, '|');
        getline(ss, address, '|');
        getline(ss, birthDate, '|');
        getline(ss, phonesStr);
        
        // Create contact with basic info
        Contact contact(first, last, email, "");
        
        // Set optional fields
        if (!middle.empty()) contact.setMiddleName(middle);
        if (!address.empty()) contact.setAddress(address);
        if (!birthDate.empty()) contact.setBirthDate(birthDate);
        
        // Add phone numbers
        stringstream phonesSS(phonesStr);
        string phone;
        while (getline(phonesSS, phone, ',')) {
            if (!phone.empty()) {
                contact.addPhone(phone);
            }
        }
        
        contacts.push_back(contact);
    }
    
    file.close();
    cout << "Loaded " << contacts.size() << " contacts from " << filename << endl;
    
    return contacts;
}