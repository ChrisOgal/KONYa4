//
// Created by client on 2018-10-27.
//

#include "GamePieces.h"
#include <iostream>

using namespace std;

//Token Class

Token::Token() {
    name = "";
}

Token::Token(string aName) {
    name = aName;
}


string Token::getName() {
    return string();
}

void Token::setName(string value) {
    name = value;
}

Token:: ~Token() {
    //TODO implement destructor
}

void Token::toString() {
    cout << name << " Token. " << endl;

}


//Card Class

Card::Card() {
    cost = -1;
    howToPlay = "";
    effect = "";
}

Card::Card(int aCost, string keepOrDiscard, string anEffect) {
    cost = aCost;
    howToPlay = keepOrDiscard;
    effect = anEffect;
}

int Card::getCost() const {
    return cost;
}

string Card::getHowToPlay() {
    return howToPlay;
}

string Card::getEffect() {
    return effect;
}

void Card::setCost(int number) {
    cost = number;
}

void Card::setHowToPlay(string value) {
    howToPlay = value;
}

void Card::setEffect(string value) {
    effect = value;
};


//To output the Card attributes
void Card::toString() const {
    cout << "Energy Cubes: " << getCost() << endl
         << "It's a " << howToPlay << " Card" << endl
         << effect << endl;
}

Card:: ~Card() {
    //TODO add destructor
}

//Tile Class

Tile::Tile()
{
    name = "";
    type = "";
    durability = -1;
    reward = -1;
    destroyed = false;

}

Tile::Tile(string aName, string aType, int startDurability, int startReward) {

    name = aName;
    type = aType;
    durability = startDurability;
    reward = startReward;
    destroyed = false;
};


//To output Tile attributes
void Tile::toString() {
    cout << "symbol = " << name << ", durability = " << durability << ", reward = " << reward << endl;
}

void Tile::changeToUnit(int initialDurability)
{
    setType("Unit");

    switch (initialDurability) {
        case 1: setName("Infantry"); setDurability(1); setReward(1); break;
        case 2: setName("Jet"); setDurability(3); setReward(2); break;
        case 3: setName("Tank"); setDurability(4); setReward(3); break;
    }

}

int Tile::destroyHighRise(int number){
    int durabilityStart = durability;
    for (int i = 0; i < number; i++){
        durability--;
        if (durability == 0) break;
        }

    if(durability == 0) {
        changeToUnit(durabilityStart);
        Message::confirmDestruction();
        this->toString();
        cout << endl;
        return reward;
    }

    return 0;

}

int Tile::destroyPowerPlant(int number){
    int durabilityStart = durability;
    for (int i = 0; i < number; i++){
        durability--;
        if(durability == 0) {
            changeToUnit(durabilityStart);
            Message::confirmDestruction();
            cout << endl;
            return reward;
        }
    }

    return 0;

}

int Tile::destroyHospital(int number){
    int durabilityStart = durability;
    for (int i = 0; i < number; i++){
        durability--;
        if(durability == 0) {
            Message::confirmDestruction();
            cout << endl;
            changeToUnit(durabilityStart);
            return reward;
        }
    }

    return 0;
}

int Tile::destroyTank(int number){
    for (int i = 0; i < number; i++){
        durability--;
        if(durability == 0) {
            destroyed = true;
            cout << "Unit destroyed!" << endl;
            cout << endl;
            return reward;
        }
    }

    return 0;

}

int Tile::destroyJet(int number){
    for (int i = 0; i < number; i++){
        durability--;
        if(durability == 0) {
            destroyed = true;
            cout << "Unit destroyed!" << endl;
            cout << endl;
            return reward;
        }
    }

    return 0;

}

int Tile::destroyInfantry(int number){
    for (int i = 0; i < number; i++){
        durability--;
        if(durability == 0) {
            destroyed = true;
            cout << "Unit destroyed!" << endl;
            cout << endl;
            return reward;
        }
    }

    return 0;

}

Tile:: ~Tile() {
    //TODO add destructor
}

vector<Card> LoadGamePieces::createCards() {

    vector<Card> cardDeck;

    for (int i = 0; i < NUM_CARDS; i++) {
        cardDeck.push_back(Card());
    }

    cardDeck[0] = Card(0, "DISCARD", "Gain 4 ENERGY CUBES and take 4 damage.");
    cardDeck[1] = Card(5, "KEEP", "If your results are 2 DESTRUCTION, you get an extra Attack, 4 you get an extra 2 Attacks, 6 you win the game");
    cardDeck[2] = Card(5, "KEEP", "Monsters you attack lose 1 VICTORY POINT. ");
    cardDeck[3] = Card(7, "KEEP", "You get 1 extra die.");
    cardDeck[4] = Card(10, "KEEP", "You get 1 extra die.");
    cardDeck[5] = Card(3,"KEEP", "You need only 2 Destruction to destroy a Jet.");
    cardDeck[6] = Card(3,"KEEP", "Heal 2 damage when you enter Manhattan.");


    return cardDeck;
}

vector<Tile> LoadGamePieces::createTiles() {

    const int NUM_HIGHRISE_BIG = 3;
    const int NUM_HIGHRISE_MEDIUM = 8;
    const int NUM_HIGHRISE_SMALL = 22;
    const int NUM_HOSPITAL_BIG = 3;
    const int NUM_HOSPITAL_SMALL = 3;
    const int NUM_POWERPLANT_BIG = 3;
    const int NUM_POWERPLANT_SMALL = 3;

    vector<Tile> tilesDeck;

    for (int i = 0; i < NUM_HIGHRISE_BIG; i++)
        tilesDeck.push_back(Tile("High-Rise", "building", 3, 3));

    for (int i = 0; i < NUM_HIGHRISE_MEDIUM; i++)
        tilesDeck.push_back(Tile("High-Rise", "building", 2, 2));

    for (int i = 0; i < NUM_HIGHRISE_SMALL; i++)
        tilesDeck.push_back(Tile("High-Rise", "building", 1, 1));

    for (int i = 0; i < NUM_HOSPITAL_BIG; i++)
        tilesDeck.push_back(Tile("Hospital", "building", 3, 3));

    for (int i = 0; i < NUM_HOSPITAL_SMALL; i++)
        tilesDeck.push_back(Tile("Hospital", "building", 2, 2));

    for (int i = 0; i < NUM_POWERPLANT_BIG; i++)
        tilesDeck.push_back(Tile("Power Plant", "building", 3, 3));

    for (int i = 0; i < NUM_POWERPLANT_SMALL; i++)
        tilesDeck.push_back(Tile("Power Plant", "building", 2, 2));

    return tilesDeck;
}

vector<Token> LoadGamePieces::createTokens() {

    vector<Token> tokenDeck;

    const int WEB_TOKENS = 13;
    const int JINX_TOKENS = 13;
    const int SOUVENIR_TOKENS = 5;
    const int CARAPACE_TOKENS = 15;

    for (int i = 0; i < WEB_TOKENS; i++)
        tokenDeck.push_back(Token("Web Token"));

    for (int i = 0; i < JINX_TOKENS; i++)
        tokenDeck.push_back(Token("Jinx Token"));

    for (int i = 0; i < SOUVENIR_TOKENS; i++)
        tokenDeck.push_back(Token("Souvenir Token"));

    for (int i = 0; i < CARAPACE_TOKENS; i++)
        tokenDeck.push_back(Token("Carapace Token"));

    return tokenDeck;

}



