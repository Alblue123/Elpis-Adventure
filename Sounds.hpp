#pragma once

#include "Game.hpp"

class Sounds
{
public:
	Sounds();
	~Sounds();

	void addSound(std::string path);
	void playSound();
	void HandleSound(SDL_Event ev);

private:
	Mix_Music* music;

};
