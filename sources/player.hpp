//
// Created by beni on 3/21/23.
//

#ifndef CARDWAR_A_MAIN_PLAYER_H
#define CARDWAR_A_MAIN_PLAYER_H

#include <iostream>
#include "card.hpp"

using namespace std;
namespace ariel {
    class Player {
    private:
        int stack_size;
        int cards_taken;
        string player_name;
        Card *player_deck;
        Card *side_deck;

    public:

        Player(std::string player_name);

        ~Player();

        int stacksize();

        int cardesTaken();

    };
}

#endif //CARDWAR_A_MAIN_PLAYER_H
