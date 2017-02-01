//
// Created by Janusz Grzesik on 01.02.2017.
//

#include "Game.h"
#include "GameRound.h"

Game::Game(vector<Player> playersVector, int smallBlind, int initalMoney) {
    players = playersVector;
    blind = smallBlind;
    money = initalMoney;
}

void Game::start() {
    players[0].setStatus(smallBlind);
    players[1].setStatus(bigBlind);
//    while (players.size() > 1) {
//
//
//    }
    for (auto player : players) {
        player.addMoney(money);
    }

    GameRound g = GameRound(players, blind);

    vector<Player> w = g.start();

    for (auto k : w) {
        cout << "WON: " << k.getName();
    }


}

vector<Player> Game::copyPlayers() {
    vector<Player> copy = vector<Player>();
    std::copy(players.begin(), players.end(), back_inserter(copy));
    return copy;
}

void Game::updateBlindsAndRemove() {

//    CyclicIterator<Player> it = CyclicIterator(players);
//
//    bool smallFound = false;
//    bool bigFound = false;
//
//    while (true) {
//        if ((*it).getStatus() == smallBlind) {
//            smallFound = true;
//        }
//
//        if ((*it).getMoney() < 2 * blind) {
////            players.erase(it,i)
//        }
//        //TODO
//
//    }
//

}

