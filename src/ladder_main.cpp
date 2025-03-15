#include "ladder.h"
#include <iostream>
#include <string>
#include <set>

using namespace std;

int main() {
    string start_word, end_word;
    cout << "Enter start word: ";
    cin >> start_word;
    cout << "Enter end word: ";
    cin >> end_word;
    
    if(start_word == end_word) {
        error(start_word, end_word, "Start and end words must be different.");
        return 1;
    }

    set<string> word_list;
    load_words(word_list, "src/words.txt");
    
    vector<string> ladder = generate_word_ladder(start_word, end_word, word_list);
    if(ladder.empty()){ cout << "No word ladder found from " << start_word << " to " << end_word << "." << endl; } 
    else{ print_word_ladder(ladder); }
    // verify_word_ladder();
    
    return 0;
}
