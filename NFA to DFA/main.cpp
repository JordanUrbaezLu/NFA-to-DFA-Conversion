#include "DFA.h"
#include "iostream"
#include "NFA.h"
/*
== Conversion from NFA to DFA ==

1) DATA REPRESENTATION of NFA which must be faithful to the formal definition.
  you could use a function to check whether an instance of the data representation is a valid NFA.

2) a FUNCTION that takes an NFA and returns a DFA representation that is a valid input of the interpreter for DFA above.

3) EXAMPLE TESTS: you will decide how many and which examples to show but the overall set of examples must be exhaustive (exercise all aspects of NFA).
  You will show the execution and the resulting DFA on screen.
  You will also show that the resulting DFA can indeed run with your interpreter for DFA above. You will do this by giving in input a few strings that exercise the DFA, but you don't have to exhaustively test the DFA with a large number of tests.

*/
 //checks if DFA is faithful to the definition
string DFA_checker(DFA dfa, string test_string); //checks whether a string is accepted or not with a given DFA
string NFA_checker(NFA nfa, string test_string);
//DFA NFA_to_DFA(NFA nfa); //converts a NFA to a DFA
using namespace std;

int main(int argc, char* argv[])
{
    cout << "***************************************************************" << endl;
    cout << "DFA" << endl;
    cout << "***************************************************************" << endl;
    set<pair<char, int> > d0;
    d0.insert((make_pair('0', 0))); // state 0
    d0.insert((make_pair('1', 1))); // state 0
    set<pair<char, int> > d1;
    d1.insert((make_pair('1', 0))); // state 1
    d1.insert((make_pair('0', 1))); // state 1
    map<int, set<pair<char, int > > > dm1;
    dm1[0] = d0;
    dm1[1] = d1;
    ////////////////////////////////////////////
    char d_alphabet[2] = {0, 1};
    int d_final_states[1] = {1};
  
    //DFA That accepts odd number of 1s
    DFA dfa1(2, d_alphabet, 2, dm1, 0, d_final_states, 1);
    if (faithful_DFA(dfa1))
        cout << "Faithful\n";
    else
        cout << "Not Faithful\n";
    //Start Tests
    cout << DFA_checker(dfa1, "") << endl;
    cout << DFA_checker(dfa1, "0") << endl;
    cout << DFA_checker(dfa1, "111") << endl;
    cout << DFA_checker(dfa1, "101011010100110010101") << endl;
  
    
    //make NFA
    cout << endl << "***************************************************************" << endl;
    cout << "NFA" << endl;
    cout << "***************************************************************" << endl;
    set<pair<char, int> > n0;
    n0.insert((make_pair('0', 0))); // state 0
    n0.insert((make_pair('1', 2))); // state 0
    set<pair<char, int> > n1;
    n1.insert((make_pair(NULL, NULL))); // state 1
    set<pair<char, int> > n2;
    n2.insert((make_pair('1', 2))); // state 2
    n2.insert((make_pair('1', 1))); // state 2
    map<int, set<pair<char, int > > > nm1;
    nm1[0] = n0;
    nm1[1] = n1;
    nm1[2] = n2;

    char n_alphabet[2] = {0, 1};
    int n_final_states[1] = {1};
    
    vector<vector<int>> epsilon;
    epsilon.resize(3);
    vector<int> epsilon1;
    epsilon1.resize(1);
    epsilon1.at(0) = 1;
    //epsilon1.at(1) = 2;
    epsilon.at(0) = epsilon1;

    NFA nfa1(3, n_alphabet, 2, nm1, 0, n_final_states, 1, epsilon);
    
    if (faithful_NFA(nfa1))
        cout << "Faithful\n";
    else
        cout << "Not Faithful\n";
    //Start Tests
    cout << NFA_checker(nfa1, "1111") << endl;
    cout << NFA_checker(nfa1, "1") << endl;
    cout << NFA_checker(nfa1, "0") << endl;
    cout << NFA_checker(nfa1, "10") << endl;
    cout << NFA_checker(nfa1, "01") << endl;
    cout << NFA_checker(nfa1, "0010") << endl;
    cout << NFA_checker(nfa1, "101010101000110") << endl;
  
    return 0;
}

/*DFA convert(NFA nfa)
{
    State dfa_initial_state;
    vector<State> dfa_states;
    map<int, set<pair<char, int>>> dfa_step_functions;
    
    
    vector<State> myStates = nfa.get_all_states();
    State initial_state = nfa.get_all_states().at(nfa.get_initial_state_index());
    // Subset Construction Algorithm
    // 1. Create start state of DFA by taking the e-closure of the start state of the NFA
    // 2. Perform the following for the new DFA state:
    // For each possible input symbol: (for all characters in the alphabet)
    //     1. Apply next state to the newly created state, and the input symbol; this edits the current set of states
    //     2. Apply the e-closure to this set of states, possibly resulting in a new set
    // This set of NFA states will be a single state in the DFA
    // 3. Each time we generate a new DFA state, repeat step #2 on this newly created state
    // 4. The finish states of the DFA are those which contain any of the finish states of the NFA.
    
}*/
