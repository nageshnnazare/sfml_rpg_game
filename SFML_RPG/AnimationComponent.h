#ifndef ANIMATION_H
#define ANIMATION_H

#include <iostream>
#include <string>
#include <map>

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

class AnimationComponent
{
private:
	class Animation
	{
	public:
		Animation(sf::Sprite& sprite, sf::Texture& texture_sheet, 
			float animationTimer, int width, int height,
			int start_frame_x, int start_frame_y,
			int frames_x, int frames_y);
		~Animation();

		sf::Sprite& sprite;
		sf::Texture& textureSheet;
		sf::IntRect startRect;
		sf::IntRect endRect;
		sf::IntRect currentRect;

		float animationTimer;
		float timer;
		int width;
		int height;

		bool play(const float& dt);
		bool play(const float& dt, float mod_percent);
		void reset();
	};

	sf::Sprite& sprite;
	sf::Texture& textureSheet;

	std::map<std::string, Animation*> animations;
	Animation* lastAnimation;
	Animation* priorityAnimation;

public:
	AnimationComponent(sf::Sprite& sprite, sf::Texture& texture_sheet);
	virtual ~AnimationComponent();
	
	void add_animation(const std::string key, float animation_timer, 
		int width, int height, int start_frame_x, int start_frame_y, 
		int frames_x, int frames_y);

	void play(const std::string key, const float& dt, const bool priority = false);
	void play(const std::string key, const float& dt, const float& modifier, 
		const float& modifier_max, const bool priority = false);
};

#endif // !ANIMATION_H
