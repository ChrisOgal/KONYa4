#include "DiceRollingFacility.h"

Die::Die() {

    value = -1;
    played = false;
}

Die::Die(int value) {
    setValue(value);
}

int Die::getValue()
{
    return value;
}

void Die::setValue(int newValue)
{
    value = newValue;
}

bool Die::isPlayed() const {
    return played;
}

void Die::setPlayed(bool played) {
    Die::played = played;
}




DiceRollingFacility::DiceRollingFacility()
{

}

DiceRollingFacility::DiceRollingFacility(int number)
{
    for (int i = 0; i < number; i++) {
        dice.push_back(Die());
    }

    needHeal = 0;
}

void DiceRollingFacility::setDice(vector<Die> newDice)
{
    dice = newDice;
}

void DiceRollingFacility::setDice() {

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<>dis(0,5);

    for (int i = 0; i < dice.size(); i++) {
        int number = (signed int)(dis(gen));
        if(number < 0) number = (-number);
        dice[i].setValue(number);
    }

    display();
}

void DiceRollingFacility::resetDice() {

    for (int i = 0; i < dice.size(); i++) {
        dice[i].setPlayed(false);
    }
}

void DiceRollingFacility::setRollStrategy(Strategy *chosenStrategy)
{
    rollStrategy = chosenStrategy;
}

void DiceRollingFacility::display() {

    cout << endl << "You rolled: " << endl;
    for (int i = 0; i < dice.size(); i++) {
        if(!dice[i].isPlayed())
            cout << "[" << i << "]" << faces[dice[i].getValue()] << endl;
    }

    cout << endl;
}

void DiceRollingFacility::reRoll(int number) {

    int answer = rollStrategy->isReroll(countAttacks(),countHeal(),needHeal);

    if (answer == 1) {
        rollStrategy->rollDice(&dice);

        display();

        if (number != 2)
            reRoll(2);
    }
}

DiceRollingFacility::~DiceRollingFacility()
{
}

int DiceRollingFacility::countAttacks()
{
    int count = 0;
    for (int i = 0; i < dice.size(); i++) {
        if (dice[i].getValue() == 1) count++;
    }
    return count;
}

int DiceRollingFacility::countDestruction()
{
    int count = 0;
    for (int i = 0; i < dice.size(); i++) {
        if (dice[i].getValue() == 2) count++;
    }
    return count;
}

int DiceRollingFacility::countEnergy()
{
    int count = 0;
    for (int i = 0; i < dice.size(); i++) {
        if (dice[i].getValue() == 0) count++;
    }
    return count;
}

int DiceRollingFacility::countHeal()
{
    int count = 0;
    for (int i = 0; i < dice.size(); i++) {
        if (dice[i].getValue() == 3) count++;
    }
    return count;
}

int DiceRollingFacility::size()
{
    return dice.size();
}

int DiceRollingFacility::valueAt(int index)
{
    return dice.at(index).getValue();
}

void DiceRollingFacility::removeEffect(int effect)
{
    for (int i = 0; i < dice.size(); i++) {
        if(dice[i].getValue() == effect)
            dice[i].setPlayed(true);
    }
}

bool DiceRollingFacility::isEmpty()
{
    int count = 0;
    for (int i = 0; i < dice.size(); i++){
        if(!dice[i].isPlayed())
            count++;
    }

    return count == 0;
}

int DiceRollingFacility::countCelebrity() {
    int count = 0;
    for (int i = 0; i < dice.size(); i++) {
        if (dice[i].getValue() == 4) count++;
    }
    return count;
}

int DiceRollingFacility::countOuch() {
    int count = 0;
    for (int i = 0; i < dice.size(); i++) {
        if (dice[i].getValue() == 5) count++;
    }
    return count;
}

int DiceRollingFacility::getNeedHeal() const {
    return needHeal;
}

void DiceRollingFacility::setNeedHeal(int needHeal) {
    DiceRollingFacility::needHeal = needHeal;
}

