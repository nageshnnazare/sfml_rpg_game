#include "Button.h"

Button::Button(float x, float y, float width, float height, 
	sf::Font* font, std::string text, 
	sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor)
{
	this->buttonState = ButtonStates::BTN_IDLE;

	this->shape.setPosition(sf::Vector2f(x, y));
	this->shape.setSize(sf::Vector2f(width, height));
	this->font = font;
	this->text.setFont(*this->font);
	this->text.setString(text);
	this->text.setFillColor(sf::Color::White);
	this->text.setCharacterSize(20);
	this->text.setPosition(sf::Vector2f(
		((this->shape.getPosition().x) + (this->shape.getGlobalBounds().width / 2.f)
		- (this->text.getGlobalBounds().width / 2.f)),
		((this->shape.getPosition().y) + (this->shape.getGlobalBounds().height / 2.f)
		- (this->text.getGlobalBounds().height))
	));

	this->idleColor = idleColor;
	this->hoverColor = hoverColor;
	this->activeColor = activeColor;
	this->text.setFillColor(this->activeColor);
}

Button::~Button()
{
}

void Button::update(const sf::Vector2f mousePos)
{
	this->buttonState = ButtonStates::BTN_IDLE;

	if (this->shape.getGlobalBounds().contains(mousePos)) {
		this->buttonState = ButtonStates::BTN_HOVER;

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			this->buttonState = ButtonStates::BTN_ACTIVE;
		}
	}

	switch (this->buttonState) {
		case ButtonStates::BTN_IDLE:
			this->shape.setFillColor(this->idleColor);
			break;

		case ButtonStates::BTN_HOVER:
			this->shape.setFillColor(this->hoverColor);
			break;

		case ButtonStates::BTN_ACTIVE:
			this->shape.setFillColor(this->activeColor);
			break;

		default:
			this->shape.setFillColor(sf::Color::Red);
			break;
	}
}

void Button::render(sf::RenderTarget* target)
{
	target->draw(this->shape);
	target->draw(this->text);
}

const bool Button::isPressed() const
{
	if (this->buttonState == ButtonStates::BTN_ACTIVE) return true;
	return false;
}
