//
// Created by client on 2018-11-21.
//

#pragma once
#include <iostream>


//This struct conatins common messages that will be displayed throughout the game to keep track of what is happening. It is easier to have them here as functions that can and will be called multiple times to allow for reusable code.

struct Message{
	//Opening message to the game that provides a welcome message before the fun begins.
    static void welcomeMessage(){

        std::cout << std::endl;

        int width = 20;
        int height = 5;

        for (int i= 0; i < height; i++){

            if(i == 0 | i == 4) {
                for (int j = 0; j < width; j++)
                    std::cout << "* ";
                std::cout << std::endl;
            }

            else if(i == 2) std::cout << "*        WELCOME TO THE GAME          *\n";
        }

        std::cout << std::endl;
    }


	//informs the players when a building or vehicle is destroyed and confirms what is on the other side of the card.
    static void confirmDestruction(){
        std::cout << "Building destroyed! \n\nOn the other side: \n" << std::endl;
    }


	//Provides the number of victory points before a given action, usually before a player's turn or before they use a certain card.
    static void victoryPointsBefore(){
        std::cout << "Number of victory points before: ";
    }

	//Provides the number of victory points after a given action, usually at the end of the player's turn.
    static void victoryPointsAfter(){
        std::cout << "Number of victory points after: ";
    }

	//Provides the number of health points before a given action, usually before a player's turn or before they use a certain card.
    static void lifePointsBefore(){
        std::cout << "Number of life points before: ";
    }

	//Provides the number of health points after a given action, usually at the end of the player's turn.
    static void lifePointsAfter(){
        std::cout << "Number of life points after: ";
    }

	//Provides the number of energy cubes before a given action, usually before a player's turn or before they use a certain card.
    static void energyCubesBefore(){
        std::cout << "Number of energy cubes before: ";
    }

	//Provides the number of energy cubes after a given action, usually at the end of the player's turn.
    static void energyCubesAfter(){
        std::cout << "Number of energy cubes after: ";
    }

};
