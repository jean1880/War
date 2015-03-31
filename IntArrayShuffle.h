/*
 * IntArrayShuffle.h
 *
 *  Created on: Mar 20, 2015
 *      Author: jdesroches
 */

#ifndef INTARRAYSHUFFLE_H_
#define INTARRAYSHUFFLE_H_

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

class IntArrayShuffle{
public:
	IntArrayShuffle(){};
	// A function to generate a random permutation of arr[]
	template<int N> 
	void randomize ( int (&arr)[N])
	{
		// Use a different seed value so that we don't get same
		// result each time we run this program
		srand ( time(NULL) );

		int n = sizeof(arr)/ sizeof(arr[0]);

		// Start from the last element and swap one by one. We don't
		// need to run for the first element that's why i > 0
		for (int i = n-1; i > 0; i--)
		{
			// Pick a random index from 0 to i
			int j = rand() % (i+1);

			// Swap arr[i] with the element at random index
			swap(&arr[i], &arr[j]);
		}
	}
private:
	// A utility function to swap to integers
	void swap (int *a, int *b)
	{
		int temp = *a;
		*a = *b;
		*b = temp;
	}
};

#endif /* INTARRAYSHUFFLE_H_ */
