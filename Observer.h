//
// Created by client on 2018-11-14.
//

#pragma once
#include <string>


//Observer class to a subject that will be looking at a given aspect of the subject, logging and updating the given information that will be passed on or displayed to the user.
class Observer {

public:

    virtual ~Observer(); //Observer destructor.

    virtual void Update() = 0; //Default update method that will keep track of or pass on some information about a subject.

    virtual void Update(std::string message) = 0; //Update method that will display any changes to the information being tracked by the observer.

    virtual void Update(int cardNumber) = 0; //Update method that will display any changes to the information being tracked by the observer.

protected:

    Observer(); //Observer constructor.
};
