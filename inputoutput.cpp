#include <cstdio> // size_t
#include <ncurses.h>

#include "inputoutput.h"

void IO::initialize() {
}

void IO::update() {
	IO::keyCode = getch();

	if (keyCode == KEY_ESC) {
		IO::setQuit();
		return;
	}
}

std::string IO::trim(std::string str) {
    size_t first = str.find_first_not_of(" ");
    if (first == std::string::npos) {
        return "";
    }
    size_t last = str.find_last_not_of(" ");
    return str.substr(first, (last - first + 1));
}

std::string IO::untrim(std::string str, unsigned int length) {
	unsigned int strLength = str.length();
	if (length > strLength) {
		int halfDiff = (length - strLength) / 2;

		std::string tmpStr;
		for (int i = 0; i < halfDiff; i++) {
			tmpStr += " ";
		}

		str.insert(0, tmpStr);
		str.append(tmpStr);
	}

	return str;
}

int IO::getKeyCode() {
	return IO::keyCode;
}

std::string IO::getKeyName() {
	return std::string(keyname(IO::keyCode));
}

std::string IO::getStrInput() {
	echo();
	char *tmp = new char();
	getstr(tmp);
	noecho();
	return std::string(tmp);
}

bool IO::getQuit() {
	return IO::quit;
}

void IO::setQuit() {
	IO::quit = true;
}

int IO::keyCode = ERR;
bool IO::quit = false;
