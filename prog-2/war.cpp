//Author: Yunis Nabiyev
//CECS 325-02 Prog 2: More War
//Due: 02/27/2024

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip>

using namespace std;

class Card{
	private:
		char rank;
		char suit;
	public:
		Card(char cardRank, char cardSuit){
			rank = cardRank;
			suit = cardSuit;
		}
		
		Card(){
			rank = ' ';
			suit = ' ';
		}

		void display(){
			if(rank == 'k'){
				cout << 'K';
			}
			else if(rank == '@'){
				cout << 10;
			}
			else if(rank == '1'){
				cout << 'A';
			}
			else{
				cout << rank;
			}
			cout << suit << " ";
		}

		int compare(Card other){
			if(rank > other.rank){
				return 1;
			}
			else if(rank < other.rank){
				return -1;
			}
			else{
				return 0;
			}
		}
};

class Deck{
	private:
		int size = 52;
		Card deck[52];
	public:
		Deck(){
			char suits[] = {'S', 'H', 'D', 'C'};
			char ranks[] = {'k', 'Q', 'J', '@', '9', '8', '7', '6', '5', '4', '3', '2', '1'};
			int i = 0;
			for(char suit : suits){
				for(char rank : ranks){
					deck[i] = Card(rank,suit);
					i++;
				}
			}
		}

		Card deal(){
			if(isEmpty()){
				throw 0;
			}
			
			Card card = deck[size-1];
			size--;
			return card;
		}

		void display(){
			int i = 0;
			while(i < size){
				deck[i].display();
				i++;
			}
			cout << endl;
		}

		void shuffle(){
			srand(time(0));
			int shuffleMax = 10000000; // 10 million
			int shuffleMin = 100000;	    // 100 thousand
			int shuffleCount = rand() % (shuffleMax - shuffleMin + 1) + shuffleMin;
			
			for(int i = 0; i <= shuffleCount; i++){
				Card* card1 = &(deck[rand() % size]);
				Card* card2 = &(deck[rand() % size]);
				Card temp = *card1;
				*card1 = *card2;
				*card2 = temp;
			}

			cout << shuffleCount << " random card swaps completed" << endl;
		}

		bool isEmpty(){
			return size <= 0;
		}
	
};

int main(){
	string p1, p2;
	int score[3] = {0,0,0}; //p1 W/L/T, or p2 L/W/T
	cout << "Enter Player 1's Name: ";
	cin >> p1;
	cout << "Enter Player 2's Name: ";
	cin >> p2;

	int gameAmt;
	cout << "Games to play? ";
	cin >> gameAmt;

	Deck deck = Deck();
	cout << "Deck Loaded: " << endl;
	deck.display();
	deck.shuffle();
	cout << "Deck Shuffled: " << endl;
	deck.display();
	
	int curr = 0;
	while(gameAmt > 0){
		curr++;
		cout << endl << "Game #" << curr << " :" << endl;
		Card p1Card, p2Card;
		try{
			p1Card = deck.deal();
			p2Card = deck.deal();
		}
		catch(int e){
			cout << "The deck is empty..." << endl;
			gameAmt = 0;
			break;
		}

		cout << p1 << ": ";
		p1Card.display();
		cout << endl << p2 << ": ";
		p2Card.display();
		cout << endl;

		switch(p1Card.compare(p2Card)){
			case 1:
				cout << p1 << " won!" << endl;
				score[0]++;
				break;
			case -1:
				cout << p2 << " won!" << endl;
				score[1]++;
				break;
			case 0:
				cout << "Tie!" << endl;
				score[2]++;
				break;
			default:
				break;
		}
		gameAmt--;
	}
		cout << setfill(' ') << "Player" << setw(5) << "W" << setw(5) << "L" << setw(5) << "T" << endl;
		cout << setfill(' ') << setw(6) << p1 << setw(5) << score[0] << setw(5) << score[1] << setw(5) << score[2] << endl;
		cout << setfill(' ') << setw(6) << p2 << setw(5) << score[1] << setw(5) << score[0] << setw(5) << score[2] << endl;

		if(score[0] > score[1]){
			cout << p1 << " has won the game!" << endl;
		}
		else if(score[0] < score[1]){
			cout << p2 << " has won the game!" << endl;
		}
		else{
			cout << "The game concludes in a tie..." << endl;
		}

}
