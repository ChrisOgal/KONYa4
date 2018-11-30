#include <iostream>
#include "GamePlayObserver.h"
#include "Player.h"
#include "DiceRollingFacility.h"
#include "GamePieces.h"
#include "Output.h"
#include <random>

int main() {

    GamePlay play;
    GamePlayObserver *playObserver = new GamePlayObserver(&play);

    Message::welcomeMessage();

    play.setGameMap();

    play.setGamePlayers();

    play.outputGameState();

    play.GameLoop();

    return 0;
}