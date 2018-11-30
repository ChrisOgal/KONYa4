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

    void attach(Observer* o); //Links an observer to the calling subject.
    void detach(Observer* o); //Ends the relationship between observer and the subject.
    void notify(); //Provides the necessary observed information that has been observed.
    void notify(string message); //Provides a message that will be displayed for the information observed.
    void notify(int cardNumber); //Notifies about the right action to perform

    Subject(); //Subject constructor.
    ~Subject(); //Subject destructor

private:

    list<Observer*> *_observers; //Provides all the observers linked to the calling subject.
};
