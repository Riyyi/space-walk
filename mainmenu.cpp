#include "inputoutput.h"
#include "maingame.h"
#include "mainmenu.h"
#include "player.h"
#include "window.h"

void MainMenu::initialize() {
	int rows;
	int cols;
	Window::getMaXYZ(stdscr, rows, cols);

	this->window = new Window(rows, cols, 0, 0);
	this->titleScreen = true;
	this->player = new Player*[PLAYER_SIZE] { nullptr };
}

void MainMenu::update() {
	if (this->titleScreen) {
		IO::update();

		if (IO::getKeyName() == " ") {
			this->titleScreen = false;
		}
	}
	else {
		int y;
		int x;
		std::string tmpStr;
		unsigned char colors[PLAYER_SIZE] = { PAIR_RED_BLACK, PAIR_BLUE_BLACK };
		for (int i = 0; i < PLAYER_SIZE; i++) {
			if (this->player[i] == nullptr) {
				this->window->getYX(y, x);

				tmpStr = "";
				while (tmpStr == "") {
					tmpStr = IO::trim(this->window->getStr());
					this->window->setYX(y, x);
				}

				this->player[i] = new Player();
				this->player[i]->setName(tmpStr);
				this->player[i]->setColor(colors[i]);
				break;
			}

			if (i == PLAYER_SIZE - 1) {
				gameStateManager.setState(new MainGame(this->player));
			}
		}
	}
}

void MainMenu::render() {
	this->window->clear();

	this->window->update();
	this->window->setWindow(this->window->getMaxRows(), this->window->getMaxCols(), 0, 0);
	this->window->resize();

	if (this->titleScreen) {
		this->window->printSide("", "Rick van Vonderen");
		this->window->setYX(1, 0);
		this->window->printSide("", "0945444");
		this->window->setYX(2, 0);
		this->window->printSide("", "TI2B");

		this->window->setYX(this->window->getRows() / 2 - 1, 0);
		this->window->printCenter("---   Space Walk   ---");

		this->window->setYX(this->window->getRows() - 4, 0);
		this->window->printCenter("Press <Space> to walk..");
	}
	else {
		int x = this->window->getCols() / 2 - 11 ;
		int y = this->window->getRows() / 2;
		std::string tmp;
		for (int i = 0; i < PLAYER_SIZE; i++) {
			tmp = std::string("Enter Player ") + std::to_string(i + 1) + std::string(" name: ");

			if (this->player[i] != nullptr) {
				tmp += this->player[i]->getName();
			}

			this->window->print(tmp, y, x);
			y++;

			if (this->player[i] == nullptr) {
				break;
			}
		}
	}

	this->window->render();
}

void MainMenu::destroy() {
	delete this->window;
}
