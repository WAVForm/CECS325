//Author: Yunis Nabiyev
//CECS 325-02 Prog 1: War
//Due: 02/15/2024

#include <iostream>
#include <iomanip>
#include "card.h"
#include "deck.h"

int main(){
	Deck deck = Deck();
	std::string p1, p2;
	int score[2][3] = {{0,0,0},{0,0,0}};
	std::cout << "Enter Player 1's Name: ";
	std::cin >> p1;
	std::cout << "Enter Player 2's Name: ";
	std::cin >> p2;
	
	std::cout << "Deck Loaded: ";
	deck.display();
	deck.shuffle();
	std::cout << std::endl << "Deck Shuffled: ";
	deck.display();

	for(int i = 0; i < 26; i++){
		std::cout << std::endl;
		std::cout << "Game #" << i+1 << " :" << std::endl;

		Card p1Card = deck.deal();
		Card p2Card = deck.deal();

		std::cout  << p1 << ": ";
		p1Card.display();
		std::cout << std::endl;
		std::cout << p2 << ": ";
		p2Card.display();
		std::cout << std::endl;

		switch (p1Card.compare(p2Card)){
			case 1:
				std::cout << "Player " << p1 <<"  won!" << std::endl;
				score[0][0]++;
				score[1][1]++;
				break;
			case -1:
				std::cout << "Player " <<  p2 << " won!" << std::endl;
				score[0][1]++;
				score[1][0]++;
				break;
			default:
				std::cout << "Tie!" << std::endl;
				score[0][2]++;
				score[1][2]++;
				break;
		}
	}
	std::cout << std::setfill(' ') << "Player" << std::setw(5) << "W" << std::setw(5) << "L" << std::setw(5) << "T" << std::endl;
	std::cout << std::setfill(' ') << std::setw(6) << p1 << std::setw(5) << score[0][0] << std::setw(5) << score[0][1] << std::setw(5) << score[0][2] << std::endl;
	std::cout << std::setfill(' ') << std::setw(6) << p2 << std::setw(5) << score[1][0] << std::setw(5) << score[1][1] << std::setw(5) << score[1][2] << std::endl;
	std::cout << std::endl;

	if(score[0][0] > score[1][0]){
		std::cout << "Player " << p1 << " has won the game!" << std::endl;
	}
	else if(score[0][0] < score [1][0]){
		std::cout << "Player " << p2 << " has won the game!" << std::endl;
	}
	else{
		std::cout << "The game concludes in a tie..." << std::endl;
	}
}
