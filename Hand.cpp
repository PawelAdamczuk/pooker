//
// Created by pawel on 22.01.17.
//

#include "Hand.h"
#include "cmath"

//id_card_1 := the hightest card
bool Hand::CheckHighCard() {
    this->identity_card_1 = this->cards[4];
    this->ranking = high_card;
    return true;
}

//id_card_1 := the pair rank card
bool Hand::CheckPair() {
    bool a = false;

    if(this->cards[0].getRank() == this->cards[1].getRank()) {
        this->identity_card_1 = this->cards[0];
        this->ranking = pair;
        a = true; }

    if(this->cards[1].getRank() == this->cards[2].getRank()) {
        this->identity_card_1 = this->cards[1];
        this->ranking = pair;
        a = true; }

    if(this->cards[2].getRank() == this->cards[3].getRank()) {
        this->identity_card_1 = this->cards[2];
        this->ranking = pair;
        a = true; }

    if(this->cards[3].getRank() == this->cards[4].getRank()) {
        this->identity_card_1 = this->cards[3];
        this->ranking = pair;
        a = true; }

    return a;
}

//id_card_1 := the higher pair rank card
//id_card_2 := the lower pair rank card
bool Hand::CheckTwoPair() {
    bool a = false;

    if(this->cards[0].getRank() == this->cards[1].getRank() && this->cards[2].getRank() == this->cards[3].getRank()) {
        this->identity_card_1 = this->cards[2];
        this->identity_card_2 = this->cards[0];
        this->ranking = two_pair;
        a = true; }

    if(this->cards[1].getRank() == this->cards[2].getRank() && this->cards[3].getRank() == this->cards[4].getRank()) {
        this->identity_card_1 = this->cards[3];
        this->identity_card_2 = this->cards[1];
        this->ranking = two_pair;
        a = true; }


    if(this->cards[0].getRank() == this->cards[1].getRank() && this->cards[3].getRank() == this->cards[4].getRank()) {
        this->identity_card_1 = this->cards[3];
        this->identity_card_2 = this->cards[0];
        this->ranking = two_pair;
        a = true; }

    return a;
}

//id_card_1 := the thip rank card
bool Hand::CheckThreeOfAKind() {
    bool a = false;

    if(this->cards[0].getRank() == this->cards[1].getRank() &&
       this->cards[1].getRank() == this->cards[2].getRank()) {
        this->identity_card_1 = this->cards[0];
        this->ranking = three_of_a_kind;
        a = true; }

    if(this->cards[1].getRank() == this->cards[2].getRank() &&
       this->cards[2].getRank() == this->cards[3].getRank()) {
        this->identity_card_1 = this->cards[1];
        this->ranking = three_of_a_kind;
        a = true; }

    if(this->cards[2].getRank() == this->cards[3].getRank() &&
       this->cards[3].getRank() == this->cards[4].getRank()) {
        this->identity_card_1 = this->cards[2];
        this->ranking = three_of_a_kind;
        a = true; }

    return a;
}

//id_card_1 := the straight starting card
bool Hand::CheckStraight() {
    bool a = false;
    if(this->cards[1].getRank() == this->cards[0].getRank() + 1 &&
       this->cards[2].getRank() == this->cards[0].getRank() + 2 &&
       this->cards[3].getRank() == this->cards[0].getRank() + 3 &&
       this->cards[4].getRank() == this->cards[0].getRank() + 4) {
        this->identity_card_1 = this->cards[0];
        this->ranking = straight;
        a = true; }

    return a;
}

//id_card_1 := the hightest rank card
bool Hand::CheckFlush() {
    bool a = false;
    if(this->cards[1].getSuit() == this->cards[0].getSuit() &&
       this->cards[2].getSuit() == this->cards[0].getSuit() &&
       this->cards[3].getSuit() == this->cards[0].getSuit() &&
       this->cards[4].getSuit() == this->cards[0].getSuit()) {
        this->identity_card_1 = this->cards[4];
        this->ranking = flush;
        a = true; }

    return a;
}

//id_card_1 := the trip rank card
//id_card_2 := the pair rank card
bool Hand::CheckFullHouse() {
    bool a = false;
    if(this->cards[0].getRank() == this->cards[1].getRank() &&
       this->cards[1].getRank() == this->cards[2].getRank() &&
       this->cards[3].getRank() == this->cards[4].getRank()) {
        this->identity_card_1 = this->cards[0];
        this->identity_card_2 = this->cards[3];
        this->ranking = full_house;
        a = true; }

    if(this->cards[0].getRank() == this->cards[1].getRank() &&
       this->cards[2].getRank() == this->cards[3].getRank() &&
       this->cards[3].getRank() == this->cards[4].getRank()) {
        this->identity_card_1 = this->cards[3];
        this->identity_card_2 = this->cards[0];
        this->ranking = full_house;
        a = true; }

    return a;
}

//id_card_1 := the four rank card
bool Hand::CheckFourOfAKind() {
    bool a = false;

    if(this->cards[0].getRank() == this->cards[1].getRank() &&
       this->cards[1].getRank() == this->cards[2].getRank() &&
       this->cards[2].getRank() == this->cards[3].getRank()) {
        this->identity_card_1 = this->cards[0];
        this->identity_card_2 = this->cards[4];
        this->ranking = four_of_a_kind;
        a = true; }

    if(this->cards[1].getRank() == this->cards[2].getRank() &&
       this->cards[2].getRank() == this->cards[3].getRank() &&
       this->cards[3].getRank() == this->cards[4].getRank()) {
        this->identity_card_1 = this->cards[1];
        this->identity_card_2 = this->cards[0];
        this->ranking = four_of_a_kind;
        a = true; }

    return a;
}

//id_card_1 := the straight flush starting rank card
bool Hand::CheckStraightFlush() {
    bool _straight = false;
    if(this->cards[1].getRank() == this->cards[0].getRank() + 1 &&
       this->cards[2].getRank() == this->cards[0].getRank() + 2 &&
       this->cards[3].getRank() == this->cards[0].getRank() + 3 &&
       this->cards[4].getRank() == this->cards[0].getRank() + 4) {
        _straight = true; }

    bool _flush = false;
    if(this->cards[1].getSuit() == this->cards[0].getSuit() &&
       this->cards[2].getSuit() == this->cards[0].getSuit() &&
       this->cards[3].getSuit() == this->cards[0].getSuit() &&
       this->cards[4].getSuit() == this->cards[0].getSuit()) {
        _flush = true; }

    if(_flush && _straight) {
        this->identity_card_1 = this->cards[0];
        this->ranking = straight_flush;
    }

    return _flush && _straight;
}

//id_card_1 := the ace
bool Hand::CheckRoyalFlush() {
    bool _straight = false;
    if(this->cards[1].getRank() == this->cards[0].getRank() + 1 &&
       this->cards[2].getRank() == this->cards[0].getRank() + 2 &&
       this->cards[3].getRank() == this->cards[0].getRank() + 3 &&
       this->cards[4].getRank() == this->cards[0].getRank() + 4) {
        _straight = true; }

    bool _flush = false;
    if(this->cards[1].getSuit() == this->cards[0].getSuit() &&
       this->cards[2].getSuit() == this->cards[0].getSuit() &&
       this->cards[3].getSuit() == this->cards[0].getSuit() &&
       this->cards[4].getSuit() == this->cards[0].getSuit()) {
        _flush = true; }

    bool _royal = false;
    if(this->cards[4].getRank() == ace)
        _royal = true;

    if(_flush && _straight && _royal) {
        this->identity_card_1 = this->cards[4];
        this->ranking = royal_flush;
    }

    return _flush && _straight && _royal;

}

Hand::Hand(Card *_cards, int _size) {
    for (int i = 0; i < 5; ++i) {
        Card newCard(_cards[i]);
        this->cards[i] = newCard;
    }

    std::sort(this->cards, this->cards + 5);

    this->CheckHighCard();
    this->CheckPair();
    this->CheckTwoPair();
    this->CheckThreeOfAKind();
    this->CheckStraight();
    this->CheckFlush();
    this->CheckFullHouse();
    this->CheckFourOfAKind();
    this->CheckStraightFlush();
    this->CheckRoyalFlush();

}

std::ostream &operator<<(std::ostream &os, const Hand &hand) {
    switch(hand.ranking) {
        case high_card:
            os << "high card: " << hand.identity_card_1;
            break;
        case pair:
            os << "pair of " << hand.identity_card_1.getRankString() << "s";
            break;
        case two_pair:
            os << "two pair: " << hand.identity_card_1.getRankString() << "s over " << hand.identity_card_2.getRankString() << "s";
            break;
        case three_of_a_kind:
            os << "three of a kind: " << hand.identity_card_1.getRankString() << "s";
            break;
        case straight:
            os << "straight, starting with: " << hand.identity_card_1.getRankString();
            break;
        case flush:
            os << "flush, with high card: " << hand.identity_card_1.getRankString();
            break;
        case full_house:
            os << "full house: " << hand.identity_card_1.getRankString() << "s on " << hand.identity_card_2.getRankString() << "s";
            break;
        case four_of_a_kind:
            os << "full house: " << hand.identity_card_1.getRankString() << "s";
            break;
        case straight_flush:
            os << "straight flush, starting with: " << hand.identity_card_1.getRankString();
            break;
        case royal_flush:
            os << "ROYAL FLUSH BABYY";
            break;
    }
    return os;
}

bool Hand::operator<(const Hand &rhs) const {
    if(ranking < rhs.ranking)
        return true;
    else if (ranking > rhs.ranking)
        return false;

    //hands are equal in rankings
    int i = 4;
    switch(ranking) {
        case high_card:
            if(identity_card_1.getRank() != rhs.identity_card_1.getRank())
                return identity_card_1 < rhs.identity_card_1;
            while(cards[i] != rhs.cards[i] && i >= 0)
                --i;
            return i < 0 || (cards[i] < rhs.cards[i]);
        case pair:
            if(identity_card_1.getRank() != rhs.identity_card_1.getRank())
                return identity_card_1.getRank() < rhs.identity_card_1.getRank();
            while(cards[i] != rhs.cards[i] && i >= 0)
                --i;
            return i < 0 || (cards[i] < rhs.cards[i]);
        case two_pair:
            if(identity_card_1.getRank() != rhs.identity_card_1.getRank())
                return identity_card_1.getRank() < rhs.identity_card_1.getRank();
            if(identity_card_2.getRank() != rhs.identity_card_2.getRank())
                return identity_card_2.getRank() < rhs.identity_card_2.getRank();
            while(cards[i] != rhs.cards[i] && i >= 0)
                --i;
            return i < 0 || (cards[i] < rhs.cards[i]);
        case three_of_a_kind:
            if(identity_card_1.getRank() != rhs.identity_card_1.getRank())
                return identity_card_1.getRank() < rhs.identity_card_1.getRank();
            while(cards[i] != rhs.cards[i] && i >= 0)
                --i;
            return i < 0 || (cards[i] < rhs.cards[i]);
        case straight:
            return identity_card_1.getRank() < rhs.identity_card_1.getRank();
        case flush:
            return identity_card_1.getRank() < rhs.identity_card_1.getRank();
        case full_house:
            if(identity_card_1.getRank() != rhs.identity_card_1.getRank())
                return identity_card_1.getRank() < rhs.identity_card_1.getRank();
            if(identity_card_2.getRank() != rhs.identity_card_2.getRank())
                return identity_card_2.getRank() < rhs.identity_card_2.getRank();
            while(cards[i] != rhs.cards[i] && i >= 0)
                --i;
            return i < 0 || (cards[i] < rhs.cards[i]);
        case four_of_a_kind:
            if(identity_card_1.getRank() != rhs.identity_card_1.getRank())
                return identity_card_1.getRank() < rhs.identity_card_1.getRank();
            while(cards[i] != rhs.cards[i] && i >= 0)
                --i;
            return i < 0 || (cards[i] < rhs.cards[i]);
        case straight_flush:
            return identity_card_1.getRank() < rhs.identity_card_1.getRank();
        case royal_flush:
            return false;
    }
    return true;
}

std::vector<Hand> Hand::evaluate(std::vector<Card> &cards) {
    unsigned int set_size = (unsigned int) cards.size();
    unsigned int pow_set_size = (unsigned int) pow(2, set_size);
    std::vector<Hand> hands;

    if(set_size < 5)
        return hands;

    if(set_size == 5){
        Card handCards[5];
        for (int i = 0; i < 5; ++i) {
            Card newCard(cards[i]);
            handCards[i] = newCard;
        }
        Hand newHand(handCards, 5);
        hands.push_back(newHand);
    }

    for (int counter = 0; counter < pow_set_size; ++counter) {
        int subset_size = 0;
        for (int j = 0; j < set_size; ++j) {
            if(counter & (1<<j))
                subset_size++;
        }

        if(subset_size == 5) {
            Card handCards[5];
            int handCardsIndex = 0;
            for (int j = 0; j < set_size; ++j) {
                if(counter & (1<<j)) {
                    Card newCard(cards[j]);
                    handCards[handCardsIndex++] = newCard;
                }
            }
            Hand newHand(handCards, 5);
            hands.push_back(newHand);
        }
    }
    return hands;
}
