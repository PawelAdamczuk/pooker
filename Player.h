//
// Created by Janusz Grzesik on 26.01.2017.
//

#ifndef POOKER_PLAYER_H
#define POOKER_PLAYER_H

#include <string>
#include <vector>
#include "Card.h"
#include <map>
#include "utils.h"

using namespace std;

enum PlayerStatus {
    pleb, smallBlind, bigBlind
};

class Player {
protected:
    vector<Card> hand;
    int money;
    string name;
    PlayerStatus status;


public:
    Player(string name, int money);

    void addCard(Card card);

    void setStatus(PlayerStatus s);

    virtual int call(int amount, bool canRaise, const RoundPhase phase, int pot, const vector<Player> *otherPlayers,
                         const vector<Card> *cards, const map<string, int> *bets, int smallBlind);

    void subtractChips(int amount);
    string getName() const;
    int getMoney();

    PlayerStatus getStatus() const;

    void addMoney(int amount);

    vector<Card> getCards();

    bool isDealer;
};


#endif //POOKER_PLAYER_H
