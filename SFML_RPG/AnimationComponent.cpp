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

bool AnimationComponent::Animation::play(const float& dt)
{
	bool done = false;
	this->timer += 100.f * dt;
	if (this->timer >= this->animationTimer) {
		this->timer = 0.f;

		if(this->currentRect != this->endRect) {
			this->currentRect.left += this->width;
		}
		else {
			this->currentRect.left = this->startRect.left;
			done = true;
		}
		this->sprite.setTextureRect(this->currentRect);
	}
	return done;
}

bool AnimationComponent::Animation::play(const float& dt, float mod_percent)
{
	bool done = false;
	if (mod_percent < 0.5f) {
		mod_percent = 0.5;
	}
	this->timer += (mod_percent) * 100.f * dt;
	if (this->timer >= this->animationTimer) {
		this->timer = 0.f;

		if (this->currentRect != this->endRect) {
			this->currentRect.left += this->width;
		}
		else {
			this->currentRect.left = this->startRect.left;
			done = true;
		}
		this->sprite.setTextureRect(this->currentRect);
	}
	return done;
}

void AnimationComponent::Animation::reset()
{
	this->timer = this->animationTimer;
	this->currentRect = this->startRect;
}

// AnimationComponent

AnimationComponent::AnimationComponent(sf::Sprite& sprite, 
	sf::Texture& texture_sheet)
	: sprite(sprite), textureSheet(texture_sheet), 
	lastAnimation(nullptr), priorityAnimation(nullptr)
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

void AnimationComponent::play(const std::string key, const float& dt, 
	const bool priority)
{
	if (this->priorityAnimation) {
		if (this->priorityAnimation == this->animations[key]) {
			if (this->lastAnimation != this->animations[key]) {
				if (this->lastAnimation) {
					this->lastAnimation->reset();
				}
				this->lastAnimation = this->animations[key];
			}
			if (this->animations[key]->play(dt)) {
				this->priorityAnimation = nullptr;
			}
		}
	}
	else {
		if (priority) {
			this->priorityAnimation = this->animations[key];
		}
		if (this->lastAnimation != this->animations[key]) {
			if (this->lastAnimation) {
				this->lastAnimation->reset();
			}
			this->lastAnimation = this->animations[key];
		}
		this->animations[key]->play(dt);
	}
}

void AnimationComponent::play(const std::string key, const float& dt, 
	const float& modifier, const float& modifier_max, const bool priority)
{
	if (this->priorityAnimation) {
		if (this->priorityAnimation == this->animations[key]) {
			if (this->lastAnimation != this->animations[key]) {
				if (this->lastAnimation) {
					this->lastAnimation->reset();
				}
				this->lastAnimation = this->animations[key];
			}
			if (this->animations[key]->play(dt, abs(modifier / modifier_max))) {
				this->priorityAnimation = nullptr;
			}
		}
	}
	else {
		if (priority) {
			this->priorityAnimation = this->animations[key];
		}
		if (this->lastAnimation != this->animations[key]) {
			if (this->lastAnimation) {
				this->lastAnimation->reset();
			}
			this->lastAnimation = this->animations[key];
		}
		this->animations[key]->play(dt, abs(modifier / modifier_max));
	}
}
