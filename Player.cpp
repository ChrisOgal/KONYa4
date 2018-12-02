//
// Created by client on 2018-10-27.
//


#include "Player.h"
int Player:: count = 0;

Player::Player(){


    monster = "";
    playerDice = new DiceRollingFacility(6);
    currentPosition = NULL;
    //currentCards = NULL;
    gameCards = NULL;
    vector <Token*> playerTokens (0);
    energyCubes = 10; //TODO change to 0 after testing
    zoneNumber = 0;
    if(count % 3 == 0) setStrategy(new Human());
    else if(count % 3 == 1) setStrategy(new Moderate());
    else if(count % 3 == 2) setStrategy(new Aggressive());
    count++;
    hasCelebrity = false;
    hasStatueOfLiberty = false;
    victoryPoints = 0;
    lifePoints = 5; //TODO change to 10 after testing
    lost = false;

}

Player:: ~Player() {
    //TODO Implement
    for(std::vector<Token*>::iterator i = playerTokens.begin(); i != playerTokens.end(); ++i){
        delete (*i);
        }
}

void Player::setMonster(string newMonster)
{
    monster = newMonster;
}


void Player::setRegion(Subgraph* newRegion)
{
    currentPosition = newRegion;
}

void Player::setDice(DiceRollingFacility* newDice)
{
    this->playerDice = newDice;
}

void Player::setCurrentCards(vector<Card> aVector) {
    currentCards = aVector;
}

void Player::setPlayerTokens(vector<Token*> aVector) {
    playerTokens = aVector;
}

void Player::setEnergyCubes(int number) {
    energyCubes = number;
}

void Player::addCard(Card aCard)
{
    currentCards.push_back(aCard);
    currentCards.back().addSubject(this);

}

void Player::setStrategy(Strategy *chosenMentality)
{
    this->mentality = chosenMentality;
    playerDice->setRollStrategy(mentality);
}


string Player::getMonster()
{
    return monster;
}


Subgraph* Player::getCurrentPosition()
{
    return currentPosition;
}

DiceRollingFacility* Player::getDice()
{
    return playerDice;
}


vector <Card> Player::getCurrentCards() {
    return currentCards;
}

int Player::getEnergyCubes() {
    return energyCubes;
}

//Add/removes energy cubes from a player
void Player::changeEnergyCubes(int number) {
    energyCubes += number;
}

//To output Player attributes.
void Player::toString()
{
    cout << monster << ": victory points = " << victoryPoints <<", life points: " << lifePoints << endl;

    cout << "Currently in " << currentPosition->getRegion()[zoneNumber].getName();
    cout << endl << "Has " << energyCubes << " energy cubes." << endl;

    if (playerTokens.size() == 0)
        cout << "Has no tokens." << endl;
    else {
        cout << "Has these tokens: " << endl;
        for (int i = 0; i < playerTokens.size(); i++)
            playerTokens[i]->toString();
    }

    if (currentCards.size() == 0)
        cout << "Has no cards." << endl;
    else {
        cout << "Has these cards:" << endl;
        for (int i = 0; i < currentCards.size(); i++)
            currentCards[i].toString();
    }
}


//Adds/removes victory points
void Player::changeVictoryPoints(int number) {
    if (number < 0){
        for (int i = number; i < 0; i++) {
            if (victoryPoints == 0) break;
            victoryPoints--;
        }
    }
    else {
        for (int i = 0; i < number; i++) {
            if (victoryPoints == 20) break;
            victoryPoints++;
        }
    }
}

void Player::changeLifePoints(int number)
{
    if (number < 0){
        for (int i = number; i < 0; i++) {
            if (lifePoints == 0) break;
            lifePoints--;
        }
    }
    else {
        for (int i = 0; i < number; i++) {
            if (lifePoints == 10) break;
            lifePoints++;
        }
    }
}

void Player::startTurn() {

    notify(21);
    notify(48);

}
void Player::rollDice()

{
    playerDice->setDice();
    playerDice->reRoll(1);
}

void Player::firstRoll() {
    playerDice->setDice();
}

int Player::attacksRolled() {

    return(playerDice->countAttacks());
}

void Player::resolveTheDice() {

    checkHeal();

    while (!playerDice->isEmpty()) {

        playerDice->display();

        int answer = mentality->resolveDiceStrategy (&(playerDice->getDice()));

        switch (playerDice->valueAt(answer)) {
            case 0:
                cout << "- - - - Resolving Energy - - - -\n\n";
                resolveEnergy();
                playerDice->removeEffect(0);
                cout << "\n- - - - - - - - - - - - - - - - - \n";
                break;
            case 1:
                cout << "- - - - Resolving Attack - - - -\n";
                resolveAttack();
                playerDice->removeEffect(1);
                cout << "\n- - - - - - - - - - - - - - - - - \n";
                break;
            case 2:
                cout << "- - - - Resolving Destruction - - - -\n\n";
                resolveDestruction(); playerDice->removeEffect(2);
                currentPosition->getGameMap()->outputState();
                cout << "- - - - - - - - - - - - - - - - - \n";
                break;
            case 3:
                cout << "- - - - Resolving Heal - - - -\n\n";
                resolveHeal();
                playerDice->removeEffect(3);
                cout << "\n- - - - - - - - - - - - - - - - - \n";
                break;
            case 4:
                cout << "- - - - Resolving Celebrity - - - -\n\n";
                resolveCelebrity();
                playerDice->removeEffect(4);
                cout << "\n- - - - - - - - - - - - - - - - - \n";
                break;
            case 5:
                cout << "- - - - Resolving Ouch! - - - -\n\n";
                resolveOuch();
                playerDice->removeEffect(5);
                cout << "- - - - - - - - - - - - - - - - - \n";
                break;
        }
    }

    playerDice->resetDice();
}

void Player::resolveEnergy() {
    cout << "Number of energy cubes before: " << energyCubes << endl;
    changeEnergyCubes(playerDice->countEnergy());
    cout << "Your energy cubes increased by " << playerDice->countEnergy() << endl;
    cout << "Number of energy cubes after: " << energyCubes << endl;

    playerDice->removeEffect(0);
}

void Player::resolveAttack() {

    if (currentPosition->getIsMain()) {

        Subgraph *position = currentPosition->getEdge();

        while (position->getName() != currentPosition->getName()) {
            if (position->getIsMain());
            else {
                position->attackOwners(-(playerDice->countAttacks()));
            }
            position = position->getEdge();
        }
    }

    else {

        Subgraph *position = currentPosition->getEdge();

        while (position->getName() != currentPosition->getName()) {
            if (position->getIsMain()) {
                if(position->getOwners().size() == 0)
                    cout << "\nThere is no one to attack." << endl;
                else {
                    position -> attackOwners(-(playerDice->countAttacks()));
                }
            }
            position = position->getEdge();
        }
    }
}

void Player::resolveHeal() {

    Message::lifePointsBefore();
    cout << lifePoints << endl;

    if (!(currentPosition->getIsMain())) {
        if(lifePoints < 10)
            cout << "You gained " << playerDice->countHeal() << endl;
        else
            cout << "You are already at the maximum number of life points." << endl;
        changeLifePoints(playerDice->countHeal());
    }

    Message::lifePointsAfter();
    cout << lifePoints << endl;
}

void Player::resolveDestruction() {

    int remainingDestruction = playerDice->countDestruction();

    while(remainingDestruction != 0) {

        if (currentPosition->getTiles().size() == 0) {
            cout << "Everything has been destroyed" << endl;
            break;

        } else {

            int input;

            for (int i = 0; i < 3; i++) {


                if (!(currentPosition->getTiles()[i]->isDestroyed())) {

                    if (currentPosition->getTiles()[i]->getDurability() <= remainingDestruction) {


                        cout << "Do you want to destroy (1 = YES, 0 = NO)? ";
                        currentPosition->getTiles()[i]->toString();
                        Tile *currentTile = currentPosition->getTiles()[i];
                        cin >> input;

                        if (Validate::checkInput(0, 1, input) && input == 1) {

                            int rewardNumber;

                            if (currentTile->getName() == "High-Rise") {

                                int remainingDestructionStart = remainingDestruction;
                                if (currentTile->getDurability() >= remainingDestruction)
                                    remainingDestruction -= remainingDestruction;
                                remainingDestruction -= currentTile->getDurability();
                                rewardNumber = currentTile->destroyHighRise(remainingDestructionStart);
                                Message::victoryPointsBefore();
                                cout << victoryPoints << endl;
                                changeVictoryPoints(rewardNumber);
                                Message::victoryPointsAfter();
                                cout << victoryPoints << endl << endl;
                                break;

                            } else if (currentTile->getName() == "Hospital") {
                                int remainingDestructionStart = remainingDestruction;
                                if (currentTile->getDurability() >= remainingDestruction)
                                    remainingDestruction -= remainingDestruction;
                                rewardNumber = currentTile->destroyHospital(remainingDestructionStart);
                                Message::lifePointsBefore();
                                cout << lifePoints << endl;
                                changeLifePoints(rewardNumber);
                                Message::lifePointsAfter();
                                cout << lifePoints << endl;
                                break;

                            } else if (currentTile->getName() == "Power Plant") {
                                int remainingDestructionStart = remainingDestruction;
                                if (currentTile->getDurability() >= remainingDestruction)
                                    remainingDestruction -= remainingDestruction;
                                rewardNumber = currentTile->destroyPowerPlant(remainingDestructionStart);
                                Message::energyCubesBefore();
                                cout << energyCubes << endl;
                                changeEnergyCubes(rewardNumber);
                                Message::energyCubesBefore();
                                cout << energyCubes << endl;
                                break;

                            } else if (currentTile->getName() == "Infantry") {

                                int remainingDestructionStart = remainingDestruction;
                                remainingDestruction -= currentTile->getDurability();
                                rewardNumber = currentTile->destroyInfantry(remainingDestructionStart);
                                Message::lifePointsBefore();
                                cout << lifePoints << endl;
                                changeLifePoints(rewardNumber);
                                Message::lifePointsAfter();
                                cout << lifePoints << endl;
                                notify(38);
                                break;

                            } else if (currentTile->getName() == "Jet") {
                                int remainingDestructionStart = remainingDestruction;
                                remainingDestruction -= currentTile->getDurability();
                                rewardNumber = currentTile->destroyJet(remainingDestructionStart);
                                Message::energyCubesBefore();
                                cout << energyCubes << endl;
                                changeEnergyCubes(rewardNumber);
                                Message::energyCubesBefore();
                                cout << energyCubes << endl;
                                notify(38);
                                break;

                            } else if (currentTile->getName() == "Tank") {
                                int remainingDestructionStart = remainingDestruction;
                                remainingDestruction -= currentTile->getDurability();
                                rewardNumber = currentTile->destroyTank(remainingDestructionStart);
                                Message::victoryPointsBefore();
                                cout << victoryPoints << endl;
                                changeVictoryPoints(rewardNumber);
                                Message::victoryPointsAfter();
                                cout << victoryPoints << endl << endl;
                                notify(38);
                                break;

                            }

                        }

                    }
                }
            }

            bool valid = true;
            int answer;

            do {
                cout << "Do you want to exit? (1 = YES, 0 = NO)" << endl;
                cin >> answer;
                valid = Validate::checkInput(0, 1, answer);
            } while (!valid);

            if (answer == 1) break;

        }
    }

}


void Player::resolveCelebrity() {

    if (hasCelebrity) {
        cout << "You have the Celebrity Card.\n You gained " << playerDice->countCelebrity() << " victory points!\n";
        cout << "New number of victory points: " << victoryPoints << endl;
        changeVictoryPoints(playerDice->countCelebrity());
    }

    else {
        if (playerDice->countCelebrity() >= 3) {

            cout << "You rolled 3 or more Celebrity." << endl;

            Subgraph *position = currentPosition->getEdge();
            while (position->getName() != currentPosition->getName()) {
                for (int i = 0; i < position->getOwners().size(); i++) {
                    if (position->getOwners()[i]->isHasCelebrity()) {
                        cout << "You stole the Celebrity Card from " << position->getOwners()[i]->getMonster() << endl;
                        position->getOwners()[i]->setHasCelebrity(false);
                        setHasCelebrity(true);
                        cout << "You gained " << (1 + playerDice->countCelebrity() - 3) << " victory points\n";
                        changeVictoryPoints(1 + playerDice->countCelebrity() - 3);
                    }
                }

                position = position->getEdge();
            }
        }

        else cout << "You didn't roll enough Celebrity to get the Celebrity Card." << endl;
    }
}

void Player::resolveOuch(){

    Message::lifePointsBefore();
    cout << lifePoints << endl;

    switch(playerDice->countOuch()){
        case 1:
            changeLifePoints(-(currentPosition->countUnits()));
            cout << "You lost as many life points. \n" << endl;
            break;
        case 2: currentPosition->ouch(); break;
        default:
            currentPosition->ouch();
            Subgraph* position = currentPosition->getEdge();
            while(position != currentPosition){
                position->ouch();
                position = position->getEdge();
            }

            if(!isHasStatueOfLiberty()){
                Subgraph *position = currentPosition->getEdge();
                while (position->getName() != currentPosition->getName()) {
                    for (int i = 0; i < position->getOwners().size(); i++) {
                        if (position->getOwners()[i]->isHasStatueOfLiberty()) {
                            position->getOwners()[i]->setHasStatueOfLiberty(false);
                            position->getOwners()[i]->changeVictoryPoints(3);
                        }

                    }

                    position = position -> getEdge();
                }

                setHasStatueOfLiberty(true);
                changeVictoryPoints(3);
            }
    }

    Message::lifePointsAfter();
    cout << lifePoints << endl << endl;
}

void Player::move() {


        //If the player is not in Manhattan
        if (!currentPosition->getIsMain()) {

            //If there is someone in Manhattan
            if (!mainFree())
                askMove();

                //If there is no one in Manhattan
            else
                moveToMain();
        }

        else {
            if (getZoneNumber() != currentPosition->getRegion().size() - 1) {
                cout << "Move up a zone." << endl;
                setZoneNumber(getZoneNumber() + 1);
                cout << "You are now in " << currentPosition->getRegion()[getZoneNumber()];
            }

            else
                cout << "You are in " << currentPosition->getRegion()[getZoneNumber()]
                     << "Stay where you are." << endl;
        }

}

void Player::askMove() {

    cout << monster << ": ";

        if (isMoving()) {

            Subgraph* position = currentPosition->getEdge();

            bool valid;
            int input;

            while(position->getName() != currentPosition->getName()){
                if ((!(position->getIsMain())) && (position->getOwners().size()) < position->getMaxOwners()){
                    cout << "Do you want to move to ";
                    position->toString();
                    cout << endl << "(1 = YES, 0 NO)? " <<  endl;
                    cin >> input;
                    if(Validate::checkInput(0,1,input) && input == 1) break;
                }
                position = position->getEdge();
            }

            Subgraph* temp = currentPosition;

            position->addOwner(this);
            currentPosition = position;
            temp->removeOwner(this);

            }

}

void Player::askMoveSuperSpeed() {

    cout << monster << ": ";

    if (isMoving()) {

        Subgraph* position = currentPosition->getEdge();

        bool valid;
        int input;

        while(position->getName() != currentPosition->getName()){
            if ((position->getOwners().size()) < position->getMaxOwners()){
                cout << "Do you want to move to ";
                position->toString();
                cout << endl << "(1 = YES, 0 NO)? " <<  endl;
                cin >> input;
                if(Validate::checkInput(0,1,input) && input == 1) break;
            }
            position = position->getEdge();
        }

        Subgraph* temp = currentPosition;

        position->addOwner(this);
        currentPosition = position;
        temp->removeOwner(this);

    }

}

bool Player::isMoving() {

    return mentality -> isMovingStrategy();
}


void Player::moveToMain(){

    notify(4);

    Subgraph* position = currentPosition->getEdge();

    while(position->getName() != currentPosition->getName()) {
        if (position->getIsMain()) break;
        position = position->getEdge();
    }

    cout << "There is place in " << position->getName() << ".\nMove to "
        << position->getRegion()[0].getName() << "." << endl;

    Message::victoryPointsBefore();
    cout << victoryPoints << endl;
    cout << "You gained 1 Victory Point." << endl;
    changeVictoryPoints(1);
    Message::victoryPointsAfter();
    cout << victoryPoints << endl << endl;
    Subgraph* temp = currentPosition;

    position->addOwner(this);
    currentPosition = position;
    temp->removeOwner(this);

}


bool Player::isHasStatueOfLiberty() const {
    return hasStatueOfLiberty;
}

void Player::setHasStatueOfLiberty(bool hasStatueOfLiberty) {
    Player::hasStatueOfLiberty = hasStatueOfLiberty;
}

void Player::buyCard() {

    cout << "The top 3 Cards are: \n\n";
    cout << "[0] ";
    ((*gameCards).begin()+0)->toString();
    cout << endl;
    cout << "[1] ";
    ((*gameCards).begin()+1)->toString();
    cout << endl;
    cout << "[2] ";
    ((*gameCards).begin()+2)->toString();
    cout << endl;

    if(getEnergyCubes() >= 2) {

        bool valid = true;
        int answer;

        do {
            cout << "Do you want to discard 3 cards? (1 = YES, 0 = NO)" << endl;
            cin >> answer;
            valid = Validate::checkInput(0, 1, answer);
        } while (!valid);

        if (answer == 1) {
            (*gameCards).erase((*gameCards).begin() + 0);
            (*gameCards).erase((*gameCards).begin() + 0);
            (*gameCards).erase((*gameCards).begin() + 0);
            cout << "\nCards discarded." << endl;

            Message::energyCubesBefore();
            cout << energyCubes << endl;
            changeEnergyCubes(-2);
            Message::energyCubesAfter();
            cout << energyCubes << endl << endl;

            cout << "The new top 3 Cards are: \n\n";
            cout << "[0] ";
            ((*gameCards).begin() + 0)->toString();
            cout << endl;
            cout << "[1] ";
            ((*gameCards).begin() + 1)->toString();
            cout << endl;
            cout << "[2] ";
            ((*gameCards).begin() + 2)->toString();
            cout << endl;
        }
    }

    bool doContinue = false;
    if(((*gameCards).begin()+0)->getCost() <= getEnergyCubes()) doContinue = true;
    if(((*gameCards).begin()+1)->getCost() <= getEnergyCubes()) doContinue = true;
    if(((*gameCards).begin()+2)->getCost() <= getEnergyCubes()) doContinue = true;

    int answer = mentality -> getInputForBuyCard(doContinue);

    if(answer == 1){
        bool valid = true;
        int answer;

        do {
            cout << "Pick one (enter a number): " << endl;
            cin >> answer;
            valid = Validate::checkInput(0, 2, answer);
        } while (!valid);

        cout << endl;

        if((*gameCards)[answer].getCost() <= getEnergyCubes()){

            Message::energyCubesBefore();
            cout << energyCubes << endl;
            changeEnergyCubes(-(*gameCards)[answer].getCost());
            Message::energyCubesAfter();
            cout << energyCubes << endl;

            if((*gameCards)[answer].getHowToPlay() == "KEEP") {
                cout << "You bought a KEEP card\n";
                cout << "Number of cards before: " << currentCards.size() << endl;
                addCard(Card((*gameCards)[answer]));
                cout << "Number of cards after: " << currentCards.size() << endl;

            }

            else {
                cout << "You bought a DISCARD card.\n";
                cout << "Number of cards before: " << currentCards.size() << endl;
                cout << "Number of cards after: " << currentCards.size() << endl;
                (*gameCards)[answer].addSubject(this);
                notify(18);
                (*gameCards)[answer].removeSubject();
            }

            gameCards->erase(gameCards->begin()+answer);
        }

        else
            cout << "You don't have enough energy cubes" << endl;
        buyCard();
    }

}

void Player::setGameCards(vector<Card> *gameCards){
 this->gameCards = gameCards;
}

bool Player::mainFree() {

    Subgraph* position = currentPosition->getEdge();

    while(position->getName() != currentPosition->getName()){
        if(position->getIsMain())
            return (position->getOwners().size() < position->getMaxOwners());
        position = position->getEdge();
    }
    return true;
}

int Player::getVictoryPoints() {
    return victoryPoints;
}

int Player::getLifePoints() {
    return lifePoints;
}

vector <Token> Player::getMonsterTokens() {
    return monsterTokens;
}

//Adds tokens to the Monster
void Player::addMonsterToken(Token newToken) {
    monsterTokens.push_back(newToken);
}

//Removes the last token from the Monster
void Player::removeMonsterToken() {
    monsterTokens.pop_back();
}


void Player::setVictoryPoints(int number) {
    victoryPoints = number;
}

void Player::setLifePoints(int number) {
    lifePoints = number;
}

void Player::setMonsterTokens(vector<Token> aVector) {
    monsterTokens = aVector;
}

void Player::checkHeal() {

    if(lifePoints < 10)
        playerDice->setNeedHeal(10-lifePoints);
}

bool Player::isLost() const {
    return lost;
}

void Player::setLost(bool lost) {
    Player::lost = lost;
}


int NumPlayersSelector::selectNumPlayers() {

    int choice;
    bool validChoice;

    do {
        std::cout << "Please enter the number of players (2-6): ";
        std::cin >> choice;
        validChoice = true;

        //Checks if user input is non-numeric
        if (!std::cin.good()) {
            std::cin.clear();
            string ignore;
            std::cin >> ignore;
            validChoice = false;
            continue;
        }
        //Checks if choice is valid
        if (choice < MIN_PLAYERS || choice > MAX_PLAYERS)
            validChoice = false;

    } while (!validChoice);

    return choice;
}


vector<Player> NumPlayersSelector::select() {
    PlayersCreation creator;
    creator.createPlayers(selectNumPlayers());
    return creator.gamePlayers;
}





PlayersCreation::PlayersCreation() {

}

void PlayersCreation::createPlayers(int number){

    for (int i = 0; i < number; i++){
        Player temp;
        gamePlayers.push_back(temp);
    }
}

PlayersCreation::~PlayersCreation() {
//TODO implement destructor
}

