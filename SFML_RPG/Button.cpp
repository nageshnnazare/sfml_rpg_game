#include "Button.h"

Button::Button(float x, float y, float width, float height, 
	sf::Font* font, std::string text, unsigned character_size, 
	sf::Color text_idle_color, sf::Color text_hover_color, sf::Color text_active_color,
	sf::Color idle_color, sf::Color hover_color, sf::Color active_color)
{
	this->buttonState = ButtonStates::BTN_IDLE;

	this->idleColor = idle_color;
	this->hoverColor = hover_color;
	this->activeColor = active_color;

	this->shape.setPosition(sf::Vector2f(x, y));
	this->shape.setSize(sf::Vector2f(width, height));
	this->shape.setFillColor(this->idleColor);


	this->textIdleColor = text_idle_color;
	this->textHoverColor = text_hover_color;
	this->textActiveColor = text_idle_color;

	this->font = font;
	this->text.setFont(*this->font);
	this->text.setString(text);
	this->text.setFillColor(this->idleColor);
	this->text.setCharacterSize(character_size);
	this->text.setPosition(sf::Vector2f(
		((this->shape.getPosition().x) + (this->shape.getGlobalBounds().width / 2.f)
			- (this->text.getGlobalBounds().width / 2.f)),
		((this->shape.getPosition().y) + (this->shape.getGlobalBounds().height / 2.f)
			- (this->text.getGlobalBounds().height / 2.f))
	));
}

Button::~Button()
{
}

void Button::update(const sf::Vector2f mouse_pos)
{
	this->buttonState = ButtonStates::BTN_IDLE;

	if (this->shape.getGlobalBounds().contains(mouse_pos)) {
		this->buttonState = ButtonStates::BTN_HOVER;

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			this->buttonState = ButtonStates::BTN_ACTIVE;
		}
	}

	switch (this->buttonState) {
		case ButtonStates::BTN_IDLE:
			this->shape.setFillColor(this->idleColor);
			this->text.setFillColor(this->textIdleColor);
			break;

		case ButtonStates::BTN_HOVER:
			this->shape.setFillColor(this->hoverColor);
			this->text.setFillColor(this->textHoverColor);
			break;

		case ButtonStates::BTN_ACTIVE:
			this->shape.setFillColor(this->activeColor);
			this->text.setFillColor(this->textActiveColor);
			break;

		default:
			this->shape.setFillColor(sf::Color::Red);
			this->text.setFillColor(sf::Color::Blue);
			break;
	}
}

void Button::render(sf::RenderTarget& target)
{
	target.draw(this->shape);
	target.draw(this->text);
}

const bool Button::isPressed() const
{
	if (this->buttonState == ButtonStates::BTN_ACTIVE) return true;
	return false;
}
