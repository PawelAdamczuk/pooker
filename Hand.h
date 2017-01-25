//
// Created by pawel on 22.01.17.
//

#ifndef POOKER_HAND_H
#define POOKER_HAND_H

enum hand_rankings_t{high_card = 0, pair, two_pair, three_of_a_kind, straight, flush, full_house, four_of_a_kind,
                     straight_flush, royal_flush};
#include "Card.h"
#include <algorithm>
#include <ostream>
#include <vector>

class Hand {
private:
    Card identity_card_1;
    Card identity_card_2;
    hand_rankings_t ranking;

    bool CheckHighCard();
    bool CheckPair();
    bool CheckTwoPair();
    bool CheckThreeOfAKind();
    bool CheckStraight();
    bool CheckFlush();
    bool CheckFullHouse();
    bool CheckFourOfAKind();
    bool CheckStraightFlush();
    bool CheckRoyalFlush();

public:
    Card cards[5];
    Hand(Card *_cards, int _size);

    bool operator<(const Hand &rhs) const;

    friend std::ostream &operator<<(std::ostream &os, const Hand &hand);

    static std::vector<Hand> evaluate(std::vector<Card> &cards);

};


#endif //POOKER_HAND_H
