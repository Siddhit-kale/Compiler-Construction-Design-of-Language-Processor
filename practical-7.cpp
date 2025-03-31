#include <iostream>
#include <map>
#include <set>
#include <vector>

using namespace std;

map<char, set<char>> first, follow;
map<char, vector<string>> grammar;
set<char> nonTerminals;

void computeFirst(char symbol);
void computeFollow(char symbol);
bool isNonTerminal(char symbol) { return nonTerminals.count(symbol); }

int main() {
    // Define the grammar
    grammar['S'] = {"ABC", "D"};
    grammar['A'] = {"a", ""};
    grammar['B'] = {"b", ""};
    grammar['C'] = {"(S)", "c"};
    grammar['D'] = {"AC"};
    
    // Identify non-terminals
    for (auto &rule : grammar) nonTerminals.insert(rule.first);
    
    // Compute First sets
    for (char nt : nonTerminals) computeFirst(nt);
    
    // Compute Follow sets
    follow['S'].insert('$'); // Start symbol gets '$' in Follow set
    for (char nt : nonTerminals) computeFollow(nt);
    
    // Display First sets
    cout << "First Sets:\n";
    for (auto &entry : first) {
        cout << "First(" << entry.first << ") = { ";
        for (char c : entry.second) cout << c << " ";
        cout << "}\n";
    }
    
    // Display Follow sets
    cout << "\nFollow Sets:\n";
    for (auto &entry : follow) {
        cout << "Follow(" << entry.first << ") = { ";
        for (char c : entry.second) cout << c << " ";
        cout << "}\n";
    }
    
    return 0;
}

void computeFirst(char symbol) {
    if (!first[symbol].empty()) return; // Already computed
    
    for (string rule : grammar[symbol]) {
        if (!rule.empty() && !isNonTerminal(rule[0])) {
            first[symbol].insert(rule[0]); // Terminal
        } else {
            for (char ch : rule) {
                if (isNonTerminal(ch)) {
                    computeFirst(ch);
                    first[symbol].insert(first[ch].begin(), first[ch].end());
                    if (first[ch].count('\0') == 0) break; // Stop if ε not present
                } else {
                    first[symbol].insert(ch);
                    break;
                }
            }
        }
    }
}

void computeFollow(char symbol) {
    for (auto &rule : grammar) {
        for (string prod : rule.second) {
            for (size_t i = 0; i < prod.length(); i++) {
                if (prod[i] == symbol) {
                    size_t j = i + 1;
                    while (j < prod.length()) {
                        if (isNonTerminal(prod[j])) {
                            follow[symbol].insert(first[prod[j]].begin(), first[prod[j]].end());
                            follow[symbol].erase('\0');
                            if (first[prod[j]].count('\0') == 0) break;
                        } else {
                            follow[symbol].insert(prod[j]);
                            break;
                        }
                        j++;
                    }
                    if (j == prod.length() && rule.first != symbol) {
                        computeFollow(rule.first);
                        follow[symbol].insert(follow[rule.first].begin(), follow[rule.first].end());
                    }
                }
            }
        }
    }
}
