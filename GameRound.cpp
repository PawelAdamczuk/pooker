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
    smallBlind = blind;

    pot = 0;
    bestBet = 0;
    betsSum = 0;
}


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
    for(std::map<Player,int>::iterator it = bets.begin(); it != bets.end(); ++it) {
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

    //TODO
}

RoundPhase GameRound::getRoundPhase() {
    return flop;
}

std::ostream &operator<<(std::ostream &os, const GameRound &hand) {
    return <#initializer#>;
}

void GameRound::bet(Player p, int amount) {

}

void GameRound::fold(Player p) {

}


