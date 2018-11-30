#pragma once

#include "Player.h"
#include <string>
#include "Input.h"

using namespace std;

class Die;




// Abstract Strategy Class
class Strategy {

public:

    virtual int isReroll(int numberAttack, int numberHeal, int lifePoints)=0;  //Determines the dice that will be rerolled. Is to be implemented to different strategies based on max attacks for aggressive and max healing for moderate. Human players will be unaffected.
    virtual void rollDice(vector<Die>* dice)=0; //The rolling dice function that will be adapted to the provided game strategies.
    virtual int resolveDiceStrategy(vector<Die>* dice)=0; //The resolve dice strategy that will favor attack and destruction for aggressive players and healing and energy cubes for moderate players. Human players will be unaffected. 
    virtual bool isMovingStrategy()=0; //The move a player makes will be determined by the given strategy and will be implemented for each type of player. Human players have freedom to chooose their own valid moves.
    virtual int getInputForBuyCard(bool value)=0; //Attempts to see if a player wants to and can buy cards. Will then translate to buying cards that favor the given player's strategy. Human players will have free reign.
};




//Human strategy allows the human player to make any valid moves they see fit. Implemented to give the user as many choices as possible.
class Human : public Strategy {

public:

    int isReroll(int numberAttack, int numberHeal, int missingHealNum);
    void rollDice(vector<Die>* dice);
    int resolveDiceStrategy(vector<Die>* dice);
    bool isMovingStrategy();
    int getInputForBuyCard(bool value);

};




//Aggressive strategy that will aim to capitalize on maximum attack and destruction before anything else.
class Aggressive: public Strategy {

public:

    int isReroll(int numberAttack, int numberHeal, int missingHealNum);
    void rollDice(vector<Die>* dice);
    int resolveDiceStrategy(vector<Die>* dice);
    bool isMovingStrategy();
    int getInputForBuyCard(bool value);
};




//Moderate player strategy that will aim to capitalize on maximum healing and energy cubes, aiming to outlast opponents as opposed to attacking.
class Moderate : public Strategy {

public:

    int isReroll(int numberAttack, int numberHeal, int missingHealNum);
    void rollDice(vector<Die>* dice);
    int resolveDiceStrategy(vector<Die>* dice);
    bool isMovingStrategy();
    int getInputForBuyCard(bool value);

};





