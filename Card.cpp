//
// Created by pawel on 15.01.17.
//

#include "Card.h"

std::ostream &operator<<(std::ostream &stream, const Card &card) {
    //http://stackoverflow.com/questions/3342726/c-print-out-enum-value-as-text
    char *Ranks[] = {"incorrect_rank", "incorrect_rank", "two", "three", "four", "five", "six", "seven",
                    "eight", "nine", "ten", "jack", "queen", "king", "ace"};

    char *Suits[] = {"spades", "hearts", "diamonds", "clubs"};

    stream << Ranks[card.rank] << " of " << Suits[card.suit];
    return stream;
}

Card::Card(ranks_t rank, suits_t suit) : suit(suit), rank(rank) {}

suits_t Card::getSuit() const {
    return suit;
}

ranks_t Card::getRank() const {
    return rank;
}

//only compares ranks
bool Card::operator<(const Card &b) const {
    if(this->rank < b.rank)
        return true;
    return false;
}
//only compares ranks
bool Card::operator>(const Card &b) const {
    if(this->rank > b.rank)
        return true;
    return false;
}

//takes the suit into account (used in sorting that needs to be deterministic)
short Card::compare(const Card &a) {
    if(a > *this)
        return 1;
    if (a < *this)
        return -1;

    if(a.getSuit() > this->getSuit())
        return 1;
    if(a.getSuit() < this->getSuit())
        return -1;

    return 0;
}
