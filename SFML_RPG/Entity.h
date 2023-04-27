#ifndef ENTITY_H
#define ENTITY_H

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

class Entity
{
private:

protected:
	sf::RectangleShape shape;

	float movementSpeed;

public:
	Entity();
	virtual ~Entity();

	// Functions
	virtual void update(const float& dt);
	virtual void render(sf::RenderTarget* target);

	void move(const float& dt, const float dir_x, const float dir_y);
};

#endif	

