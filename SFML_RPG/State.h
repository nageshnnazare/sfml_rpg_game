#ifndef STATE_H
#define STATE_H

#include "Entity.h"

class State
{
private:

protected:
	sf::RenderWindow* window;
	sf::Vector2i mousePosScreen;
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;

	std::stack<State*>* states;
	std::vector<sf::Texture> textures;
	std::map<std::string, int>* supportedKeys;
	std::map<std::string, int> keyBinds;

	bool quit;

	virtual void init_key_binds() = 0;

public:
	State(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys,
		std::stack<State*>* states);
	virtual ~State();

	// Functions
	virtual void update(const float& dt) = 0;
	virtual void update_mouse_positions();
	virtual void render(sf::RenderTarget* target = nullptr) = 0;
	virtual void update_input(const float& dt) = 0;
	virtual void end_state() = 0;

	virtual void check_for_quit();

	const bool& get_quit() const;
};

#endif
