//
// Created by Janusz Grzesik on 26.01.2017.
//

#include "Player.h"
#include "GameRound.h"

using namespace std;

void Player::addCard(Card card) {
    hand.push_back(card);
}

void Player::setStatus(PlayerStatus s) {
    status = s;
}

int Player::call(int amount, bool canRaise, const RoundPhase phase, int pot, const vector<Player*> otherPlayers,
                 const vector<Card> *cards, const map<string, int> *bets, int smallBlind) {

    return -1;
}

void Player::subtractChips(int amount) {
    if (amount > money) {
        throw std::runtime_error("Attempting to subtract too much");
    }

    money -= amount;
}

Player::Player(string playersName, int amount) {
    name = playersName;
    money = amount;
    hand = vector<Card>();
}

int Player::getMoney() {
    return money;
}

string Player::getName() const {
    return name;
}

PlayerStatus Player::getStatus() const {
    return status;
}

void Player::addMoney(int amount) {
    money += amount;
}

vector<Card> Player::getCards() {
    return hand;
}

