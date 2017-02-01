//
// Created by Janusz Grzesik on 26.01.2017.
//

#ifndef POOKER_ABSTRACTROUND_H
#define POOKER_ABSTRACTROUND_H

#include "Player.h"
#include "vector"
#include "map"
#include "Card.h"
#include "CardDeck.h"
#include <string>

enum RoundPhase {
    preflop = 0, flop, turn, river
};

template<class T>
class CyclicIterator {
private:
    std::vector<T> vec;
    typename std::vector<T>::iterator it;

public:
    CyclicIterator(std::vector<T> vec) : vec(vec), it(vec.begin()) {}

    CyclicIterator& operator++() {
        it++;
        if (isEnd()) {
            it = vec.begin();
        }
        return *this;
    }

    CyclicIterator& operator--() {
        it++;
        if (isEnd()) {
            it = vec.begin();
        }
        return *this;
    }

    bool isEnd() {
        return it == vec.end();
    }

    T &operator*() {
        return *it;
    }
};

class GameRound {
private:
    std::vector<Player> players;
    std::map<string, int> bets;
    std::vector<Card> burnedCards;
    std::vector<Card> tableCards;

    CardDeck deck;
    RoundPhase phase;
    int bestBet;
    int blind;
    int pot;


    void burnCard();

    bool shouldFinish();

    void playPreflop();

    void playFlop();

    void playTurn();

    void playRiver();

    void prepareNextRound();

    bool betsAreEqualized();

    void roundOfBetting(CyclicIterator<Player> it);

    void removePlayer(Player p);

    int getPlayerBets(Player p);

    int getPlayerBetToCall(Player p);

    void addCardToTable();

    void callPlayer(Player &player, int amount, bool canRaise, bool isBlindCall);

    void addPlayersBet(const Player &player, int amount);
public:
    GameRound(std::vector<Player> playersVector, int smallBlind);

    RoundPhase getRoundPhase();

    void start();

    std::vector<Player> getWinners();

};

#endif //POOKER_ABSTRACTROUND_H
