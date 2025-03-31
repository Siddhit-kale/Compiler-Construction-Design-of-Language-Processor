#include <iostream>
#include <regex>
using namespace std;

bool isValidString(const string &input) {
    regex pattern("^a*bb$");
    return regex_match(input, pattern);
}

int main() {
    string input;
    cout << "Enter a string: ";
    getline(cin, input);

    if (isValidString(input)) {
        cout << "Valid string" << endl;
    } else {
        cout << "Invalid string" << endl;
    }

    return 0;
}
