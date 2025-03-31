#include <iostream>
#include <map>
#include <set>
#include <vector>
using namespace std;

struct FiniteAutomata {
    set<char> input_symbols;
    set<int> states;
    int initial_state;
    set<int> accepting_states;
    map<pair<int, char>, int> transitions;

    bool validateString(const string &input) {
        int current_state = initial_state;
        for (char ch : input) {
            if (transitions.find({current_state, ch}) == transitions.end()) {
                return false;
            }
            current_state = transitions[{current_state, ch}];
        }
        return accepting_states.count(current_state) > 0;
    }
};

int main() {
    FiniteAutomata fa;
    int num_symbols, num_states, num_accepting;
    char symbol;
    int state_from, state_to;
    string input_str;

    cout << "Number of input symbols: ";
    cin >> num_symbols;
    cout << "Input symbols: ";
    for (int i = 0; i < num_symbols; ++i) {
        cin >> symbol;
        fa.input_symbols.insert(symbol);
    }

    cout << "Enter number of states: ";
    cin >> num_states;
    for (int i = 1; i <= num_states; ++i) {
        fa.states.insert(i);
    }

    cout << "Initial state: ";
    cin >> fa.initial_state;

    cout << "Number of accepting states: ";
    cin >> num_accepting;
    cout << "Accepting states: ";
    for (int i = 0; i < num_accepting; ++i) {
        cin >> state_from;
        fa.accepting_states.insert(state_from);
    }

    cout << "Transition table (format: state symbol new_state):\n";
    while (cin >> state_from >> symbol >> state_to) {
        if (fa.states.count(state_from) && fa.states.count(state_to) && fa.input_symbols.count(symbol)) {
            fa.transitions[{state_from, symbol}] = state_to;
        } else {
            break;
        }
    }

    cin.clear();
    cin.ignore();

    cout << "Input string: ";
    cin >> input_str;

    if (fa.validateString(input_str)) {
        cout << "Valid string" << endl;
    } else {
        cout << "Invalid string" << endl;
    }

    return 0;
}
