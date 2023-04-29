#ifndef GAME_STATE_H
#define GAME_STATE_H

#include "State.h"

class GameState : public State
{
private:
	Player* player;

	// init
	void init_key_binds() override;
	void init_textures();
	void init_players();

public:
	GameState(sf::RenderWindow* window, 
		std::map<std::string, int>* supported_keys,
		std::stack<State*>* states);
	virtual ~GameState();

	// Functions
	// update
	void update(const float& dt) override;
	void update_input(const float& dt) override;

	// render
	void render(sf::RenderTarget* target = nullptr) override;

};

#endif // !GAME_STATE_H
