//
// Created by Janusz Grzesik on 01.02.2017.
//

#include "Player.h"
#include "BotPlayer.h"
#include "GameRound.h"
#include "Game.h"


int main() {
    BotPlayer *james = new BotPlayer("James", 100);
    BotPlayer *kate = new BotPlayer("Kate", 100);
    BotPlayer *bruce = new BotPlayer("Bruce", 100);
    BotPlayer *ian = new BotPlayer("Ian",100);
    vector<Player*> players = {
            james,
            kate,
            bruce,
            ian
    };


    Game g = Game(players, 5);
    g.start();
}
