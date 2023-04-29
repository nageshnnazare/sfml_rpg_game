#include "GameState.h"

GameState::GameState(sf::RenderWindow* window, 
	std::map<std::string, int>* supported_keys, std::stack<State*>* states)
	: State(window, supported_keys, states)
{
	this->init_key_binds();
	this->init_textures();
	this->init_players();
}

GameState::~GameState()
{
	delete this->player;
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

void GameState::init_textures()
{
	if (!this->textures["PLAYER_IDLE"].loadFromFile("Resources/Images/Sprites/Player/sword.png")) {
		throw ("Error: game_state - Failed to load player idle sprite\n");
	}
}

void GameState::init_players()
{
	this->player = new Player(0, 0, this->textures["PLAYER_IDLE"]);
}

void GameState::update(const float& dt)
{
	this->update_mouse_positions();
	this->update_input(dt);

	this->player->update(dt);
}

void GameState::update_input(const float& dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBinds.at("MOVE_LEFT")))) {
		this->player->move(dt, -1.f, 0.f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBinds.at("MOVE_RIGHT")))) {
		this->player->move(dt, 1.f, 0.f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBinds.at("MOVE_UP")))) {
		this->player->move(dt, 0.f, -1.f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBinds.at("MOVE_DOWN")))) {
		this->player->move(dt, 0.f, 1.f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBinds.at("CLOSE")))) {
		this->end_state();
	}
}

void GameState::render(sf::RenderTarget* target)
{
	if (!target) {
		target = this->window;
	}
	this->player->render(target);
}

