//
// Created by beni on 3/21/23.
//

#ifndef CARDWAR_A_MAIN_CARD_H
#define CARDWAR_A_MAIN_CARD_H

#include <iostream>

using namespace std;
namespace ariel {
    class Card {
        int card_number;//(ace(1),2-10,Jack(11),queen(12),king(13))
        string shape;//(clubs (♣), diamonds (♦), hearts (♥), and spades (♠))

    public:
        Card(int card_number, string shape);

        Card();

        ~Card();

        string toString();

        int getCard_number();

        string getShape();

        int compare(Card other);

    };
}


#endif //CARDWAR_A_MAIN_CARD_H
