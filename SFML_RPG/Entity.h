#ifndef ENTITY_H
#define ENTITY_H

#include "MovementComponent.h"
#include "AnimationComponent.h"

class Entity
{
private:
	void init_variables();

protected:
	sf::Sprite sprite;

	MovementComponent* movementComponent;
	AnimationComponent* animationComponent;

	float movementSpeed;

public:
	Entity();
	virtual ~Entity();

	// Functions
	// components
	void set_texture(sf::Texture& texture);
	void create_movement_component(const float max_velocity, 
		const float acceleration, const float deceleration);
	void create_animation_component(sf::Texture& texture_sheet);

	// update/ render
	virtual void update(const float& dt);
	virtual void render(sf::RenderTarget* target);

	virtual void set_position(const float x, const float y);
	virtual void move(const float& dt, const float dir_x, const float dir_y);
};

#endif // !ENTITY_H

