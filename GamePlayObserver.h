//
// Created by client on 2018-11-21.
//

#pragma once
#include <string>

#include "Observer.h"
#include "GamePlay.cpp"

class GamePlay;

//General observer for the entire game. Will be used to provide updates on what all the players and doing and their current locations that will allow for the human players to plan their next moves.
class GamePlayObserver : public Observer {

public:
    GamePlayObserver(); //Observer constructor that will be generated at the beginning of the game loop.
    GamePlayObserver(GamePlay* observed); 
    ~GamePlayObserver(); //Destructor.

	//Similar implementation to the regular observers but expanded to report on all playrs and major events that will be displayed after every player turn or after significant game events.
    void Update();
    void Update(std::string message);
    void display(std::string message);

private:
    GamePlay* _subject; //Subject that will be the main game loop.
};
