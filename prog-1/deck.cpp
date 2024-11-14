//Author: Yunis Nabiyev
//CECS 325-02 Prog 1: War
//Due: 02/15/2024

#include "deck.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

Deck::Deck(){
	char ranks[] = {'k', 'Q', 'J', '@', '9', '8', '7', '6', '5', '4', '3', '2', '1'};
	char suits[] = {'S', 'H', 'D', 'C'};
	for(char suit : suits){
		for(char rank : ranks){
			deck.push_back(Card(rank, suit));	
		}
	}
}

Card Deck::deal(){
	Card card = deck.back();
	deck.pop_back();
	return card;
}

void Deck::display(){
	for(Card card : deck){
		card.display();
	}
	std::cout << std::endl;
}

void Deck::shuffle(){
	srand(time(nullptr));
	int shuffleMax = 10000;
	int shuffleMin = 1000;
	int shuffleCount = rand() % (shuffleMax - shuffleMin + 1) + shuffleMin;
	for(int i = 0; i <= shuffleCount; i++){
		Card* card1 = &deck.at(rand() % deck.size());
		Card* card2 = &deck.at(rand() % deck.size());
		Card temp = *card1;
		*card1 = *card2;
		*card2 = temp;
	}
	std::cout << shuffleCount << " random card swaps completed" << std::endl;
}

