//
// Created by client on 2018-10-27.
//

#pragma once
#include <iostream>
#include <string>
#include "GamePieces.h"
#include "Map.h"
#include "Strategy.h"
#include "DiceRollingFacility.h"

using namespace std;

class Subgraph;
class DiceRollingFacility;
class DiceEffectsObserver;
class Strategy;


//Player class. the main part of the game that will keep track of a player, their health, victory points and what they own at each and every stage of the game.
class Player: public Subject

{

public:

    static int count;

    Player();//Default constructor. 
    //Destructors
    ~Player();

    //Accessors
    string getMonster();
    DiceRollingFacility* getDice();
    Subgraph* getCurrentPosition();
    vector <Card> getCurrentCards();
    vector <Token*> getPlayerTokens;
    int getEnergyCubes();
    inline int getZoneNumber() { return zoneNumber; }
    bool isHasCelebrity() const {
        return hasCelebrity;
    }
    bool isHasStatueOfLiberty() const;
    bool isHasShadowDouble() const { return hasShadowDouble; }
    bool isLost() const;
    int getVictoryPoints();
    int getLifePoints();
    vector <Token> getMonsterTokens();
	//bool hasCard(Card aCard);



    //Mutators
    void setMonster(string newMonster);
    void setDice(DiceRollingFacility* newDice);
    void setRegion(Subgraph* newRegion);
    void setCurrentCards(vector <Card> aVector);
    void setPlayerTokens(vector <Token*> aVector);
    void setEnergyCubes(int number);
    inline void setZoneNumber(int number) { zoneNumber = number; }
    void setHasCelebrity(bool hasCelebrity) {
        Player::hasCelebrity = hasCelebrity;
    }
    void setHasStatueOfLiberty(bool hasStatueOfLiberty);
    void setHasShadowDouble(bool ownsShadowDouble);
    void setGameCards(vector<Card> *gameCards);
    void setLost(bool lost);
    void setStrategy(Strategy* chosenMentality);//Strategy selector
    void setVictoryPoints(int number);
    void setLifePoints(int number);
    void setMonsterTokens(vector <Token> aVector);
	void changeEnergyCubes(int number);
	void changeVictoryPoints(int number);
	void changeLifePoints(int number);


    //Other methods
    void toString();

    void startTurn();
    void rollDice();//player rolls the game die and will later resolve them.

	//Various methods to resolve the game die as per what the player rolled.
    void resolveTheDice();
    void resolveEnergy();
    void resolveHeal();
    void resolveDestruction();
    void resolveAttack();
    void resolveCelebrity();
    void resolveOuch();
    
	//Functions providing the player with the ability to move as per the designated moves from the game rules. Some moves may be forced to due to factors decided elsewhere in the game.
	void move();
    void askMove();
    void askMoveSuperSpeed();

	//manhattan move functions. main refers to mahattan as it is the main borough in the  game.
    void moveToMain();
    bool mainFree();

    bool isMoving(); // True if the player is currently moving.
    
	void buyCard(); //Purchase of game cards as per the energy cubes owned.
    void checkHeal(); 
    void addCard(Card aCard);//Adds the given card to player's personal deck.
    void addMonsterToken(Token newToken); //Adds the given token to player's monster card.
    void removeMonsterToken();//Removes the given token to player's monster card.
    void firstRoll();//First roll to determine the game order.
    int attacksRolled();//Returns the number of attacks rolled by the player.
	



private:
	//Player class data members.
    string monster;
    DiceRollingFacility* playerDice;
    DiceEffectsObserver * diceObserver;
    Subgraph* currentPosition;
    vector <Card> currentCards;
    vector <Card>* gameCards;
    vector <Token*> playerTokens;
    int energyCubes;
    int zoneNumber;
    Strategy* mentality;
    bool hasCelebrity;
    bool hasStatueOfLiberty;
    bool hasShadowDouble;
    int victoryPoints;
    int lifePoints;
    vector <Token> monsterTokens;
    bool lost;

};




//Determines the number of players for the game places them in a player vector.
class NumPlayersSelector{

public:

    const static int MIN_PLAYERS = 2;
    const static int MAX_PLAYERS = 6;

    static vector<Player> select();

private:
    static int selectNumPlayers();

};




//Creates the assigned number of players from the value passed in the NumPlayerSelector class
class PlayersCreation {

public:

    PlayersCreation();
    ~PlayersCreation();

    void createPlayers(int number);

    vector<Player> gamePlayers;

};




