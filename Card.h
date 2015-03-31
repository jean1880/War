/*
 * Card.h
 *
 *  Created on: Mar 20, 2015
 *      Author: jdesroches
 */

#ifndef CARD_H_
#define CARD_H_


struct Card{
	int value;
	char *suite;
	char *charValue;

	bool operator == (const Card &card) const
	{
		return (value == card.value);
	}
};

char *CardCharValue[14] = {
	"two",
	"three",
	"four",
	"five",
	"six",
	"seven",
	"eight",
	"nine",
	"ten",
	"jack",
	"queen",
	"king",
	"ace"
};

#endif /* CARD_H_ */
