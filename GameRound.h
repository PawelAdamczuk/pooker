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
#include "utils.h"
#include <string>


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

    vector<Player> getWinners();
public:
    GameRound(std::vector<Player> playersVector, int smallBlind);

    std::vector<Player> start();

    void printPlayersInGame();
};

#endif //POOKER_ABSTRACTROUND_H
