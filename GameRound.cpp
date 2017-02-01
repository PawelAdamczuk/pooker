//
// Created by Janusz Grzesik on 26.01.2017.
//

#include "GameRound.h"
#include "Hand.h"

GameRound::GameRound(vector<Player> playersVector, int smallBlind) {
    players = playersVector;

    deck = CardDeck();
    bets = map<string, int>();
    burnedCards = vector<Card>();
    tableCards = vector<Card>();

    blind = smallBlind;
    pot = 0;
    bestBet = 0;
}

void GameRound::burnCard() {
    cout << "GameRound: burning card" << endl;
    this->burnedCards.push_back(this->deck.deal());
}

bool compareHands(Player first, Player second) {
    vector<Card> firstCards = vector<Card>();
    std::copy(first.getCards().begin(), first.getCards().end(), back_inserter(firstCards));

    vector<Card> secondCards = vector<Card>();
    std::copy(second.getCards().begin(), second.getCards().end(), back_inserter(secondCards));

    vector<Hand> firstHands = Hand::evaluate(firstCards);
    vector<Hand> secondHands = Hand::evaluate(secondCards);

    auto f = firstHands.begin();
    auto s = secondHands.begin();

    while (true) {
        bool firstEnded = f == firstHands.end();
        bool secondEnded = s == secondHands.end();
        if (firstEnded && secondEnded) return false;

        if (firstEnded) return true;

        if (secondEnded) return true;

        bool handsAreEqual = *f < *s && *s < *f;
        if (!handsAreEqual) return *f < *s;

        f++;
        s++;
    }
}


vector<Player> GameRound::getWinners() {
    sort(this->players.begin(), this->players.end(), compareHands);
    vector<Player> winners;

    auto it = this->players.end();
    winners.push_back(*it--);

    while (compareHands(*it, winners.back())) { //TODO ensure good sorting
        winners.push_back(*it--);
    }

    return winners;
}

bool GameRound::shouldFinish() {
    return this->players.size() <= 1;
}

vector<Player> GameRound::start() {
    while (true) {
        this->playPreflop();

        this->prepareNextRound();
        if (this->shouldFinish()) break;

        this->playFlop();

        this->prepareNextRound();
        if (this->shouldFinish()) break;

        this->playTurn();

        this->prepareNextRound();
        if (this->shouldFinish()) break;

        this->playRiver();
    }

    return this->getWinners();
}

void GameRound::printPlayersInGame() {
    cout << "players in game: ";

    for (auto p: players) {
        cout << p.getName() << " ";
    }

    cout << endl;
}

void GameRound::playPreflop() {
    cout << "GameRound: Starting preflop";
    this->printPlayersInGame();

    phase = preflop;

    for (auto player :players) {
        player.addCard(deck.deal());
        player.addCard(deck.deal());
    }


    CyclicIterator<Player> it = CyclicIterator<Player>(players);

    while ((*it).getStatus() != smallBlind) {
        ++it;
    }

    cout << "GameRound: small blind: " << endl;
    this->callPlayer(*it, blind, false, true); // small blind
    ++it;
    cout << "GameRound: big blind: " << endl;
    this->callPlayer(*it, blind * 2, false, true); //big blind
    ++it;

    do {
        this->roundOfBetting(it);
    } while (!this->betsAreEqualized());
}

void GameRound::playFlop() {
    cout << "GameRound: Starting flop" << endl;
    this->printPlayersInGame();

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
    cout << "GameRound: Starting turn" << endl;
    this->printPlayersInGame();

    phase = turn;

    this->burnCard();

    this->addCardToTable();

    CyclicIterator<Player> it = CyclicIterator<Player>(players);

    do {
        this->roundOfBetting(it);
    } while (!this->betsAreEqualized());
}

void GameRound::playRiver() {
    cout << "GameRound: Starting river" << endl;
    this->printPlayersInGame();

    phase = river;

    this->burnCard();

    this->addCardToTable();

    CyclicIterator<Player> it = CyclicIterator<Player>(players);

    do {
        this->roundOfBetting(it);
    } while (!this->betsAreEqualized());
}

void GameRound::prepareNextRound() {
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

    const Card &card = deck.deal();
    cout << "GameRound: adding card to table: " << card;
    tableCards.push_back(card);
}

void GameRound::callPlayer(Player &player, int amount, bool canRaise = false, bool isBlindCall = false) {
    cout << "GameRound: call to player" << player.getName() << " for amount: " << amount << " pot is: " << pot << endl;
    if (isBlindCall) {
        player.subtractChips(amount);
        this->addPlayersBet(player, amount);
    }

    int finalAmount = player.call(amount, canRaise, phase, pot, &players, &tableCards, &bets, blind);
    if (finalAmount == -1 || finalAmount < amount) {
        cout << "GameRound" << player.getName() << " folded" << endl;
        return this->removePlayer(player);
    }

    player.subtractChips(finalAmount);
    this->addPlayersBet(player, finalAmount);
}

void GameRound::addPlayersBet(const Player &player, int amount) {
    pot += amount;
    amount += this->getPlayerBets(player);

    this->bets[player.getName()] = amount;

    if (bestBet < amount) {
        bestBet = amount;
        cout << "GameRound" << player.getName() << " raised! Best bet: " << bestBet << endl;
    } else {
        cout << "GameRound" << player.getName() << " called" << endl;

    }
}




