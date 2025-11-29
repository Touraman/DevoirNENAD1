#include "Validator.h"
#include <regex>

using namespace std;

// Validate name: letters, numbers, hyphen, space
// Start with letter, no hyphen at start/end
bool Validator::checkName(string name) {
    string cleanName = removeSpaces(name);
    if(cleanName.empty()) return false;
    
    // Regex: start with letter, then letters/numbers/hyphen/space, end with letter/number
    regex pattern("^[a-zA-Z][a-zA-Z0-9\\s-]*[a-zA-Z0-9]$");
    return regex_match(cleanName, pattern);
}

// Validate email format
bool Validator::checkEmail(string email) {
    string cleanEmail = removeSpaces(email);
    if(cleanEmail.empty()) return false;
    
    // Simple email regex
    regex pattern("^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,}$");
    return regex_match(cleanEmail, pattern);
}

// Validate Russian phone formats
bool Validator::checkPhone(string phone) {
    string cleanPhone = removeSpaces(phone);
    if(cleanPhone.empty()) return false;
    
    // Russian phone formats: +7xxxxxxxxxx, 8xxxxxxxxxx, with brackets and hyphens
    regex pattern("^(\\+7|8)[\\s\\(\\)\\-\\d]{10,15}$");
    return regex_match(cleanPhone, pattern);
}

// Simple date validation (will be improved)
bool Validator::checkDate(string date) {
    string cleanDate = removeSpaces(date);
    return !cleanDate.empty(); // Basic check for now
}

// Remove all spaces from text
string Validator::removeSpaces(string text) {
    string result = "";
    for(char c : text) {
        if(c != ' ') result += c;
    }
    return result;
}