#ifndef BOARD_H
#define BOARD_H

#define BOARD_SIZE 14

#include <vector>

class SpaceShip;

class Board
{
public:
	Board();
	~Board();

	SpaceShip *getShip(unsigned char planet, unsigned char pos);
	std::vector<SpaceShip *> *getShips(unsigned char planet);
	bool setShip(unsigned char planet, SpaceShip *ship);
	bool moveShip(unsigned char planet, SpaceShip *ship);
	void sortPlanet(unsigned char planet);

private:
	// Data layout:
	// Black hole, 6 planets, 6 planets, black hole
	std::vector<SpaceShip *> *planets[BOARD_SIZE];
};

#endif // BOARD_H
