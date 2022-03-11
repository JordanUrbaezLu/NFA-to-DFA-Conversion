#ifndef DFA_HEADER
#define DFA_HEADER

#include <vector>
#include "states.h"
#include <string>
#include <iostream>

class DFA {
public:
    //Constructor for DFA
    DFA(int number_of_states, char alphabet[], int alphabet_size, map<int, set<pair<char, int>>> all_step_functions, int initial_state_index, int final_states_indeces[], int number_of_final_states);

    int get_current_state_index() const { return current_state_index_; }
    int get_initial_state_index() const { return initial_state_index_; }
    void set_current_state_index(int index) { current_state_index_ = index; }
    vector<State> get_all_states() const { return States_; }
    vector<char> get_alphabet() { return Alphabet_; }
    //map<int, map<char, int>> get_all_step_functions() {    return all_step_functions_; }
    friend bool faithful_DFA(const DFA dfa);
    
    
private:
    vector<State> States_;
    vector<char> Alphabet_;
    int current_state_index_;
    int initial_state_index_;
    map<int, set<pair<char, int>>> all_step_functions_;
};

#endif
