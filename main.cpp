// SPA 2 - Wordle Assist, Fall 2024, Michael Wood
#include <iostream>
#include <cassert>
using namespace std;


void run_checks();
bool can_match(string, string, string);

int main() {
    run_checks();
    return 0;
}

void run_checks() {
    assert( can_match("abcde", "axbxf", ".-\?--"));
    assert(!can_match("abcde", "axbxd", ".-\?--"));
    assert( can_match("abcde", "easty", "\?\?---"));
    assert(!can_match("abcde", "abcdf", "....."));
    assert( can_match("abcde", "uvwxy", "-----"));
}

bool can_match(string possible_answer, string guess, string letter_matches) {
    bool valid = true;
    for(int i = 0; valid && i < guess.length(); i++) {
        if(letter_matches[i] == '.') {
            if(possible_answer[i] != guess[i]) { valid = false; }
        } else if(letter_matches[i] == '-') {
            if(possible_answer.find(guess[i]) != string::npos) { valid = false; }
        } else if(letter_matches[i] == '?') {
            if(possible_answer[i] == guess[i] || possible_answer.find(guess[i]) == string::npos) {
                valid = false;
            }
        }
    }
    return valid;
}

void read_word_list(string word_list[], int &word_count) {
    word_count = 0;
    string current_word;
    cin >> current_word;
    while(cin && current_word != "END") {
        word_list[word_count++] = current_word;
        cin >> current_word;
    }


}