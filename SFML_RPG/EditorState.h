#ifndef EDITOR_STATE_H
#define EDITOR_STATE_H

#include "State.h"
#include "Button.h"

class EditorState : public State
{
private:
	sf::Font font;

	std::map<std::string, Button*> buttons;

	// init
	void init_variables();
	void init_background();
	void init_fonts();
	void init_key_binds() override;
	void init_buttons();

public:
	EditorState(sf::RenderWindow* window,
		std::map<std::string, int>* supported_keys,
		std::stack<State*>* states);
	virtual ~EditorState();

	// Functions
	//update
	void update(const float& dt) override;
	void update_input(const float& dt) override;
	void update_btns();

	// render
	void render(sf::RenderTarget* target = nullptr) override;
	void render_btns(sf::RenderTarget& target);
};


#endif // !EDITOR_STATE_H
