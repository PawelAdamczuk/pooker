#include <iostream>
#include "Card.h"
#include "CardDeck.h"
#include "Hand.h"

void test_Card_1() {
    Card card1(two, hearts);
    Card card2(ace, spades);
    std::cout << card1 << std::endl;
    std::cout << card1 << " > " << card2 << "?" << std::endl;
    std::cout << (card1 > card2) << std::endl;
}

void test_CardDeck_1() {
    CardDeck cd;
    std::cout << "deck 1:" << std::endl;
    std::cout << cd << std::endl;
    cd.shuffle();
    std::cout << "deck 1 shuffled:" << std::endl;
    std::cout << cd << std::endl;
}

void test_Hand_1() {
    Card card1(three, spades);
    Card card2(three, diamonds);
    Card card3(four, spades);
    Card card4(four, clubs);
    Card card5(ace, spades);

    Card cards[5] = {card1, card2, card3, card4, card5};

    Hand hand(cards, 5);

    std::cout << hand << std::endl;
}

void test_Hand_2() {
    CardDeck cd;
    cd.shuffle();
    Card card_set_1[5];
    Card card_set_2[5];
    for (int i = 0; i < 5; ++i) {
        card_set_1[i] = cd.deal();
    }
    for (int i = 0; i < 5; ++i) {
        card_set_2[i] = cd.deal();
    }

    Hand hand1(card_set_1, 5);
    Hand hand2(card_set_2, 5);

    std::cout << "hand 1:                    hand2:" << std::endl;
    for (int i = 0; i < 5; ++i) {
        std::cout << hand1.cards[i] << "               " << hand2.cards[i] << std::endl;
    }

    std::cout << hand1 << "               " << hand2 << std::endl;
    std::cout << "hand 2 stronger: " << (hand1 < hand2) << std::endl;
}

void test_CardDeck_deal() {
    CardDeck cd;
    cd.shuffle();
    std::cout << "deal:" << std::endl;
    for (int i = 0; i < 52; ++i) {
        std::cout << cd.deal() << std::endl;
    }
}


int main() {
    std::cout << "Hello, World!" << std::endl;

//    test_Card_1();
//    test_CardDeck_1();
//    test_CardDeck_deal();
//    test_Hand_1();
    test_Hand_2();
    return 0;
}