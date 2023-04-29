#include "State.h"

State::State(sf::RenderWindow* window, std::map<std::string, int>* supported_keys,
	std::stack<State*>* states)
{
	this->window = window;
	this->supportedKeys = supported_keys;
	this->states = states;
	this->quit = false;
}

State::~State()
{
}

void State::update_mouse_positions()
{
	this->mousePosScreen = sf::Mouse::getPosition();
	this->mousePosWindow = sf::Mouse::getPosition(*this->window);
	this->mousePosView = this->window->mapPixelToCoords(
		sf::Mouse::getPosition(*this->window));
}

const bool& State::get_quit() const
{
	return this->quit;
}

void State::end_state()
{
	this->quit = true;
}
