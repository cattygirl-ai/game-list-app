#include "include/Subject.h"

using namespace std;

void Subject::attach(Observer* o)
{
    observers.push_back(o);
}

void Subject::detach(Observer* o)
{
    vector<Observer*>::iterator it;

    for(it = observers.begin(); it < observers.end(); ++it) {
        if((*it) == o) {
            observers.erase(it);
        }
    }
}

void Subject::notify()
{
    vector<Observer*>::iterator it;

    for(it = observers.begin(); it < observers.end(); ++it) {
        (*it)->update();
    }
}
