/*
* DeckBuilder.h
*
*  Created on: Mar 20, 2015
*      Author: jdesroches
*/

#include "IntArrayShuffle.h"
#include "Card.h"
#include <queue>

#ifndef DECKBUILDER_H_
#define CARD_H_
#define ARRAY_SIZE(array) (sizeof((array))/sizeof((array[0])))
using namespace std;
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
	void GetDecks(queue <Card> &PlayerDeck,	queue <Card> &CPUDeck){
		BuildDeck();
		DealDeck(PlayerDeck, CPUDeck);
	}

private:
	Card Deck[52];
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
			// card to be inserted into the deck
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
	void DealDeck(queue <Card> &PlayerDeck, queue <Card> &CPUDeck){
		// shuffle the deck int values
		int card[52];

		for (int i = 0; i < (ARRAY_SIZE(Deck)); i++){
			card[i] = i;
		}
		IntArrayShuffle::randomize(card);

		// deal cards to player and CPU
		for (int i = 0; i < ARRAY_SIZE(Deck); i++){
			if (i > 25){
				CPUDeck.push(Deck[card[i]]);
			}
			else{
				PlayerDeck.push(Deck[card[i]]);
			}
		}
	}
};


#endif /* DECKBUILDER_H_ */
