#include "Contact.h"

// Constructor - create contact with basic info
Contact::Contact(string first, string last, string mail, string phone) {
    firstName = cleanString(first);
    lastName = cleanString(last);
    email = cleanString(mail);
    if(!phone.empty()) {
        phoneNumbers.push_back(cleanString(phone));
    }
}

// Remove spaces from start and end of text
string Contact::cleanString(string text) {
    // Find first character that is not space
    size_t start = text.find_first_not_of(" \t\n\r");
    if(start == string::npos) return ""; // All spaces
    
    // Find last character that is not space  
    size_t end = text.find_last_not_of(" \t\n\r");
    
    // Return text without spaces
    return text.substr(start, end - start + 1);
}