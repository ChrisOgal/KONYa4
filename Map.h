//
// Created by client on 2018-10-27.
//

#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include "Player.h"
#include "GamePieces.h"
#include "Subject.h"
#include "Observer.h"

using namespace std;

class Player;
class Map;
class Card;
class Tile;
class Token;

const static int MAIN_ZONE = 0;
const static int NON_MAIN_FIRST = 1;
const static int NON_MAIN_LAST = 4;





class Borough {

public:

    //Constructors
    Borough();
    Borough(string &aName);
    //Destructor
    ~Borough();

    //Accessors
    string getName();

    //Mutators
    void setName(string aName);


private:

    string name;

    friend ostream &operator<<(ostream &strm, const Borough &aBorough);

};




//Subgraph is especcially essential for Manhattan that contains mini-regions within it.
class Subgraph {

public:
	//Constant values as decided by the game rules.
    const int static MAX_OWNERS_DEFAULT = 2;
    const int static VISIBLE_TILES = 3;

    Subgraph(); //Subgraph Constructor.
    ~Subgraph(); //Subgraph Destructor.

	//Data member getters.
    vector <Borough> getRegion();
    vector<Player *> getOwners();
    vector<Tile *> getTiles();
    inline string getName() { return name; }
    int getMaxOwners();
    bool getIsMain() { return isMain; }
    bool getIsLast() { return isLast; }
    inline Subgraph* getEdge() { return edge;}
    inline Map* getGameMap() {return gameMap;}


	//Data member setters
    void setOwners(vector<Player *> playersVector);
    void setTiles(vector<Tile*> tilesVector);
    inline void setMaxOwners(int number) { maxOwners = number; }
    inline void setName(string value) { name = value; }
    inline void setRegion(vector<Borough> value) { region = value; }
    inline void setIsMain(bool value) { isMain = value; }
    inline void setIsLast(bool value) { isLast = value; }
    inline void setGameMap(Map* aMap) {gameMap = aMap;}

    //Other functions
    void addTile(Tile *aTile); //Adds appropriate tiles to the assigned region.
    void removeTile(); //Deletes last element

	//Manages the players allowed to be on or off the given region.
    void addOwner(Player *aPlayer);
    void removeOwner(Player *aPlayer);
    void toString();
    int countTiles();//counts the number of tiles in the borough

    void attackOwners(int number);//Provides the attack points to all monsters in the given region as per game rules. Usually used mostly for Manhattan or due to ouch! powers.
    void setEdge(Subgraph* value);
    int countUnits(); // Returns the number of units in the area.
    void ouch();//implements the ouch power on the player in the given region.

private:
	//Subgraph data members
    vector<Borough> region;

    string name;
    int maxOwners;
    vector<Player*> owners;
    vector<Tile*> tiles;
    Subgraph* edge;
    bool isMain;
    bool isLast;
    Map* gameMap;

};




//Simple class to select and validate the file that has a map stored in it
class MapSelection {

public:
	//Allows for a maximum of five different game maps file possibilities. 
    const static int NUM_FILES = 5;
    const static string filesList[NUM_FILES];

    static vector<Subgraph> createMap(); //reads the vectors in a given map file and creates a vector that stores the various values of the various subgraph regions.

private:

    static string selectMap();
};




//Takes in the information from a selected map file and returns a playable game map.
class MapLoader {

public:

    MapLoader();//Constructor
    ~MapLoader();// Destructor

    bool loadMap(const string &filename); //Checks if the game map has been initialized properly.
    bool checkDisconnect(); //Ensures there are no islands on the game map.
    bool checkDuplicate(); //Ensures each region is created exactly once.

    vector<Subgraph> map; //The map that will be validated by this class.
};




//Map class that will be a subject for some pbservers and maintains the game information of players' positions.
class Map : public Subject {

public:

    Map(); //Constructor.
    ~Map(); //Destructor.

    vector<Subgraph> getMap() { return aMap; } // Returns the game map.

	//return the current state of the map and its regions
    void outputMap();
    void outputState();


    int size();//returns the number of regions in the map.
    vector<int> outputAvailableBoroughs();//returns any unoccupied regions in the map.
    void assignBorough(int indexBorough, Player* aPlayer); //Assigns the given region to player passed in the parameters.
    void pickBorough(Player* aPlayer);//Allows the player to choose a desired region according to game rules.
    void addTiles(vector<Tile> &tiles);
    void lessThanFourPlayers();
    Subgraph* mainZone();

private:

    vector <Subgraph> aMap;
};




//Map observer implemented as per the instructions in the Observer.h file.
class MapObserver : public Observer {

public:

    MapObserver();
    MapObserver(Map* observed);
    ~MapObserver();

    void Update();
    void Update(string message);
    void Update(int cardNumber);

    void display();
    void display(string message);

private:

    Map * _subject;
};