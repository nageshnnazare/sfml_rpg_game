#ifndef STATE_H
#define STATE_H

#include "Player.h"

class State
{
private:

protected:
	sf::RenderWindow* window;
	sf::Vector2i mousePosScreen;
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;

	std::stack<State*>* states;
	std::map<std::string, sf::Texture> textures;
	std::map<std::string, int>* supportedKeys;
	std::map<std::string, int> keyBinds;

	bool quit;

	virtual void init_key_binds() = 0;

public:
	State(sf::RenderWindow* window, std::map<std::string, int>* supported_keys,
		std::stack<State*>* states);
	virtual ~State();

	// Functions
	virtual void update(const float& dt) = 0;
	virtual void update_mouse_positions();
	virtual void render(sf::RenderTarget* target = nullptr) = 0;
	virtual void update_input(const float& dt) = 0;

	const bool& get_quit() const;
	void end_state();
};

#endif // !STATE_H
