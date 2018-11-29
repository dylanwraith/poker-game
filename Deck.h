#pragma once

struct card {
	int suit;
	int number;
};

class Deck {
private:
	//A = 0, J = 10, Q = 11, K = 12
	//0-12 = H, 13-25 = D, 26-38 = C, 39-51 = S
	card* deck[52];
	int cardsInDeck = 52;
public:
	void makeDeck();
	void randomizeDeck();
	void displayDeck();
	card* pop();
};

