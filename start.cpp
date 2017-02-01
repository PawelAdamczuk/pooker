//
// Created by Janusz Grzesik on 01.02.2017.
//

#include "Player.h"
#include "BotPlayer.h"
#include "GameRound.h"


int main() {
    vector<Player> players = {
            BotPlayer("James", 100),
            BotPlayer("Bruce", 100),
            BotPlayer("Kate", 100),
            BotPlayer("Ian", 100),
    };


    GameRound round = GameRound(players, 5);

    round.start();
}
