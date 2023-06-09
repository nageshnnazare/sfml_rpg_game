#include "Entity.h"

Entity::Entity()
{
	this->init_variables();
}

Entity::~Entity()
{
	delete this->hitboxComponent;
	delete this->movementComponent;
	delete this->animationComponent;
}

void Entity::init_variables()
{
	this->hitboxComponent = nullptr;
	this->movementComponent = nullptr;
	this->animationComponent = nullptr;
}

void Entity::set_texture(sf::Texture& texture)
{
	this->sprite.setTexture(texture);
}

void Entity::create_hitbox_component(sf::Sprite& sprite, 
	float offset_x, float offset_y, float width, float height)
{
	this->hitboxComponent = new HitboxComponent(sprite, offset_x, offset_y,
		width, height);
}

void Entity::create_movement_component(const float max_velocity,
	const float acceleration, const float deceleration)
{
	this->movementComponent = new MovementComponent(
		this->sprite,max_velocity, acceleration, deceleration);
}

void Entity::create_animation_component(sf::Texture& texture_sheet)
{
	this->animationComponent = new AnimationComponent(this->sprite, texture_sheet);
}

void Entity::update(const float& dt)
{
	//if (this->movementComponent) {
	//	this->movementComponent->update(dt);
	//}
}

void Entity::render(sf::RenderTarget& target)
{
	target.draw(this->sprite);
	
	if (this->hitboxComponent) {
		this->hitboxComponent->render(target);
	}
}

void Entity::set_position(const float x, const float y)
{
		this->sprite.setPosition(x, y);
}

void Entity::move(const float& dt, const float dir_x, const float dir_y)
{
	if (this->movementComponent) {
		this->movementComponent->move(dt, dir_x, dir_y);
	}
}
