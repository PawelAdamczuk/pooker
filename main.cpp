#include <iostream>
#include "Card.h"
#include "CardDeck.h"

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


int main() {
    std::cout << "Hello, World!" << std::endl;

//    test_Card_1();
    test_CardDeck_1();
    return 0;
}