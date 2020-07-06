# a program that reads in a description of a (deterministic) Turing machine (TM) from a
# data file, after which it prints out a description of said TM. It then prompts for 
# input strings, one per line. For each such input string, the program traces the progress of
# the TM on that string, along with printing an acceptance or rejection message if the TM halts on
# said string.

#include "TM.h"
#include <iostream>

using namespace std;

int main(int argc, char** argv)
{
    // command-line argument munging
    if (argc != 2) {
        cerr << "usage: " << argv[0] << " tm_file\n"
             << "where tm_file is the data file describing the TM\n";
        return 1;
    }   

    // open the TM data file
    ifstream tm_data(argv[1]);
    if (!tm_data) {
        cerr << argv[0] << ": couldn't open " << argv[1] << endl;
        return 2;
    }   

    // initialize the TM and print its description
    TM tm(tm_data);
    cout << "Turing machine definition:\n";
    tm.describe();
    cout << endl;

    // prompt-read-eval loop
    cout << "Enter input strings, one line at a time:\n";
    while (true) {
        cout << "? ";
        string in_string;
        getline(cin, in_string);
        if (!cin) break;
        bool success = tm.trace(in_string);
        if (success) cout << "accept!\n";
        else cout << "reject!\n";
    }   
}
