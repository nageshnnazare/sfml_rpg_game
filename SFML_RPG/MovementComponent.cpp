#include "MovementComponent.h"

MovementComponent::MovementComponent(sf::Sprite& sprite, float max_velocity) 
	: sprite(sprite), maxVelocity(max_velocity)
{
}

MovementComponent::~MovementComponent()
{
}

void MovementComponent::update(const float& dt)
{
}

void MovementComponent::move(const float& dt, const float dir_x, const float dir_y)
{
	this->velocity.x = this->maxVelocity * dir_x;
	this->velocity.y = this->maxVelocity * dir_y;

	this->sprite.move(this->velocity * dt);
}

const sf::Vector2f& MovementComponent::get_velocity() const
{
	return this->velocity;
}
