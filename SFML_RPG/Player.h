#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"

class Player : public Entity
{
private:
	// init 
	void init_variables();
	void init_components();
protected:

public:
	Player(float x, float y, sf::Texture& texture);
	virtual ~Player();
};

#endif // !PLAYER_H
