//
// Created by client on 2018-11-21.
//

#include "GamePlayObserver.h"

void GamePlayObserver::Update() {
}


void GamePlayObserver::Update(std::string message){
    display(message);
}

void GamePlayObserver::display(std::string message) {
    cout << "   =====> " << _subject->getCurrentPlayer()->getMonster() << ": " << message << endl;
}


GamePlayObserver::GamePlayObserver() {
};

GamePlayObserver::GamePlayObserver(GamePlay* observed) {
    _subject = observed;
    _subject->attach(this);
}

GamePlayObserver::~GamePlayObserver() {
    _subject->detach(this);
}

void GamePlayObserver::Update(int cardNumber) {

};
