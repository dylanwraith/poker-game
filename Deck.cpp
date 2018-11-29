#include <iostream>
#include <time.h>
#include "Deck.h"

void Deck::makeDeck() {
	cardsInDeck = 52;
	for (int i = 0; i < 52; i++) {
		//Card is a Heart
		if (i < 13) {
			card* newCard = new card;
			newCard->number = i;
			newCard->suit = 0;
			deck[i] = newCard;
		}
		//Card is a Diamond
		else if (i < 26) {
			card* newCard = new card;
			newCard->number = i - 13;
			newCard->suit = 1;
			deck[i] = newCard;
		}
		//Card is a Club
		else if (i < 39) {
			card* newCard = new card;
			newCard->number = i - 26;
			newCard->suit = 2;
			deck[i] = newCard;
		}
		//Card is a Spade
		else {
			card* newCard = new card;
			newCard->number = i - 39;
			newCard->suit = 3;
			deck[i] = newCard;
		}
	}
}

void Deck::randomizeDeck() {
	srand(time(NULL));
	for (int i = 0; i < rand(); ++i){
		int randomIndex1 = (rand() + i) % 26 + 26;
		int randomIndex2 = (rand() + i) % 26;
		card* tempCard = deck[randomIndex1];
		deck[randomIndex1] = deck[randomIndex2];
		deck[randomIndex2] = deck[51];
		deck[51] = deck[25];
		deck[25] = deck[0];
		deck[0] = tempCard;
	}
}

card* Deck::pop() {
	if (cardsInDeck > 0) {
		card* topCard = deck[cardsInDeck - 1];
		cardsInDeck--;
		return topCard;
	}
}

void Deck::displayDeck() {
	for (int i = 0; i < cardsInDeck; i++) {
		//Deck is a Heart
		if (deck[i]->suit == 0) {
			if (deck[i]->number == 0)
				std::cout << "This card is an Ace of Hearts" << std::endl;
			else if (deck[i]->number == 10)
				std::cout << "This card is a Jack of Hearts" << std::endl;
			else if (deck[i]->number == 11)
				std::cout << "This card is a Queen of Hearts" << std::endl;
			else if (deck[i]->number == 12)
				std::cout << "This card is a King of Hearts" << std::endl;
			else
				std::cout << "This card is a " << deck[i]->number + 1 << " of Hearts" << std::endl;
		}
		//Deck is a Diamond
		if (deck[i]->suit == 1) {
			if (deck[i]->number == 0)
				std::cout << "This card is an Ace of Diamonds" << std::endl;
			else if (deck[i]->number == 10)
				std::cout << "This card is a Jack of Diamonds" << std::endl;
			else if (deck[i]->number == 11)
				std::cout << "This card is a Queen of Diamonds" << std::endl;
			else if (deck[i]->number == 12)
				std::cout << "This card is a King of Diamonds" << std::endl;
			else
				std::cout << "This card is a " << deck[i]->number + 1 << " of Diamonds" << std::endl;
		}
		//Deck is a Club
		if (deck[i]->suit == 2) {
			if (deck[i]->number == 0)
				std::cout << "This card is an Ace of Clubs" << std::endl;
			else if (deck[i]->number == 10)
				std::cout << "This card is a Jack of Clubs" << std::endl;
			else if (deck[i]->number == 11)
				std::cout << "This card is a Queen of Clubs" << std::endl;
			else if (deck[i]->number == 12)
				std::cout << "This card is a King of Clubs" << std::endl;
			else
				std::cout << "This card is a " << deck[i]->number + 1 << " of Clubs" << std::endl;
		}
		//Deck is a Spade
		if (deck[i]->suit == 3) {
			if (deck[i]->number == 0)
				std::cout << "This card is an Ace of Spades" << std::endl;
			else if (deck[i]->number == 10)
				std::cout << "This card is a Jack of Spades" << std::endl;
			else if (deck[i]->number == 11)
				std::cout << "This card is a Queen of Spades" << std::endl;
			else if (deck[i]->number == 12)
				std::cout << "This card is a King of Spades" << std::endl;
			else
				std::cout << "This card is a " << deck[i]->number + 1 << " of Spades" << std::endl;
		}
	}
}
