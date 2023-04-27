#include "State.h"

State::State(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys)
{
	this->window = window;
	this->supportedKeys = supportedKeys;
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

void State::check_for_quit()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBinds.at("CLOSE")))) {
		this->quit = true;
	}
}

const bool& State::get_quit()
{
	return this->quit;
}
