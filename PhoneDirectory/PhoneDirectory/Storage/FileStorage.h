#ifndef FILESTORAGE_H
#define FILESTORAGE_H

 #include "C:\Users\krssa\Desktop\PhoneDirectory\PhoneDirectory\Core\Contact.h"
#include <vector>
#include <string>

using namespace std;

class FileStorage {
private:
    string filename;

public:
    FileStorage(string file = "contacts.txt");
    void saveContacts(const vector<Contact>& contacts);
    vector<Contact> loadContacts();
};

#endif