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
	Player(float x, float y, sf::Texture& texture_sheet);
	virtual ~Player();

	void update(const float& dt) override;
};

#endif // !PLAYER_H
