/*
* Class             CS 133 Project 3
*
* Name              Minsu Jung
*
* Date              October 12, 2023.
*
* Description       Manages a tagging game with two linked lists: tagRing and outList.
*					Provides functions to tag, check if a person is in the game,
*                   determine game over, and find the winner.
*/

#include "TagManager.h"

// Constructor for TagManager class. Initializes tagRing with a circular linked list from 'names'.
TagManager::TagManager(vector<string> names)
{
	if (names.empty())
		throw "List is empty!";
	
	// initialize first node of tagRing
	tagRing = new TagNode(names[0]);

	TagNode* current = tagRing;

	// initailize tagRings' name
	for (int i = 1; i < names.size(); i++)
	{
		current->next = new TagNode(names[i]);
		current = current->next;
	}
	current->next = nullptr;

	// make empty outList.
	outList = new TagNode("");
}

// print template {"  [name] is trying to tag [name]"}
const void TagManager::printTagRing()
{
	printList(tagRing, NODECASE::TAGRING);
}

// print template {"  [name] was tagged by [name]"}
const void TagManager::printOutList()
{
	printList(outList, NODECASE::OUTLIST);
}

// Checks if 'name' exists in the tagRing linked list.
const bool TagManager::tagRingContains(string name)
{
	return searchNameInList(tagRing, name);
}

// Checks if 'name' exists in the outList linked list.
const bool TagManager::outListContains(string name)
{
	return searchNameInList(outList, name);
}

// Checks if the game is over by examining the tagRing linked list.
const bool TagManager::isGameOver()
{
	// If tagring has only one node , game is over.
	return (tagRing->next == nullptr) ? true : false;
}

// Returns the name of the winner, which is the first person in the tagRing.
const string TagManager::winner()
{
	return isGameOver() ? tagRing->name : "";
}

// Tags a person with 'name' and updates the tagRing and outList accordingly.
const void TagManager::tag(string name)
{
	// Check if the game is over
	if (isGameOver())
		throw "Game over";

	// Check if the name exists in the tagRing
	if (!tagRingContains(name))
		throw "Not in the ring";

		
	string taggedName = convertToLowerCase(name);
	TagNode* tagFront = tagRing;
	string taggerName = "";
	
	// Traverse the tagRing to find the tagger and update the outList
	// It doesn't reach the last node.
	while (tagFront->next->next != nullptr)
	{
		string targetName = convertToLowerCase(tagFront->next->name);
		// If the tagger is found
		if (targetName == taggedName)
		{
			// Initialize the outList and change the order.
			inintOutlist(taggerName, tagFront, taggedName);
			tagFront->next = tagFront->next->next;
			break;
		}
		else
			tagFront = tagFront->next;
	}

	// Check the last node here.
	tagCheckFirstandLastPerson(tagFront, taggedName, taggerName);
	TagNode* outPerson = new TagNode(taggedName);
	outPerson->tagger = taggerName;

	outPerson->next = outList;
	outList = outPerson;

}

#pragma region Helper Function

// Initialize the outList with 'taggedName' and set 'taggerName'.
const void TagManager::inintOutlist(std::string& taggerName, TagNode* tagFront, 
	std::string& taggedName)
{
	taggerName = tagFront->name;
	taggedName = tagFront->next->name;
}

// prints a linked list with different templates based on 'node'.
const void TagManager::printList(TagNode* list, NODECASE node)
{
	TagNode* current = list;
	while (current->next != nullptr)
	{
		string nextPersonName = current->next->name;

		// print template for tagRing list.
		if (node == NODECASE::TAGRING)	
		{
			cout << "  " << current->name << " " << "is trying to tag" << " "
				<< current->next->name << endl;
		}
		// print template for outList list.
		else                            
		{
			cout << "  " << current->name << " " << "was tagged by" << " "
				<< current->tagger << endl;
		}

		// link the last and the first node.
		if (current->next == nullptr)
		{
			nextPersonName = list->name;
		}
		current = current->next;
	}
	// link the last and first node.
	if (list->next != nullptr && node == NODECASE::TAGRING)
		cout << "  " << current->name << " " << "is trying to tag" << " "
		<< list->name;

}

// returns the given word to lower case string varable.
const string TagManager::convertToLowerCase(string word)
{
	for (char& lowerCharacter : word) {
		lowerCharacter = tolower(lowerCharacter);
	}
	return word;
}

// searches for a name in a linked list, ignoring case sensitivity.
// returns true if the targetName is found in the list, and false otherwise.
const bool TagManager::searchNameInList(TagNode* list, string targetName)
{
	// Converts the targetName to lowercase for case-insensitive comparison.
	string lowercaseTargetName = convertToLowerCase(targetName);

	TagNode* current = list;

	// Searchs for the targetName in the linked list.
	while (current->next != nullptr)
	{
		string lowercaseCurrentName = convertToLowerCase(current->name);

		if (lowercaseCurrentName == lowercaseTargetName)
			return true;

		current = current->next;
	}
	string lowercaseCurrentName = convertToLowerCase(current->name);

	if (lowercaseCurrentName == lowercaseTargetName)
		return true;

	return false;
}

// Check if the tagged person is the last or first person in the tagRing.
// If the tagged person is the last, update the outList and remove them from the tagRing.
// If the tagged person is the first, set the taggerName, update taggedName, and adjust the tagRing.
const void TagManager::tagCheckFirstandLastPerson(TagNode* tagFront, std::string& taggedName, 
	std::string& taggerName)
{
	// Check if the tagged person is the last person in the tagRing
	string targetName = convertToLowerCase(tagFront->next->name);
	if (targetName == taggedName)
	{
		inintOutlist(taggerName, tagFront, taggedName);
		tagFront->next = nullptr;
	}

	// Check if the tagged person is the first person in the tagRing
	targetName = convertToLowerCase(tagRing->name);
	if (targetName == taggedName)
	{
		// Set taggerName, update taggedName, and adjust the tagRing
		taggerName = tagFront->next->name;
		taggedName = tagRing->name;
		tagRing = tagRing->next;
	}
}

#pragma endregion




