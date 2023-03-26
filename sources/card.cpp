//
// Created by beni on 3/21/23.
//

#include "card.hpp"


using namespace std;

ariel::Card::Card(int card_number, string shape) {}

ariel::Card::Card() {}

ariel::Card::~Card() {}

int ariel::Card::getCard_number() {
    return card_number;
}

string ariel::Card::getShape() {
    return shape;
}

string ariel::Card::toString() {
    return "";
}

int ariel::Card::compare(Card other) {
    return 0;
}

