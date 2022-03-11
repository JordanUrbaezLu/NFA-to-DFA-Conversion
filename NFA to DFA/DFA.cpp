#include "DFA.h"

//Constructor used if you want a certain set of rules, suing a specific step function
DFA::DFA(int number_of_states, char alphabet[], int alphabet_size, map<int, set<pair<char, int > > > all_step_functions, int initial_state_index, int final_states_indeces[], int number_of_final_states)
{
    States_.resize(number_of_states); //resize vector of states
    States_.at(initial_state_index).set_initial_state(true); //set initial state
    for (int i = 0; i < number_of_final_states; i++) { //set the final states
        int index = final_states_indeces[i];
        States_.at(index).set_final_state(true);
    }
    for (int i = 0; i < all_step_functions.size(); i++) { //set the rules for each state
        States_.at(i).set_state_rule(all_step_functions[i]);
    }
    for (int i = 0; i < alphabet_size; i++) { //create the alphabet of the language
        Alphabet_.push_back(alphabet[i]);
    }
    current_state_index_ = initial_state_index;
    initial_state_index_ = initial_state_index;
    all_step_functions_ = all_step_functions;
}

bool faithful_DFA(const DFA dfa)
{
    /*
    1. Non-empty set of states, set of final states, and alphabet.
    2. Multiple arrows for one alphabet symbol.
    3. Initial state and step function
    */

    bool faithful = true;

    if (dfa.States_.empty()) { //check for an empty set of states
        //cout << "The DFA has an empty set of states." << endl;
        faithful = false;
    }
    //else
        //cout << "The DFA has a non-empty set of states." << endl;

    bool finalisempty = true; //check for an empty set  of final states
    for (int i = 0; i < dfa.States_.size(); i++) {
        if (dfa.States_.at(i).is_final())
        {
            finalisempty = false;
        }
    }
    if (finalisempty) {
        //cout << "The DFA has an empty set of final states." << endl;
        faithful = false;
    }
    //else
        //cout << "The DFA has a non-empty set of final states." << endl;

    //check for multiple arrows for one symbol
    //cout << "If this DFA does exist it cannot have two different arrows for the same symbol since it was implemented with a set of pairs which cannot be duplicated." << endl;

    if (dfa.Alphabet_.empty()) { //check for an empty alphabet
        //cout << "The DFA has an empty alphabet." << endl;
        faithful = false;
    }
    //else
        //cout << "The DFA has a non-empty alphabet." << endl;

    //check step function and initial state
    //cout << "The constructor requires an initial state and step function so those are valid characteristics needed by the formal definition." << endl;

    return faithful;
}

string DFA_checker(DFA dfa, string test_string)
{
    vector<State> myStates = dfa.get_all_states();
    int next_state;
    set<pair<char, int> > myRules = myStates.at(dfa.get_current_state_index()).get_state_rule();
  
    for(int i = 0; i < test_string.size(); i++) {
        for (auto const &x : myRules) {
            if (test_string[i] == x.first) {// if you find the character in the pair, make its second value the nextstate index
                next_state = x.second;
                dfa.set_current_state_index(next_state);
                break;
            }
        }
        myRules = myStates.at(dfa.get_current_state_index()).get_state_rule();
    }
    if (myStates.at(dfa.get_current_state_index()).is_final()) {
        return "Accepted";
    }
  return "Not Accepted";
}
