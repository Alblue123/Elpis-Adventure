#pragma once

#include "Game.hpp"
#include "GameObject.hpp"

#define EXPLO_FRAME 6
class Explosion : public GameObject
{
public:

	Explosion();
	~Explosion();

	void setClip();
	void set_frame(const int& frame_) { frame = frame_; }

	int get_frame_width() const { return frame_width; }
	int get_frame_height() const { return frame_height; }

	bool loadIMG(std::string path, SDL_Renderer* renderer);
	void Show(SDL_Renderer* renderer);

private:
	int frame_width, frame_height;
	int frame;
	SDL_Rect frame_clip[EXPLO_FRAME];

	SDL_RendererFlip f_lip;

};