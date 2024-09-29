// SPA 2 - Wordle Assist, Fall 2024, Michael Wood
#include <iostream>
#include <cassert>
using namespace std;

/**
 * The maximum words in the list of possible solutions in wordle.
 */
constexpr int MAX_WORDS = 3000;
/**
 * The maximum guesses the user can make.
 */
constexpr int MAX_GUESSES = 10;

void run_checks();
bool can_match(string, string, string);
void read_word_list(string[], int&);
void read_guess_list(string[MAX_GUESSES][2], int&);
void find_matches(string[], int&, string[], int, string[MAX_GUESSES][2], int);
void display_output(string[MAX_GUESSES][2], int, string[], int);

int main() {
    run_checks();

    string word_list[MAX_WORDS];
    string guess_list[MAX_GUESSES][2];
    string match_list[MAX_WORDS];
    int word_count, guess_count, match_count;

    read_word_list(word_list, word_count);
    read_guess_list(guess_list, guess_count);
    find_matches(match_list, match_count, word_list, word_count, guess_list, guess_count);
    display_output(guess_list, guess_count, match_list, match_count);

    return 0;
}

/**
 * Tests for the can_match() method.
 */
void run_checks() {
    assert(can_match("abcde", "axbxf", ".-\?--"));
    assert(!can_match("abcde", "axbxd", ".-\?--"));
    assert(can_match("abcde", "easty", "\?\?---"));
    assert(!can_match("abcde", "abcdf", "....."));
    assert(can_match("abcde", "uvwxy", "-----"));
}

/**
 * Determines if the possible_answer could be an answer based on the user's guess
 * and the letter_matches associated with the guess.
 * @param possible_answer a word from the dictionary of possible answers.
 * @param guess the word entered by a user.
 * @param letter_matches the string of '.', '-', and '?' characters capturing
 * which letters in the guess are "correct".
 * @return true if possible_answer can match guess, false otherwise.
 */
bool can_match(string possible_answer, string guess, string letter_matches) {
    bool matches = true;
    for(size_t ix = 0; ix < guess.size(); ix++) {
        if(letter_matches[ix] == '.') {
            if(possible_answer[ix] != guess[ix]) {
                matches = false;
            }
        } else if(letter_matches[ix] == '-') {
            if(possible_answer.find(guess[ix]) != string::npos) {
                matches = false;
            }
        } else if(letter_matches[ix] == '?') {
            if(possible_answer[ix] == guess[ix] || possible_answer.find(guess[ix]) == string::npos) {
                matches = false;
            }
        }
    }
    return matches;
}

/**
 * Gets the word list containing all possible solutions to the wordle.
 * @param word_list the list of all possible solutions.
 * @param word_count the total words in word_list.
 */
void read_word_list(string word_list[], int &word_count) {
    word_count = 0;
    string current_word;
    cin >> current_word;
    while(cin && current_word != "END") {
        word_list[word_count++] = current_word;
        cin >> current_word;
    }
}

/**
 * Gets the guess list containing all guesses made by the user.
 * @param guess_list the list of all guesses made by the user.
 * @param guess_count the total number of guesses in guess list.
 */
void read_guess_list(string guess_list[MAX_GUESSES][2], int &guess_count) {
    guess_count = 0;
    string guess, letter_matches;
    cin >> guess >> letter_matches;
    while(cin && guess_count < MAX_GUESSES) {
        guess_list[guess_count][0] = guess;
        guess_list[guess_count][1] = letter_matches;
        guess_count++;
        cin >> guess >> letter_matches;
    }
}

/**
 * Finds all possible solutions to the wordle given a list of all possible solutions
 * and the users previous guesses along with which letters matched.
 * @param match_list the list of all possible solutions.
 * @param match_count the total number of solutions.
 * @param word_list the list of all possible solutions.
 * @param word_count the total words in word_list.
 * @param guess_list the list of all guesses made by the user.
 * @param guess_count the total number of guesses in guess list.
 */
void find_matches(string match_list[], int &match_count, string word_list[],
                  int word_count, string guess_list[MAX_GUESSES][2], int guess_count) {
    for(int i = 0; i < word_count; i++) {
        string current_word = word_list[i];
        bool valid_match = true;
        for(int j = 0; valid_match && j < guess_count; j++) {
            if(!can_match(current_word, guess_list[j][0], guess_list[j][1])) {
                valid_match = false;
            }
        }
        if(valid_match) {
            match_list[match_count++] = current_word;
        }
    }
}

/**
 * Displays the possible solutions to the console.
 * @param guess_list the list of all guesses made by the user.
 * @param guess_count the total number of guesses in guess list.
 * @param match_list the list of all possible solutions.
 * @param match_count the total number of solutions.
 */
void display_output(string guess_list[MAX_GUESSES][2], int guess_count,
                    string match_list[], int match_count) {
    cout << "Possible guesses after ";
    for(int i = 0; i < guess_count; i++) {
        cout << guess_list[i][0];
        if(i != guess_count - 1) {
            cout << ", ";
        }
    }
    cout << ": " << match_count << endl;
    for(int i = 0; i < match_count; i++) {
        cout << match_list[i] << endl;
    }
}

