//
// Created by client on 2018-10-27.
//

#include <fstream>
#include "Map.h"


Borough::Borough() {
    name = "";

}

Borough::Borough(string& aName) {
    name = aName;

}
string Borough::getName(){
    return name;
}


void Borough::setName(string aName) {
    name = aName;
}

Borough::~Borough() {
    //TODO create destructor
};

ostream& operator << (ostream& strm, const Borough& aBorough) {
    return strm << aBorough.name << endl;
}




//SUBGRAPH

Subgraph::Subgraph() {
    maxOwners = MAX_OWNERS_DEFAULT;
    isMain = false;
    isLast = false;
}

vector <Borough> Subgraph::getRegion() {
    return region;
}

vector <Player*> Subgraph::getOwners() {
    return owners;
}

vector <Tile*> Subgraph::getTiles() {
    return tiles;
};

int Subgraph::getMaxOwners() {
    return maxOwners;
}

void Subgraph::setOwners(vector <Player*> playersVector) {
    owners = playersVector;
}
void Subgraph::setTiles(vector <Tile*> tilesVector) {
    tiles = tilesVector;
}

//Adds a tile to the Borough
void Subgraph::addTile(Tile* aTile) {
    tiles.push_back(aTile);
}

//Removes a tile from the Borough
void Subgraph::removeTile() {
    if (tiles.size() > 0)
        tiles.erase(tiles.begin());
    else
        cout << "There is nothing to remove." << endl;
}
//Add a Monster to a Borough
void Subgraph::addOwner(Player *aPlayer) {
    owners.push_back(aPlayer);
}


void Subgraph::removeOwner(Player *aPlayer) {

    for (int i = 0; i < owners.size(); i++) {
        if (owners[i]->getMonster()== aPlayer->getMonster())
          owners.erase(owners.begin() + i);
    }
    gameMap->outputState();
}


//Prints attributes
void Subgraph::toString() {
    cout << "-----> " << name << ": \n" << endl << "Owned by: \n" << endl;
    if (owners.size() == 0)
        cout << "no one.\n" << endl;
    else {
        for (int i = 0; i < owners.size(); i++) {
            owners[i]->toString();
            cout << endl;
        }
    }



    cout << "It has " <<  countTiles() << " tiles on it. " << endl;

    for (int i = 0, j = 0; i < tiles.size() && j < VISIBLE_TILES;i++) {
        if(!(tiles[i]->isDestroyed())) {
            tiles[i]->toString();
            j++;
        }
    }

}

int Subgraph::countTiles(){

    int count = 0;
    for (int i = 0; i < tiles.size(); i++){
        if(!(tiles[i]->isDestroyed())) {
            count++;
        }
    }
    return count;
}

void Subgraph::attackOwners(int number)
{
    for (int i = 0; i < owners.size(); i++) {

        cout << owners[i]->getMonster() << endl;
        Message::lifePointsBefore();
        cout << owners[i]->getLifePoints() << endl;

        owners[i]->changeLifePoints(number);

        Message::lifePointsAfter();
        cout << owners[i]->getLifePoints() << endl << endl;

        if (owners[i]->getCurrentPosition()->getIsMain()) {
                owners[i]->askMove();
        }
    }
}

void Subgraph::setEdge(Subgraph* value)
{
    edge = value;
}


int Subgraph::countUnits() {

    int count = 0;
    int countUnits = 0;

    for (int i = 0; i < tiles.size() && count != 3; i++){
        if(!tiles[i]->isDestroyed()){
            count++;
            if(tiles[i]->getType() == "Unit")
                countUnits++;
        }
    }

    cout << "Units in " << name << " : " << countUnits << endl;

    return countUnits;
}

void Subgraph::ouch() {
    for (int i = 0; i < owners.size(); i++){
        owners[i]->changeLifePoints(-countUnits());
        cout << endl << owners[i]->getMonster() << " loses as many life points\n" << endl;
		Message::lifePointsAfter();
		cout << owners[i]->getMonster() << " " << owners[i]->getLifePoints() << endl << endl;
    }

}

Subgraph::~Subgraph() {
//TODO implement destructor
}





//Files stored in a directory
const string MapSelection::filesList[NUM_FILES] =
        { "NewYork.map.txt","Montreal.map.txt","BadNewYork1.map.txt","BadNewYork2.map.txt", "BadMontreal.map.txt" };

//Allows a player to select a map from a list of files
string MapSelection::selectMap() {

    int choice;
    bool validChoice;
    do {
        cout << "Please select a map (enter a number): \n";
        //Outputs the file names
        for (int i = 0; i < NUM_FILES; i++) {
            cout << "[" << i << "]" << " " << MapSelection::filesList[i] << endl;
        }
        cin >> choice;
        validChoice = true;

        //Checks if user input is non-numeric
        if (!cin.good()) {
            cin.clear();
            string ignore;
            cin >> ignore;
            validChoice = false;
            continue;
        }
        //Checks if choice is valid
        if (choice < 0 || choice > NUM_FILES)
            validChoice = false;

    } while (!validChoice);

    return MapSelection::filesList[choice];
}

vector<Subgraph> MapSelection::createMap() {

    MapLoader loader;
    bool isValid = true;
    do {
        string filename = selectMap();
        isValid = loader.loadMap(filename);
    } while (!isValid);

    return loader.map;
}





MapLoader::MapLoader() {}

bool MapLoader::loadMap(const string &file) {

    ifstream inputStream(file); //opens file and attaches to a stream

    //To check if the failbit or hardfail flag is set
    if (inputStream.fail()) {
        cout << "An operation on the stream has failed or an unrecovered error has occurred. "
             << "The program will exit." << endl;
        exit(1);
    }

    //Reads and stores the vertices
    string value1, value2;

    Subgraph tempSubgraph;

    while (!inputStream.eof()) {
        getline(inputStream, value1, ':');
        tempSubgraph.setName(value1);
        vector<Borough> temp;
        while (true) {
            getline(inputStream, value2, ',');
            if (value2 == "END") {
                inputStream.ignore(); //To skip the newline character
                break;
            }
            temp.push_back(Borough(value2));//creates a new Borough object and adds it to the array
        }
        tempSubgraph.setRegion(temp);
        map.push_back(tempSubgraph);
    }


    //Checks for missing edges
    bool validMap = checkDisconnect();

    //If the map isn't valid
    if (!validMap) {
        map.clear(); //removes all the vertices
        inputStream.close(); //closes the file
        cout << "The map is not a connected graph." << endl
             << "The chosen map is invalid.\n" << endl;
        return false;

    }

    //Checks for duplicate regions
    validMap = checkDuplicate();

    //If the map isn't valid
    if (!validMap) {
        map.clear(); //removes all the vertices
        inputStream.close(); //closes the file
        cout << "There are duplicate vertices on the map." << endl
             << "The chosen map is invalid.\n" << endl;
        return false;

    }

    //If the map is valid
    inputStream.close();
    return true;
}

bool MapLoader::checkDisconnect() {

    for (int i = 0; i < map.size(); i++) {
        if (map[i].getName().empty()) {
            return false;
        }
    }
    return true;
}

bool MapLoader::checkDuplicate() {
    for (int i = 0; i < map.size() - 1; i++) {
        for (int j = i + 1; j < map.size(); j++) {
            if (map[i].getName() == map[j].getName())
                return false;
        }
    }
    return true;
}

MapLoader::~MapLoader() {
    //TODO implement destructor

}





Map::Map() {

    aMap = MapSelection::createMap();
    aMap[MAIN_ZONE].setIsMain(true);
    aMap[NON_MAIN_LAST].setIsLast(true);

    for (int i = 0; i < aMap.size()-1; i++)
        aMap[i].setEdge(&aMap[i + 1]);
    aMap[aMap.size() - 1].setEdge(&aMap[0]);

    for (int i = 0; i < aMap.size()-1; i++)
        aMap[i].setGameMap(this);
}

void Map::outputMap() {
    for (int i = 0; i < aMap.size(); i++) {
        cout << aMap[i].getName() << ": ";
        cout << "Edge: " << aMap[i].getEdge()->getName() << ", ";
        for (int j = 0; j < aMap[i].getRegion().size(); j++)
            cout << aMap[i].getRegion()[j].getName() << ", ";
        cout << endl;
    }
    cout << aMap.size();
}

int Map::size() {
    return aMap.size();
}

//Outputs the available Boroughs
vector<int> Map::outputAvailableBoroughs() {
    vector<int> validChoices;
    cout << "The available Boroughs are: \n" << endl;
    for (int i = NON_MAIN_FIRST; i <= NON_MAIN_LAST; i++) {
        if (aMap[i].getOwners().size() < aMap[i].getMaxOwners()) {
            validChoices.push_back(i);
            cout << "[" << i << "] ";
            aMap[i].toString();
            cout << endl;
        }
    }

    return validChoices;
}

void Map::assignBorough(int indexBorough, Player* aPlayer) {
    //To assign a Player to a Borough
    aMap[indexBorough].addOwner(aPlayer);
    //To assign a Borough to a Player
    aPlayer->setRegion(&aMap[indexBorough]);

}

void Map::pickBorough(Player* aPlayer) {

    vector<int> choices = outputAvailableBoroughs();

    bool valid;
    int input;
    do {
        cout << "Please pick your Borough (enter a number) >> ";
        cin >> input;
        valid = Validate::checkInput(choices.front(), choices.back(), input);
    } while (!valid);

    assignBorough(input, aPlayer);

}

void Map::outputState() {
    notify();
}

void Map::addTiles(vector<Tile> &tiles) {

    int count = 0;

    const int TILES_PER_BOROUGH = 9;

    for (int i = 0; i < aMap.size(); i++) {
        for (int j = 0; j < TILES_PER_BOROUGH; j++)
            aMap[i].addTile(&tiles[count++]);
    }
}

void Map::lessThanFourPlayers() {
    aMap[MAIN_ZONE].setMaxOwners(aMap[MAIN_ZONE].getMaxOwners() - 1);
}

Subgraph *Map::mainZone() {
    return &aMap[MAIN_ZONE];
}

Map::~Map(){}




void MapObserver::Update() {
    display();
}

void MapObserver::display() {

    cout << "* * * * * * * * * * G A M E   S T A T E * * * * * * * * * *\n" << endl;
    vector <Subgraph> gameMap = _subject->getMap();
    for (int i = 0; i < gameMap.size(); i++) {
        gameMap[i].toString();
        cout << endl;
    }

    for (int i = 0; i < gameMap.size(); i++){
        for(int j = 0; j < gameMap[i].getOwners().size(); j++){

            for (int k = 0; k < gameMap[i].getOwners()[j]->getVictoryPoints(); k++){
                cout << "=";
            }
            cout << "  " << gameMap[i].getOwners()[j]->getMonster() << endl;
        }
    }
    cout << "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n" << endl;
}

MapObserver::MapObserver() {
};

MapObserver::MapObserver(Map* observed) {
    _subject = observed;
    _subject->attach(this);

}

MapObserver::~MapObserver() {
    _subject->detach(this);

};


void MapObserver::Update(std::string message){
}

void MapObserver::display(std::string message) {
}

void MapObserver::Update(int cardNumber) {
}
