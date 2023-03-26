//
// Created by beni on 3/21/23.
//

#ifndef CARDWAR_A_MAIN_GAME_H
#define CARDWAR_A_MAIN_GAME_H

#include <iostream>
#include "player.hpp"
#include "card.hpp"

namespace ariel {
    class Game {
    private:
        Player p1;
        Player p2;
        Card card_deck[52];
    public:
        Game(Player p1, Player p2);

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
