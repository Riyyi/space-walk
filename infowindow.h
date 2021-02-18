#ifndef INFOWINDOW_H
#define INFOWINDOW_H

#include "window.h"

class Player;
class SpaceShip;

class InfoWindow : public Window
{
public:
	InfoWindow(int height, int width, Player **player, SpaceShip **ship);
	~InfoWindow();

	void update();
	void resize();

private:
	int height;
	int width;
	Player **player;
	SpaceShip **ship;
};

#endif // INFOWINDOW_H
