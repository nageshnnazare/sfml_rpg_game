#include "Player.h"

Player::Player(float x, float y, sf::Texture& texture_sheet) : Entity()
{
	this->init_variables();
	this->init_components();

	this->set_position(x, y);

	this->create_movement_component(300.f, 15.f, 5.f);
	this->create_animation_component(texture_sheet);

	this->animationComponent->add_animation("IDLE_LEFT", 10.f, 
		192, 192, 0, 0, 13, 0);
	this->animationComponent->add_animation("WALK_LEFT", 10.f,
		192, 192, 0, 1, 11, 1);
	this->animationComponent->add_animation("WALK_RIGHT", 10.f,
		192, 192, 0, 1, 11, 1);
}

Player::~Player()
{
}

void Player::init_variables()
{
}

void Player::init_components()
{
}

void Player::update(const float& dt)
{
	this->movementComponent->update(dt);

	if (this->movementComponent->get_movement_state(MovementStates::IDLE)) {
		this->animationComponent->play("IDLE_LEFT", dt);
	}
	else if (this->movementComponent->get_movement_state(MovementStates::MOVING_LEFT)) {
		this->animationComponent->play("WALK_LEFT", dt);
	}
	else if (this->movementComponent->get_movement_state(MovementStates::MOVING_RIGHT)) {
		this->animationComponent->play("WALK_RIGHT", dt);
	}

}