#include "board.h"
#include "boardwindow.h"
#include "maingame.h"
#include "spaceship.h"

BoardWindow::BoardWindow(int height, int width, Board *board) :
	height(height),
	width(width),
	board(board) {
}

BoardWindow::~BoardWindow() {
}

void BoardWindow::update() {
	Window::update();
	this->resize();

	int twoThirds = (this->getRows() / 3) * 2;
	int halfCols = this->getCols() / 2;
	int y = (twoThirds / 2) - 12;
	int x = halfCols - 4 - 1;
	// Print black hole
	this->printBlackHole(y, x, 0);

	y += 6;
	x = (this->getCols() / 2) - (46 / 2) - 1;
	// Print all planets
	for (int i = 1; i < BOARD_SIZE - 1; i++) {
		this->printPlanet(y, x, i);
		x += 8;

		if (i == (BOARD_SIZE - 2) / 2) {
			x = (this->getCols() / 2) - (46 / 2) - 1;
			y += 6;
		}
	}

	y += 6;
	x = halfCols - 4 - 1;
	// Print black hole
	this->printBlackHole(y, x, BOARD_SIZE - 1);
}

void BoardWindow::resize() {
	int rows = this->getMaxRows() - this->height;
	int cols = this->getMaxCols() - this->width;
	this->setWindow(rows, cols, 0, 0);
	Window::resize();
}

void BoardWindow::printBlackHole(int y, int x, int planet) {
	this->print("+------+", y, x);
	this->print("|      |", y + 1, x);
	this->print("|      |", y + 2, x);
	this->print("|      |", y + 3, x);
	this->print("+------+", y + 4, x);

	this->printSpaceShip(y + 1, x + 1, planet, 6);
}

void BoardWindow::printPlanet(int y, int x, int planet) {
	this->print("+----+", y, x);
	this->print("|    |", y + 1, x);
	this->print("|    |", y + 2, x);
	this->print("|    |", y + 3, x);
	this->print("+----+", y + 4, x);

	this->printSpaceShip(y + 1, x + 1, planet, 4);
}

void BoardWindow::printSpaceShip(int y, int x, int planet, int width) {
	auto tmp = this->board->getShips(planet);
	int size = (int)tmp->size() + 1;
	for (int i = 1; i < size; i++) {
		tmp->at(i - 1)->render(this, y, x, false);
		x++;

		if (i != 1 && i % width == 0) {
			y++;
			x -= width;
		}
	}
}
