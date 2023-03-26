//
// Created by beni on 3/24/23.
//
#include "doctest.h"
#include "sources/player.hpp"
#include "sources/game.hpp"
#include "sources/card.hpp"
#include <iostream>
#include <stdexcept>

using namespace ariel;
using namespace std;


TEST_CASE("Stack initialization") {
// Creating two players
    Player p1("Alice");
    Player p2("Bob");

// Creating a new game with the two players
    Game game(p1, p2);

// Check that the stack size for each player is 26
    CHECK(p1.stacksize() == 26);
    CHECK(p2.stacksize() == 26);
    CHECK(p1.cardesTaken() == 0);
    CHECK(p2.cardesTaken() == 0);

}

TEST_CASE("Player can only be registered to one game") {
    Player p1("Alice");
    Player p2("Bob");
    Game game(p1, p2);
    CHECK_THROWS_WITH(Game game2(p1, p2), "A player cannot be registered to 2 games");
}

TEST_CASE("Trying to print stats when no turns have been played") {
    Player p1("Alice");
    Player p2("Bob");
    Game game(p1, p2);
    CHECK_THROWS_WITH(game.printLastTurn(), "No turns have been played yet");
    CHECK_THROWS_WITH(game.printStats(), "No games have been played yet");
}

TEST_CASE("Print winner without error") {
    Player p1("Alice");
    Player p2("Bob");
    Game game(p1, p2);
    CHECK_NOTHROW(game.playAll());
    CHECK_NOTHROW(game.printWiner());
}

//These tests are extra because I tested functions I created
TEST_CASE("Card initialization") {
//creating two cards
    Card c1(5, "clubs");
    Card c2(13, "hearts");
//Checks that the card has been initialized successfully
    CHECK(c1.getCard_number() == 5);
    CHECK(c1.getShape() == "clubs");
    CHECK(c2.getCard_number() == 13);
    CHECK(c1.getShape() == "hearts");
}

TEST_CASE("Card comparison") {
//creating four cards
    Card c1(5, "clubs");
    Card c2(13, "hearts");
    Card c3(1, "diamonds");
    Card c4(5, "spades");
//compares the cards
    CHECK(c1.compare(c2) < 0);
    CHECK(c1.compare(c4) == 0);
    CHECK(c2.compare(c3) > 0);
    CHECK(c4.compare(c2) < 0);

}