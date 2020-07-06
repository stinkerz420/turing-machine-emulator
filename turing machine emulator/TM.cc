#include "TM.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>

using namespace std;

// document me
istream& operator>>(istream &is, Table_entry& entry)
{
    string input;
    is >> input;
    sscanf(input.c_str(), "(%d,%c,%c)", &entry.new_state, &entry.new_char, &entry.direction);
    return is; 
}

// output the contents of a Table_entry
ostream& operator<<(ostream &os, const Table_entry& entry)
{
    os << '(' << entry.new_state << "," << entry.new_char << ',' << entry.direction << ')';
    return os;
}


// document me
TM::TM(ifstream &ifs)
{
    ifs >> num_states >> sigma >> gamma;
    blank = gamma.back();
    
    
    Table_entry entry;
    
    for (int i = 0; i < num_states; i++) {
        // create a new vector to represent a row in the transition table
        vector<Table_entry> new_row;
        
        
        // read an entry for each transition gamma in the tape alphabet
        for (unsigned int j = 0; j < gamma.size(); j++) {
            ifs >> entry;
            new_row.push_back(entry);    
        }
        // add the new row to the table
        state_table.push_back(new_row);
    }
}

// document me
void TM::describe()
{
    //cout << "Stub version of TM::describe() called\n";
    cout << "Turing machine definition: " << endl;
    cout << "sigma = " << sigma << endl;
    cout << "gamma = " << gamma << endl;
    cout << "blank = " << blank << endl;
    cout << "number of states " << num_states << endl;
    
    cout << "state transition table" << endl;
    
    for (int i = 0; i < num_states; i++) {
        for (size_t j = 0; j < gamma.size(); j++) {
            cout << setw(12) << state_table[i][j];
        }
        cout << endl;
    }
    
}

// document me
bool TM::trace(string& in_string)
{
    string tape = in_string + blank;
    int tape_index = 0;
    int current_state = 1;
    
    // while the current state isn't 0
    // might never terminate per the halting problem
    while(current_state != 0)
    {
        print_config(current_state, tape_index, tape);
        
        char current_char = tape[tape_index];
        //find gamma index
        size_t gamma_index = gamma.find(current_char);
        if (gamma_index == string::npos) {
            // input character wasnt in tape alphabet
            // reject
            return false;
        }
        // go to state_table[new_state][gamma index]
        // create a local variable to make it easier to refer to
        Table_entry transition = state_table[current_state-1][gamma_index];
        
        // if the NEW state (i.e. the one in the transition) is -1
        if (transition.new_state == -1)
            return false;
        
        // if the new state ISNT invalid:
        else {
            // follow the transition:
            // update current state
            current_state = transition.new_state;

            // update tape - not the local temp variable current_char
            tape[tape_index] = transition.new_char;

            // update index
            if (transition.direction == 'R')
                tape_index++;
            else {
                tape_index--;
            }
        }
    }
    
    return true;
}

// document me
void TM::print_config(int state, unsigned int pos, 
                      const string& in_string)
{
    //cout << "Stub version of TM::print_config() called\n";
    for (unsigned int i = 0; i < in_string.size() ; i++) {
        if(i == pos) {
            cout << "q" << state << " ";
        }
        cout << in_string[i] << " ";
    }
    cout << endl;
}