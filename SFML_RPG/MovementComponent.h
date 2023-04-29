#ifndef MOVEMENT_COMPONENT_H
#define MOVEMENT_COMPONENT_H

#include <iostream>
#include <fstream>
#include <sstream>

#include <vector>
#include <stack>
#include <map>

#include <cstdlib>
#include <ctime>

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

enum class MovementStates {
	IDLE = 0,
	MOVING,
	MOVING_LEFT,
	MOVING_RIGHT,
	MOVING_UP,
	MOVING_DOWN
};

class MovementComponent
{
private:
	sf::Sprite& sprite;
	sf::Vector2f velocity;

	float maxVelocity;
	float acceleration;
	float deceleration;

	// init

public:
	MovementComponent(sf::Sprite& sprite, float max_velocity,
		float acceleration, float deceleration);
	virtual ~MovementComponent();

	// update & render
	void update(const float& dt);

	void move(const float& dt, const float dir_x, const float dir_y);

	// Access
	const sf::Vector2f& get_velocity() const;
	
	const bool get_movement_state(MovementStates state) const;
};

#endif // !MOVEMENT_COMPONENT_H

