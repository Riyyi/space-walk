#include <algorithm>

#include "board.h"
#include "spaceship.h"

Board::Board() {
	// Reserve 0 SpaceShips of memory for each planet
	for (unsigned char i = 0; i < BOARD_SIZE; i++) {
		this->planets[i] = new std::vector<SpaceShip *>(0);
	}
}

Board::~Board() {
	for (auto planet : this->planets) {
		delete planet;
	}
}

SpaceShip *Board::getShip(unsigned char planet, unsigned char pos) {
	if (planet >= BOARD_SIZE || pos >= this->planets[planet]->size()) {
		return new SpaceShip;
	}

	return this->planets[planet]->at(pos);
}

std::vector<SpaceShip *> *Board::getShips(unsigned char planet) {
	if (planet >= BOARD_SIZE) {
		return nullptr;
	}

	return this->planets[planet];
}

bool Board::setShip(unsigned char planet, SpaceShip *ship) {
	if (planet >= BOARD_SIZE) {
		return false;
	}

	// Insert if the ship doesn't already exist on a planet
	if (ship->getPlanet() == PLANET_UNSET) {
		ship->setPlanet(planet);
		this->planets[planet]->push_back(ship);
		this->sortPlanet(planet);
	}

	return true;
}

bool Board::moveShip(unsigned char planet, SpaceShip *ship) {
	char shipPlanet = ship->getPlanet();
	if (planet >= BOARD_SIZE || shipPlanet == -1 || shipPlanet == planet) {
		return false;
	}

	auto tmp = this->planets[(unsigned char)shipPlanet];
	// Move ship to the end of the vector and then erase the last element
	// (Erase-remove idiom)
	tmp->erase(std::remove(tmp->begin(), tmp->end(), ship), tmp->end());

	ship->setPlanet(planet);
	this->planets[planet]->push_back(ship);
	this->sortPlanet(planet);

	return true;
}

void Board::sortPlanet(unsigned char planet) {
	// Sort all ships on the planet, using function/functor/lambda
	std::sort(this->planets[planet]->begin(), this->planets[planet]->end(),
		[](SpaceShip *s1, SpaceShip *s2) -> bool {
			return s1->getSize() > s2->getSize();
		});
}
