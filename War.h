/*
 * War.h
 *
 *  Created on: Mar 20, 2015
 *      Author: jdesroches
 */
#include "DeckBuilder.h"
#include <string>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <chrono>
#include <thread>
#include <queue>

#ifndef WAR_H_
#define WAR_H_

using namespace std;
/**
 * Main Game class, allows user to play a card game of War with the computer
 * @class War
 */
class War {
	public:
		/**
		 * Starts the game of war, and begins looking for user input
		 * @method __cunstructor
		**/
		War(){			
			// Notify App has started
			cout 
				<< "\******************* WAR ********************/" << endl
				<< "\* Welcome to the game of war, The deck is  */" << endl
				<< "\* divided evenly among the players, giving */" << endl 
				<< "\* each a down stack. In unison, each player*/" << endl
				<< "\* reveals the top card of their deck – this*/" << endl 
				<< "\* is a 'battle' – and the player with the  */" << endl
				<< "\* higher card takes both of the cards      */" << endl
				<< "\* played and moves them to the bottom of   */" << endl
				<< "\* their stack                              */" << endl
				<< "\*                                          */" << endl
				<< "\* For help type '--help' exit with '--exit'*/" << endl
				<< "\* Begin playing by typing '--play'         */" << endl
				<< "\********************************************/" << endl;

			// begin listening to user input until exit command recieved
			while (!exit)
			{
				// if initializing build decks
				if (initialize){
					InitializeDecks();
					GetPlayerName();
					initialize = false;
				}

				// get user input
				cin >> input;
				PlayerInteraction(input);
			}
		};
		virtual ~War(){
			// Notify App has now ended
			cout<<"Exiting War";
		};
	private:
		string input;
		string playerName;
		queue <Card> PlayerDeck;
		queue <Card> CPUDeck;
		queue <Card> CardPool;
		bool initialize = true;
		bool exit = false;

		/**
		 * Builds the core deck and distributes cards to the player and CPU
		 * @method InitializeDeck
		 **/
		void InitializeDecks(){
			DeckBuilder *deckBuilder = new DeckBuilder();
			deckBuilder->GetDecks(PlayerDeck, CPUDeck);
		}

		/**
		* Get player name from player and save the input
		* @method InitializeDeck
		**/
		void GetPlayerName(){
			cout << "Please Enter your name:" << endl;
			cin >> playerName;
			cout << "Welcome " << playerName << " type --play to play a card:" << endl;
		}

		/**
		* Checks what action the player wishes to take
		* @method PlayerInteraction
		**/
		void PlayerInteraction(string input){
			// convert input to string lower
			transform(input.begin(), input.end(), input.begin(), ::tolower);

			// check command
			if (input == "-p" || input == "--play"){
				PlayRound();
			}
			else if (input == "-h" || input == "--help"){
				DisplayHelpDoc();
			}
			else if (input == "-s" || input == "--size"){
				DisplayScore();
			}
			else if (input == "-r" || input == "--restart"){
				initialize = true;
			}
			else if (input == "-e" || input == "--exit" ){
				exit = true;
			}
			else{
				cout << "Unknown Command" << endl;
				DisplayHelpDoc();
			}
		}

		/**
		 * Plays a round with the CPU
		 * @method PlayRound
		 **/
		void PlayRound(){
			try{
				// output cards played
				OutputPlay();

				// run playthrough
				CheckWinner();
			}
			catch (exception e){
				throw;
			}
		}

		/**
		* Outputs played cards, for this round
		* @method OutputPlay
		**/
		void OutputPlay(){
			cout << playerName << " plays " << PlayerDeck.front().charValue << " of " << PlayerDeck.front().suite << endl;
			std::this_thread::sleep_for(std::chrono::milliseconds(500));
			cout << "Computer plays " << CPUDeck.front().charValue << " of " << CPUDeck.front().suite << endl;
		}

		/**
		* Checks whether the player or the computer won, if there was a tie, recursively replay until there is a winner
		* @method CheckWinner
		**/
		void CheckWinner(){
			if (PlayerDeck.front().value > CPUDeck.front().value){
				cout << "You Win!!" << endl;

				// build card pool and pass pool to player
				AddToCardPool();
				RewardWinner(PlayerDeck);
			}
			else if (PlayerDeck.front().value < CPUDeck.front().value){
				cout << "You Lose!!" << endl;


				// build card pool and pass pool to CPU
				AddToCardPool();
				RewardWinner(CPUDeck);
			}
			else{
				cout << "WAR!!" << endl;
				AddToCardPool();
				
				// play another round to look for a winner
				PlayRound();
			}
		}

		/**
		 * Checks if a players deck is empty to see if a player has won
		 * @method CheckDecks
		 **/
		void CheckDecks(){
			string input;
			if (PlayerDeck.size() == 0){
				cout
					<< "\******************* LOSE *******************/" << endl
					<< "\* " << setfill(' ') << setw(10) << playerName << ": " << setfill(' ') << setw(2) << PlayerDeck.size() << "                             */" << endl
					<< "\* CPU: " << setfill(' ') << setw(2) << CPUDeck.size() << "                                  */" << endl
					<< "\********************************************/" << endl;
			}
			else if (CPUDeck.size() == 0){
				cout
					<< "\******************* WIN ********************/" << endl
					<< "\* " << setfill(' ') << setw(10) << playerName << ": " << setfill(' ') << setw(2) << PlayerDeck.size() << "                             */" << endl
					<< "\* CPU: " << setfill(' ') << setw(2) << CPUDeck.size() << "                                  */" << endl
					<< "\********************************************/" << endl;
			}
			else{
				// neither player has won  the game, exit the method
				return;
			}

			// check if player wants to play again
			CheckRestart();
		}

		/**
		 * Checks if the player wants to restart or exit the game
		 * @method CheckRestart
		 **/
		void CheckRestart(){
			cout << "Play again?  (y/n):" << endl;
			cin >> input;

			// convert input to string lower
			transform(input.begin(), input.end(), input.begin(), ::tolower);

			// check decision
			if (input == "y" || input == "yes"){
				initialize = true;
			}
			else if (input == "n" || input == "no"){
				exit = true;
			}
			else{
				cout << "please type 'y' or 'n'" << endl;
				CheckRestart();
			}
		}

		/**
		 * Take both players cards and add them to the current winnings card pool, and remove from their deck
		 * @method AddToCardPool
		 **/
		void AddToCardPool(){
			// add both cards to the card pool to be collected on victory
			CardPool.push(PlayerDeck.front());
			PlayerDeck.pop();

			CardPool.push(CPUDeck.front());
			CPUDeck.pop();
		}

		/**
		 * Passes the current card pool into the winners deck
		 * @method RewardWinner
		 **/
		void RewardWinner(queue <Card> &WinnerDeck){
			// take all the cards in the card pool and pass to the winning deck
			while (CardPool.size() > 0){
				WinnerDeck.push(CardPool.front());
				CardPool.pop();
			}
		}

		/**
		* Displays help doc to the player
		* @method DisplayHelpDoc
		**/
		void DisplayHelpDoc(){
			cout
				<< "\******************* WAR ********************/" << endl
				<< "\* Commmands:                               */" << endl
				<< "\*         -h, --help: Opens help document  */" << endl
				<< "\*         -e, --exit:  Exits the game      */" << endl
				<< "\*         -r, --restart: Restarts the game */" << endl
				<< "\*         -p, --play:    Plays next card   */" << endl
				<< "\*         -s, --score:   Show current score*/" << endl
				<< "\********************************************/" << endl;			
		}

		/**
		 * Displays number of cards in each players deck to report current standings
		 * @method DisplayScore
		 **/
		void DisplayScore(){
			cout
				<< "\****************** SCORE *******************/" << endl
				<< "\* " << setfill(' ') << setw(10) << playerName << ": " << setfill(' ') << setw(2) << PlayerDeck.size() << "                             */" << endl
				<< "\* CPU: " << setfill(' ') << setw(2) << CPUDeck.size() << "                                  */" << endl
				<< "\********************************************/" << endl;

		}
};


#endif /* WAR_H_ */
