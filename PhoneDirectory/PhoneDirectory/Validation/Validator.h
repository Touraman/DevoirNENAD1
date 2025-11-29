#ifndef VALIDATOR_H
#define VALIDATOR_H

#include <string>
#include <regex>

using namespace std;
// ... pas besoin de changer

class Validator
{
public:
    // Check if name has only letters, numbers, hyphen, space
    // Must start with letter, cannot start/end with hyphen
    static bool checkName(string name);
    
    // Check if email has correct format
    static bool checkEmail(string email);
    
    // Check if phone has correct Russian format
    static bool checkPhone(string phone);
    
    // Check if birth date is valid
    static bool checkDate(string date);

private:
    // Remove spaces from text
    static string removeSpaces(string text);
};

#endif