//============================================================================
// Name        : Schelling.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C, Ansi-style
//============================================================================

#include <iostream>
#include "SchellingClass.h"

int main(void) {
	SchellingClass schelling_game(30, 500, 0.3);
	schelling_game.shuffle();
	schelling_game.play();
	schelling_game.display();
	return 0;
}
