#include <iostream>
#include "Card.h"

void test_card_1() {
    Card card1(two, hearts);
    Card card2(ace, spades);
    std::cout << card1 << std::endl;
    std::cout << card1 << " > " << card2 << "?" << std::endl;
    std::cout << (card1 > card2) << std::endl;
}



int main() {
    std::cout << "Hello, World!" << std::endl;

    test_card_1();
    return 0;
}