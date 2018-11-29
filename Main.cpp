#include <iostream>
#include <time.h>
#include "Deck.h"
#include "Player.h"
#include "Game.h"

using namespace std;

//*****ACE IS LOW*****
//*****Unit testing can be started by entering '100' in the main menu*****

int main() {
	int selection = -1;
	int returnValue = 0;
	Game game;
	game.initializePlayers();
	while (selection == -1) {
		cout << "\nWelcome to Poker!\n\nIf you would like to go to the table, enter '0'.\n"
			"If you would like to read the rules, enter '1'.\nIf you would like to quit, enter '2'.\n\nPlease enter your answer here: ";
		cin >> selection;
		cin.clear();
		cin.ignore('\n', 10);
		switch (selection) {
		case(0):
			game.clearScreen();
			selection = -1;
			while (selection == -1) {
				cout << "\nWelcome to the Table!\n\n";
				game.player1.displayWallet();
				game.player2.displayWallet();
				cout << "If you would like to leave the table, enter '0'.\n"
					"If you would like to play a game, enter '1'.\n\nPlease enter your answer here: ";
				cin >> selection;
				cin.clear();
				cin.ignore('\n', 10);
				switch (selection) {
				case(0):
					game.clearScreen();
					break;
				case(1):
					if (!game.gameOver()) {
						game.clearScreen();
						game.startNewGame();
						game.dealHands();
						game.roundOfBetting();
						if (!game.didPlayersFold()) {
							game.round2OfDealing();
							game.roundOfBetting();
							if (!game.didPlayersFold()) {
								cout << "\nComparing hands!\n";
								game.compareHands();
								cout << "\nDone comparing hands!\n";
							}
						}
						game.rewardWinnings();
					}
					else {
						game.clearScreen();
						cout << "ERROR : BOTH PLAYERS DO NOT HAVE ENOUGH MONEY TO PLAY\n\n";
					}
					break;
				default:
					game.clearScreen();
					cout << "\nERROR : INVALID INPUT\n\n";
					break;
				}
				if (selection != 0)
					selection = -1;
			}
			break;
		case(1):
			game.clearScreen();
			cout << "\nThe game is called 5 card draw. 2 Players will start with a $10 ante (assuming they can afford it)."
				"\nPlayers will then be dealt 5 cards each. Players will be asked if they want to bet, stay, or fold, then\n"
				"offered the opportunity to discard up to 3 cards and receive new cards from the dealer. The players will go\n"
				"through another round of betting, and if neither player has folded, the player with the best hand will win\n"
				"the money in the pot. Aces are considered low for the entirety of the game.\n\n";
			break;
		case(2):
			game.clearScreen();
			cout << "\nGOOD BYE\n\n";
			break;
		case(100):
			game.clearScreen();
			game.startNewGame();
			cout << "\nDeck before dealing cards:\n\n";
			game.deck.displayDeck();
			game.dealHands();
			cout << "\nDeck after dealing cards:\n\n";
			game.deck.displayDeck();
			game.player1.displayHand();
			game.player1.displayWallet();
			game.player2.displayHand();
			game.player2.displayWallet();
			game.player1.swapCard(game.deck.pop(), 1);
			game.player1.swapCard(game.deck.pop(), 3);
			game.player1.swapCard(game.deck.pop(), 5);
			game.player2.swapCard(game.deck.pop(), 1);
			game.player2.swapCard(game.deck.pop(), 3);
			game.player2.swapCard(game.deck.pop(), 5);
			cout << "\nDeck after giving players 4 more cards:\n";
			game.deck.displayDeck();
			cout << "\nPlayer hands after swapping 2 cards each:\n";
			game.player1.displayHand();
			game.player2.displayHand();
			cout << "\nPlayer who won is displayed below:\n";
			game.compareHands();
			game.rewardWinnings();
			game.player1.setWallet(100);
			game.player2.setWallet(100);
			returnValue = 0;
			while (returnValue != 100) {
				cout << "\nEnter '100' to return to the game: ";
				cin >> returnValue;
				cin.clear();
				cin.ignore('\n', 10);
			}
			break;
		default:
			game.clearScreen();
			cout << "\nERROR : INVALID INPUT\n\n";
			break;
		}
		if (selection != 2)
			selection = -1;
	}
	return 0;
}
