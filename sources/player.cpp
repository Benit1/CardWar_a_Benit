//
// Created by beni on 3/21/23.
//

#include "player.hpp"


using namespace std;


ariel::Player::Player(std::string player_name) {}

ariel::Player::~Player() {}

int ariel::Player::stacksize() {
    return this->stack_size;
}

int ariel::Player::cardesTaken() {
    return this->cards_taken;
}
