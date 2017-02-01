//
// Created by Janusz Grzesik on 01.02.2017.
//

#include "Player.h"
#include "BotPlayer.h"
#include "GameRound.h"
#include "Game.h"


int main() {
    BotPlayer james ("James", 100);
    BotPlayer kate ("Kate", 100);
    BotPlayer bruce("Bruce", 100);
    BotPlayer ian ("Ian",100);
    vector<Player*> players = {
            &james,
            &kate,
            &bruce,
            &ian
    };


    Game g = Game(players, 5);
    g.start();
}
