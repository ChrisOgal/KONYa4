//
// Created by client on 2018-10-27.
//

#pragma once

#include <string>
#include <vector>
#include "Output.h"
#include "Observer.h"
#include "Player.h"


using namespace std;

class Token {

public:

    Token();
    Token(string aName);
    ~Token();

    string getName();
    void setName(string value);

    void toString();

private:
    string name;
};

class Player;

//Cards that will provide the user with different advantages and disadvantages if owned and used.
class Card: public Observer {

public:

    //Constructors
    Card();
    Card(int idNum, int aCost, string keepOrDiscard, string anEffect);
    Card( const Card& original);
    ~Card();

    //Accessors
    int getCost() const;
    string getHowToPlay();
    string getEffect();
    int getId();

    //Mutators
    void setCost(int number);
    void setHowToPlay(string value);
    void setEffect(string value);

    void toString() const;


    void addSubject(Player* newSubject);
    void removeSubject();
    void Update();
    void Update(std::string message);
    void Update(int cardNumber);

    void regeneration();
    void chinatownRegular();
    void superSpeed();
    void nextStage();
    void trophyHunter();

private:

    int id;
    int cost; //in energy cubes
    string howToPlay; //KEEP OR DISCARD
    string effect; //The power that the player gets from the card.
    Player* _subject;

};


class Tile {

public:

    //Constructors
    Tile();
    Tile(string aName, string aType, int startDurability, int startReward);
    ~Tile();

    //Accessors
    inline string getName() { return name; }
    inline string getType() { return type; }
    inline int getDurability() { return durability; }
    inline int getReward() { return reward; }
    bool isDestroyed() const {
        return destroyed;
    }

    //Mutators
    inline void setName(string value) { name = value; }
    inline void setType(string value) { type = value; }
    inline void setDurability(int newDurability) { durability = newDurability; }
    inline void setReward(int newReward) { reward = newReward; }
    void setDestroyed(bool destroyed) {
        Tile::destroyed = destroyed;
    }

    //Other methods
    void toString();
    void changeToUnit(int initialDurability); // Changes to the appropriate second unit on the tile if the first unit is destroyed. 
    
	//Various destruction functions for the various buildings and vehicles on tiles.
	int destroyHighRise(int number);
    int destroyPowerPlant(int number);
    int destroyHospital(int number);
    int destroyTank(int number);
    int destroyJet(int number);
    int destroyInfantry(int number);

private:
	//Data members that show the tile's name, building or vehicle type, how many destruction points are needed to destry it and the reward for destroying it.
    string name;
    string type;
    int durability;
    int reward;
    bool destroyed;
};



//An initializer for the various game pieces that will be used. Default values are given to ensure the same number of relevant pieces are generated each time.
struct LoadGamePieces {

    const static int NUM_CARDS = 64;
    const static int NUM_TILES = 45;
    const static int NUM_TOKENS = 46;


    static vector <Card> createCards();
    static vector <Tile> createTiles();
    static vector <Token> createTokens();

};