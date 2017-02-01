//
// Created by Janusz Grzesik on 01.02.2017.
//


#include <cassert>
#include "Player.h"
#include "GameRound.h"

using namespace std;

void test(bool cond, string name = "") {
    if (!cond) {
        cout << "  ✘   " << name << endl;
    } else {
        cout << "  ✓   " << name << endl;
    }
}


void testPlayer() {
    cout<<"Player tests:"<<endl;

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

    test(p.getMoney()==81, "Subtracting less money than has - works");

    p.addCard(Card(five, diamonds));
    p.addCard(Card(ace, clubs));

    vector<Card> cards = p.getCards();

    test(cards.size() ==2 , "Adding cards works");

    test(cards[0].getRank() == five
         && cards[0].getSuit() == diamonds
         && cards[1].getRank() == ace
            && cards[1].getSuit() == clubs, "Hand is in order, cards were pushed");

}

int main() {
    testPlayer();
}