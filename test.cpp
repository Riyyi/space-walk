#include <cassert>
#include <iostream>
#include <ncurses.h>

#include "board.h"
#include "inputoutput.h"
#include "maingame.h"
#include "player.h"
#include "spaceship.h"
#include "test.h"

Test::Test() {

	// IO::print("Unit test\n");
	refresh();

	// Board tests
	Board *board = new Board;

	char arrayShip[3] = { SpaceShip::SMALL, SpaceShip::MEDIUM, SpaceShip::BIG };
	SpaceShip *ship  = new SpaceShip(1, arrayShip[0]);
	SpaceShip *ship2 = new SpaceShip(1, arrayShip[1]);
	SpaceShip *ship3 = new SpaceShip(1, arrayShip[2]);
	board->setShip(0, ship);
	board->setShip(0, ship);
	board->setShip(1, ship);
	board->setShip(1, ship2);
	board->setShip(2, ship3);

	for (int i = 0; i < 3; i++) {
		auto ships = board->getShips(i);
		// printf("%lu\n", ships->size());
		for (int j = 0; j < (int)ships->size(); j++) {
			// printf("%d\n", ships->at(j)->getSize());
			assert(ships->at(j)->getSize() == arrayShip[i]);
		}
		assert(ships->size() == 1);
	}
	board->moveShip(3, ship3);
	assert(board->getShip(3, 0)->getSize() == arrayShip[2]);

	// char array[SHIP_SIZE] = {
		// SpaceShip::SMALL, SpaceShip::SMALL, SpaceShip::SMALL,
		// SpaceShip::MEDIUM, SpaceShip::MEDIUM, SpaceShip::MEDIUM,
		// SpaceShip::BIG, SpaceShip::BIG, SpaceShip::BIG,
		// SpaceShip::SMALL, SpaceShip::SMALL, SpaceShip::SMALL,
		// SpaceShip::MEDIUM, SpaceShip::MEDIUM, SpaceShip::MEDIUM,
		// SpaceShip::BIG, SpaceShip::BIG, SpaceShip::BIG,
	// };
	// for (unsigned char i = 0; i < SHIP_SIZE; i++) {
		// // printf("%d\n", board.ships[i]->getSize());
		// // printf("%d\n", array[i]);
		// assert(board.ships[i]->getSize() == array[i]);
	// }

	// IO::print("Passed board checks..");
	refresh();

	getch();

	// Cleanup resources
	delete board;
	delete ship;
	delete ship2;
	delete ship3;

	IO::setQuit();
}
