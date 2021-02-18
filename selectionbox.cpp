#include <cstring> // strlen
#include <sstream> // istringstream

#include "inputoutput.h"
#include "selectionbox.h"

SelectionBox::SelectionBox(int height, int width) :
	height(height),
	width(width) {
	this->update();
}

void SelectionBox::update() {
	Window::update();
	this->resize();
}

void SelectionBox::resize() {
	int rows = (this->getMaxRows() - this->height) / 4;
	int cols = this->getMaxCols() - this->width;
	this->setWindow(rows, cols, this->getMaxRows() - rows, 0);
	Window::resize();
}

unsigned char SelectionBox::select(std::string str, std::string *selection) {
	int amount = 0;
	while (!selection[amount].empty()) {
		amount++;
	}

	std::string tmpStr;
	int tmpInt;
	// Display options and get user input
	while(!IO::getQuit()) {
		this->clear();
		this->update();
		this->printSelection(str, selection);
		this->render();

		tmpStr = IO::trim(this->getStr());
		if (tmpStr == "") {
			continue;
		}

		if (this->isNumber(tmpStr)) {
			tmpInt = std::stoi(tmpStr);
			if (tmpInt > 0 && tmpInt < amount + 1) {
				break;
			}
		}
	}

	return (unsigned char)tmpInt - 1;
}

void SelectionBox::printSelection(std::string str, std::string *selection) {
	int y = 0;

	// Split and print message on newline
	std::istringstream strStream(str);
	std::string tmpStr;
	while (std::getline(strStream, tmpStr, '\n')) {
		this->print(tmpStr, y, 1);
		y++;
	}
	y++;

	int amount = 0;
	while (!selection[amount].empty()) {
		if (amount < 6) {
			this->print("- " + selection[amount], y, 1);
		}
		else {
			this->print("- " + selection[amount], y - 6, 10);
		}

		y++;
		amount++;
	}

	this->print("Select option number: ", this->getRows() - 3, 1);
}

bool SelectionBox::isNumber(const std::string &s) {
    std::string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it)) it++;
    return !s.empty() && it == s.end();
}
