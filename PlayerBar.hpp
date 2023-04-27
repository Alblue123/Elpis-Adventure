#pragma once

#include "Game.hpp"
#include "GameObject.hpp"

class PlayerBar : public GameObject
{
public:
	PlayerBar();
	~PlayerBar();

	void setNum(const int& num_) { num = num_; }
	void AddPos(const int& xpos);
	void Show(SDL_Renderer* renderer);
	void Init(SDL_Renderer* renderer);
	int get_num() const { return num; }

	void IncreaseHealth();
	void DecreaseHealth();

private:
	int num;
	std::vector<int> pos_ids;
};