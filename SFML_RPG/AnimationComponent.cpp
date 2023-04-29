#include "AnimationComponent.h"

// Animation

AnimationComponent::Animation::Animation(sf::Sprite& sprite, 
	sf::Texture& texture_sheet, float animation_timer, int width, int height,
	int start_frame_x, int start_frame_y, int frames_x, int frames_y)
	: sprite(sprite), textureSheet(texture_sheet), 
	animationTimer(animation_timer), width(width), height(height)
{
	this->startRect = sf::IntRect(
		start_frame_x * width, start_frame_y * height, width, height);
	this->endRect = sf::IntRect(
		frames_x * width, frames_y * height, width, height);
	this->currentRect = this->startRect;

	this->timer = 0.f;

	this->sprite.setTexture(this->textureSheet, true);
	this->sprite.setTextureRect(this->startRect);
}

AnimationComponent::Animation::~Animation()
{
}

void AnimationComponent::Animation::play(const float& dt)
{
	this->timer += 100.f * dt;
	if (this->timer >= this->animationTimer) {
		this->timer = 0.f;

		if(this->currentRect != this->endRect) {
			this->currentRect.left += this->width;
		}
		else {
			this->currentRect.left = this->startRect.left;
		}
		this->sprite.setTextureRect(this->currentRect);
	}
}

void AnimationComponent::Animation::reset()
{
	this->timer = 0.f;
	this->currentRect = this->startRect;
}

// AnimationComponent

AnimationComponent::AnimationComponent(sf::Sprite& sprite, 
	sf::Texture& texture_sheet)
	: sprite(sprite), textureSheet(texture_sheet), lastAnimation(nullptr)
{
}

AnimationComponent::~AnimationComponent()
{
	for (auto& itr : this->animations) {
		delete itr.second;
	}
}

void AnimationComponent::add_animation(const std::string key, 
	float animation_timer, int width, int height,
	int start_frame_x, int start_frame_y, int frames_x, int frames_y)
{
	this->animations[key] = new Animation(this->sprite, this->textureSheet,
		animation_timer, width, height, start_frame_x, start_frame_y,
		frames_x, frames_y);
}

void AnimationComponent::play(const std::string key, const float& dt)
{
	if (this->lastAnimation != this->animations[key]) {
		if (this->lastAnimation) {
			this->lastAnimation->reset();
		}
		this->lastAnimation = this->animations[key];
	}

	this->animations[key]->play(dt);
}
