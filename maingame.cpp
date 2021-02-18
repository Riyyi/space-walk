#include <algorithm>

#include "board.h"
#include "boardwindow.h"
#include "inputoutput.h"
#include "maingame.h"
#include "mainmenu.h"
#include "messagebox.h"
#include "player.h"
#include "selectionbox.h"
#include "spaceship.h"
#include "window.h"
#include "infowindow.h"

MainGame::MainGame(Player **player) :
	help("Phase 1!\n\nThe players take turns, placing a spaceship on a planet\nof their choice."),
	phase(false),
	playerTurn(0),
	queuePlanet(-1),
	player(player),
	board(nullptr),
	ship(nullptr),
	boardWindow(nullptr),
	infoWindow(nullptr) {
	// Reserve 0 spaceships of memory for the queue
	this->queue = new std::vector<SpaceShip *>(0);
}

void MainGame::initialize() {
	this->board = new Board();

	this->ship = new SpaceShip*[SHIP_SIZE] { nullptr };
	unsigned char cCounter = 0;
	unsigned char colors[PLAYER_SIZE] = { PAIR_RED_BLACK, PAIR_BLUE_BLACK };
	unsigned char sCounter = 0;
	unsigned char sizes[3] = { SpaceShip::SMALL, SpaceShip::MEDIUM, SpaceShip::BIG };
	// Create 9 ships for each player, 3 of each size
	for (unsigned char i = 0; i < SHIP_SIZE; i++) {
		if (i != 0 && i % (SHIP_SIZE / PLAYER_SIZE) == 0) {
			cCounter++;
		}

		if (i != 0 && i % 3 == 0) {
			sCounter++;
		}

		if (sCounter >= 3) {
			sCounter = 0;
		}

		this->ship[i] = new SpaceShip(colors[cCounter], sizes[sCounter]);
	}

	this->boardWindow = new BoardWindow(0, 16, this->board);
	this->infoWindow = new InfoWindow(0, 16, this->player, this->ship);

	// Display help message
	MainGame::render();
	MessageBox(this->help);
}

void MainGame::update() {
	MainGame::sleep(250);

	// Display new help message on phase change
	if (this->changePhase) {
		this->phase = true;
		this->changePhase = false;

		this->help = "Phase 2!\n\nThe players take turns, evacuating a planet of their choice.";
		MessageBox(this->help);
		return;
	}

	if (!this->phase) {
		this->phase1();
	}
	else {
		this->phase2();
	}
}

void MainGame::render() {
	this->boardWindow->clear();
	this->infoWindow->clear();

	this->boardWindow->update();
	this->infoWindow->update();

	this->boardWindow->render();
	this->infoWindow->render();
}

void MainGame::destroy() {
	delete this->board;
	delete this->boardWindow;
	delete this->infoWindow;

	for (int i = 0; i < SHIP_SIZE; i++) {
		delete this->ship[i];
	}
	delete []this->ship;

	for (int i = 0; i < PLAYER_SIZE; i++) {
		delete this->player[i];
	}
	delete []this->player;
}

void MainGame::phase1() {
	std::string playerTurnStr = std::to_string(this->playerTurn + 1);
	SelectionBox s = SelectionBox(0, 16);

	// Ask the current player to pick a Spaceship size
	std::string sizeStr = "Player " + playerTurnStr + ", pick a spaceship size.";
	std::string sizeOptions[] = {"S", "M", "B", "\0"};
	unsigned char sizeSelection = s.select(sizeStr, &sizeOptions[0]);

	// Ask the current player to pick a planet
	std::string planetStr = "Player " + playerTurnStr + ", pick a planet to put this spaceship on.";
	std::string planetOptions[] = {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "\0"};
	unsigned char planetSelection = s.select(planetStr, &planetOptions[0]);

	// Calculate array index
	int startLoop = SHIP_SIZE / PLAYER_SIZE * this->playerTurn + (sizeSelection * 3);
	// Get ships of player selected planet
	auto ships = this->board->getShips(std::stoi(planetOptions[planetSelection]));

	bool placedShip = false;
	bool shouldExit;
	// Check all 3 ships of the size the player selected
	for (int i = startLoop; i < startLoop + 3; i++) {
		shouldExit = false;

		// Check if spaceship is already on a planet
		if (this->ship[i]->getPlanet() != PLANET_UNSET) {
			continue;
		}

		// If planet already holds spaceship of equal size
		for(auto ship : *ships) {
			if (this->ship[i]->getSize() == ship->getSize()) {
				shouldExit = true;
				break;
			}
		}

		if (shouldExit) {
			MessageBox("You cant place spaceships of the same size on a planet during this phase!", "Error");
			break;
		}

		// Add spaceship to planet
		this->board->setShip(std::stoi(planetOptions[planetSelection]), this->ship[i]);
		this->nextPlayerTurn();
		placedShip = true;
		break;
	}
	if (!placedShip && !shouldExit) {
		MessageBox("Please select a size of which you still have unplaced spaceships!", "Error");
	}

	// Check if all ships have been placed
	bool allPlaced = true;
	for (int i = 0; i < SHIP_SIZE; i++) {
		if (this->ship[i]->getPlanet() == PLANET_UNSET) {
			allPlaced = false;
			break;
		}
	}
	if (allPlaced) {
		this->changePhase = true;
	}
}

void MainGame::phase2() {
	std::string playerTurnStr = std::to_string(this->playerTurn + 1);
	SelectionBox s = SelectionBox(0, 16);

	// Move next spaceship in the queue
	if (this->queue->size() > 0) {
		// Determine the middle of the board
		unsigned char halfBoard = (BOARD_SIZE - 2) / 2; // 6

		// Planet rotation order, where |x| is a black hole
		// 1 ... 6 -> |13| -> 12 ... 7 -> |0| -> 1

		// 0 .. 5
		if (this->queuePlanet < halfBoard) {
			this->queuePlanet++;
		}
		// 8 .. 13
		else if (this->queuePlanet > halfBoard + 1) {
			this->queuePlanet--;
		}
		// 6
		else if (this->queuePlanet == halfBoard) {
			this->queuePlanet = BOARD_SIZE - 1;
		}
		// 7
		else if (this->queuePlanet == halfBoard + 1) {
			this->queuePlanet = 0;
		}

		unsigned char shipSelection = 0;
		// If the the current and next ship are of the same size, ask which goes first
		if (this->queue->size() > 1) {
			SpaceShip *tmpShip = this->queue->at(0);
			SpaceShip *tmpShip2 = this->queue->at(1);
			if (tmpShip->getSize() == tmpShip2->getSize() &&
				tmpShip->getColor() != tmpShip2->getColor()) {
				std::string shipStr = "Player " + playerTurnStr + ", pick the next ship that will evacuate.";
				std::string shipOptions[] = {"Yours", "Theirs", "\0"};
				shipSelection = s.select(shipStr, &shipOptions[0]);
			}
		}

		board->moveShip(this->queuePlanet, this->queue->at(shipSelection));
		return;
	}
	else if (this->queuePlanet != -1) {
		this->queuePlanet = -1;
		this->nextPlayerTurn();
		this->calculateWinner();
		return;
	}

	// Ask the current player if they want to skip their turn
	unsigned char playerChip = this->player[this->playerTurn]->getChip();
	if (playerChip > 0) {
		std::string skipStr = "Player " + playerTurnStr + ", do you want to skip your turn for 1 chip?";
		std::string skipOptions[] = {"No", "Yes", "\0"};
		unsigned char skipSelection = s.select(skipStr, &skipOptions[0]);

		if (skipOptions[skipSelection] == "Yes") {
			this->player[this->playerTurn]->setChip(playerChip - 1);
			this->nextPlayerTurn();
			return;
		}
	}

	// Ask the current player to pick a planet
	std::string planetStr = "Player " + playerTurnStr + ", pick a planet to evacuate.";
	std::string planetOptions[] = {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "\0"};
	unsigned char planetSelection = s.select(planetStr, &planetOptions[0]);

	// Get ships of player selected planet
	auto ships = this->board->getShips(std::stoi(planetOptions[planetSelection]));

	// Check if the selected planet holds a spaceship of the current player,
	// using function/functor/lambda
	unsigned char playerColor = this->player[(int)this->playerTurn]->getColor();
	auto findShip = std::find_if(ships->begin(), ships->end(),
		[playerColor](SpaceShip *ship) {return ship->getColor() == playerColor; });

	// If so, add this planet to the queue
	if (findShip != ships->end()) {
		this->queue = ships;
		this->queuePlanet = this->queue->at(0)->getPlanet();
	}
	else {
		MessageBox("Please select a planet that holds a ship of your own!", "Error");
	}
}

void MainGame::nextPlayerTurn() {
	this->playerTurn++;
	if (this->playerTurn > PLAYER_SIZE - 1) {
		this->playerTurn = 0;
	}
}

void MainGame::calculateWinner() {
	// Get all ships from the black holes
	auto blackHole1 = this->board->getShips(0);
	auto blackHole2 = this->board->getShips(BOARD_SIZE - 1);

	int totalScore = CHIP_AMOUNT * CHIP_SCORE +
		3 * SpaceShip::BIG +
		3 * SpaceShip::MEDIUM +
		3 * SpaceShip::SMALL;

	// Fill players possible total score
	int score[PLAYER_SIZE];
	std::fill_n(score, PLAYER_SIZE, totalScore);

	// Calculate players score
	int crashedShips;
	bool gameOver = false;
	for (int i = 0; i < PLAYER_SIZE; i++) {

		// Subtract all used chips from the total score
		score[i] -= (CHIP_AMOUNT - this->player[i]->getChip()) * CHIP_SCORE;

		crashedShips = 0;
		for (auto ship : *blackHole1) {
			if (this->player[i]->getColor() == ship->getColor()) {
				crashedShips++;

				// Subtract crashed ship from the total score
				score[i] -= ship->getSize();
			}
		}
		for (auto ship : *blackHole2) {
			if (this->player[i]->getColor() == ship->getColor()) {
				crashedShips++;

				// Subtract crashed ship from the total score
				score[i] -= ship->getSize();
			}
		}

		// If a player has run out of ships..
		if (crashedShips == SHIP_SIZE / PLAYER_SIZE) {
			gameOver = true;
		}
	}

	// Print victory screen
	if (gameOver) {
		std::string printStr;

		int winnerIdx = 0;
		for (int i = 0; i < PLAYER_SIZE; i++) {
			printStr += "Player " + std::to_string(i + 1) + ": scored " +
				std::to_string(score[i]) + " points.\n";

			if (i < PLAYER_SIZE - 1 && score[i] < score[i + 1]) {
				winnerIdx = i + 1;
			}
		}

		printStr.insert(0, this->player[winnerIdx]->getName() + " has won!\n\n");
		MessageBox(printStr, "Victory");

		gameStateManager.setState(new MainMenu());
	}
}
