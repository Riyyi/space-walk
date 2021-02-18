#ifndef SPACESHIP_H
#define SPACESHIP_H

#define PLANET_UNSET -1

class Window;

class SpaceShip
{
public:
	SpaceShip();
	SpaceShip(unsigned char color, unsigned char size);

	void render(Window *window, int y, int x, bool checkPlaced = true);

	unsigned char getColor();
	void setColor(unsigned char color);
	unsigned char getSize();
	void setSize(unsigned char size);
	char getPlanet();
	void setPlanet(char planet);

	enum Size {
		SIZE_UNSET = 0,
		SMALL = 1,
		MEDIUM = 3,
		BIG = 4,
	};

private:
	unsigned char color;
	unsigned char size;
	char planet;
};

#endif // SPACESHIP_H
