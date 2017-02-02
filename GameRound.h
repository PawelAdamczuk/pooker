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
#include "Hand.h"
#include <string>


class GameRound {
private:
    std::vector<Player*> players;
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

    void addCardToTable();

    vector<Player*> getWinners();

    void printPlayersInGame();

    void printTableCards();

    void addPlayersBet(string playersName, int amount);

    int getPlayerBets(string playersName);

    void removePlayer(string playersName);

    void callPlayer(Player *player, int amount, bool canRaise, bool isBlindCall);

    int getPlayerBetToCall(string playersBet);

    void roundOfBetting();

    std::vector<Hand> getPlayerHands(Player *player);
public:
    GameRound(std::vector<Player*> playersVector, int smallBlind);

    std::vector<Player*> start();

    bool compareHands(Player *first, Player *second);

    int getPot();
};

#endif //POOKER_ABSTRACTROUND_H
