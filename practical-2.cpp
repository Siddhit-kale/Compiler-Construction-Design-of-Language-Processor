#include <iostream>
#include <map>
#include <vector>
#include <set>
#include <string>

using namespace std;

int main() {
    int num_symbols, num_states, num_accepting_states;
    set<char> input_symbols;
    set<int> accepting_states;
    int initial_state;
    map<pair<int, char>, int> transitions;

    cout << "Number of input symbols: ";
    cin >> num_symbols;
    cout << "Input symbols: ";
    for (int i = 0; i < num_symbols; i++) {
        char symbol;
        cin >> symbol;
        input_symbols.insert(symbol);
    }

    cout << "Enter number of states: ";
    cin >> num_states;

    cout << "Initial state: ";
    cin >> initial_state;

    cout << "Number of accepting states: ";
    cin >> num_accepting_states;
    cout << "Accepting states: ";
    for (int i = 0; i < num_accepting_states; i++) {
        int state;
        cin >> state;
        accepting_states.insert(state);
    }

    cout << "Transition table: \n";
    for (int i = 0; i < num_states * num_symbols; i++) {
        int from_state;
        char input_symbol;
        int to_state;
        cin >> from_state >> input_symbol >> to_state;
        transitions[make_pair(from_state, input_symbol)] = to_state;
    }

    string input_string;
    cout << "Input string: ";
    cin >> input_string;

    int current_state = initial_state;
    bool is_valid = true;

    for (char c : input_string) {
        if (transitions.find({current_state, c}) != transitions.end()) {
            current_state = transitions[{current_state, c}];
        } else {
            is_valid = false;
            break;
        }
    }

    if (is_valid && accepting_states.count(current_state)) {
        cout << "Valid string" << endl;
    } else {
        cout << "Invalid string" << endl;
    }

    return 0;
}
