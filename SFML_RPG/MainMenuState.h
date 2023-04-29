#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include "GameState.h"
#include "Button.h"

class MainMenuState : public State
{
private:
	sf::RectangleShape background;
	sf::Texture backgroundTexture;
	sf::Font font;

	std::map<std::string, Button*> buttons;

	// init
	void init_variables();
	void init_background();
	void init_fonts();
	void init_key_binds() override;
	void init_buttons();

public:
	MainMenuState(sf::RenderWindow* window, 
		std::map<std::string, int>* supported_keys,
		std::stack<State*>* states);
	virtual ~MainMenuState();

	// Functions
	//update
	void update(const float& dt) override;
	void update_input(const float& dt) override;
	void update_btns();

	// render
	void render(sf::RenderTarget* target = nullptr) override;
	void render_btns(sf::RenderTarget* target = nullptr);

};

#endif // !MAIN_MENU_H

