//
// Created by Janusz Grzesik on 01.02.2017.
//

#include "Player.h"
#include "BotPlayer.h"
#include "GameRound.h"
#include "Game.h"


int main() {
    vector<Player> players = {
            BotPlayer("James", 100),
            BotPlayer("Bruce", 100),
            BotPlayer("Kate", 100),
            BotPlayer("Ian", 100),
    };


    Game g = Game(players, 5, 100);
    g.start();
}
