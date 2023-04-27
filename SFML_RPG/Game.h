#ifndef GAME_H
#define GAME_H

#include "GameState.h"

class Game
{	
private:
	sf::RenderWindow* window;
	sf::Event sfEvent;
	sf::Clock dtClk;

	std::stack<State*> states;
	std::map<std::string, int> supportedKeys;

	float dt;

	// Init funcs
	void init_window();
	void init_keys();
	void init_states();

public:
	Game();
	virtual ~Game();

	// Functions
	void end_app();
	
	// updates
	void update_SFML_events();
	void update();
	void update_dt();

	// renders
	void render();
	
	// core
	void run();
};

#endif
