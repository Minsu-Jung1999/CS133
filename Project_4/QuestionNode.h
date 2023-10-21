/*
* Class             CS 133 Project 4
*
* Name              Minsu Jung
*
* Date              October 19, 2023.
*
* Description       This file is responsible for managing a structure...
*                   that stores data based on the user's responses.
*
*
*/
#include <iostream>

class QuestionNode {
public:
    std::string data;
    QuestionNode* left;
    QuestionNode* right;
    // initialize data variable using text
    // left and right pointers are pointing nullptr initially.
    QuestionNode(const std::string& text);
};
