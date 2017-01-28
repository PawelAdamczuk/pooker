//
// Created by Janusz Grzesik on 26.01.2017.
//

#include "GameRound.h"

GameRound::GameRound(std::vector<Player> playersVector, Presenter pres, int blind) {
    presenter = pres;
    players = playersVector;

    deck = CardDeck();
    bets = std::map<Player, int>();
    burnedCards = std::vector<Card>();
    tableCards = std::vector<Card>();
    blind = blind;

    pot = 0;
    bestBet = 0;
    betsSum = 0;
}

template<class T>
class CyclicIterator {
private:
    std::vector<T> vec;
    std::vector<T>::iterator it;

public:
    CyclicIterator(std::vector<T> vec) : vec(vec), it(vec.begin()) {}

    CyclicIterator &operator++() {
        it++;
        if (isEnd()) {
            it = vec.begin();
        }
    }

    CyclicIterator &operator--() {
        it++;
        if (isEnd()) {
            it = vec.begin();
        }
    }

    bool isEnd() {
        return it == vec.end();
    }

    T &operator*() {
        return *it;
    }
};

void GameRound::burnCard() {
    this->burnedCards.push_back(this->deck.deal());
}

std::vector<Player> GameRound::getWinners() {
    std::sort(this->players.begin(), this->players.end());
    std::vector<Player> winners;

    auto it = this->players.end();
    winners.push_back(*it--);

    while (*it == winners.back()) {
        winners.push_back(*it--);
    }

    return winners;
}

bool GameRound::shouldFinish() {
    return this->players.size() <= 1;
}

void GameRound::addBetsToPot() {
    for (std::map<Player, int>::iterator it = bets.begin(); it != bets.end(); ++it) {
        pot += it->second;
    }

    bets.clear();
}

void GameRound::present() {
    presenter.update(this);
}

void GameRound::dealCardToPlayer(Player p) {
    p.addCard(deck.deal());
}

void GameRound::start() {
    this->playPreflop();

}


void GameRound::playPreflop() {
    phase = preflop;

    for (auto player :players) {
        player.addCard(deck.deal());
        player.addCard(deck.deal());
    }

    CyclicIterator<Player> it = CyclicIterator(players);
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

RoundPhase GameRound::getRoundPhase() {
    return flop;
}

std::ostream &operator<<(std::ostream &os, const GameRound &hand) {
    return <#initializer#>;
}


bool GameRound::betsAreEqualized() {
    for (Player p : players) {
        if (!this->getPlayerBetToCall(p) == 0) {
            return false;
        }
    }

    return true;
}

void GameRound::roundOfBetting(CyclicIterator it) {
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
        if (players[i] == p) {
            players.erase(players.begin() + i);
            return;
        }
    }
}

int GameRound::getPlayerBets(Player p) {
    if (this->bets.find(p) != this->bets.end()) {
        return this->bets[p];
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

    int finalAmount = player.call(amount, canRaise);
    if (finalAmount == -1) {
        return this->removePlayer(player);
    }

    player.subtractChips(finalAmount);
    this->addPlayersBet(player, finalAmount);
}

void GameRound::addPlayersBet(Player &player, int amount) {
    if (this->bets.find(player) != this->bets.end()) {
        amount += this->bets[player];
    }

    this->bets[player] = amount;

    if (bestBet < amount) {
        bestBet = amount;
    }
}



