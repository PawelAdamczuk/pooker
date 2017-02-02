//
// Created by Janusz Grzesik on 01.02.2017.
//

#include "BotPlayer.h"
#include <random>


BotPlayer::BotPlayer(const string &name, int money) : Player(name, money) {}

int BotPlayer::call(int amount, bool canRaise, const RoundPhase phase, int pot, const vector<Player *> otherPlayers,
                    const vector<Card> *cards, const map<string, int> *bets, int smallBlind) {

    if (amount > money) return -1;

    switch (phase) {
        case preflop: {
            if (randomTest(90)) return amount;
            if (randomTest(10)) return this->getMaxPossible(amount + 2 * smallBlind);
            break;
        }

        case flop : {
            if (amount == 0 && randomTest(20)) return this->getMaxPossible(amount + 4 * smallBlind);
            if (randomTest(30)) return this->getMaxPossible(amount + 2 * smallBlind);
            if (randomTest(80)) return amount;
            break;
        }

        case turn : {
            if (amount == 0 && randomTest(30)) return this->getMaxPossible(amount + 8 * smallBlind);
            if (randomTest(40)) return this->getMaxPossible(amount + 4 * smallBlind);
            if (randomTest(80)) return amount;
            break;
        }

        case river : {
            if (amount == 0 && randomTest(40)) return this->getMaxPossible(amount + 2 * smallBlind);
            if (randomTest(20)) return this->getMaxPossible(amount + smallBlind);
            if (randomTest(20)) return amount;
            break;
        }
    }

    return (amount == 0) ? 0 : -1;
}


bool BotPlayer::randomTest(int probability) {
    return std::rand() % 100 <= probability;
}

int BotPlayer::getMaxPossible(int bet) {
    return bet > money ? money : bet;
}
