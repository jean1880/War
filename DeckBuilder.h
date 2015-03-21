/*
* DeckBuilder.h
*
*  Created on: Mar 20, 2015
*      Author: jdesroches
*/

#include <iostream>
#include "IntArrayShuffle.h"
#include "Card.h"

#ifndef DECKBUILDER_H_
#define CARD_H_
#define ARRAY_SIZE(array) (sizeof((array))/sizeof((array[0])))

class DeckBuilder
{
public:
	DeckBuilder(){
	};
	virtual ~DeckBuilder(){
	};

	/**
	 * Returns palyer and CPU deck through passed in variables
	 * @method GetDecks
	 * @param 
	**/
	void GetDecks(Card(&PlayerDeck)[26], Card(&CPUDeck)[26]){
		BuildDeck();
		DealDeck(PlayerDeck, CPUDeck);
	}

private:
	Card Deck[52];
	int count();
	void BuildSuite();

	/**
	* Builds the starting Deck
	* @method BuildDeck
	*/
	void BuildDeck(){
		int cur = 0;

		// define suite names
		char *s[] = {
			"hearts",
			"diamonds",
			"spades",
			"clubs"
		};

		// loop through suites and compile suite set
		for (int i = 0; i < ARRAY_SIZE(s); i++){
			BuildSuite(s[i], cur);
		}

	}


	/**
	* Build the card set for a suite
	* @method BuildSuite
	* @param {char[]} suite
	*/
	void BuildSuite(char suite[], int &cur){
		int SuiteSize = 13;

		for (int i = 0; i < SuiteSize; i++){
			// create card to be inserted into the deck
			Card newCard;
			newCard.suite = suite;
			newCard.value = i;
			newCard.charValue = CardCharValue[i];

			// pass card into deck
			Deck[cur] = newCard;
			cur++;
		}
	}

	/**
	* Shuffles the deck
	* @method ShuffleDeck
	*/
	void DealDeck(Card (&PlayerDeck)[26], Card (&CPUDeck)[26]){
		// shuffle the deck int values
		int card[52];
		for (int i = 0; i < (ARRAY_SIZE(Deck)); i++){
			card[i] = i;
		}
		IntArrayShuffle::randomize(card);

		// deal cards to player and CPU
		for (int i = 0; i < ARRAY_SIZE(Deck); i++){
			if (i > 26){
				CPUDeck[i - 26] = Deck[card[i]];
			}
			else{
				PlayerDeck[i] = Deck[card[i]];
			}
		}
		for (int i = 0; i < ARRAY_SIZE(Deck); i++){
			// temporarily spew results
			if (i == 0){
				std::cout << "Player's Deck" << std::endl;
			}
			else if (i == 26){
				std::cout << "CPU's Deck" << std::endl;
			}
			if (i < 26){
				std::cout << PlayerDeck[i].charValue
					<< " of " << PlayerDeck[i].suite
					<< "=" << PlayerDeck[i].value
					<< std::endl;
			}
			else{
				std::cout << CPUDeck[i - 26].charValue
					<< " of " << CPUDeck[i - 26].suite
					<< "=" << CPUDeck[i - 26].value
					<< std::endl;
			}

		}
	}
};


#endif /* DECKBUILDER_H_ */