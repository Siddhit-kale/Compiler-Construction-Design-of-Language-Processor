#include <iostream>
#include <string>
using namespace std;

string input;
int pos = 0;

// Function prototypes
bool S();
bool L();
bool L_prime();

// Function to check 'S' → ( L ) | a
bool S() {
    if (pos < input.length()) {
        if (input[pos] == 'a') {  // S → a
            pos++;
            return true;
        } else if (input[pos] == '(') {  // S → ( L )
            pos++;  // Move past '('
            if (L()) {
                if (pos < input.length() && input[pos] == ')') {
                    pos++;  // Move past ')'
                    return true;
                }
            }
        }
    }
    return false;
}

// Function to check 'L' → S L'
bool L() {
    if (S()) {
        return L_prime();
    }
    return false;
}

// Function to check 'L’ → , S L’ | ϵ
bool L_prime() {
    if (pos < input.length() && input[pos] == ',') {
        pos++;  // Move past ','
        if (S()) {
            return L_prime();
        }
        return false;
    }
    return true;  // ϵ (empty) is always valid
}

int main() {
    cout << "Enter a string: ";
    cin >> input;
    pos = 0;
    
    if (S() && pos == input.length()) {
        cout << "Valid string" << endl;
    } else {
        cout << "Invalid string" << endl;
    }
    return 0;
}
