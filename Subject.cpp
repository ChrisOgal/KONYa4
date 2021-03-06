//
// Created by client on 2018-11-14.
//

#include "Subject.h"

Subject::Subject() {
    _observers = new list<Observer*>;
}

Subject::~Subject() {
    if(_observers->size() > 0)
    delete _observers;
}

void Subject::attach(Observer *o) {
    _observers->push_back(o);
}

void Subject::detach(Observer *o) {
    _observers->remove(o);
}

void Subject::notify() {
    list<Observer *>::iterator i = _observers->begin();
    for (; i != _observers->end(); ++i)
        (*i)->Update();
}

void Subject::notify(string message) {
    list<Observer *>::iterator i = _observers->begin();
    for (; i != _observers->end(); ++i)
        (*i)->Update(message);
}

void Subject::notify(int cardNumber) {
    list<Observer *>::iterator i = _observers->begin();
    for (; i != _observers->end(); ++i)
        (*i)->Update(cardNumber);
}


