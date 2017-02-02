//
// Created by Janusz Grzesik on 01.02.2017.
//

#include "Game.h"
#include "GameRound.h"

Game::Game(vector<Player *> playersVector, int smallBlind) {
    players = playersVector;
    blind = smallBlind;
}

void Game::start() {

    int i = 0;
    int j;

    while (players.size() > 1) {
        i = (int) ((i % players.size()));
        j = (int) (((i + 1) % players.size()));

        players[i]->setStatus(smallBlind);
        players[j]->setStatus(bigBlind);

        GameRound g = GameRound(players, blind);

        vector<Player *> w = g.start();

        std::cout << "^^^ winners of the round ^^^" << std::endl;

        int amount = (int) w.size();
        int each = g.getPot() / amount;
        for (Player *k : w) {
            cout << "Player: " << k->getName() << " gets: " << each << " chips" << endl;
            k->addMoney(each);
        }

        this->updateBlindsAndRemove();
        i++;
    }

    std::cout << "*** The winner is " << players[0]->getName() << " won: " << players[0]->getMoney() << " ***"
              << std::endl;
}

void Game::updateBlindsAndRemove() {
    std::vector<Player *> newPlay = std::vector<Player *>();

    for (auto it = players.begin(); it != players.end(); it++) {
        if ((*it)->getMoney() <= blind * 2) {
            cout << (*it)->getName() << " will be removed" << endl;
        } else {
            newPlay.push_back((*it));
            (*it)->clearHand();
        }
    }

    players.clear();
    for (Player *p: newPlay) {
        players.push_back(p);
    }
}

Game::~Game() {
    for (std::vector<Player *>::iterator it = players.begin(); it != players.end(); ++it) {
        delete (*it);
    }
    players.clear();
}

