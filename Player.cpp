#include <iostream>
#include "Player.h"
#include "Deck.h"

//Set player wallet value
void Player::setWallet(int value) {
	wallet = value;
}

//newCard == Deck::pop()
void Player::receiveCardFromDealer(card* newCard) {
	if (cardsInHand < 5) {
		hand[cardsInHand] = newCard;
		cardsInHand++;
	}
}

//newCard == Deck::pop()
void Player::swapCard(card* newCard, int discardedCardIndex) {
	delete hand[discardedCardIndex - 1];
	hand[discardedCardIndex - 1] = newCard;
}

void Player::displayHand() {
	if (isPlaying) {
		std::cout << "Player " << playerNumber << "'s hand:\n";
		for (int i = 0; i < cardsInHand; i++) {
			std::cout << "Card " << i + 1 << ": ";
			//Deck is a Heart
			if (hand[i]->suit == 0) {
				if (hand[i]->number == 0)
					std::cout << "This card is an Ace of Hearts" << std::endl;
				else if (hand[i]->number == 10)
					std::cout << "This card is a Jack of Hearts" << std::endl;
				else if (hand[i]->number == 11)
					std::cout << "This card is a Queen of Hearts" << std::endl;
				else if (hand[i]->number == 12)
					std::cout << "This card is a King of Hearts" << std::endl;
				else
					std::cout << "This card is a " << hand[i]->number + 1 << " of Hearts" << std::endl;
			}
			//Deck is a Diamond
			if (hand[i]->suit == 1) {
				if (hand[i]->number == 0)
					std::cout << "This card is an Ace of Diamonds" << std::endl;
				else if (hand[i]->number == 10)
					std::cout << "This card is a Jack of Diamonds" << std::endl;
				else if (hand[i]->number == 11)
					std::cout << "This card is a Queen of Diamonds" << std::endl;
				else if (hand[i]->number == 12)
					std::cout << "This card is a King of Diamonds" << std::endl;
				else
					std::cout << "This card is a " << hand[i]->number + 1 << " of Diamonds" << std::endl;
			}
			//Deck is a Club
			if (hand[i]->suit == 2) {
				if (hand[i]->number == 0)
					std::cout << "This card is an Ace of Clubs" << std::endl;
				else if (hand[i]->number == 10)
					std::cout << "This card is a Jack of Clubs" << std::endl;
				else if (hand[i]->number == 11)
					std::cout << "This card is a Queen of Clubs" << std::endl;
				else if (hand[i]->number == 12)
					std::cout << "This card is a King of Clubs" << std::endl;
				else
					std::cout << "This card is a " << hand[i]->number + 1 << " of Clubs" << std::endl;
			}
			//Deck is a Spade
			if (hand[i]->suit == 3) {
				if (hand[i]->number == 0)
					std::cout << "This card is an Ace of Spades" << std::endl;
				else if (hand[i]->number == 10)
					std::cout << "This card is a Jack of Spades" << std::endl;
				else if (hand[i]->number == 11)
					std::cout << "This card is a Queen of Spades" << std::endl;
				else if (hand[i]->number == 12)
					std::cout << "This card is a King of Spades" << std::endl;
				else
					std::cout << "This card is a " << hand[i]->number + 1 << " of Spades" << std::endl;
			}
		}
		std::cout << std::endl;
	}
}

void Player::makeBet(int betAmount) {
	wallet -= betAmount;
}

int Player::getWallet() {
	return wallet;
}

void Player::displayWallet() {
	std::cout << "Player " << playerNumber << " has $" << wallet << std::endl << std::endl;
}

void Player::setPlayerNumber(int number) {
	playerNumber = number;
}

int Player::getPlayerNumber() {
	return playerNumber;
}

void Player::setIsPlaying(int number) {
	isPlaying = number;
}

int Player::getIsPlaying() {
	return isPlaying;
}

void Player::winMoney(int winnings) {
	wallet += winnings;
}

int Player::getCardValue(int cardNumber) {
	return hand[cardNumber-1]->number;
}

int Player::getCardSuit(int cardNumber) {
	return hand[cardNumber-1]->suit;
}
