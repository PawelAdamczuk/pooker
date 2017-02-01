//
// Created by Janusz Grzesik on 26.01.2017.
//

#include "GameRound.h"

GameRound::GameRound(std::vector<Player> playersVector, int smallBlind) {
    players = playersVector;

    deck = CardDeck();
    bets = std::map<string, int>();
    burnedCards = std::vector<Card>();
    tableCards = std::vector<Card>();

    blind = smallBlind;
    pot = 0;
    bestBet = 0;
}

void GameRound::burnCard() {
    this->burnedCards.push_back(this->deck.deal());
}

std::vector<Player> GameRound::getWinners() {
//    std::sort(this->players.begin(), this->players.end()); //TODO FIX
    std::vector<Player> winners;

    auto it = this->players.end();
    winners.push_back(*it--);
    //TODO FIX
//    while (*it == winners.back()) {
//        winners.push_back(*it--);
//    }

    return winners;
}

bool GameRound::shouldFinish() {
    return this->players.size() <= 1;
}

void GameRound::start() {
    this->playPreflop();

    this->prepareNextRound();
    if (this->shouldFinish()) {
        return;
    }

    this->playFlop();

    this->prepareNextRound();
    if (this->shouldFinish()) {
        return;
    }

    this->playTurn();

    this->prepareNextRound();
    if (this->shouldFinish()) {
        return;
    }

    this->playRiver();

}

void GameRound::playPreflop() {
    phase = preflop;

    for (auto player :players) {
        player.addCard(deck.deal());
        player.addCard(deck.deal());
    }

    CyclicIterator<Player> it = CyclicIterator<Player>(players);
    while ((*it).getStatus() != smallBlind) {
        ++it;
    }

    this->callPlayer(*it, blind, false, true); // small blind
    ++it;
    this->callPlayer(*it, blind * 2, false, true); //big blind
    ++it;

    do {
        this->roundOfBetting(it);
    } while (!this->betsAreEqualized());
}

void GameRound::playFlop() {
    phase = flop;

    this->burnCard();

    this->addCardToTable();
    this->addCardToTable();
    this->addCardToTable();

    CyclicIterator<Player> it = CyclicIterator<Player>(players);

    do {
        this->roundOfBetting(it);
    } while (!this->betsAreEqualized());
}

void GameRound::playTurn() {
    phase = turn;

    this->burnCard();

    this->addCardToTable();

    CyclicIterator<Player> it = CyclicIterator<Player>(players);

    do {
        this->roundOfBetting(it);
    } while (!this->betsAreEqualized());
}

void GameRound::playRiver() {
    phase = river;

    this->burnCard();

    this->addCardToTable();

    CyclicIterator<Player> it = CyclicIterator<Player>(players);

    do {
        this->roundOfBetting(it);
    } while (!this->betsAreEqualized());
}

void GameRound::prepareNextRound() {
    for (auto elem : bets) {
        pot += elem.second;
    }

    bets.clear();
    bestBet = 0;
}

bool GameRound::betsAreEqualized() {
    for (Player p : players) {
        if (this->getPlayerBetToCall(p) != 0) {
            return false;
        }
    }

    return true;
}

void GameRound::roundOfBetting(CyclicIterator<Player> it) {
    int toGo = (int) players.size();

    while (toGo != 0) {
        toGo--;
        int toCall = this->getPlayerBetToCall(*it);
        this->callPlayer(*it, toCall, true, false);
        ++it;
    }
}

void GameRound::removePlayer(Player p) {
    for (int i = 0; i < players.size(); i++) {
        if (players[i].getName() == p.getName()) {
            players.erase(players.begin() + i);
            return;
        }
    }
}

int GameRound::getPlayerBets(const Player p) {
    if (this->bets.find(p.getName()) != this->bets.end()) {
        return this->bets[p.getName()];
    }
    return 0;
}

int GameRound::getPlayerBetToCall(Player p) {
    return bestBet - this->getPlayerBets(p);
}

void GameRound::addCardToTable() {
    tableCards.push_back(deck.deal());
}

void GameRound::callPlayer(Player &player, int amount, bool canRaise = false, bool isBlindCall = false) {
    if (isBlindCall) {
        player.subtractChips(amount);
        this->addPlayersBet(player, amount);
    }

    int finalAmount = player.call(amount, canRaise, phase, pot, &players, &tableCards, &bets, blind);
    if (finalAmount == -1 || finalAmount < amount) {
        return this->removePlayer(player);
    }

    player.subtractChips(finalAmount);
    this->addPlayersBet(player, finalAmount);
}

void GameRound::addPlayersBet(const Player &player, int amount) {
    amount += this->getPlayerBets(player);

    this->bets[player.getName()] = amount;

    if (bestBet < amount) {
        bestBet = amount;
    }
}




