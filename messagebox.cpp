#include <ncurses.h> // A_REVERSE
#include <sstream> // istringstream
#include <vector>

#include "inputoutput.h"
#include "messagebox.h"

MessageBox::MessageBox(std::string message) :
	MessageBox(message, "") {
}

MessageBox::MessageBox(std::string message, std::string title) {
	// Split message on newline
	std::vector<std::string> lines;
	std::istringstream strStream(message);
	std::string tmpStr;
	while (std::getline(strStream, tmpStr, '\n')) {
		lines.push_back(tmpStr);
	}

	int rows;
	int cols;
	Window::getMaXYZ(stdscr, rows, cols);

	// Calculate window dimension and size
	int winRows = lines.size() + 8;
	int winCols = cols * 0.9;
	int y = (rows - winRows) / 2;
	int x = (cols - winCols) / 2;
	this->setWindow(winRows, winCols, y, x);

	// Print title
	title = IO::untrim(!title.empty() ? title : "Message", winCols - 2);
	this->print(title, 0, 0, A_REVERSE);

	// Print the message line by line
	y = (winRows - lines.size()) / 2 - 1;
	for (auto l : lines) {
		this->setYX(y, 0);
		this->printCenter(l);
		y++;
	}

	this->setYX(winRows - 3, 0);
	this->printCenter("Press <Space> to continue ",
			COLOR_PAIR(PAIR_GRAY_BLACK_BRIGHT));

	this->render();

	// Press space to continue
	while(!IO::getQuit()) {
		IO::update();
		if (IO::getKeyName() == " ") {
			break;
		}
	}
}
