//
// Created by pawel on 02.02.17.
//

#include "HumanPlayer.h"

bool HumanPlayer::randomTest(int probability) {
    return rand() % 100 <= probability;
}

int HumanPlayer::getMaxPossible(int bet) {
    return bet > money ? money : bet;
}

HumanPlayer::HumanPlayer(const string &name, int money) : Player(name, money) {}

int HumanPlayer::call(int amount, bool canRaise, const RoundPhase phase, int pot, const vector<Player *> otherPlayers,
                      const vector<Card> *cards, const map<string, int> *bets, int smallBlind) {

    if (amount > money) return -1;

    std::cout << "Player " << this->name << " ready to see your hand and bid?" << std::endl;
    std::cin.ignore();
    std::cout << this->name << "\'s hand: " << std::endl;
    for (std::vector<Card>::iterator it = this->hand.begin(); it != this->hand.end(); ++it) {
        std::cout << "  " << *it << std::endl;
    }

    std::cout << "Chips left: " << this->money << " to call: " << amount << std::endl;

    int bid = -2;
    while (bid < -1 || bid > this->money) {
        std::cout << "Please place your bid [-1 to fold, 0 to check]: "<<std::endl;
        std::cin >> bid;
    }

    return bid;
}
