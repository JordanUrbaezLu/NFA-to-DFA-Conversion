#ifndef NFA_HEADER
#define NFA_HEADER

#include <vector>
#include "states.h"
#include <string>
#include <iostream>

class NFA {
public:
    //Constructor for NFA
    NFA(int number_of_states, char alphabet[], int alphabet_size, map<int, set<pair<char, int>>> all_step_functions, int initial_state_index, int final_states_indeces[], int number_of_final_states, vector<vector<int>> epsilon_transition);

    vector<int> get_current_states() const { return current_states_; }
    int get_initial_state_index() const { return initial_state_index_; }
    void set_current_states(vector<int> states) { current_states_ = states; }
  vector<int> get_current_states(){return current_states_; }
    vector<State> get_all_states() const { return States_; }
    vector<char> get_alphabet() { return Alphabet_; }
    //map<int, map<char, int>> get_all_step_functions() {    return all_step_functions_; }
    friend bool faithful_NFA(const NFA nfa);
    
    
private:
    vector<State> States_;
    vector<char> Alphabet_;
    vector<int> current_states_;
    int initial_state_index_;
    map<int, set<pair<char, int>>> all_step_functions_;
};

#endif
