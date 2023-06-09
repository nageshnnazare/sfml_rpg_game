#ifndef GAME_H
#define GAME_H

#include "MainMenuState.h"

class Game
{	
private:
	sf::RenderWindow* window;
	sf::Event sfEvent;
	sf::Clock dtClk;
	sf::ContextSettings windowSettings;

	std::stack<State*> states;
	std::map<std::string, int> supportedKeys;
	std::vector<sf::VideoMode> videoModes;

	float dt;
	bool fullScreen;

	// Init funcs
	void init_variables();
	void init_window();
	void init_keys();
	void init_states();

public:
	Game();
	virtual ~Game();

	// Functions
	// updates
	void update_SFML_events();
	void update();
	void update_dt();

	// renders
	void render();
	
	// core
	void run();
	void end_app();
};

#endif // !GAME_H
