#include "NFA.h"
#include "iostream"

//Constructor used if you want a certain set of rules, suing a specific step function
NFA::NFA(int number_of_states, char alphabet[], int alphabet_size, map<int, set<pair<char, int > > > all_step_functions, int initial_state_index, int final_states_indeces[], int number_of_final_states, vector<vector<int>> epsilon_transition)
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
    for(int i = 0; i < epsilon_transition.size(); i++)
    {
        States_.at(i).set_epsilon_states(epsilon_transition.at(i));
    }
    for (int i = 0; i < alphabet_size; i++) { //create the alphabet of the language
        Alphabet_.push_back(alphabet[i]);
    }
    current_states_.push_back(initial_state_index);
    initial_state_index_ = initial_state_index;
    all_step_functions_ = all_step_functions;
}

bool faithful_NFA(const NFA nfa)
{
    /*
    1. Non-empty set of states, set of final states, and alphabet.
    2. Multiple arrows for one alphabet symbol.
    3. Initial state and step function
    */

    bool faithful = true;

    if (nfa.States_.empty()) { //check for an empty set of states
        //cout << "The NFA has an empty set of states." << endl;
        faithful = false;
    }
    //else
        //cout << "The NFA has a non-empty set of states." << endl;

    bool finalisempty = true; //check for an empty set  of final states
    for (int i = 0; i < nfa.States_.size(); i++) {
        if (nfa.States_.at(i).is_final())
        {
            finalisempty = false;
        }
    }
    if (finalisempty) {
        //cout << "The NFA has an empty set of final states." << endl;
        faithful = false;
    }
    //else
        //cout << "The NFA has a non-empty set of final states." << endl;

    //check for multiple arrows for one symbol
    //cout << "If this NFA does exist it cannot have two different arrows for the same symbol since it was implemented with a set of pairs which cannot be duplicated." << endl;

    if (nfa.Alphabet_.empty()) { //check for an empty alphabet
        //cout << "The NFA has an empty alphabet." << endl;
        faithful = false;
    }
    //else
        //cout << "The NFA has a non-empty alphabet." << endl;

    //check step function and initial state
    //cout << "The constructor requires an initial state and step function so those are valid characteristics needed by the formal definition." << endl;

    return faithful;
}

string NFA_checker(NFA nfa, string test_string)
{
    vector<State> myStates = nfa.get_all_states();
    State current_state = nfa.get_all_states().at(nfa.get_initial_state_index()); //get initial state
    vector<int> temp_curr_states = nfa.get_current_states();

    set<pair<char, int> > myRules;
    //vector<int> temp_curr_states = nfa.get_current_states();
    vector<int> temp2;
    vector<int> temp3;
  
    //initial case to create set of current state indices
    vector<int> curr_state_epsilons = current_state.get_epsilon_states();
    vector<int> next_state_epsilons;

    for(int i = 0; i < curr_state_epsilons.size(); i++)
    {
        temp_curr_states.push_back(curr_state_epsilons.at(i));
        next_state_epsilons = myStates.at(curr_state_epsilons.at(i)).get_epsilon_states();
        for (int j = 0; j < next_state_epsilons.size(); j++){ //while the current states epsilon is not NULL/100, this loop will get all the states from the epsilon travel into temp_curr_states
            temp_curr_states.push_back(next_state_epsilons.at(i)); //push the index of the epsilon state onto temp_currr_states
        }
    }
    
    for (int i = 0; i < test_string.size(); i++){ //go through the whole string
        for (int j = 0; j < temp_curr_states.size(); j++){
            myRules = myStates.at(temp_curr_states.at(j)).get_state_rule(); //make rules set to each of the current states' rules
            for (auto const &x : myRules) { //loop through the set of pairs of rules and search for the matching pair

                if (test_string[i] == x.first) { //found pair
                    temp2.push_back(x.second); //push second value on temp2 vector of ints
                }
            }
      
            for (int k = 0; k < temp2.size(); k++) {
                temp3.push_back(temp2.at(k));
                current_state = myStates.at(temp2.at(k));
          
                curr_state_epsilons = current_state.get_epsilon_states();

                for(int i = 0; i < curr_state_epsilons.size(); i++)
                {
                    temp3.push_back(curr_state_epsilons.at(i));
                    next_state_epsilons = myStates.at(curr_state_epsilons.at(i)).get_epsilon_states();
                    for (int j = 0; j < next_state_epsilons.size(); j++){ //while the current states epsilon is not NULL/100, this loop will get all the states from the epsilon travel into temp_curr_states
                        temp3.push_back(next_state_epsilons.at(i)); //push the index of the epsilon state onto temp_currr_states
                    }
                }
            }
            temp2.clear();
        }
        temp_curr_states = temp3;
        temp3.clear();
    }
    for (int i = 0; i < temp_curr_states.size(); i++){
        if (myStates.at(temp_curr_states.at(i)).is_final()) {
            return "Accepted";
        }
    }
    return "Not Accepted";
}
