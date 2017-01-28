//
// Created by Janusz Grzesik on 26.01.2017.
//

#ifndef POOKER_PLAYER_H
#define POOKER_PLAYER_H


#include "Card.h"

enum PlayerStatus {
    pleb, dealer, smallBlind, bigBlind
};

class Player {

public:
    bool operator==(const Player &b) const;

    bool operator<(const Player &b) const;

    void addCard(Card card);

    PlayerStatus getStatus();

    int call(int amount, bool canRaise);

    void subtractChips(int amount );
};


#endif //POOKER_PLAYER_H
