//
// Created by pawel on 02.02.17.
//

#ifndef POOKER_HUMANPLAYER_H
#define POOKER_HUMANPLAYER_H


#include "Player.h"

class HumanPlayer : public Player {
public:
    HumanPlayer(const string &name, int money);

    int call(int amount, bool canRaise, const RoundPhase phase, int pot, const vector<Player*> otherPlayers,
             const vector<Card> *cards, const map<string, int> *bets, int smallBlind);
private:
    bool randomTest(int probability);

    int getMaxPossible(int bet);
};


#endif //POOKER_HUMANPLAYER_H
