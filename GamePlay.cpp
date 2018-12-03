//
// Created by client on 2018-10-27.
//

#include "Map.h"
#include "Player.h"
#include "Subject.h"


//General Functions used to enforce the rules while running the game
class GamePlay: public Subject {


private:

	//Data members
    Map *gameMap;
    MapObserver *gameMapObserver;
    vector <Player> gamePlayers;
    vector <Card> cardDeck;
    vector <Tile> tileDeck;
    vector <Token> tokenDeck;
    Player* currentPlayer;

public:

    Player *getCurrentPlayer() const {  //Returns the player whose turn it is
        return currentPlayer;
    }


    void setGameMap() {  //Sets up the game map and places the appropriate buildings around.

        gameMap = new Map();
        gameMapObserver = new MapObserver(gameMap);
        setTileDeck();
        shuffleTilesDeck();
        placeTiles();
        setTokenDeck();

    }

    void setGamePlayers() {  //Sets the number of players and spreads them out according to the rules of the game.

        gamePlayers = NumPlayersSelector::select();
        cout << endl;
        pickMonsters();
        decideOrder();
        adjustMapForPlayers();
        chooseBoroughs();
        setCardDeck();
        addGameCards();

    }

    void setCardDeck() {
        cardDeck = LoadGamePieces::createCards();
        //TODO uncomment after testing
        //shuffleCardDeck();
    }

    void shuffleCardDeck(){

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<>dis(0,6);

        for(int i = 0; i < 6; i++){
            Card temp = cardDeck[i];
            cardDeck[i] = cardDeck[dis(gen)];
            cardDeck[dis(gen)] = temp;
        }
    }

    void decideOrder(){  //First die roll to decide the game order of the players

        cout << "===> Deciding order: " << endl << endl;

        for (int i = 0; i < gamePlayers.size(); i++){
            cout << gamePlayers[i].getMonster() << endl;
            gamePlayers[i].firstRoll();
        }

        vector<Player> temp;

        while(!gamePlayers.empty()) {
            temp.push_back(gamePlayers[findMax()]);
            gamePlayers.erase(gamePlayers.begin() + findMax());
        }

        gamePlayers.swap(temp);

        cout << "The order of play is: " << endl;

        for (int i = 0; i < gamePlayers.size(); i++){
            cout << i+1 << ". " << gamePlayers[i].getMonster() << endl;
        }

        cout << endl;
    }

    int findMax(){  //Finds the highest number of attacks rolled. Helper function to the decideOrder function.

        int first = 0;
        for (int i = 1; i < gamePlayers.size(); i++){
            if(gamePlayers[first].attacksRolled() < gamePlayers[i].attacksRolled())
                first = i;
        }

        return first;

    }

    void shuffleTilesDeck(){

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<>dis(0,tileDeck.size()-1);

        for(int i = 0; i < tileDeck.size(); i++){
            Tile temp = tileDeck[i];
            tileDeck[i] = tileDeck[dis(gen)];
            tileDeck[dis(gen)] = temp;
        }
    }

    void setTileDeck() {
        tileDeck = LoadGamePieces::createTiles();
    }

    void setTokenDeck() {
        tokenDeck = LoadGamePieces::createTokens();
    }

    void pickMonsters() {

        vector<string> monsterDeck;

        monsterDeck.push_back("Captain Fish");
        monsterDeck.push_back("Mantis");
        monsterDeck.push_back("Kong");
        monsterDeck.push_back("Sheriff");
        monsterDeck.push_back("Drakonis");
        monsterDeck.push_back("Rob");

        for (int i = 1; i <= gamePlayers.size(); i++) {
            cout << "The available Monsters are: " << endl;
            for (int j = 0; j < monsterDeck.size(); j++) {
                cout << "[" << j << "] ";
                cout << monsterDeck[j] << endl;
            }
            cout << "Player " << i
                 << " please pick your Monster (enter a number) >> ";
            int input;
            cin >> input;
            //To assign a Monster to Player
            gamePlayers[i - 1].setMonster(monsterDeck[input]);
            monsterDeck.erase(monsterDeck.begin() + input); //remove Monster Card from deck
            cout << endl;
        }
    }

    void placeTiles() {

        gameMap->addTiles(tileDeck);
    }


    void chooseBoroughs() {
        for (int i = 0; i < gamePlayers.size(); i++) {
            cout << "=====> Player " << i + 1 << " please pick your Borough \n" << endl;
            gameMap->pickBorough(&gamePlayers[i]);
            cout << endl;
        }
    }

    void adjustMapForPlayers() {
        if (gamePlayers.size() < 5)
            gameMap->lessThanFourPlayers();
    }

    void outputGameState() {
        gameMap->outputState();
    }

    void addGameCards(){
        for (int i = 0; i < gamePlayers.size(); i++){
            gamePlayers[i].setGameCards(&cardDeck);
        }
    }


    bool endGame() {   //Checks for game ending scenarios

            int countAlive = 0;
            int alive = -1;

            for (int i = 0; i < gamePlayers.size(); i++) {


                if (gamePlayers[i].getLifePoints() > 0 && !(gamePlayers[i].isLost())) {
                    countAlive++;
                    alive = i;
                }

            }

        if (countAlive == 1) {
            gamePlayers[alive].toString();
            cout << "W O N!" << endl;
            cout << "Is the only one still alive!\n";
            return true;
        }

        return false;
    }

    bool winner(){  //Checks for players in a game winning scenario

        if(currentPlayer->getVictoryPoints() == 20 && currentPlayer->getLifePoints() > 0) {
            currentPlayer->toString();
            cout << "W O N! " << endl;
            if(currentPlayer-> getVictoryPoints() == 20)
                cout << "Reached 20 Victory Points! \n";
            if(currentPlayer->getLifePoints() > 0)
                cout << "Is still alive! \n";
            return true;
        }

        return false;
    }

    void GameLoop() {  //Main game loop. Runs until a game ending scenario is achieved.

        while (!endGame()) {

            for (int i = 0; i < gamePlayers.size(); i++) {

                currentPlayer = &gamePlayers[i];

                if (!(gamePlayers[i].isLost())) {

                    notify("Start turn");
                    gamePlayers[i].startTurn();

                    notify("Roll Dice Step");
                    gamePlayers[i].rollDice();

                    notify("Resolve Dice Step");
                    gamePlayers[i].resolveTheDice();
                    cout << endl;

                    notify("Move Step\n");
                    gamePlayers[i].move();

                    notify("Buy Cards Step\n");
                    gamePlayers[i].buyCard();

                    if (gamePlayers[i].getLifePoints() <= 0) {
                        cout << "E L I M I N A T E D! \nYou lost all your life points." << endl;
                        currentPlayer->setLost(true);
                    }
                    cout << "\nEND OF YOUR TURN. \n\n";
                    outputGameState();
                    if(winner()) break;
                }
            }
        }
    }

    //NOT USED

    void outputNumPlayers() {
        cout << gamePlayers.size() << " players are playing this game." << endl;
    }


    void outputNumCards() {
        cout << "There are " << cardDeck.size() << " cards in the deck." << endl;
    }

    void outputTiles() {
        for (int i = 0; i < tileDeck.size(); i++)
            tileDeck[i].toString();
    }

    void outputPlayers() {
        for (int i = 0; i < gamePlayers.size(); i++) {
            gamePlayers[i].toString();
        }
    }

    void outputNumTokens() {
        cout << "There are " << tokenDeck.size() << " tokens in the play area." << endl;
    }

};
