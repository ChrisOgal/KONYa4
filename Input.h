//
// Created by client on 2018-11-21.
//

#pragma once
#include <iostream>

using namespace std;


//Used to validate various human input. Allows for cleaner reusable code.
struct Validate{

    static bool checkInput(int first, int last, int choice) {

        bool validChoice = true;

        //Checks if user input is non-numeric
        if (!cin.good()) {
            cin.clear();
            string ignore;
            cin >> ignore;
            validChoice = false;
        }

        //Checks if choice is valid
        if (choice < first || choice > last)
            validChoice = false;

        return validChoice;
    }
};