#pragma once
#include "Deck.h"
#include "Player.h"

//Global Variables
class Game {
private:
	//Ask player for bet
	int askPlayerToBet(Player*);

	//Put money into pot
	void addToPot(Player*, int);

	//Player has bet
	void playerBet(Player*, int);

	//Ask player to stay in the game after bet
	void askPlayerToStay(Player*, int);

	//Set who is first
	void setFirstPlayer();

	//See if player wants to exchange cards in their hand
	void askForNewCards(Player*);

	//Give player new cards
	void swapCards(Player*, int);

	//Returns win value of player
	int getWinValue(Player*);

	//Returns highest card value of player
	int getHighValue(Player*);

public:
	Deck deck;
	Player player1;
	Player player2;
	int pot = 0;

	//Clears screes
	void clearScreen();

	//Set player numbers
	void initializePlayers();

	//Put in order a list of 5 numbers
	void putInNumberOrder(int*, int*, int*, int*, int*);

	//Make new deck and shuffle it, 
	void startNewGame();

	//Deal hands to players
	void dealHands();

	//Ask players if they want to bet, stay, or fold
	void roundOfBetting();

	//Check if a player decided to fold
	int didPlayersFold();

	//Ask if players want to be dealt new cards
	void round2OfDealing();

	//Check who has the best hand
	void compareHands();

	//Give money to winner
	void rewardWinnings();

	//If players cannot afford ante, game is over
	int gameOver();
};
