//
// Created by client on 2018-11-14.
//

#pragma once

#include "Observer.h"
#include <list>
#include <iostream>

using namespace std;


//Abstract subject class for the observer design pattern implementation.
class Subject {

public:

    virtual void attach(Observer* o); //Links an observer to the calling subject.
    virtual void detach(Observer* o); //Ends the relationship between observer and the subject.
    virtual void notify(); //Provides the necessary observed information that has been observed.
    virtual void notify(string message); //Provides a message that will be displayed for the information observed.

    Subject(); //Subject constructor.
    ~Subject(); //Subject destructor

private:

    list<Observer*> *_observers; //Provides all the observers linked to the calling subject.
};
