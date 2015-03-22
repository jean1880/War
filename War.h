/*
 * War.h
 *
 *  Created on: Mar 20, 2015
 *      Author: jdesroches
 */
#include "DeckBuilder.h"
#include <string>
#include <iostream>
#include <algorithm>
#include <chrono>
#include <thread>

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
		Card PlayerDeck[26];
		Card CPUDeck[26];
		int round = 0;
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
		* Checks what action the player is taking
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

				// iterate round
				round++;
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
			cout << playerName << " plays " << PlayerDeck[round].charValue << " of " << PlayerDeck[round].suite << endl;
			std::this_thread::sleep_for(std::chrono::milliseconds(500));
			cout << "Computer plays " << CPUDeck[round].charValue << " of " << CPUDeck[round].suite << endl;
		}

		/**
		* Checks whether the player or the computer won, if there was a tie, recursively replay until there is a winner
		* @method CheckWinner
		**/
		void CheckWinner(){
			if (PlayerDeck[round].value > CPUDeck[round].value){
				cout << "You Win!!" << endl;
			}
			else if (PlayerDeck[round].value < CPUDeck[round].value){
				cout << "You Lose!!" << endl;
			}
			else{
				cout << "Tie!!" << endl;
				// iterate round
				round++;
				PlayRound();
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
				<< "\********************************************/" << endl;			
		}
};


#endif /* WAR_H_ */
