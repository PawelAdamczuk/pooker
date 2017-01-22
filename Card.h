//
// Created by pawel on 15.01.17.
//

#ifndef POOKER_CARD_H
#define POOKER_CARD_H

#include <iostream>

//http://www.cplusplus.com/doc/tutorial/other_data_types/
enum suits_t{spades = 0, hearts, diamonds, clubs};
enum ranks_t{two = 2, three, four, five, six, seven, eight, nine, ten, jack, queen, king, ace};

class Card {

private:
    suits_t suit;
    ranks_t rank;

public:
    Card() : Card(ace, spades){};
    Card(ranks_t rank, suits_t suit);
    suits_t getSuit() const;
    ranks_t getRank() const;
    friend std::ostream& operator<< (std::ostream& stream, const Card& card);
    short compare(const Card& a);
    bool operator <(const Card &b) const;
    bool operator >(const Card &b) const;
    std::string getRankString() const;
    bool operator==(const Card &rhs) const;
    bool operator!=(const Card &rhs) const;
};


#endif //POOKER_CARD_H
