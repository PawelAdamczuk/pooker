//
// Created by Janusz Grzesik on 01.02.2017.
//

#ifndef POOKER_BOTPLAYER_H
#define POOKER_BOTPLAYER_H


#include "Player.h"

class BotPlayer : public Player{
public:
    BotPlayer(const string &name, int money);

    int call(int amount, bool canRaise, const RoundPhase phase, int pot, const vector<Player*> otherPlayers,
                 const vector<Card> *cards, const map<string, int> *bets, int smallBlind);
private:
    bool randomTest(int probability);

    int getMaxPossible(int bet);
};

#endif //POOKER_BOTPLAYER_H
