#ifndef CONTACT_H
#define CONTACT_H

#include <string>
#include <vector>

using namespace std;

class Contact
{
private:
    string firstName;
    string lastName;  
    string middleName;
    string address;
    string birthDate;
    string email;
    vector<string> phoneNumbers;

public:
    // Create new contact with required fields
    Contact(string first, string last, string mail, string phone);
    
    // Get contact information
    string getFirstName() const { return firstName; }
    string getLastName() const { return lastName; }
    string getMiddleName() const { return middleName; }
    string getAddress() const { return address; }
    string getBirthDate() const { return birthDate; }
    string getEmail() const { return email; }
    vector<string> getPhones() const { return phoneNumbers; }
    string getFullName() const { return firstName + " " + lastName; }

    // Update contact information
    void setFirstName(string name) { firstName = cleanString(name); }
    void setLastName(string name) { lastName = cleanString(name); }
    void setMiddleName(string name) { middleName = cleanString(name); }
    void setAddress(string addr) { address = cleanString(addr); }
    void setBirthDate(string date) { birthDate = cleanString(date); }
    void setEmail(string mail) { email = cleanString(mail); }
    
    void addPhone(string phone) { 
        if(!phone.empty()) phoneNumbers.push_back(cleanString(phone)); 
    }
    
    bool removePhone(int index) {
        if(index >= 0 && index < phoneNumbers.size()) {
            phoneNumbers.erase(phoneNumbers.begin() + index);
            return true;
        }
        return false;
    }
    
    // Check if contact has required fields
    bool isValid() const {
        return !firstName.empty() && !lastName.empty() && 
               !email.empty() && !phoneNumbers.empty();
    }

    // Display all contact information
    string toString() const {
        string result = firstName + " " + lastName;
        
        // Add middle name if exists
        if (!middleName.empty()) {
            result += " " + middleName;
        }
        
        result += " - " + email;
        
        // Add birth date if exists
        if (!birthDate.empty()) {
            result += " - Born: " + birthDate;
        }
        
        // Add address if exists
        if (!address.empty()) {
            result += " - Address: " + address;
        }
        
        // Add all phone numbers
        if (!phoneNumbers.empty()) {
            result += " - Phones: ";
            for (size_t i = 0; i < phoneNumbers.size(); ++i) {
                result += phoneNumbers[i];
                if (i < phoneNumbers.size() - 1) {
                    result += ", ";
                }
            }
        }
        
        return result;
    }

    // Method to serialize contact for file storage
    string toFileString() const {
        string result = firstName + "|" + lastName + "|" + middleName + "|" +
                       email + "|" + address + "|" + birthDate + "|";
        
        // Add all phone numbers separated by commas
        for (size_t i = 0; i < phoneNumbers.size(); ++i) {
            result += phoneNumbers[i];
            if (i < phoneNumbers.size() - 1) {
                result += ",";
            }
        }
        
        return result;
    }

private:
    // Remove extra spaces
    string cleanString(string text);
};

#endif