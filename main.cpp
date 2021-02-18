/*
 * Rick van Vonderen
 * 0945444
 * TI2B
 *
 * Avoid repeated writing by using:
 * - functions with parameters (no globals) instead of almost identical pieces of code
 * - repetitive loops and arrays            instead of identical activities
 * - constants                              instead of identical values
 *
 * Divide your program into modules and/or classes that:
 * - have an explicit, well-defined interface
 * - be as independent as possible
 * - to be developed and tested separately
 *
 * Make your code understandable for others by using:
 * - Clear names in camel case, only start class names with a capital letter, consistently indent
 * - Clear, concise commentary, only where this adds something
 * - Standard terminology from the customer's field or application
 *
 *  ClassExample
 *  variableExample
 *  DEFINE_EXAMPLE
 */

#include <cstring> // strcmp()
#include <ncurses.h> // refresh()

#include "gamestate.h"
#include "inputoutput.h"
#include "mainmenu.h"
#include "test.h"

GameStateManager gameStateManager;

int main(int argc, char *argv[]) {

#ifdef DEBUG
	// IO::print("DEBUG MODE ENABLED");
	refresh();
	GameState::sleep(1000);

	if (argc >= 2 && strcmp(argv[1], "-t") == 0) {
		Test();
	}
#endif

	gameStateManager.setState(new MainMenu());

	while (!IO::getQuit()) {
		gameStateManager.render();
		gameStateManager.update();
	}

	return 0;
}
