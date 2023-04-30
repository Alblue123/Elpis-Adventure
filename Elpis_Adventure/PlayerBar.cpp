#include "PlayerBar.hpp"

PlayerBar::PlayerBar()
{
	num = 4;
}

PlayerBar::~PlayerBar()
{

}

void PlayerBar::AddPos(const int& xpos)
{
	pos_ids.push_back(xpos);
}

void PlayerBar::Init(SDL_Renderer* renderer)
{
	bool load = loadIMG("graphics//Supportive//heart.png", renderer);
	if (pos_ids.size() > 0)
	{
		pos_ids.clear();
	}
	if (load)
	{
		AddPos(20);
		AddPos(60);
		AddPos(100);
		AddPos(140);
	}
}
void PlayerBar::Show(SDL_Renderer* renderer)
{
	for (int i = 0; i < (pos_ids.size()); ++i)
	{
		rect.x = pos_ids.at(i);
		rect.y = 4;
		render(renderer);
	}
}

void PlayerBar::DecreaseHealth()
{
	if (num <= 4 && num > 0)
	{
		num--;
	}
	if (!pos_ids.empty())
	{
		pos_ids.pop_back();
	}
}

void PlayerBar::IncreaseHealth()
{
	if (num >= 4) num = 4;
	else
	{
		num++;
		int last_pos = pos_ids.back();
		last_pos += 40;
		pos_ids.push_back(last_pos);
	}
}