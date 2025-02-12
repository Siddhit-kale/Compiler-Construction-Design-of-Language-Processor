#include <iostream>
#include <regex>
using namespace std;

int main() {
    string text;
    cout << "Enter a string: ";
    cin >> text;

    regex pattern("^a*bb$");

    if (regex_match(text, pattern)) {
        cout << "Valid String" << endl;
    } else {
        cout << "Invalid String" << endl;
    }

    return 0;
}
