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

class MovementComponent
{
private:
	sf::Sprite& sprite;

	sf::Vector2f velocity;
	sf::Vector2f acceleration;
	sf::Vector2f deceleration;

	float maxVelocity;

	// init

public:
	MovementComponent(sf::Sprite& sprite, float max_velocity);
	virtual ~MovementComponent();

	// update & render
	void update(const float& dt);

	void move(const float& dt, const float dir_x, const float dir_y);

	// Access
	const sf::Vector2f& get_velocity() const;
};

#endif // !MOVEMENT_COMPONENT_H

