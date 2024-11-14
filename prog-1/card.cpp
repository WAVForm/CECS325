//Author: Yunis Nabiyev
//CECS 325-02 Prog 1: War
//Due: 02/15/2024

#include "card.h"
#include <iostream>

Card::Card(char cardRank, char cardSuit){
	rank = cardRank;
	suit = cardSuit;
}

void Card::display(){
	if(rank == 'k'){
		std::cout << 'K';
	}
	else if(rank == '@'){
		std::cout << 10;
	}
	else if(rank == '1'){
		std::cout << 'A';
	}
	else{
		std::cout << rank;
	}
	std::cout << suit << " ";
	std::cout << " ";
}

int Card::compare(Card other){
	if(rank > other.rank){
		return 1;
	}else if(rank < other.rank){
		return -1;
	}else{
		return 0;
	}
}
