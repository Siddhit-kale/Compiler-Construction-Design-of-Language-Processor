#include <iostream>
#include <fstream>
#include <cctype>
#include <unordered_set>
#include <unordered_map>
using namespace std;

unordered_set<string> keywords = {"int", "float", "char", "return", "if", "else", "while", "for", "void"};
unordered_set<char> operators = {'+', '-', '*', '/', '=', '<', '>', '!', '&', '|'};
unordered_set<char> punctuation = {';', ',', '(', ')', '{', '}', '[', ']'};
unordered_map<string, int> symbolTable;

bool isIdentifier(const string &str) {
    if (!isalpha(str[0]) && str[0] != '_') return false;
    for (char ch : str) if (!isalnum(ch) && ch != '_') return false;
    return true;
}

bool isConstant(const string &str) {
    for (char ch : str) if (!isdigit(ch)) return false;
    return true;
}

void processToken(const string &token) {
    if (token.empty()) return;
    if (keywords.count(token)) cout << "Keyword: " << token << endl;
    else if (isConstant(token)) cout << "Constant: " << token << endl;
    else if (isIdentifier(token)) {
        cout << "Identifier: " << token << endl;
        symbolTable[token]++;
    } else cout << "Lexical Error: " << token << endl;
}

void analyze(string filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Error opening file: " << filename << endl;
        return;
    }
    string token;
    char ch;
    bool inString = false, inComment = false;
    while (file.get(ch)) {
        if (ch == '"') inString = !inString;
        if (inString) { cout << "String: \""; while (file.get(ch) && ch != '"') cout << ch; cout << "\"" << endl; continue; }
        if (ch == '/' && file.peek() == '/') { file.ignore(1000, '\n'); continue; }
        if (ch == '/' && file.peek() == '*') { file.ignore(); while (file.get(ch) && !(ch == '*' && file.peek() == '/')); file.ignore(); continue; }
        if (isspace(ch)) { processToken(token); token.clear(); continue; }
        if (operators.count(ch)) { processToken(token); cout << "Operator: " << ch << endl; token.clear(); continue; }
        if (punctuation.count(ch)) { processToken(token); cout << "Punctuation: " << ch << endl; token.clear(); continue; }
        token += ch;
    }
    processToken(token);
    cout << "\nSymbol Table:" << endl;
    for (auto &[id, count] : symbolTable) cout << id << "\n";
}

int main() {
    string filename;
    cout << "Enter C source code filename: ";
    cin >> filename;
    analyze(filename);
    return 0;
}
