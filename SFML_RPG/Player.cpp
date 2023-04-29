#include "Player.h"

Player::Player(float x, float y, sf::Texture& texture) : Entity()
{
	this->init_variables();
	this->init_components();

	this->set_texture(texture);
	this->set_position(x, y);
}

Player::~Player()
{
}

void Player::init_variables()
{
}

void Player::init_components()
{
	this->create_movement_component(100.f);
}
