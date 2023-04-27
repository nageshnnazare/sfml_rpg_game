#ifndef GAME_STATE_H
#define GAME_STATE_H

#include "State.h"

class GameState : public State
{
private:
	Entity player;

	void init_key_binds() override;

public:
	GameState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys);
	virtual ~GameState();

	// Functions
	void update(const float& dt) override;
	void render(sf::RenderTarget* target = nullptr) override;
	void update_input(const float& dt) override;
	void end_state() override;
};

#endif
