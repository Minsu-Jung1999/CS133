/*
* Class             CS 133 Project 4
*
* Name              Minsu Jung
*
* Date              October 19, 2023.
*
* Description       it recursively iterates using a helper function.
*                   When saving the game, nodes are saved in ...
*                   a preorder traversal format.
*
*/

#include "QuestionTree.h"

// Constructor for initializing a new question tree.
QuestionTree::QuestionTree(UserInterface* ui)
{
    this->ui = ui;
    root = new QuestionNode("computer");
    gamesPlayed = 0;
    wonCount=0;
}

// plays a guessing game.
const void QuestionTree::play()
{
    gamesPlayed++;
    QuestionNode* currentNode = root;
    playHelper(currentNode);
}

// Helper function for playing a game.
const void QuestionTree::playHelper(QuestionNode* currentNode){
    ui->printLine(currentNode->data);
    // reach a leaf node.
    if(currentNode->left == nullptr && currentNode->right == nullptr)
    {
        ui->print("Would your object happen to be " +
                  currentNode->data + "? ");
        // reaching an answer leaf node.
        if(ui->readBoolean())
        {
            ui->printLine("I win!");
            wonCount++;
        }
        else
        {
            ui->print("I lose. What is your object? ");
            string userObject = ui->readLine();
            ui->print("Type a yes/no question to distinguish your item from "
                      + currentNode->data + ": ");
            string newQuestion = ui->readLine();
            ui->print("And what is the answer for your object?   ");
            bool answer = ui->readBoolean();

            // Update the tree
            currentNode->left = new QuestionNode(
                answer ? userObject : currentNode->data);
            currentNode->right = new QuestionNode(
                answer ? currentNode->data : userObject);
            currentNode->data = newQuestion;
        }
        return;
    }
    else
    {
        ui->print(currentNode->data);
        bool userAnswer = ui->readBoolean();
        currentNode = userAnswer ? currentNode->left : currentNode->right;
    }
    playHelper(currentNode);
}

// Function to save the data to an output stream.
const void QuestionTree::save(ostream* output)
{
    saveHelper(output, root);
}

// Helper function to save the data to the tree recursively.
const void QuestionTree::saveHelper(ostream* output,
                                    const QuestionNode* currentNode)
{
    if(currentNode == nullptr)
        return ;

    if(currentNode->left == nullptr && currentNode->right == nullptr)
        (*output) << "A: " << currentNode->data << endl;
    else
    {
        (*output) << "Q: " << currentNode->data << endl;
        saveHelper(output, currentNode->left);
        saveHelper(output, currentNode->right);
    }
}

// loads the data file from an input stream.
const void QuestionTree::load(istream* input)
{
    cleanUp(root);
    root = new QuestionNode("");
    loadHelper(root, *input);
}

// Helper function to load the data from a file recursively.
const void QuestionTree::loadHelper(QuestionNode*& currentNode,
                                    istream& input)
{
    string line;

    getline(input,line);

    if(line.empty())
        return;

    char type = line[0];
    string data = line.substr(3);
    if(type == 'A')
    {
        currentNode = new QuestionNode(data);
    }
    else if(type == 'Q')
    {
        if (currentNode == nullptr) {
            ui->printLine("Error: Invalid file format.");
            return;
        }

        currentNode->data = data;
        currentNode->left = new QuestionNode("");
        currentNode->right = new QuestionNode("");
        cout << data << endl;
        loadHelper(currentNode->left, input);
        loadHelper(currentNode->right, input);
    }
}

// returns the total number of games played.
const int QuestionTree::totalGames() const
{
    return gamesPlayed;
}

// returns the number of games won.
const int QuestionTree::gamesWon() const
{
    return wonCount;
}

// Destructor to clean up memory.
QuestionTree::~QuestionTree()
{
    cleanUp(root);
}

// Helper function for cleaning up nodes.
const void QuestionTree::cleanUp(QuestionNode* node) {
    if (node == nullptr) {
        return;
    }

    //clear all node.
    cleanUp(node->left);
    cleanUp(node->right);
    delete node;
}
