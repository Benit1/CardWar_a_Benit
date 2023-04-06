//
// Created by beni on 3/25/23.
//
#include "game.hpp"

#include <random>

ariel::Game::Game(Player &pl1, Player &pl2) : pl1(pl1), pl2(pl2), logger(), turns(0) {
    pl1.setPlaying(true);
    pl2.setPlaying(true);
    this->setCardDeck();
    shuffleGameDeckAndDeal(this->card_deck);

}


void ariel::Game::playAll() {
    while (logger.getWinner() == 3) {
        this->playTurn();
    }
}

void ariel::Game::playTurn() {
    if (logger.getWinner() != 3) {
        throw logic_error("Game has ended can't play another turn");
    }
    if (!pl1.isPlaying() && !pl2.isPlaying()) {
        throw std::invalid_argument("The game has ended");
    }
    if (pl1.getID() == pl2.getID()) {
        throw std::logic_error("A player can't play with himself.");
    }
    string turnLog;
    turns++;
    vector<Card> pl1ThrownCards = pl1.getSideDeck();
    vector<Card> pl2ThrownCards = pl1.getSideDeck();
    bool lowAmountOfCards = false;
    enum winner currentWinner;
    int round = 0;
    if (pl1.stacksize() > 0 || pl2.stacksize() > 0) {
        if (pl1.stacksize() <= 1 || pl2.stacksize() <= 1) {
            lowAmountOfCards = true;
        }
        Card pl1Card;
        Card pl2Card;
        drawCardEach(pl1ThrownCards, pl2ThrownCards, pl1Card, pl2Card);
        currentWinner = pl1Card.compare(pl2Card);
        while (true) {
            if (currentWinner == player1) {
                player1WonTurn(pl1ThrownCards, pl2ThrownCards, currentWinner, pl1Card, pl2Card);
                break;
            } else if (currentWinner == player2) {
                player2WonTurn(pl1ThrownCards, pl2ThrownCards, currentWinner, pl1Card, pl2Card);
                break;
            } else if (currentWinner == draw) {
                if (lowAmountOfCards && round > 0) {
                    if (pl1.stacksize() == 0 || pl2.stacksize() == 0) {
                        pl1.setCardsTaken(1);
                        pl2.setCardsTaken(1);
                    } else {
                        pl1.setCardsTaken(2);
                        pl2.setCardsTaken(2);
                    }
                    return;
                }
                round += 1;
                updateDraws();
                logger.addLog(currentWinner, pl1, pl2, pl1Card, pl2Card);
                if (lowAmountOfCards) {
                    reshuffle(pl1ThrownCards, pl2ThrownCards);
                    drawCardEach(pl1ThrownCards, pl2ThrownCards, pl1Card, pl2Card);
                    currentWinner = pl1Card.compare(pl2Card);
                    break;
                } else if (pl1.stacksize() >= 2 || pl2.stacksize() >= 2) {
                    draw2Cards(pl1ThrownCards, pl2ThrownCards, pl1Card, pl2Card);
                    currentWinner = pl1Card.compare(pl2Card);
                } else {
                    break;
                }
            }
            if (pl1.stacksize() == 0 || pl2.stacksize() == 0) {
                if (!pl1ThrownCards.empty() || !pl2ThrownCards.empty()) {
                    if (currentWinner == player1) {
                        player1WonTurn(pl1ThrownCards, pl2ThrownCards, currentWinner, pl1Card, pl2Card);
                    } else if (currentWinner == player2) {
                        player2WonTurn(pl1ThrownCards, pl2ThrownCards, currentWinner, pl1Card, pl2Card);
                    } else {
                        pl1.setCardsTaken(pl1ThrownCards.size());
                        pl2.setCardsTaken(pl2ThrownCards.size());
                    }
                }
                setWinner();
                break;
            }
        }
        if (pl1.stacksize() == 0 || pl2.stacksize() == 0) {
            setWinner();
        }
    }
}

void ariel::Game::drawCardEach(vector<Card> &pl1ThrownCards, vector<Card> &pl2ThrownCards, ariel::Card &pl1Card,
                               ariel::Card &pl2Card) {
    pl1Card = pl1.drawCard();
    pl2Card = pl2.drawCard();
    pl1ThrownCards.push_back(pl1Card);
    pl2ThrownCards.push_back(pl2Card);
}

void ariel::Game::setWinner() {
    pl1.setPlaying(false);
    pl2.setPlaying(false);
    if (pl1.cardesTaken() > pl2.cardesTaken()) {
        logger.setWinner(player1);
    } else if (pl1.cardesTaken() < pl2.cardesTaken()) {
        logger.setWinner(player2);
    } else {
        logger.setWinner(draw);
    }
}

void ariel::Game::draw2Cards(vector<Card> &pl1ThrownCards, vector<Card> &pl2ThrownCards, ariel::Card &pl1Card,
                             ariel::Card &pl2Card) {
    pl1Card = pl1.drawCard();
    pl1ThrownCards.push_back(pl1Card);
    pl2Card = pl2.drawCard();
    pl2ThrownCards.push_back(pl2Card);
    pl1Card = pl1.drawCard();
    pl2Card = pl2.drawCard();
    pl1ThrownCards.push_back(pl1Card);
    pl2ThrownCards.push_back(pl2Card);

}

void ariel::Game::updateDraws() {
    pl1.setDrawRate(turns);
    pl2.setDrawRate(turns);
    pl1.setDraws();
    pl2.setDraws();
}

void ariel::Game::reshuffle(vector<Card> &pl1ThrownCards, vector<Card> &pl2ThrownCards) {
    vector<Card> pl1Deck = pl1.getPlayerDeck();
    pl1Deck.insert(pl1Deck.end(), pl1ThrownCards.begin(), pl1ThrownCards.end());
    unsigned seed = time(nullptr);
    shuffle(pl1Deck.begin(), (pl1Deck.end()), default_random_engine(seed));
    pl1.setPlayerDeck(pl1Deck);
    pl1ThrownCards.clear();
    vector<Card> pl2Deck = pl2.getPlayerDeck();
    pl2Deck.insert(pl2Deck.end(), pl2ThrownCards.begin(), pl2ThrownCards.end());
    seed = time(nullptr);
    shuffle(pl2Deck.begin(), (pl2Deck.end()), default_random_engine(seed));
    pl2.setPlayerDeck(pl2Deck);
    pl2ThrownCards.clear();
}

void
ariel::Game::player1WonTurn(const vector<Card> &pl1ThrownCards, const vector<Card> &pl2ThrownCards,
                            winner &currentWinner,
                            const ariel::Card &pl1Card, const ariel::Card &pl2Card) {
    pl1.setCardsTaken(pl1ThrownCards.size() + pl2ThrownCards.size());
    pl1.setWins();
    setRates();
    logger.addLog(currentWinner, pl1, pl2, pl1Card, pl2Card);
}

void ariel::Game::setRates() {
    pl1.setWinRate(turns);
    pl2.setWinRate(turns);
    pl1.setDrawRate(turns);
    pl2.setDrawRate(turns);
}

void
ariel::Game::player2WonTurn(const vector<Card> &pl1ThrownCards, const vector<Card> &pl2ThrownCards,
                            winner &currentWinner,
                            const ariel::Card &pl1Card, const ariel::Card &pl2Card) {
    pl2.setCardsTaken(pl1ThrownCards.size() + pl2ThrownCards.size());
    pl2.setWins();
    setRates();
    logger.addLog(currentWinner, pl1, pl2, pl1Card, pl2Card);
}

void ariel::Game::printLastTurn() {
    logger.printLastTurn();
}

void ariel::Game::printLog() {
    logger.printLog();
}

void ariel::Game::printStats() const {
    Logger::printStats(this->getPl1(), this->getPl2());
}

void ariel::Game::printWiner() {
    logger.printWinner(pl1.getPlayerName(), pl2.getPlayerName());
}

ariel::Player &ariel::Game::getPl1() const {
    return pl1;
}


ariel::Player &ariel::Game::getPl2() const {
    return pl2;
}

void ariel::Game::setCardDeck() {
    array<Card, CARD_DECK_SIZE> newDeck;
    for (size_t index = 0; index < 13; ++index) {
        for (size_t jndex = 0; jndex < 4; ++jndex) {
            std::string cardShape;
            cardShape = numberToCardShape((int) jndex, cardShape);
            Card currentCard((int) (index + 1), cardShape);
            newDeck[(index * 4) + jndex] = currentCard;
        }
    }
    this->card_deck = newDeck;
}

string &ariel::Game::numberToCardShape(int index, string &cardShape) {
    switch (index) {
        case 0:
            cardShape = "Clubs (♣)";
            break;
        case 1:
            cardShape = "Diamonds (♦)";
            break;
        case 2:
            cardShape = "Hearts (♥)";
            break;
        case 3:
            cardShape = "Spades (♠)";
            break;
        default:
            break;
    }
    return cardShape;
}

void ariel::Game::shuffleGameDeckAndDeal(std::array<ariel::Card, CARD_DECK_SIZE> deck) {
    unsigned seed = time(nullptr);
    shuffle(deck.begin(), (deck.end()), default_random_engine(seed));
    vector<Card> pl1Deck;
    vector<Card> pl2Deck;
    for (size_t i = 0; i < deck.size(); i++) {
        if (i < 26) {
            pl1Deck.push_back(deck[i]);
        } else {
            pl2Deck.push_back(deck[i]);
        }
    }
    pl1.setPlayerDeck(pl1Deck);
    pl2.setPlayerDeck(pl2Deck);
}
