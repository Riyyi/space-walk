#ifndef MAINGAME_H
#define MAINGAME_H

// Each player holds 9 ships, 3 of each size
#define SHIP_SIZE 18
#define PLAYER_SIZE 2

#include <vector>

#include "gamestate.h"

class Board;
class BoardWindow;
class InfoWindow;
class Player;
class SpaceShip;

class MainGame : public GameState
{
public:
	MainGame(Player **player);

    void initialize();
    void update();
    void render();
    void destroy();

private:
    void phase1();
    void phase2();
    void nextPlayerTurn();
    void calculateWinner();

	std::string help;
	bool phase;
	bool changePhase;
	unsigned char playerTurn;

	char queuePlanet;
	std::vector<SpaceShip *> *queue;

	Player **player;
	Board *board;
	SpaceShip **ship;
	BoardWindow *boardWindow;
	InfoWindow *infoWindow;
};

#endif // MAINGAME_H
