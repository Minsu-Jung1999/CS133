/*
* Class             CS 133 Project 4
*
* Name              Minsu Jung
*
* Date              October 19, 2023.
*
* Description       This file saves the user's responses ...
*                   and initializes pointer addresses.
*
*
*/
#include "QuestionNode.h"
QuestionNode::QuestionNode(const std::string& text)
{
    data = text;
    left = nullptr;
    right = nullptr;
}
