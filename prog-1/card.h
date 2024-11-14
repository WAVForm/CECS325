//Author: Yunis Nabiyev
//CECS 325-02 Prog 1: War
//Due: 02/15/2024

#ifndef CARD_H
#define CARD_H

class Card{
private:
	char rank;
	char suit;
public:
	Card(char cardRank, char cardSuit);

	void display();

	int compare(Card other);
};
#endif 
