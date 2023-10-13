/*
* Class             CS 133 Project 2
*
* Name              Minsu Jung
*
* Date              October 5, 2023.

* Description       The WordGuesser class simulates a word guessing game where...
*                   it selects a word based on user input, tracks guessed letters,...
*                   calculates the display pattern, and manages the game state. 
*                   The 'record' function processes player guesses, updating ...
*                   the word set and remaining guesses. 
*                   The game continues until the player guesses the word or...
*                   runs out of maxGuesses. 
*/

#include "WordGuesser.h"



// Constructor for WordGuesser class. Initializes the game with a dictionary,
// word length, and maximum allowed guesses. It populates the wordSet with words
// of the specified length from the dictionary.
// Throws an exception if the word length or maxGuesses is less than one.
WordGuesser::WordGuesser(vector<string>& dictionary, int wordLength, int maxGuesses)
{
	if (wordLength < 1 || maxGuesses < 1)
	{
        throw "Length or maxGuess is less than one.";
	}

	this->wordLength = wordLength;
	this->maxGuesses = maxGuesses;

	// Populates the wordSet with words of the specified length from the dictionary.
	for (const string& words : dictionary)
	{
		if (words.length() == wordLength)
			wordSet.insert(words);
	}
}


// Returns a pointer to the set of possible answer words.
set<string>* WordGuesser::getWords()
{
	// Possible answers are stored in 'wordSet'.
	return &wordSet;
}

// Returns the remaining number of guesses allowed.
int WordGuesser::getGuessesLeft() const
{
	return maxGuesses;
}

// Returns a copy of the set containing guessed letters.
const set<char> WordGuesser::getGuesses() const
{
	// Returns the set of guessed letters.
	return guessedLetters;
}


// Initialize the pattern with '-' characters and spaces.
string WordGuesser::getPattern()
{
	string pattern(wordLength * 2 - 1, '-');

	// Loop through each character position in the pattern.
	for (int i = 0; i < pattern.size(); i++)
	{
		// Set spaces at odd indices to separate characters.
		if (i % 2 == 1)
		{
			pattern[i] = ' ';
		}
		// Iterate through words in the word set and place guessed letters in the pattern.
		for (string word : wordSet)
		{
			if (i < word.length() && guessedLetters.count(word[i]))
			{
				pattern[i * 2] = word[i];
			}
		}
	}
	// Return the generated pattern.
	return pattern;
}

// Updates game state based on a guessed letter and returns a ratio of correct guesses...
//  to the remaining wordSet size.
int WordGuesser::record(char guessedLetter)
{
#pragma region Exception.
    if (maxGuesses < 1)
    {
        throw "No more guesses left";
    }
    else if (guessedLetters.count(guessedLetter))
    {
        throw "Letter already guessed";
    }
    else if (wordSet.empty())
    {
        throw "Word set is empty";
    }
#pragma endregion

    guessedLetters.insert(guessedLetter);
    // Size of a word in the wordSet
    int maxSize = 0;
    // Number of letters that the player guessed correctly
    int correctWords = 0;

    // Calculate word families and store them in a map.
    map<string, set<string>> wordFamilies;
    for (string word : wordSet)
    {
        string family = getWordFamily(word, guessedLetter);
        wordFamilies[family].insert(word);
    }

    

    // Determine the largest family and update the wordSet.
    for (const auto& pair : wordFamilies)
    {
        if (pair.second.size() > maxSize)
        {
            maxSize = pair.second.size();
            wordSet.clear();
            // Refresh the wordSet by inserting strings into it.
            for (string word : pair.second)
            {
                wordSet.insert(word);
            }
        }
    }

    // Count correct guesses within the remaining wordSet.
    correctWords = numberOfCurrectWords(guessedLetter, correctWords);

    // Decrement guesses left if there are no correct guesses.
    if (correctWords == 0)
    {
        maxGuesses--;
    }

    // Return the ratio of correct guesses to the size of the remaining wordSet.
    return correctWords;
}

// This function counts the number of words in the wordSet where the guessedLetter is present
// and returns the ratio of correct words to the size of the remaining wordSet.
int WordGuesser::numberOfCurrectWords(char guessedLetter, int correctWords)
{

    // In the string "word," it searches for the number of times each word matches the player's input value.
    for (string word : wordSet)
    {
        for (char letter : word)
        {
            if (letter == guessedLetter)
            {
                correctWords++;
            }
        }
    }

    // Avoid division by zero and return the ratio as an integer.
    return (wordSet.empty()) ? 0 : correctWords / wordSet.size();;
}


// Returns a word family string for the given word and guessed letter, using '-' for unguessed letters.
string WordGuesser::getWordFamily(const string& word, char guessedLetter) const
{
    string family = "";

    // Loop through each character in the word to create the word family.
    for (int i = 0; i < wordLength; i++)
    {
        if (word[i] == guessedLetter)
        {
            family += guessedLetter;  // Add guessed letter to the word family.
        }
        else
        {
            family += "-";  // Add '-' for unguessed letters.
        }
        family += " ";  // Add a space to separate characters.
    }
    return family;
}
