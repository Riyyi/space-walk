#ifndef BOARDWINDOW_H
#define BOARDWINDOW_H

#include "window.h"

class Board;

class BoardWindow : public Window
{
public:
	BoardWindow(int height, int width, Board *board);
	~BoardWindow();

	void update();
	void resize();
	void printBlackHole(int y, int x, int planet);
	void printPlanet(int y, int x, int planet);
	void printSpaceShip(int y, int x, int planet, int width);

private:
	int height;
	int width;
	Board *board;
};

#endif // BOARDWINDOW_H
