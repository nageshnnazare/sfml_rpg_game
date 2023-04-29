#ifndef HITBOX_H
#define HITBOX_H

#include <iostream>

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

class HitboxComponent
{
private:
	sf::Sprite& sprite;
	sf::RectangleShape hitbox;

	float offsetX;
	float offsetY;

public:
	HitboxComponent(sf::Sprite& sprite, 
		float offset_x, float offset_y, float width, float height);
	virtual ~HitboxComponent();

	// update & render
	void update();
	void render(sf::RenderTarget& target);

	bool check_intersect(const sf::FloatRect& frect) const;
};

#endif // !HITBOX_H

