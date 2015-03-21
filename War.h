/*
 * War.h
 *
 *  Created on: Mar 20, 2015
 *      Author: jdesroches
 */
#include "DeckBuilder.h"
#include <iostream>

#ifndef WAR_H_
#define WAR_H_


/**
 * Main Game class, allows user to play a card game of War with the computer
 * @class War
 */
class War {
	public:
		War(){
			// Notify App has started
			std::cout<<"Starting War"<<std::endl;

			DeckBuilder *deckBuilder{};
			deckBuilder->GetDecks(PlayerDeck, CPUDeck);
			delete deckBuilder;
			std::cout << "Built PLayer Decks" << std::endl;
		};
		virtual ~War(){
			// Notify App has now ended
			std::cout<<"Exiting War";
		};
	private:
		Card PlayerDeck[26];
		Card CPUDeck[26];

};


#endif /* WAR_H_ */
