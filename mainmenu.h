#ifndef MAINMENU_H
#define MAINMENU_H

#include <memory>

#include "gamestate.h"

class Player;
class Window;

class MainMenu : public GameState
{
public:
    void initialize();
    void update();
    void render();
    void destroy();

private:
	bool titleScreen;
	Window *window;
	Player **player;
};

#endif // MAINMENU_H
