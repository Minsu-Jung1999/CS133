/*
* Class             CS 133 Project 4
*
* Name              Minsu Jung
*
* Date              October 19, 2023.
*
* Description       This is a yes/no guessing game. Each round of the game begins...
*                   by player thinking of an object. The computer will try to guess
*                   player's object by asking the palyer a series of yes or no questions.
*                   It provides the user to save the game or load the previous game from...
*                   a file.
*/
#include <iostream>
#include <fstream>
#include <string>
#include "UserInterface.h"
#include "QuestionNode.h"

using namespace std;

class QuestionTree
{
private:

    // responsible for handling user interface functions  ...
    // related to reading true/false button input values or...
    // displaying characters.
    UserInterface* ui;

    // A linked list that stores answers and questions in a  ...
    // tree structure based on the user's responses.
    // It stores values in a tree structure, ...
    // using the left pointer for positive responses and the  ...
    // right pointer for negative responses.
    QuestionNode* root;

    // The total count of games played.
    int gamesPlayed;

    // The count of games won with correct answers.
    int wonCount;

    // plays one complete guessing game with the user, asking yes/no...
    // questions until reaching an answer object to guess.
    // A game begins with the root node of the...
    // tree and ends upon reaching an answer leaf node.
    // If the computer wins the game, print a message saying so.
    // Otherwise, the tree asks the user what object he/she was thinking ...
    // of a question to distinguish that object from the player's guess,...
    // and whether the player's object is the yes or no ...
    // answer for that question.
    const void playHelper(QuestionNode* currentNode);

    // stores the current tree state to an output file represented by the...
    // given ostream*.
    // The tree can grow each time the user runs the program.
    // The tree is specified by a sequence of lines, one for each node.
    // Each line must start with either Q: to indicate a question...
    // node or A: to indicate an answer (a leaf).
    const void saveHelper(ostream* output, const QuestionNode* currentNode);

    // replaces the current tree by reading another tree from a file.
    // reads from a file and replaces the current tree nodes with a new...
    // tree using the information in the file.
    const void loadHelper(QuestionNode*& currentNode, istream& input);

    // This helper function frees nodes.
    const void cleanUp(QuestionNode* node);

public:
    // initializes a new question tree.
    // The tree will use this user interface for printing output messages...
    // and asking questions in the game.
    // Initially the tree starts out containing only a single answer leaf
    // node with the word "computer" in it.
    QuestionTree(UserInterface* ui);

    // adds one to gamesPlayed and plays the game by calling...
    // playerHelper function.
    const void play();

    // saves the data in the tree by calling...
    // savehelper function.
    const void save(ostream* output);

    // frees all existed data in the tree and...
    // load data front a file.
    const void load(istream* input);

    // return number of games played.
    const int totalGames() const;

    // return number of correct answers.
    const int gamesWon() const;

    // frees all data in the tree by calling...
    // cleanup function.
    ~QuestionTree();
};
