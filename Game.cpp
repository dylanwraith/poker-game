#include <iostream>
#include <time.h>
#include "Game.h"
#include "Deck.h"
#include "Player.h"

void Game::clearScreen() {
	std::cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
}

void Game::initializePlayers() {
	player1.setPlayerNumber(1);
	player2.setPlayerNumber(2);
}

void Game::startNewGame() {
	deck.makeDeck();
	deck.randomizeDeck();
	player1.setIsPlaying(1);
	player2.setIsPlaying(1);
	setFirstPlayer();
	addToPot(&player1, 10);
	addToPot(&player2, 10);
}

void Game::setFirstPlayer() {
	if (player1.isFirst == 0) {
		player1.isFirst = 1;
		player2.isFirst = 0;
	}
	else {
		player1.isFirst = 0;
		player2.isFirst = 1;
	}
}

void Game::addToPot(Player* player, int amount) {
	player->makeBet(amount);
	pot += amount;
}

void Game::dealHands() {
	for (int i = 0; i < 5; i++) {
		if (player1.isFirst){
			player1.receiveCardFromDealer(deck.pop());
			player2.receiveCardFromDealer(deck.pop());
		}
		else {
			player2.receiveCardFromDealer(deck.pop());
			player1.receiveCardFromDealer(deck.pop());
		}
	}
}

void Game::roundOfBetting() {
	int betHasNotOccurred;
	if (player1.isFirst) {
		betHasNotOccurred = askPlayerToBet(&player1);
		if (betHasNotOccurred)
			askPlayerToBet(&player2);
	}
	else {
		betHasNotOccurred = askPlayerToBet(&player2);
		if (betHasNotOccurred)
			askPlayerToBet(&player1);
	}
}

int Game::askPlayerToBet(Player* player) {
	int selection = -1;
	if (player1.getWallet() == 0 || player2.getWallet() == 0) {
		std::cout << "\nNot all players can afford to bet, so no betting will take place this round.\n\n";
		return 0;
	}
	else {
		while (selection == -1) {
			std::cout << "\nPlayer " << player->getPlayerNumber() << ": Would you like to bet, fold, or stay?\n\n"
				"Enter '0' for bet, '1' for fold, '2' for stay, or '3' to display hand and wallet.\n\nEnter your anwer here: ";
			std::cin >> selection;
			std::cin.clear();
			std::cin.ignore('\n', 10);
			//Player wants to bet
			if (selection == 0) {
				playerBet(player, 0);
				return 0;
			}
			//Player wants to fold
			else if (selection == 1) {
				player->setIsPlaying(0);
				return 0;
			}
			//Player wants to stay
			else if (selection == 2) {
				clearScreen();
				return 1;
			}
			//Display hand
			else if (selection == 3) {
				player->displayHand();
				player->displayWallet();
				selection = -1;
			}
			else {
				std::cout << "\nERROR : INVALID ANSWER\n\n";
				selection = -1;
			}
		}
	}
}

void Game::playerBet(Player* player, int previousBet) {
	int betAmount = 0;
	do {
		std::cout << "\nEnter bet amount here: ";
		std::cin >> betAmount;
		std::cin.clear();
		std::cin.ignore('\n', 10);
		//Not all players can afford the bet
		if ((betAmount - previousBet) > player1.getWallet() || (betAmount - previousBet) > player2.getWallet() || betAmount > player->getWallet()) {
				std::cout << "\nERROR : Not all players can afford this bet.\n\n";
				player1.displayWallet();
				player2.displayWallet();
				betAmount = 0;
		}
		//User enters negative number
		else if (betAmount < 0)
			std::cout << "\nERROR : Bet must be more than 0.\n\n";
		//User does not enter value equivalent to raising the bet
		else if (betAmount <= previousBet) {
			std::cout << "\nERROR : Bet must be more than previous bet. Previous bet was $" << previousBet << "\n\n";
			betAmount = 0;
		}
	} while (betAmount < 1);
	addToPot(player, betAmount);
	clearScreen();
	if (player->getPlayerNumber() == 1)
		askPlayerToStay(&player2, betAmount - previousBet);
	else
		askPlayerToStay(&player1, betAmount - previousBet);
}

void Game::askPlayerToStay(Player* player, int bet) {
	int selection = -1;
	while (selection == -1) {
		std::cout << "\nPlayer " << player->getPlayerNumber() << ": Enter '0' to fold, '1' to match the bet, '2' to raise the bet, or '3' to display hand and wallet."
			"\nPlease enter your selection here: ";
		std::cin >> selection;
		std::cin.clear();
		std::cin.ignore('\n', 10);
		//Player folds
		if (selection == 0) {
			player->setIsPlaying(0);
		}
		//Player matches bet
		else if (selection == 1) {
			if (player->getWallet() < bet) {
				std::cout << "\nERROR : INSUFFICIENT FUNDS\n\n";
				player->displayWallet();
				selection = -1;
			}
			else {
				addToPot(player, bet);
				clearScreen();
			}
		}
		//Player raises bet
		else if (selection == 2) {
			if (player->getWallet() <= bet) {
				std::cout << "\nERROR : INSUFFICIENT FUNDS\n\n";
				player->displayWallet();
				selection = -1;
			}
			else {
				playerBet(player, bet);
			}
		}
		else if (selection == 3) {
			player->displayHand();
			player->displayWallet();
			selection = -1;
		}
		//Invalid input
		else {
			std::cout << "\nERROR : INVALID ANSWER\n\n";
			selection = -1;
		}
	}
}

int Game::didPlayersFold() {
	if (player1.getIsPlaying() == 0 || player2.getIsPlaying() == 0)
		return 1;
	return 0;
}

void Game::round2OfDealing() {
	if (player1.isFirst) {
		askForNewCards(&player1);
		askForNewCards(&player2);
	}
	else {
		askForNewCards(&player2);
		askForNewCards(&player1);
	}
}

void Game::askForNewCards(Player* player) {
	int selection = -1;
	clearScreen();
	while (selection == -1) {
		std::cout << "\nPlayer " << player->getPlayerNumber() << ": Enter '0' to swap 0 cards, '1' to swap 1 card, "
			"'2' to swap 2 cards,\n'3' to swap 3 cards, or '4' to display hand and wallet\n\nPlease enter your selection here: ";
		std::cin >> selection;
		std::cin.clear();
		std::cin.ignore('\n', 10);
		if (selection == 1)
			swapCards(player, 1);
		else if (selection == 2)
			swapCards(player, 2);
		else if (selection == 3)
			swapCards(player, 3);
		else if (selection == 4) {
			player->displayHand();
			player->displayWallet();
			selection = -1;
		}
		else if (selection != 0) {
			std::cout << "\nERROR : INVALID ANSWER\n\n";
			selection = -1;
		}
	}
}

void Game::swapCards(Player* player, int numberOfCards) {
	int timesRan = 0;
	int card1 = 0;
	int card2 = 0;
	int card3 = 0;
	int selection = -1;
	while (timesRan < numberOfCards) {
		if (card1 == 0) {
			while (selection == -1) {
				player->displayHand();
				std::cout << "\nEnter the card number you would like to discard here, or enter 0 to display hand and wallet: ";
				std::cin >> selection;
				std::cin.clear();
				std::cin.ignore('\n', 10);
				if (selection >= 1 && selection <= 5)
					card1 = selection;
				else if (selection == 0) {
					player->displayHand();
					player->displayWallet();
					selection = -1;
				}
				else {
					std::cout << "\nERROR : INVALID ANSWER\n\n";
					selection = -1;
				}
			}
			++timesRan;
			selection = -1;
		}
		else {
			while (selection == -1) {
				player->displayHand();
				std::cout << "Enter another card number you would like to discard here: ";
				std::cin >> selection;
				std::cin.clear();
				std::cin.ignore('\n', 10);
				if (selection >= 1 && selection <= 5 && card1 != selection && card2 != selection) {
					if (card2 == 0)
						card2 = selection;
					else
						card3 = selection;
				}
				else {
					std::cout << "\nERROR : INVALID ANSWER\n\n";
					selection = -1;
				}
			}
			++timesRan;
			selection = -1;
		}
	}
	player->swapCard(deck.pop(), card1);
	if (card2 != 0)
		player->swapCard(deck.pop(), card2);
	if (card3 != 0)
		player->swapCard(deck.pop(), card3);
}

//If both players are still playing after this runs, it is a tie.
void Game::compareHands() {
	int p1win = getWinValue(&player1);
	int p2win = getWinValue(&player2);
	if (p1win > p2win)
		player2.setIsPlaying(0);
	else if (p2win > p1win) 
		player1.setIsPlaying(0);
	else {
		p1win = getHighValue(&player1);
		p2win = getHighValue(&player2);
		if (p1win > p2win)
			player2.setIsPlaying(0);
		else if (p2win > p1win)
			player1.setIsPlaying(0);
	}
}

int Game::getWinValue(Player* player) {
	int winValue = 0;
	int card1Val = player->getCardValue(1);
	int card1Suit = player->getCardSuit(1);
	int card2Val = player->getCardValue(2);
	int card2Suit = player->getCardSuit(2);
	int card3Val = player->getCardValue(3);
	int card3Suit = player->getCardSuit(3);
	int card4Val = player->getCardValue(4);
	int card4Suit = player->getCardSuit(4);
	int card5Val = player->getCardValue(5);
	int card5Suit = player->getCardSuit(5);

	putInNumberOrder(&card1Val, &card2Val, &card3Val, &card4Val, &card5Val);
	
	//Check for Flush(18), then for Straight Flush (21)
	if (card1Suit == card2Suit && card2Suit == card3Suit && card3Suit == card4Suit && card4Suit == card5Suit) {
		winValue = 18;
		if ((card1Val + 1) == card2Val && (card2Val + 1) == card3Val && (card3Val + 1) == card4Val && (card4Val + 1) == card5Val)
			winValue = 21;
	}

	//Check for Two of a kind(14), then Two pairs(15), then Three of a kind(16), then Full house(19), then Four of a kind(20)
	//Find pair
	else if (card1Val == card2Val) {
		if (card2Val == card3Val) {
			if (card4Val == card5Val)
				winValue = 19;
			else if (card3Val == card4Val)
				winValue = 20;
			else
				winValue = 16;
		}
		else if (card3Val == card4Val) {
			if (card4Val == card5Val)
				winValue = 19;
			else
				winValue = 15;
		}
		else if (card4Val == card5Val)
			winValue = 15;
		else
			winValue = 14;
	}
	else if (card2Val == card3Val) {
		if (card3Val == card4Val) {
			if (card4Val == card5Val)
				winValue = 20;
			else
				winValue = 16;
		}
		else if (card4Val == card5Val)
			winValue = 15;
		else
			winValue = 14;
	}
	else if (card3Val == card4Val) {
		if (card4Val == card5Val)
			winValue = 16;
		else
			winValue = 14;
	}
	else if (card4Val == card5Val)
		winValue = 14;
	
	//Check for Straight (17)
	else if ((card1Val + 1) == card2Val && (card2Val + 1) == card3Val && (card3Val + 1) == card4Val && (card4Val + 1) == card5Val)
		winValue = 17;

	//Check for High Card (0 = Ace, King = 12)
	else
		winValue = card5Val;

	return winValue;
}

void Game::putInNumberOrder(int* val1, int* val2, int* val3, int* val4, int* val5) {
	//While numbers are not sorted
	int temp;
	while (!(val1[0] <= val2[0]) || !(val2[0] <= val3[0]) || !(val3[0] <= val4[0]) || !(val4[0] <= val5[0])) {
		if (!(val1[0] <= val2[0])) {
			temp = val1[0];
			val1[0] = val2[0];
			val2[0] = temp;
		}
		if (!(val2[0] <= val3[0])) {
			temp = val2[0];
			val2[0] = val3[0];
			val3[0] = temp;
		}
		if (!(val3[0] <= val4[0])) {
			temp = val3[0];
			val3[0] = val4[0];
			val4[0] = temp;
		}
		if (!(val4[0] <= val5[0])) {
			temp = val4[0];
			val4[0] = val5[0];
			val5[0] = temp;
		}
	}
}

int Game::getHighValue(Player* person) {
	int highValue = person->getCardValue(1);
	if (highValue < person->getCardValue(2))
		highValue = person->getCardValue(2);
	if (highValue < person->getCardValue(3))
		highValue = person->getCardValue(3);
	if (highValue < person->getCardValue(4))
		highValue = person->getCardValue(4);
	if (highValue < person->getCardValue(5))
		highValue = person->getCardValue(5);
	return highValue;
}

void Game::rewardWinnings() {
	if (player1.getIsPlaying() == 0) {
		player2.winMoney(pot);
		std::cout << "Player 2 wins!\n\n";
		player1.displayWallet();
		player2.displayWallet();
		pot = 0;
	}
	else if (player2.getIsPlaying() == 0) {
		player1.winMoney(pot);
		std::cout << "Player 1 wins!\n\n";
		player1.displayWallet();
		player2.displayWallet();
		pot = 0;
	}
	else {
		std::cout << "Its was a draw!\n\n";
		player1.winMoney(pot / 2);
		player2.winMoney(pot / 2);
		pot = 0;
	}
}

int Game::gameOver() {
	if (player1.getWallet() < 10 || player2.getWallet() < 10)
		return 1;
	return 0;
}
