#include "infowindow.h"
#include "maingame.h"
#include "player.h"
#include "spaceship.h"

InfoWindow::InfoWindow(int height, int width, Player **player, SpaceShip **ship) :
	height(height),
	width(width),
	player(player),
	ship(ship) {
}

InfoWindow::~InfoWindow() {
}

void InfoWindow::update() {
	Window::update();
	this->resize();

	int y = 0;
	int x = 1;
	for (unsigned char i = 0; i < PLAYER_SIZE; i++) {
		this->player[i]->render(this, y, x, i + 1);
		y += 6;

		int shipIdx = i * SHIP_SIZE / 2;
		for (unsigned char j = shipIdx; j < shipIdx + SHIP_SIZE / 2; j++) {
			this->ship[j]->render(this, y, x);
			x++;

			if (x > 3) {
				y++;
				x = 1;
			}
		}

		y += 2;
	}
}

void InfoWindow::resize() {
	int rows = this->getMaxRows() - this->height;
	int x = this->getMaxCols() - this->width;
	int cols = this->getMaxCols() - x;
	this->setWindow(rows, cols, 0, x);
	Window::resize();
}
