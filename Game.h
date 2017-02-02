//
// Created by Janusz Grzesik on 01.02.2017.
//

#ifndef POOKER_GAME_H
#define POOKER_GAME_H


#include "Player.h"

class Game {
private :
    vector<Player*> players;
    int blind;


public:
    virtual ~Game();

    Game(vector<Player*>, int);

    void start();

    vector<Player*> copyPlayers();

    void updateBlindsAndRemove();

};


#endif //POOKER_GAME_H
