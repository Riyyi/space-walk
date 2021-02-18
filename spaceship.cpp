#include "spaceship.h"
#include "window.h"

SpaceShip::SpaceShip() :
	color(COLOR_UNSET),
	size(SpaceShip::SIZE_UNSET),
	planet(PLANET_UNSET) {
}

SpaceShip::SpaceShip(unsigned char color, unsigned char size) :
	color(color),
	size(size),
	planet(PLANET_UNSET) {
}

void SpaceShip::render(Window *window, int y, int x, bool checkPlaced) {
	if (checkPlaced && this->planet != PLANET_UNSET) {
		return;
	}

	std::string print = "";
	if (this->size == SpaceShip::SMALL) {
		print = "S";
	}
	else if (this->size == SpaceShip::MEDIUM) {
		print = "M";
	}
	else if (this->size == SpaceShip::BIG) {
		print = "B";
	}

	window->print(print, y, x, COLOR_PAIR(this->color));
}

unsigned char SpaceShip::getColor() {
	return this->color;
}

void SpaceShip::setColor(unsigned char color) {
	this->color = color;
}

unsigned char SpaceShip::getSize() {
	return this->size;
}

void SpaceShip::setSize(unsigned char size) {
	this->size = size;
}

char SpaceShip::getPlanet() {
	return this->planet;
}

void SpaceShip::setPlanet(char planet) {
	this->planet = planet;
}
