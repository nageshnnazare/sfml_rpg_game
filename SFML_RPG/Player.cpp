#include "Player.h"

Player::Player(float x, float y, sf::Texture& texture_sheet) : Entity()
{
	this->init_variables();
	this->init_components();

	this->set_position(x, y);

	this->create_hitbox_component(this->sprite, (192/2.f)-20.f, (192/2.f)-40.f, (192/2.f), (192/2.f)+30.f);
	this->create_movement_component(300.f, 15.f, 5.f);
	this->create_animation_component(texture_sheet);

	this->animationComponent->add_animation("IDLE", 10.f, 
		192, 192, 0, 0, 13, 0);
	this->animationComponent->add_animation("WALK", 10.f,
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
		this->animationComponent->play("IDLE", dt);
	}
	else if (this->movementComponent->get_movement_state(MovementStates::MOVING_LEFT)) {
		this->sprite.setOrigin(0.f, 0.f);
		this->sprite.setScale(1.f, 1.f);
		this->animationComponent->play("WALK", dt);
	}
	else if (this->movementComponent->get_movement_state(MovementStates::MOVING_RIGHT)) {
		this->sprite.setOrigin(192+(192/2.f)-40.f, 0.f);
		this->sprite.setScale(-1.f, 1.f);
		this->animationComponent->play("WALK", dt);
	}
	else if (this->movementComponent->get_movement_state(MovementStates::MOVING_UP)) {
		this->animationComponent->play("WALK", dt);
	}
	else if (this->movementComponent->get_movement_state(MovementStates::MOVING_DOWN)) {
		this->animationComponent->play("WALK", dt);
	}

	this->hitboxComponent->update();

}