#include "Player.h"

Player::Player(float x, float y, sf::Texture& texture_sheet) : Entity()
{
	this->init_variables();
	this->init_components();

	this->set_position(x, y);

	this->create_hitbox_component(this->sprite, 
		(192/2.f)-20.f, (192/2.f)-40.f, (192/2.f), (192/2.f)+30.f);
	this->create_movement_component(350.f, 15.f, 5.f);
	this->create_animation_component(texture_sheet);

	this->animationComponent->add_animation("IDLE", 11.f, 
		192, 192, 0, 0, 13, 0);
	this->animationComponent->add_animation("WALK", 7.f,
		192, 192, 0, 1, 11, 1);
	this->animationComponent->add_animation("ATTACK", 6.f,
		192 * 2, 192, 0, 2, 13, 2);
}

Player::~Player()
{
}

void Player::init_variables()
{
	this->attacking = false;
}

void Player::init_components()
{
}

void Player::update(const float& dt)
{
	this->movementComponent->update(dt);

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		this->attacking = true;
	}
	if (this->attacking) {
		this->animationComponent->play("ATTACK", dt, true);
	}

	if (this->movementComponent->get_movement_state(MovementStates::IDLE)) {
		this->animationComponent->play("IDLE", dt);
	}
	else if (this->movementComponent->get_movement_state(MovementStates::MOVING_LEFT)) {
		this->attacking = false;
		this->sprite.setOrigin(0.f, 0.f);
		this->sprite.setScale(1.f, 1.f);
		this->animationComponent->play("WALK", dt, 
			this->movementComponent->get_velocity().x, this->movementComponent->get_max_velocity());
	}
	else if (this->movementComponent->get_movement_state(MovementStates::MOVING_RIGHT)) {
		this->attacking = false;
		this->sprite.setOrigin(192+(192/2.f)-40.f, 0.f);
		this->sprite.setScale(-1.f, 1.f);
		this->animationComponent->play("WALK", dt,
			this->movementComponent->get_velocity().x, this->movementComponent->get_max_velocity());
	}
	else if (this->movementComponent->get_movement_state(MovementStates::MOVING_UP)) {
		this->attacking = false;
		this->animationComponent->play("WALK", dt,
			this->movementComponent->get_velocity().y, this->movementComponent->get_max_velocity());
	}
	else if (this->movementComponent->get_movement_state(MovementStates::MOVING_DOWN)) {
		this->attacking = false;
		this->animationComponent->play("WALK", dt,
			this->movementComponent->get_velocity().y, this->movementComponent->get_max_velocity());
	}

	this->hitboxComponent->update();

}