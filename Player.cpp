//
// Created by Janusz Grzesik on 26.01.2017.
//

#include "Player.h"

bool Player::operator==(const Player &b) const {
    return false;
}

bool Player::operator<(const Player &b) const {
    return false;
}

void Player::addCard(Card card) {

}

PlayerStatus Player::getStatus() {
    return pleb;
}

int Player::call(int amount, bool canRaise) {
    return 0;
}

void Player::subtractChips(int amount) {
}
