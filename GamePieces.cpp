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

    id = -1;
    cost = 1000;
    howToPlay = "";
    effect = "";

}

Card::Card (int idNum, int aCost, string keepOrDiscard, string anEffect) {

    id = idNum;
    cost = aCost;
    howToPlay = keepOrDiscard;
    effect = anEffect;
}

Card::Card( const Card& original)
{
    id = original.id;
    cost = original.cost;
    effect = original.effect;
    howToPlay = original.howToPlay;
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
    //_subject->detach(this);
}

void Card::addSubject(Player* newSubject) {

    _subject = newSubject;
    _subject->attach(this);
}

void Card::removeSubject(){
    _subject->detach(this);
}
void Card::Update() {

}

void Card::Update(std::string message) {

}

void Card::Update(int cardNumber) {

    switch(cardNumber){
        case 4:
            if(id == cardNumber) chinatownRegular(); break;
        case 18:
            if(id == cardNumber) nextStage(); break;
        case 21:
            if (id == cardNumber) superSpeed(); break;
        
        case 33:
            if (id == cardNumber) hunter(); break;

		case 37:
			if (id == cardNumber) kingOfQueens(); break;

        case 38:
            if(id == cardNumber) trophyHunter(); break;

        case 44:
            if (id == cardNumber) personalSpotlight(); break;
        case 45:
            if (id == cardNumber) leveler(); break;
        case 48:
            if(id == cardNumber) regeneration(); break;
    }

}

void Card::regeneration() {

    cout << "Regeneration card: " << endl;
    cout <<  effect << endl;
    Message::lifePointsBefore();
    cout << _subject->getLifePoints() << endl;
    _subject->changeLifePoints(1);
    Message::lifePointsAfter();
    cout << _subject->getLifePoints() << endl;
}

void Card::chinatownRegular() {
    cout << "Chinatown Regular card: " << endl;
    cout <<  effect << endl;
    Message::lifePointsBefore();
    cout << _subject->getLifePoints() << endl;
    _subject->changeLifePoints(2);
    Message::lifePointsAfter();
    cout << _subject->getLifePoints() << endl;
}

void Card::superSpeed(){

    cout << "Super Speed card: " << endl;
    cout <<  effect << endl;
    _subject->askMoveSuperSpeed();

}

void Card::nextStage() {

    cout << "Next Stage card: " << endl;
    cout <<  effect << endl;

    int victoryPointsStart = _subject->getVictoryPoints();

    Message::victoryPointsBefore();
    cout << _subject->getVictoryPoints() << endl;
    _subject->changeVictoryPoints(-(_subject->getVictoryPoints()));
    Message::victoryPointsAfter();
    cout << _subject->getVictoryPoints() << endl;

    if(victoryPointsStart > 0) {
        bool valid = true;
        int answer;

        do {
            cout << "Enter 1 if you want to gain Energy Cubes, enter 0 if you want to Heal: " << endl;
            cin >> answer;
            valid = Validate::checkInput(0, 1, answer);
        } while (!valid);

        if (answer == 1) {
            Message::energyCubesBefore();
            cout << _subject->getEnergyCubes() << endl;
            _subject->changeEnergyCubes(victoryPointsStart);
            Message::energyCubesAfter();
            cout << _subject->getEnergyCubes() << endl;
        }

        if (answer == 0) {

            Message::lifePointsBefore();
            cout << _subject->getLifePoints() << endl;
            _subject->changeLifePoints(victoryPointsStart);
            Message::lifePointsAfter();
            cout << _subject->getLifePoints() << endl;
        }
    }

}

void Card::trophyHunter() {

    cout << "Trophy Hunter card: " << endl;
    cout <<  effect << endl;
    Message::victoryPointsBefore();
    cout << _subject->getVictoryPoints() << endl;
    _subject->changeVictoryPoints(1);
    Message::victoryPointsAfter();
    cout << _subject->getVictoryPoints() << endl;

}

void Card::leveler()
{
    cout << "Leveler card: " << endl;
    cout << effect << endl;
    Message::victoryPointsBefore();
    cout << _subject->getVictoryPoints() << endl;
    _subject->changeVictoryPoints(1);
    Message::victoryPointsAfter();
    cout << _subject->getVictoryPoints() << endl;
}
void Card::hunter()
{
    cout << "Hunter card: " << endl;
    cout << effect << endl;
    Message::lifePointsBefore();
    cout << _subject->getLifePoints() << endl;
    _subject->changeLifePoints(1);
    Message::lifePointsAfter();
    cout << _subject->getEnergyCubes() << endl;
}
void Card::kingOfQueens()
{
    cout << "King Of Queens card: " << endl;
    cout << effect << endl;
    Message::energyCubesBefore();
    cout << _subject->getEnergyCubes() << endl;
    Message::lifePointsBefore();
    cout << _subject->getLifePoints() << endl;
    if (_subject->getCurrentPosition()->getName().compare("Queens") == 0)
    {
        _subject->changeEnergyCubes(1);
        _subject->changeLifePoints(1);
    }
    Message::energyCubesAfter();
    cout << _subject->getEnergyCubes() << endl;
    Message::lifePointsAfter();
    cout << _subject->getLifePoints() << endl;
}
void Card::personalSpotlight()
{
    cout << "Personal Spotlight card: " << endl;
    cout << effect << endl;
    Message::victoryPointsBefore();
    cout << _subject->getVictoryPoints() << endl;
	_subject->changeVictoryPoints(1);
    Message::victoryPointsAfter();
    cout << _subject->getVictoryPoints() << endl;
}
void Card::shadowDouble()
{
    cout << "Shadow Double card: " << endl;
    cout << effect << endl;
}


int Card::getId() {
    return id;
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
            this->toString();
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
            this->toString();
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

    cardDeck[0] = Card(48, 5,"KEEP", "Heal 1 damage at the start of your turn");
    cardDeck[1] = Card(4, 3,"KEEP", "Heal 2 damage when you enter Manhattan.");
    cardDeck[2] = Card(38, 5, "KEEP", "Gain 1 VICTORY POINT each time you destroy a Unit.");
    cardDeck[3] = Card(18, 4, "DISCARD", "Lose all your VICTORY POINTS. Gain 1 ENERGY CUBE or heal 1 damage for each VICTORY POINT you lost this way");
    cardDeck[4] = Card(21, 4, "KEEP", "You have a free move before rolling the dice");
    cardDeck[5] = Card(33, 5, "KEEP", "Heal 1 damage each time you destroy an infantry");
    cardDeck[6] = Card(37, 5, "KEEP", "Gain 1 ENERGY CUBE and heal 1 damage when you start your turn in Queens. ");
    cardDeck[7] = Card(44, 5, "KEEP", "Gain 1 VICTORY POINT each turn you rolled at least 1 Celebrity.");
    cardDeck[8] = Card(45, 5, "KEEP", "Gain 1 VICTORY POINT each turn that you destroy at least one Building. ");
    cardDeck[9] = Card(64, 12, "KEEP", "Whenever you attack, you deal double damage. ");

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



