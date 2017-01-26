//
// Created by pawel on 22.01.17.
//

#include <random>
#include "CardDeck.h"

CardDeck::CardDeck() {
    std::vector<Card> temp(0);
    this->cards = temp;
    for (int i = spades; i != clubs+1; ++i) {
        for (int j = two; j != ace+1; ++j) {
            this->cards.push_back(Card(static_cast<ranks_t >(j), static_cast<suits_t >(i)));
        }
    }
    this->shuffled = false;
}

bool CardDeck::isShuffled() const {
    return shuffled;
}

void CardDeck::shuffle() {
    long seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::shuffle(this->cards.begin(), this->cards.end(), std::default_random_engine(seed));
}

std::ostream &operator<<(std::ostream &os, const CardDeck &deck) {
    for(std::vector<Card>::const_iterator it = deck.cards.begin(); it != deck.cards.end(); ++it) {
        os << *it << std::endl;
    }
    return os;    
}

Card CardDeck::deal() {
    Card temp = this->cards.back();
    this->cards.pop_back();
    return temp;
}


