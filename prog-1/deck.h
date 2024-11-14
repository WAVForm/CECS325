//Author: Yunis Nabiyev
//CECS 325-02 Prog 1: War
//Due: 02/15/2024

#ifndef DECK_H
#define DECK_H

#include "card.h"
#include <vector>

class Deck{
private:
	std::vector<Card> deck;

public:
	Deck();

	Card deal();

	void display();

	void shuffle();
};
#endif
