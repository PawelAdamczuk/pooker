//
// Created by Janusz Grzesik on 26.01.2017.
//

#include "GameRound.h"
#include "Hand.h"

GameRound::GameRound(std::vector<Player *> playersVector, int smallBlind) {
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
    std::cout << "GameRound: burning card" << std::endl;
    this->burnedCards.push_back(this->deck.deal());
}

bool GameRound::compareHands(Player *first, Player *second) { //true if first precedes second
    std::vector<Hand> firstHands = this->getPlayerHands(first);
    std::vector<Hand> secondHands = this->getPlayerHands(second);

    auto f = firstHands.begin();
    auto s = secondHands.begin();

    if(*f == *s)
        return false;

    return !(*f < *s);
}

std::vector<Hand> GameRound::getPlayerHands(Player *player) {
    std::vector<Card> playerCards = std::vector<Card>();

    std::copy(tableCards.begin(), tableCards.end(), back_inserter(playerCards));

    std::vector<Hand> result = Hand::evaluate(playerCards);

    std::sort(result.begin(), result.end());

    return result;
}


std::vector<Player *> GameRound::getWinners() {
    if (this->players.size() == 1) return players;

    std::sort(this->players.begin(), this->players.end(), [this](Player *l, Player *s) -> bool {
        return this->compareHands(l, s);
    });
    std::vector<Player *> winners;

    auto it = this->players.begin();
    winners.push_back(*it);
    it++;

    while (it != players.end() && !(compareHands(*it, winners.back()))) { //TODO ensure good sorting
        winners.push_back(*it);
        it++;
    }

    return winners;
}

bool GameRound::shouldFinish() {
    return this->players.size() <= 1;
}

std::vector<Player *> GameRound::start() {
    std::cout << "Shuffling the deck" << endl;
    deck.shuffle();
    deck.shuffle();

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
        break;
    }

    for (Player *p : this->players) {
        vector<Hand> hands = getPlayerHands(p);

        if (hands.size() > 0) {
            std::cout << p->getName() << ": " << hands[0] << std::endl;
            for (auto k : hands) {
                cout << k << endl;
            }
        } else {
            std::cout << p->getName() << ": nothing" << std::endl;
        }
    }

    return this->getWinners();
}

void GameRound::printPlayersInGame() {
    std::cout << "players in game: ";

    for (Player *p: players) {
        std::cout << p->getName() << " ";
    }

    std::cout << std::endl;
}

void GameRound::playPreflop() {
    std::cout << "Starting preflop ";
    this->printPlayersInGame();

    phase = preflop;

    for (Player *player :players) {
        player->addCard(deck.deal());
        player->addCard(deck.deal());
    }

    this->printTableCards();


    CyclicIterator<Player *> it = CyclicIterator<Player *>(&players);

    while ((*it)->getStatus() != smallBlind) {
        ++it;
    }

    std::cout << "Small blind: " << std::endl;
    this->callPlayer((*it), blind, false, true); // small blind
    ++it;
    std::cout << "Big blind: " << std::endl;
    this->callPlayer((*it), blind * 2, false, true); //big blind
    ++it;

    do {
        this->roundOfBetting();
        std::cout << std::endl;
    } while (!this->betsAreEqualized());
    std::cout << std::endl;
}

void GameRound::playFlop() {
    std::cout << "Starting flop" << std::endl;
    this->printPlayersInGame();

    phase = flop;

    this->burnCard();

    this->addCardToTable();
    this->addCardToTable();
    this->addCardToTable();

    this->printTableCards();

    CyclicIterator<Player *> it = CyclicIterator<Player *>(&players);

    do {
        this->roundOfBetting();
        std::cout << std::endl;
    } while (!this->betsAreEqualized());
    std::cout << std::endl;
}

void GameRound::playTurn() {
    std::cout << "Starting turn" << std::endl;
    this->printPlayersInGame();

    phase = turn;

    this->burnCard();

    this->addCardToTable();

    this->printTableCards();

    CyclicIterator<Player *> it = CyclicIterator<Player *>(&players);

    do {
        this->roundOfBetting();
        std::cout << std::endl;
    } while (!this->betsAreEqualized());
    std::cout << std::endl;
}

void GameRound::playRiver() {
    std::cout << "Starting river" << std::endl;
    this->printPlayersInGame();

    phase = river;

    this->burnCard();

    this->addCardToTable();

    this->printTableCards();

    CyclicIterator<Player *> it = CyclicIterator<Player *>(&players);

    do {
        this->roundOfBetting();
        std::cout << std::endl;
    } while (!this->betsAreEqualized());
    std::cout << std::endl;
}

void GameRound::prepareNextRound() {
    bets.clear();
    bestBet = 0;
}

bool GameRound::betsAreEqualized() {
    for (Player *p: players) {
        if (this->getPlayerBetToCall(p->getName()) != 0) {
            return false;
        }
    }

    return true;
}

void GameRound::roundOfBetting() {
    int toGo = (int) players.size();

    CyclicIterator<Player *> it = CyclicIterator<Player *>(&players);

    while (toGo != 0) {
        toGo--;
        int toCall = this->getPlayerBetToCall((*it)->getName());
        this->callPlayer(*it, toCall, true, false);
        ++it;
    }
}

void GameRound::removePlayer(string playersName) {
    for (auto it = players.begin(); it != players.end(); it++) {

        if ((*it)->getName() == playersName) {
            players.erase(it);
            return;
        }
    }
}

int GameRound::getPlayerBets(string playersName) {
    if (this->bets.find(playersName) != this->bets.end()) {
        return this->bets[playersName];
    }
    return 0;
}

int GameRound::getPlayerBetToCall(string playersName) {
    return bestBet - this->getPlayerBets(playersName);
}

void GameRound::addCardToTable() {

    const Card &card = deck.deal();
    std::cout << "Adding card to table: " << card << std::endl;
    tableCards.push_back(card);
}

void GameRound::callPlayer(Player *player, int amount, bool canRaise = false, bool isBlindCall = false) {
    const string playersName = player->getName();

    std::cout << "Call to: " << playersName << " for amount: " << amount << " pot is: " << pot << std::endl;
    if (isBlindCall) {
        player->subtractChips(amount);
        return this->addPlayersBet(playersName, amount);
    }

    int finalAmount = player->call(amount, canRaise, phase, pot, players, &tableCards, &bets, blind);
    if (finalAmount == -1 || finalAmount < amount) {
        std::cout << playersName << " folded" << std::endl;
        return this->removePlayer(playersName);
    }

    player->subtractChips(finalAmount);
    this->addPlayersBet(playersName, finalAmount);
}

void GameRound::addPlayersBet(string playersName, int amount) {
    pot += amount;
    amount += this->getPlayerBets(playersName);

    this->bets[playersName] = amount;

    if (bestBet < amount) {
        bestBet = amount;
        std::cout << playersName << " raised the bet: " << bestBet << std::endl;
    } else {
        std::cout << playersName << " called" << std::endl;

    }
}

void GameRound::printTableCards() {
    std::cout << "Cards on the table: " << std::endl;
    for (std::vector<Card>::iterator it = this->tableCards.begin(); it != this->tableCards.end(); ++it) {
        std::cout << "  " << *it << std::endl;
    }
}

int GameRound::getPot() {
    return pot;
}





