#ifndef STATES_HEADER
#define STATES_HEADER

#include <map>
#include <utility>
#include <set>
#include <vector>

using namespace std;

class State {
public:
    State() {}
    void set_initial_state(bool initial_state) {initial_state_ = initial_state;}
    void set_final_state(bool final_state) {final_state_ = final_state;}
    bool is_final() const { return final_state_; }
    void set_state_rule(set<pair<char, int> > state_rule) { state_rule_ = state_rule; }
    set<pair<char, int> > get_state_rule(void) {return state_rule_;}
    void set_epsilon_states(vector<int> states){epsilon_states_ = states;}
    vector<int> get_epsilon_states(){ return epsilon_states_; }
  
    
private:
    bool initial_state_ = false;
    bool final_state_ = false;
    vector<int> epsilon_states_;
    set<pair<char, int>> state_rule_;
};

#endif
