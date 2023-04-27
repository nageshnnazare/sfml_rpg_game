#include "GameState.h"

GameState::GameState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys)
	: State(window, supportedKeys)
{
	this->init_key_binds();
}

GameState::~GameState()
{
}

void GameState::init_key_binds()
{
	std::ifstream ifs("Configs/game_state_key_binds.ini");

	if (ifs.is_open()) {
		std::string key = "";
		std::string key_char = "";

		while (ifs >> key >> key_char) {
			this->keyBinds[key] = this->supportedKeys->at(key_char);
		}
	}
	ifs.close();
}

void GameState::update(const float& dt)
{
	this->update_input(dt);

	this->player.update(dt);
}

void GameState::render(sf::RenderTarget* target)
{
	if (!target) {
		target = this->window;
	}
	this->player.render(target);
}

void GameState::update_input(const float& dt)
{
	this->check_for_quit();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBinds.at("MOVE_LEFT")))) {
		this->player.move(dt, -1.f, 0.f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBinds.at("MOVE_RIGHT")))) {
		this->player.move(dt, 1.f, 0.f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBinds.at("MOVE_UP")))) {
		this->player.move(dt, 0.f, -1.f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBinds.at("MOVE_DOWN")))) {
		this->player.move(dt, 0.f, 1.f);
	}
}

void GameState::end_state()
{
}
