/*
 * War.cpp
 *
 *  Created on: Mar 20, 2015
 *      Author: jdesroches
 */

#include <iostream>
#include <exception>
#include "War.h"

// initiate the game
int main(){
	try {
		War();
		return 0;
	} catch (std::exception e) {
		std::cout<<e.what()<<std::endl;
	}
}
