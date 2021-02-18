#include <ncurses.h> // A_REVERSE
#include <stdio.h>

#include "player.h"
#include "infowindow.h"

Player::Player() :
	chip(CHIP_AMOUNT),
	name("") {
}

void Player::render(InfoWindow *window, int y, int x, unsigned char number) {
	std::string print;
	print += "   Player ";
	print += std::to_string(number);
	print += "   ";
	window->print(print, y, x - 1, A_REVERSE);
	y += 2;

	window->print(this->name, y, x, COLOR_PAIR(this->color));
	y += 2;

	for (unsigned char i = 0; i < this->chip; i++) {
		window->print("C", y, x, COLOR_PAIR(PAIR_WHITE_BLACK));
		x++;
		window->print(" ", y, x);
		x++;
	}
}

unsigned char Player::getChip() {
	return this->chip;
}

void Player::setChip(unsigned char chip) {
	this->chip = chip;
}

unsigned char Player::getColor() {
	return this->color;
}

void Player::setColor(unsigned char color) {
	this->color = color;
}

std::string Player::getName() {
	return this->name;
}

void Player::setName(std::string name) {
	this->name = name;
}
