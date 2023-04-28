#pragma once

#include "Game.hpp"
#include "GameObject.hpp"
#include "TextObject.hpp"

class Menu : public GameObject
{
public:

    Menu();
    ~Menu();

    int ShowMenu(SDL_Renderer* renderer, TTF_Font* font);
    int ShowResetMenu(SDL_Renderer* renderer, TTF_Font* font);
    bool loadMenu(std::string path, SDL_Renderer* renderer);
    bool CheckFousWithRect(const int& x, const int& y, const SDL_Rect& rect);

   

private:
    int width_frame;
    int height_frame;
};