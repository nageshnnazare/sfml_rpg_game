#ifndef BUTTON_H
#define BUTTON_H

#include <iostream>
#include <sstream>

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

enum class ButtonStates {
	BTN_IDLE = 0,
	BTN_HOVER,
	BTN_ACTIVE
};


class Button
{
private:
	sf::RectangleShape shape;
	sf::Font* font;
	sf::Text text;

	sf::Color idleColor;
	sf::Color hoverColor;
	sf::Color activeColor;

	sf::Color textIdleColor;
	sf::Color textHoverColor;
	sf::Color textActiveColor;

	ButtonStates buttonState;

public:
	Button(float x, float y, float width, float height, 
		sf::Font * font, std::string text, unsigned character_size,
		sf::Color text_idle_color, sf::Color text_hover_color, sf::Color text_active_color,
		sf::Color idle_color, sf::Color hover_color, sf::Color active_olor);
	virtual ~Button();

	// Functions
	// update
	void update(const sf::Vector2f mouse_pos);

	// render
	void render(sf::RenderTarget* target);

	// accessors
	const bool isPressed() const;
};

#endif // !BUTTON_H