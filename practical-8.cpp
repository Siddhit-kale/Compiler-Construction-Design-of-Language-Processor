#include <iostream>
#include <map>
#include <set>
#include <stack>
#include <string>
#include <vector>

using namespace std;

// First and Follow Sets
map<char, set<string>> firstSets = {
    {'S', {"a", "b", "(", "c"}},
    {'A', {"a", "ε"}},
    {'B', {"b", "ε"}},
    {'C', {"(", "c"}},
    {'D', {"a", "(", "c"}}
};

map<char, set<string>> followSets = {
    {'S', {")", "$"}},
    {'A', {"b", "(", "c"}},
    {'B', {"(", "c"}},
    {'C', {")", "$"}},
    {'D', {")", "$"}}
};

// Predictive Parsing Table
map<pair<char, string>, string> parsingTable;

// Grammar Rules
map<char, vector<string>> grammar = {
    {'S', {"A B C", "D"}},
    {'A', {"a", "ε"}},
    {'B', {"b", "ε"}},
    {'C', {"( S )", "c"}},
    {'D', {"A C"}}
};

// Function to create the predictive parsing table
void constructParsingTable() {
    for (const auto& rule : grammar) {
        char nonTerminal = rule.first;
        for (const string& production : rule.second) {
            vector<string> first;
            if (production == "ε") {
                first = vector<string>(followSets[nonTerminal].begin(), followSets[nonTerminal].end());
            } else {
                string firstSymbol = string(1, production[0]);
                if (firstSets.count(firstSymbol[0])) {
                    first = vector<string>(firstSets[firstSymbol[0]].begin(), firstSets[firstSymbol[0]].end());
                } else {
                    first.push_back(firstSymbol);
                }
            }

            for (const string& terminal : first) {
                parsingTable[{nonTerminal, terminal}] = production;
            }
        }
    }
}

// Function to check if the grammar is LL(1)
bool isLL1Grammar() {
    for (const auto& entry : parsingTable) {
        char nonTerminal = entry.first.first;
        string terminal = entry.first.second;
        if (parsingTable.count({nonTerminal, terminal}) > 1) {
            return false; // Conflict found, so it's not LL(1)
        }
    }
    return true;
}

// Function to validate input string using predictive parsing table
bool validateString(const string& input) {
    stack<char> parseStack;
    parseStack.push('$');
    parseStack.push('S'); // Start symbol

    int i = 0;
    string augmentedInput = input + "$";

    while (!parseStack.empty()) {
        char top = parseStack.top();
        parseStack.pop();

        if (top == augmentedInput[i]) {
            i++;
        } else if (parsingTable.count({top, string(1, augmentedInput[i])})) {
            string production = parsingTable[{top, string(1, augmentedInput[i])}];
            if (production != "ε") {
                for (int j = production.length() - 1; j >= 0; j--) {
                    parseStack.push(production[j]);
                }
            }
        } else {
            return false;
        }
    }

    return (i == augmentedInput.length());
}

// Main function
int main() {
    constructParsingTable();

    // Print Parsing Table
    cout << "Predictive Parsing Table:\n";
    for (const auto& entry : parsingTable) {
        cout << "M[" << entry.first.first << ", " << entry.first.second << "] = " << entry.second << endl;
    }

    // Check if the grammar is LL(1)
    if (isLL1Grammar()) {
        cout << "\nThe given grammar is LL(1)\n";
    } else {
        cout << "\nThe given grammar is NOT LL(1)\n";
        return 0;
    }

    // Test cases
    vector<string> testCases = {"abc", "ac", "(abc)", "c", "(ac)", "a", "( )", "(ab)", "abcabc", "b"};
    cout << "\nString Validation Results:\n";
    for (const string& testCase : testCases) {
        cout << "String: " << testCase << " -> " << (validateString(testCase) ? "Valid" : "Invalid") << endl;
    }

    return 0;
}
