//
// Created by Janusz Grzesik on 01.02.2017.
//

#include "Player.h"
#include "BotPlayer.h"
#include "GameRound.h"
#include "Game.h"
#include "HumanPlayer.h"


int main() {
    std::string playerName;
    int monies;
    int smallblind;
    std::cout << "Please input your name: " << std::endl;
    std::cin >> playerName;
    std::cout << "Please input the initial amount of money for every player: " << std::endl;
    std::cin >> monies;
    std::cout << "Please input the small blind: " << std::endl;
    std::cin >> smallblind;
    BotPlayer *james = new BotPlayer("James", monies);
    BotPlayer *kate = new BotPlayer("Kate", monies);
    BotPlayer *bruce = new BotPlayer("Bruce", monies);
    HumanPlayer *human = new HumanPlayer(playerName, monies);
    vector<Player*> players = {
            james,
            kate,
            bruce,
            human
    };

    Game g = Game(players, smallblind);
    g.start();
}
