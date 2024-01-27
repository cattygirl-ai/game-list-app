#ifndef SUBJECT_H
#define SUBJECT_H

#include <iostream>
#include <vector>

#include "Observer.h"

class Subject
{
public:
    virtual ~Subject() {};
    void attach(Observer* o);
    void detach(Observer* o);
    void notify();

private:
    std::vector<Observer*> observers;

};

#endif // SUBJECT_H
