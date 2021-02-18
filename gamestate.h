#ifndef GAMESTATE
#define GAMESTATE

#include <chrono> // time
#include <thread> // sleep_for

#include "inputoutput.h"
#include "window.h"

class GameState
{
public:
	// Makes sure that the inherited class's destructor is called
	virtual ~GameState() {}

	virtual void initialize() {}
	virtual void update() {}
	virtual void render() {}
	virtual void destroy() {}

	static void sleep(int amount) {
		// Sleep for amount ms
		std::this_thread::sleep_for(std::chrono::milliseconds(amount));
	}
};

class GameStateManager
{
public:
	GameStateManager() : state(nullptr) {
		Window::initialize();
	}

	~GameStateManager() {
		if(this->state != nullptr) {
			this->state->destroy();
			delete this->state;
		}

		Window::destroy();
	}

	void setState(GameState* state) {
		if(this->state != nullptr) {
			this->state->destroy();
			delete this->state;
		}

		this->state = state;
		if(this->state != nullptr) {
			this->state->initialize();
		}
	}

	void update() {
		GameState::sleep(15);

		if(this->state != nullptr) {
			this->state->update();
		}
	}

	void render() {
		if(this->state != nullptr) {
			this->state->render();
		}
	}

private:
	GameState *state;
};

extern GameStateManager gameStateManager;

#endif // GAMESTATE
