#pragma once

#include <string>
#include <vector>
#include<iostream>
#include <random>

#include "Strategy.h"


using namespace std;

class Strategy;


//Die class that provides an int that is linked to a game power. Used to keep track of these powers and provides a basis for rolling the game die.
class Die {

public:

    Die(); //Default constructor with a 0 face.
    Die(int value); //Constructor with a set value on the face of the die.

	//Die data member getters.
    int getValue();
    bool isPlayed() const;

	//Die data memver setters
    void setValue(int newValue);
    void setPlayed(bool played);


private:
	//Die data members. Int refers to the face value and played is set to mark die that have been resolved.
    int value;
    bool played;
};




//Takes in the 6 game die and allows for various functions that involve the die including deciding who the game order and possible rolls and rerolls.
class DiceRollingFacility {


public:

    const string faces[6] = { "Energy", "Attack", "Destruction", "Heal", "Celebrity", "Ouch!" }; //The six powers of the game die.

    DiceRollingFacility();//Default constructor.
    DiceRollingFacility(int number);
    ~DiceRollingFacility();//Destructor.

	//Getters for the dice rolling facility data members.
    vector<Die> &getDice() {
        return dice;
    }
    int getNeedHeal() const;

	//Setters for the dice rolling facility data members.
    void setDice(vector<Die> newDice);
    void setRollStrategy(Strategy* chosenStrategy);
    void setNeedHeal(int needHeal);
    void setDice();

	
    void reRoll(int number);//Reroll function with the number of die the player wishes to reroll.
    void display();//Displays the game die's current state.

	//Various counters for each of the provided powers.
    int countAttacks();
    int countDestruction();
    int countEnergy();
    int countHeal();
    int countCelebrity();
    int countOuch();


    int size();
    int valueAt(int index);// returns the value of a die at the given index of its vector.
    void removeEffect(int effect);// Removes the dice' effect after it has been resolved.
    bool isEmpty();
    void resetDice();//reset the dice for a new roll


private:
	//Data members.
    vector <Die> dice;
    Strategy* rollStrategy;
    int needHeal;
};

