/*
* Class             CS 133 Project 2
*
* Name              Minsu Jung
*
* Date              October 5, 2023.

* Description       The WordGuesser class simulates a word guessing game where the program...
*                   selects a word based on user input and provides clues to the player. 
*                   The constructor initializes the game with a dictionary, word length,
*                   and maximum allowed guesses. The WordGuesser object keeps track of guessed ...
*                   letters, calculates the pattern to be displayed, and manages the game state.
*                   The 'record' function processes player guesses, updating the
*                   word set and guesses left. The game continues until the player either guesses...
*                   the word or runs out of maxGuesses.
* 
* record()          The record function manages the game's progression by processing a guessed letter. 
*                   It checks for exceptions, adds the guessed letter to the set of guessed letters,...
*                   calculates different word families based on the letter, selects the largest family...
*                   to update the word set, counts the number of correct guesses ...
*                   within the remaining word set, and adjusts the remaining guesses accordingly.
*                   Ultimately, it returns the ratio of correct guesses to the size of the remaining word set,...
*                   helping to guide the game towards its conclusion.
*/
#include <set>
#include <iostream>
#include <vector>
#include <map>

using namespace std;

class WordGuesser
{
private:
    set<string> wordSet;        // Set to store possible answer words.
    set<char> guessedLetters;   // Set to store guessed letters.
    int wordLength;             // Length of the word from user's input.
    int maxGuesses;             // Maximum number of allowed guesses.

    /* Private function to generate a word family for a given word and guessed letter.*/ 
    string getWordFamily(const string& word, char guessedLetter) const;

    /* Returns the count of correct characters by the player. */
    int numberOfCurrectWords(char guessedLetter, int correctWords);


public:
    /*
    * Use the passed in values to initialize the state of the game.
    * The set of words should initially be all words from the dictionary...
    * that are of the given length.
    * The constructor should throw string exception if the passed in length...
    * is less than 1 or if the
    * passed in max is less than 0.
    */
    WordGuesser(vector<string>& dictionary, int wordLength, int maxGuesses);

    /*
    * The client calls this member function to get access to the current set of words.. 
    * being considered by the letter guesser.
    */
    set<string>* getWords();

    /*
    * The client calls this member function to find out how many guesses the player has left
    */
    int getGuessesLeft() const;

    /*
    * The client calls this member function to find out the current set of ...
    * letters that have been guessed by the user.
    * These should be in alphabetical order.
    */
    const set<char> getGuesses() const;

    /*
    * Return the current pattern to be displayed for the guessing game taking into ...
    * account guesses that have been made.
    * Letters that have not yet been guessed should be displayed as a dash and there...
    * should be spaces separating the letters.
    * There should be no leading or trailing spaces.
    * This member function should throw a string exception if the set of words is empty.
    */
    string getPattern();

    /*
    * This is the member function that does most of the work by recording the next guess made by the user.
    * It should throw a string exception if the number of guesses left is not at least 1.
    * Using this guess, it should decide what set of words to use going forward.
    * It should return the number of occurrences of the guessed letter in the new pattern ...
    * and it should appropriately update the number of guesses left.
    * This member function should also throw a string exception if the list of words is empty.
    * It should throw a string exception if the list of words is nonempty and the character ...
    * being guessed was guessed previously.
    */
    int record(char guessedLetter);


};

// print operator for a set of any type
// outputs all items in the set separated by spaces
template <typename T>
ostream& operator<< (ostream& out, const set<T>& words) {
    for (const T& word : words) {
        cout << (T)word << " ";
    }
    return out;
}
