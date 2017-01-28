//
// Created by Janusz Grzesik on 26.01.2017.
//

#ifndef POOKER_ABSTRACTROUND_H
#define POOKER_ABSTRACTROUND_H
#include "Player.h"
#include "vector"
#include "map"
#include "Card.h"
#include "Presenter.h"
#include "CardDeck.h"

enum RoundPhase{preflop= 0, flop, turn, river};

class GameRound {
private:
    std::vector<Player> players;
    Presenter presenter;
    std::map<Player,int> bets;
    std::vector<Card> burnedCards;
    std::vector<Card> tableCards;

    CardDeck deck;
    RoundPhase phase;
    int bestBet;
    int betsSum;
    int blind;
    int pot;


    void burnCard();
    bool shouldFinish();
    void addBetsToPot();
    void dealCardToPlayer(Player p);
    void present();



 public:
    GameRound(std::vector<Player> playersVector, Presenter presenter, int smallBlind);
    RoundPhase getRoundPhase();

    void start();
    void bet(Player p, int amount);
    void fold(Player p);

    const std::vector<Card> getTableCards;

    friend std::ostream &operator<<(std::ostream &os, const GameRound &hand);

    std::vector<Player> getWinners();

    void playPreflop();

    void addCardToTable();


    void addPlayersBet(Player &player, int amount);

    void removePlayer(Player p);

    void callPlayer(Player &player, int amount, bool canRaise, bool isBlindCall);

    void cycleToEqualizeBets(CyclicIterator it);

    bool playerBetIsEqual(Player p);

    int getPlayerBets(Player p);

    bool betsAreEqualized();

    int getPlayerBetToCall(Player p);

    void roundOfBetting(CyclicIterator it);
};


#endif //POOKER_ABSTRACTROUND_H
