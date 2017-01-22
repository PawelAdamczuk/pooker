//
// Created by pawel on 22.01.17.
//

#ifndef POOKER_CARDDECK_H
#define POOKER_CARDDECK_H

#include <vector>
#include "Card.h"
#include <chrono>
#include <algorithm>
#include <ostream>

class CardDeck {
private:
    std::vector<Card> cards;
    bool shuffled;
public:
    CardDeck();
    bool isShuffled() const;
    void shuffle();
    friend std::ostream &operator<<(std::ostream &os, const CardDeck &deck);
    Card deal();
};


#endif //POOKER_CARDDECK_H
