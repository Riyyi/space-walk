#ifndef PLAYER_H
#define PLAYER_H

#define CHIP_AMOUNT 4
#define CHIP_SCORE 2

#include <string>

class InfoWindow;

class Player
{
public:
	Player();

	void render(InfoWindow *window, int y, int x, unsigned char number);

	unsigned char getChip();
	void setChip(unsigned char chip);
	unsigned char getColor();
	void setColor(unsigned char color);
	std::string getName();
	void setName(std::string name);

private:
	unsigned char chip;
	unsigned char color;
	std::string name;
};

#endif // PLAYER_H
