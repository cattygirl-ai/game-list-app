#ifndef LISTOBSERVER_H
#define LISTOBSERVER_H

#include <QWidget>
#include "Observer.h"

class ListObserver : public Observer
{
public:
    ListObserver();
    ~ListObserver();
    void update();

private:
};

#endif // LISTOBSERVER_H
