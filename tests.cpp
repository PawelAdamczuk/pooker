#include <iostream>
#include "Player.h"
#include "BotPlayer.h"
#include "Card.h"
#include "CardDeck.h"
#include "Hand.h"
#include "map"
#include <string>

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

void test_Hand_3() {
    CardDeck cd;
    cd.shuffle();
    std::vector<Card> card_set;
    for (int i = 0; i < 6; ++i) {
        card_set.push_back(cd.deal());
    }

    std::vector<Hand> hands = Hand::evaluate(card_set);

    std::cout << "cards:" << std::endl;

    for (int i = 0; i < 6; ++i) {
        std::cout << card_set[i] << std::endl;
    }

    std::sort(hands.begin(), hands.end());

    std::cout << "" << std::endl;

    for (int j = 0; j < hands.size(); ++j) {
        std::cout << hands[j] << std::endl;
    }
}

void test_CardDeck_deal() {
    CardDeck cd;
    cd.shuffle();
    std::cout << "deal:" << std::endl;
    for (int i = 0; i < 52; ++i) {
        std::cout << cd.deal() << std::endl;
    }
}

void test(bool cond, string name = "") {
    if (!cond) {
        std::cout << "  ✘   " << name << std::endl;
    } else {
        std::cout << "  ✓   " << name << std::endl;
    }
}


void testPlayer() {
    std::cout << "Player tests:" << std::endl;

    Player p("Random", 1);
    test(p.getMoney() == 1, "Get money works");
    test(p.getName() == "Random", "Get name works");
    test(!p.isDealer, "Is by default a not a dealer");
    test(p.getStatus() == pleb, "Is by default a pleb");

    p.setStatus(bigBlind);
    test(p.getStatus() == bigBlind, "setStatus and getStatus work");

    p.addMoney(100);

    test(p.getMoney() == 101, "Adding money works");

    bool errored = false;
    try {
        p.subtractChips(102);
    } catch (...) {
        errored = true;
    }
    test(errored, "Subtracting more money than has - throws an error");

    p.subtractChips(20);

    test(p.getMoney() == 81, "Subtracting less money than has - works");

    p.addCard(Card(five, diamonds));
    p.addCard(Card(ace, clubs));

    vector<Card> cards = p.getCards();

    test(cards.size() == 2, "Adding cards works");

    test(cards[0].getRank() == five
         && cards[0].getSuit() == diamonds
         && cards[1].getRank() == ace
         && cards[1].getSuit() == clubs, "Hand is in order, cards were pushed");
}

void testBotPlayer() {
    std::cout << "Bot player tests" << std::endl;
    BotPlayer p("Kaka", 1);

    vector<Player*> v = {&p};

    auto it = v.begin();

    test((*it)->call(1, true, preflop, 1, std::vector<Player*>(), nullptr, nullptr, 10) != -127, "Can make virtual call");
}


int main() {
    testPlayer();
    testBotPlayer();

    std::cout << "Hello, World!" << std::endl;

//    test_Card_1();
//    test_CardDeck_1();
//    test_CardDeck_deal();
//    test_Hand_1();
//    test_Hand_2();
    test_Hand_3();
    return 0;
}