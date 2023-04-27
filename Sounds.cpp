#include "Sounds.hpp"

Sounds::Sounds()
{
	music = NULL;
}

Sounds::~Sounds()
{
	Mix_FreeMusic(music);
	music = NULL;
}

void Sounds::addSound(std::string path)
{
	music = Mix_LoadMUS(path.c_str());
}

void Sounds::playSound()
{
	Mix_PlayMusic(music, -1);
}

void Sounds::HandleSound(SDL_Event ev)
{
	if (ev.type == SDL_KEYDOWN)
	{
		if (ev.key.keysym.sym == SDLK_1)
		{
			if (Mix_PlayingMusic() == 0)
			{
				//Play the music
				playSound();
			}
			//If music is being played
			else
			{
				//If the music is paused
				if (Mix_PausedMusic() == 1)
				{
					//Resume the music
					Mix_ResumeMusic();
				}
				//If the music is playing
				else
				{
					//Pause the music
					Mix_PauseMusic();
				}
			}
		}
	}
}