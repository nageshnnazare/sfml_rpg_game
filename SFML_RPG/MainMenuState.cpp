#include "MainMenuState.h"

MainMenuState::MainMenuState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys)
	: State(window, supportedKeys)
{
	this->init_fonts();
	this->init_key_binds();
	this->init_buttons();

	this->background.setSize(sf::Vector2f(window->getSize().x, window->getSize().y));
	this->background.setFillColor(sf::Color::Magenta);
}

MainMenuState::~MainMenuState()
{

	for (auto it = this->buttons.begin(); it != this->buttons.end(); ++it) {
		delete it->second;
	}
}

void MainMenuState::init_fonts()
{
	if (!this->font.loadFromFile("Fonts/Dosis-Light.ttf")) {
		throw("Error: main_menu_state - could not load fonts\n");
	}
}

void MainMenuState::init_key_binds()
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

void MainMenuState::init_buttons()
{
	this->buttons["GAME_STATE"] = new Button(100, 100, 150, 50, &this->font, "New Game",
		sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 200), sf::Color(20, 20, 20, 200));

	this->buttons["EXIT_STATE"] = new Button(100, 300, 150, 50, &this->font, "Quit Game",
		sf::Color(100, 100, 100, 200), sf::Color(150, 150, 150, 200), sf::Color(20, 20, 20, 200));
}

void MainMenuState::update(const float& dt)
{
	this->update_mouse_positions();
	this->update_input(dt);
	this->update_btns();
}

void MainMenuState::update_input(const float& dt)
{
	this->check_for_quit();
}

void MainMenuState::update_btns()
{
	for (auto& btn : this->buttons) {
		btn.second->update(this->mousePosView);
	}

	if (this->buttons["GAME_STATE"]->isPressed()) {
		//this->states.push(new MainMenuState(this->window, &this->supportedKeys));
	}

	if (this->buttons["EXIT_STATE"]->isPressed()) {
		this->quit = true;
	}
}

void MainMenuState::render(sf::RenderTarget* target)
{
	if (!target) {
		target = this->window;
	}
	target->draw(this->background);	

	this->render_btns(target);
}

void MainMenuState::render_btns(sf::RenderTarget* target)
{
	for (auto& btn : this->buttons) {
		btn.second->render(target);
	}
}

void MainMenuState::end_state()
{
}
