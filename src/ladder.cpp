#include "ladder.h"
#include <algorithm>
#include <cctype>

using namespace std;

static string to_lower(const string &s){
    string result = s;
    transform(result.begin(), result.end(), result.begin(), ::tolower);
    return result;
}

void error(string word1, string word2, string msg){
    cerr << "Error: " << word1 << " " << word2 << "  " << msg << endl;
}

bool edit_distance_within(const string& str1, const string& str2, int d){
    if(d < 0) return false;

    int len1 = str1.size();
    int len2 = str2.size();
    
    if(abs(len1 - len2) > 1) return false;
    if(len1 == len2){
        int diff=0;
        for(int i=0; i<len1; ++i){
            if(tolower(str1[i]) != tolower(str2[i])){
                ++diff;
                if(diff > 1) return false;
            }
        }
        return diff <= 1;
    } 
    else{
        const string &s = (len1 < len2) ? str1 : str2;
        const string &t = (len1 < len2) ? str2 : str1;
        size_t i = 0, j = 0;
        int diff = 0;
        while(i < s.size() && j < t.size()){
            if(tolower(s[i]) == tolower(t[j])){ ++i; ++j; } 
            else{
                ++diff;
                if(diff > 1) return false;
                ++j;
            }
        }
        if(j < t.size()) ++diff;
        return diff <= 1;
    }
}


bool is_adjacent(const string& word1, const string& word2){ return edit_distance_within(word1, word2, 1); }

vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list){
    if (to_lower(begin_word) == to_lower(end_word)){
        error(begin_word, end_word, "Start and end words are to be different.");
        return vector<string>();
    }
    
    queue<vector<string>> ladder_queue;
    vector<string> start_ladder = { to_lower(begin_word) };
    ladder_queue.push(start_ladder);
    set<string> visited;
    visited.insert(to_lower(begin_word));
    
    while(!ladder_queue.empty()){
        vector<string> ladder = ladder_queue.front();
        ladder_queue.pop();
        string last_word = ladder.back();
        for(const auto &word : word_list){
            if(is_adjacent(last_word, word) && visited.find(word) == visited.end()){
                visited.insert(word);
                vector<string> new_ladder = ladder;
                new_ladder.push_back(word);
                if(word == to_lower(end_word)){ return new_ladder; }
                ladder_queue.push(new_ladder);
            }
        }
    }
    return vector<string>();
}

void load_words(set<string>& word_list, const string& file_name){
    ifstream in(file_name);
    string word;
    while(in >> word){word_list.insert(to_lower(word)); }
    in.close();
}

void print_word_ladder(const vector<string>& ladder){
    if(ladder.empty()){ cout << "No word ladder found." << endl; return; }
    cout << "Word ladder found: ";
    for(size_t i=0; i<ladder.size(); ++i){ cout << ladder[i] << " "; }
    cout << endl;
}

void verify_word_ladder(){
    set<string> word_list;
    load_words(word_list, "src/words.txt");
    
    auto test = [&](const string& start, const string& end, size_t expected_length){
        vector<string> ladder = generate_word_ladder(start, end, word_list);
        if(ladder.size() == expected_length){
            cout << "Test passed for " << start << " -> " << end << endl;
        }
        else{
            cout << "Test failed for " << start << " -> " << end
                 << ". Expected ladder length: " << expected_length
                 << ", got: " << ladder.size() << endl;
        }
    };
    
    test("cat", "dog", 4);
    test("marty", "curls", 6);
    test("code", "data", 6);
    test("work", "play", 6);
    test("sleep", "awake", 8);
    test("car", "cheat", 4);
}
