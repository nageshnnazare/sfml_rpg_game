#include "EditorState.h"

EditorState::EditorState(sf::RenderWindow* window,
	std::map<std::string, int>* supported_keys, std::stack<State*>* states)
	: State(window, supported_keys, states)
{
	this->init_variables();
	this->init_background();
	this->init_fonts();
	this->init_key_binds();
	this->init_buttons();
}

EditorState::~EditorState()
{
	for (auto& it : this->buttons) {
		delete it.second;
	}
}

void EditorState::init_variables()
{
}

void EditorState::init_background()
{
}

void EditorState::init_fonts()
{
	if (!this->font.loadFromFile("Fonts/Dosis-Light.ttf")) {
		throw("Error: editor_state - Failed to load fonts\n");
	}
}

void EditorState::init_key_binds()
{
	std::ifstream ifs("Configs/editor_state_key_binds.ini");

	if (ifs.is_open()) {
		std::string key = "";
		std::string key_char = "";

		while (ifs >> key >> key_char) {
			this->keyBinds[key] = this->supportedKeys->at(key_char);
		}
	}
	ifs.close();
}

void EditorState::init_buttons()
{
}

void EditorState::update(const float& dt)
{
	this->update_mouse_positions();
	this->update_input(dt);
	this->update_btns();
}

void EditorState::update_input(const float& dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBinds.at("CLOSE")))) {
		this->end_state();
	}
}

void EditorState::update_btns()
{
	for (auto& btn : this->buttons) {
		btn.second->update(this->mousePosView);
	}
}

void EditorState::render(sf::RenderTarget* target)
{
	if (!target) {
		target = this->window;
	}

	this->render_btns(*target);
}

void EditorState::render_btns(sf::RenderTarget& target)
{
	for (auto& btn : this->buttons) {
		btn.second->render(target);
	}
}
