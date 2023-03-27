//
// Created by beni on 3/21/23.
//

#ifndef CARDWAR_A_MAIN_GAME_H
#define CARDWAR_A_MAIN_GAME_H

#include <array>
#include <iostream>
#include "player.hpp"
#include "card.hpp"

namespace ariel {
    class Game {
    private:
        Player &p1;
        Player &p2;
        static constexpr int CARD_DECK_SIZE = 52;
        std::array <Card, CARD_DECK_SIZE> card_deck;

    public:
        Game(Player &pl1, Player &pl2);

        ~Game();

        void playAll();

        void printWiner();

        void printLog();

        void printStats();

        void playTurn();

        void printLastTurn();

    };
}

#endif //CARDWAR_A_MAIN_GAME_H
