#include "MovementComponent.h"

MovementComponent::MovementComponent(sf::Sprite& sprite,
	float max_velocity, float acceleration, float deceleration)
	: sprite(sprite), maxVelocity(max_velocity), 
	acceleration(acceleration), deceleration(deceleration)
{
}

MovementComponent::~MovementComponent()
{
}

void MovementComponent::update(const float& dt)
{
	if (this->velocity.x > 0.f) {
		this->velocity.x = (this->velocity.x > this->maxVelocity) ?
			this->maxVelocity : this->velocity.x;

		this->velocity.x -= this->deceleration;
		this->velocity.x = (this->velocity.x < 0.f) ?
			0.f : this->velocity.x;
	} 	
	else if (this->velocity.x < 0.f) {
		this->velocity.x = (this->velocity.x < -this->maxVelocity) ?
			-this->maxVelocity : this->velocity.x;

		this->velocity.x += this->deceleration;
		this->velocity.x = (this->velocity.x > 0.f) ?
			0.f : this->velocity.x;
	}
	
	if (this->velocity.y > 0.f) {
		this->velocity.y = (this->velocity.y > this->maxVelocity) ?
			this->maxVelocity : this->velocity.y;

		this->velocity.y -= this->deceleration;
		this->velocity.y = (this->velocity.y < 0.f) ?
			0.f : this->velocity.y;
	}
	else if (this->velocity.y < 0.f) {
		this->velocity.y = (this->velocity.y < -this->maxVelocity) ?
			-this->maxVelocity : this->velocity.y;

		this->velocity.y += this->deceleration;
		this->velocity.y = (this->velocity.y > 0.f) ?
			0.f : this->velocity.y;
	}

	this->sprite.move(this->velocity * dt);
}

void MovementComponent::move(const float& dt, const float dir_x, const float dir_y)
{
	this->velocity.x += this->acceleration * dir_x;

	this->velocity.y += this->acceleration * dir_y;
}

const sf::Vector2f& MovementComponent::get_velocity() const
{
	return this->velocity;
}

const float& MovementComponent::get_max_velocity() const
{
	return this->maxVelocity;
}

const bool MovementComponent::get_movement_state(MovementStates state) const
{
	switch (state) {
	case MovementStates::IDLE:
		return (this->velocity.x == 0.f && this->velocity.y == 0.f);
		break;

	case MovementStates::MOVING:
		return (this->velocity.x != 0.f && this->velocity.y != 0.f);
		break;

	case MovementStates::MOVING_LEFT:
		return (this->velocity.x < 0.f);
		break;

	case MovementStates::MOVING_RIGHT:
		return (this->velocity.x > 0.f);
		break;

	case MovementStates::MOVING_UP:
		return (this->velocity.y < 0.f);
		break;

	case MovementStates::MOVING_DOWN:
		return (this->velocity.y > 0.f);
		break;

	default:
		break;
	}

	return false;
}