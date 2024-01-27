#ifndef GAME_H
#define GAME_H
#include "iostream"
#include "Comment.h"
#include <vector>
using namespace std;

class Comment{

    private:
    int id;
    std::string author;
    std::string text;
    std::string date; 

    public:
    int getID();
    std::string getAuthor();
    std::string getText();
    std::string getDate();
    void setAuthor(std::string username);
    void setText(std::string text);
    void setDate(std::string date);
    void setID(int id);
};
#endif