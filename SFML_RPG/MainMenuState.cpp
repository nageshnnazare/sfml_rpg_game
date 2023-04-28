#include "MainMenuState.h"

MainMenuState::MainMenuState(sf::RenderWindow* window, 
	std::map<std::string, int>* supportedKeys, std::stack<State*>* states)
	: State(window, supportedKeys, states)
{
	this->init_variables();
	this->init_background();
	this->init_fonts();
	this->init_key_binds();
	this->init_buttons();
}

MainMenuState::~MainMenuState()
{

	for (auto it = this->buttons.begin(); it != this->buttons.end(); ++it) {
		delete it->second;
	}
}

void MainMenuState::init_variables()
{
}

void MainMenuState::init_background()
{
	this->background.setSize(sf::Vector2f(
		static_cast<float>(this->window->getSize().x),
		static_cast<float>(this->window->getSize().y)));

	if (!this->backgroundTexture.loadFromFile("Resources/Images/Backgrounds/bg1.png")) {
		throw("Error: main_menu_state - Failed to load background texture\n");
	}

	this->background.setTexture(&this->backgroundTexture);
}

void MainMenuState::init_fonts()
{
	if (!this->font.loadFromFile("Fonts/Dosis-Light.ttf")) {
		throw("Error: main_menu_state - Failed to load fonts\n");
	}
}

void MainMenuState::init_key_binds()
{
	std::ifstream ifs("Configs/main_menu_state_key_binds.ini");

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
	this->buttons["GAME_STATE"] = new Button(300, 480, 250, 50, &this->font, "New Game",
		sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 200), sf::Color(20, 20, 20, 200));

	this->buttons["SETTINGS"] = new Button(300, 580, 250, 50, &this->font, "Settings",
		sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 200), sf::Color(20, 20, 20, 200));

	this->buttons["EXIT_STATE"] = new Button(300, 780-50, 250, 50, &this->font, "Quit",
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
		this->states->push(new GameState(this->window, 
			this->supportedKeys, this->states));
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

#ifdef DEBUG
	sf::Text mouse_text;
	mouse_text.setPosition(this->mousePosView.x, this->mousePosView.y-20);
	mouse_text.setFont(this->font);
	mouse_text.setCharacterSize(12);

	std::stringstream ss;
	ss << this->mousePosView.x << "  " << this->mousePosView.y;
	mouse_text.setString(ss.str());

	target->draw(mouse_text);
#endif
}

void MainMenuState::render_btns(sf::RenderTarget* target)
{
	for (auto& btn : this->buttons) {
		btn.second->render(target);
	}
}

void MainMenuState::end_state()
{
	std::cout << "Ending Main Menu State" << std::endl;
}
