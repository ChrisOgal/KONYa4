#include "Strategy.h"

using namespace std;


int Aggressive:: isReroll(int numberAttack, int numberHeal, int missingHealNum){

    cout << "Do you want to reroll? (1 = YES, 0 = NO)" << endl;

    if(numberAttack < 6) {
        cout << 1;
        return 1;
    }

    else {
        cout << 0;
        return 0;
    }

}

void Aggressive::rollDice(vector<Die>* dice){

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<>dis(0,5);

    for (std::vector<Die>::iterator it = (*dice).begin(); it != (*dice).end(); ++it){
        if(it->getValue() !=  1)
            it->setValue(dis(gen));
    }
}

int Aggressive::resolveDiceStrategy(vector<Die>* dice) {


    for (int i = 0; i < dice->size();i++){
        if(((*dice)[i].getValue() == 1) && (!((*dice)[i].isPlayed())))
            return i;
    }

    int answer;
    bool valid = true;

    do {
        cout << "Please enter the number of the Dice Effect you want to resolve : " << endl;
        cin >> answer;
        valid = (Validate::checkInput(0, (dice->size())-1, answer)) && (!(*dice)[answer].isPlayed());
    } while (!valid);

    return answer;
}

bool Aggressive::isMovingStrategy() {
    bool valid = true;
    int answer;

    do {
        cout << "Do you want to move? (1 = YES, 0 = NO)" << endl;
        cin >> answer;
        valid = Validate::checkInput(0, 1, answer);
    } while (!valid);

    return answer == 1;
}

int Aggressive::getInputForBuyCard(bool value) {
    bool valid = true;
    int answer;

    do {
        cout << "Do you want to buy a card? (1 = YES, 0 = NO)" << endl;
        cin >> answer;
        valid = Validate::checkInput(0, 1, answer);
    } while (!valid);

    return answer;

}

int Human::isReroll(int numberAttack, int numberHeal, int missingHealNum) {

    bool valid = true;
    int answer;

    do {
        cout << "Do you want to reroll? (1 = YES, 0 = NO)" << endl;
        cin >> answer;
        valid = Validate::checkInput(0, 1, answer);
    } while (!valid);

    return answer;

}

void Human::rollDice(vector<Die>* dice){

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<>dis(0,5);

    while (!dice->empty()) {

        bool valid = true;
        int answer;
        do {
            cout << "Please enter the number of the die you want to reroll (-1 to exit)" << endl;
            cin >> answer;
            valid = Validate::checkInput(-1, dice->size()-1, answer);
        } while (!valid);

        if (answer == -1) break;
        if (valid)
            (*dice)[answer].setValue(dis(gen));
    }
}

int Human::resolveDiceStrategy(vector<Die>* dice) {

    int answer;
    bool valid = true;

    do {
        cout << "Please enter the number of the Dice Effect you want to resolve : " << endl;
        cin >> answer;
        valid = (Validate::checkInput(0, (dice->size())-1, answer)) && (!(*dice)[answer].isPlayed());
    } while (!valid);

    return answer;
}

bool Human::isMovingStrategy() {
    bool valid = true;
    int answer;

    do {
        cout << "Do you want to move? (1 = YES, 0 = NO)" << endl;
        cin >> answer;
        valid = Validate::checkInput(0, 1, answer);
    } while (!valid);

    return answer == 1;
}

int Human::getInputForBuyCard(bool value) {
    bool valid = true;
    int answer;

    do {
        cout << "Do you want to buy a card? (1 = YES, 0 = NO)" << endl;
        cin >> answer;
        valid = Validate::checkInput(0, 1, answer);
    } while (!valid);

    return answer;

}

int Moderate:: isReroll(int numberAttack, int numberHeal, int missingHealNum){

    cout << "Do you want to reroll? (1 = YES, 0 = NO)" << endl;

    if(numberHeal < 6 && numberHeal < missingHealNum) {
        cout << 1 << endl;
        return 1;
    }

    else {
        cout << 0 << endl;
        return 0;
        }
}

void Moderate::rollDice(vector<Die>* dice){

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<>dis(0,5);

    for (std::vector<Die>::iterator it = (*dice).begin(); it != (*dice).end(); ++it){
        if(it->getValue() !=  3)
            it->setValue(dis(gen));
    }
}

int Moderate::resolveDiceStrategy(vector<Die>* dice) {


    for (int i = 0; i < dice->size();i++){
        if(((*dice)[i].getValue() == 3) && (!((*dice)[i].isPlayed())))
            return i;
    }

    int answer;
    bool valid = true;

    do {
        cout << "Please enter the number of the Dice Effect you want to resolve : " << endl;
        cin >> answer;
        valid = (Validate::checkInput(0, (dice->size())-1, answer)) && (!(*dice)[answer].isPlayed());
    } while (!valid);

    return answer;
}

bool Moderate::isMovingStrategy() {
    cout << "Do you want to move? (1 = YES, 0 = NO)\n0\n" << endl;
    return 0;
}

int Moderate::getInputForBuyCard(bool value) {
    cout << "Do you want to buy a card? (1 = YES, 0 = NO)" << endl;

    if(value) {
        cout << "1\n";
        return 1;
    }

    else {
        cout << "0\n";
        return 0;
    }
}

