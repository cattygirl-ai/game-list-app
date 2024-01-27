/*
Author: Tina Agbamuche
Description of file contents: This class lets users comment on a game, so that I can share my opinions and interact with other users.
2022-10-28
*/

#include <iostream>
#include "Comment.h"

/*
1. Adding a comment for a certain game within the max. character limit (pass). check if it exceeds
2. Being able to remove comments from a game (pass)
*/

int Comment::getID(){
    return id; 
}
    
std::string Comment::getAuthor(){
    return author; 

}

std::string Comment::getText(){
    return text;   
}

std::string Comment::getDate(){
    return date; 
}

void Comment::setAuthor(std::string author){
    this->author = author; 

}

void Comment::setText(std::string text){
    this->text = text;

}

void Comment::setDate(std::string date){
    this->date = date;
     

}

void Comment::setID(int id){
     this->id = id; 

}

