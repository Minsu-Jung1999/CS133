/*
* Class             CS 133 Project 3
*
* Name              Minsu Jung
*
* Date              October 12, 2023.
*
* Description       It maintains two linked lists: tagRing and outList, 
*					representing the current players and those who have been 
*					tagged, respectively.
*					This file provides various functions for managing  the 
*					game, such as checking if a person is in the tagRing or 
*					outList, determining if the game is over, and finding the winner. 
*                   The core functionality is the 'tag' function, which records
*					the tagging of a person and transfers them to the outList.
* 
* tagRinig			It represents the players who are alive.
* outList			It represents the players who are tagged(not alive).
*
*/

#include <iostream>
#include <vector>
#include "TagNode.h"

using namespace std;

class TagManager
{
private:

	// enum for represeting each liked lists.
	enum NODECASE
	{
		TAGRING = 0,  // Represents tagRing linked list.
		OUTLIST        // Represents outList linked list.
	};

	// a pointer to the front node of the tag ring
	TagNode* tagRing;	

	// a pointer to the front node of the out list (nullptr if empty)
	TagNode* outList;

	// uses the TagList received as a parameter and a sentence string to produce output.
	const void printList(TagNode* list,NODECASE node);

	// accepts a reference of string variable and changes it to lower case then returns it.
	const string convertToLowerCase(string word);

	// It returns true if the targetName is found in the list, and false otherwise.
	const bool searchNameInList(TagNode* list, string name);
	
	// Simplifies the process of initialize the outList.
	const void inintOutlist(std::string& taggerName, TagNode* tagFront, std::string& taggedName);

	// Check if the tagged person is either the first or the last person in the tagFront.
	const void tagCheckFirstandLastPerson(TagNode* tagFront, std::string& taggedName, std::string& taggerName);

public:

	// initialize a new tag manger for the given list of people.
	// doesn't modify the list, but it build own tag ring of linked nodes...
	// that contains these names in the same order.
	// throws a string exception if the list has a size of 0.
	TagManager(vector<string> names);
	
	// prints the names of the people in the tag ring,
	// one per line, indented by two spaces, as
	// "name" was tagged by "name".
	// prints opposite of the order in which they were tagged.
	// produces no output if the out list is empty.
	const void printTagRing();

	// prints the names of the people in the out list,
	// one per line, indented by two spaces, as
	// "name" is tryeing to tag "name".
	// The behavioris unspecified if the game is over.
	const void printOutList();

	// returns true if the given name is in the current tag...
	// and false otherwise.
	// ignore case in comparing names.
	const bool tagRingContains(string name);

	// returns true if the given name is in the current out list...
	// and false otherwise.
	// ignore case in comparing names.
	const bool outListContains(string name);

	// returns true if the game is over (if the tag ring has just one person)...
	// and false otherwise.
	const bool isGameOver();

	// returns the name of the winner of the game, or an empty string if the ...
	// game is not over.
	const string winner();

	// records the tagging of the person with the  given name, transferring the ...
	// person from the tag ring to the front of the out list. This operation should not...
	// change the relative order of the tag ring. 
	// Ignore case in comparing names.
	// A node remembers who tagged the person in its tagger member variable. 
	// throws a string exception of "game over" if the game is over, or a string ...
	// exception of "not in ring" if the given name is not part of the tag ring.
	// (if both of these conditions are true, the "game over" takes precedence).
	const void tag(string name);

};