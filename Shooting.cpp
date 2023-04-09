#include "Shooting.hpp"

Shooting::Shooting()
{
    x_val = 0;
    y_val = 0;
    Move = false;
}

Shooting::~Shooting()
{

}

void Shooting::LoadIMG_Magic(SDL_Renderer* renderer)
{
    if (magic_type == WATER_LASER)
    {
        loadIMG("graphics//Spell2//waterlaser.png", renderer);
    }
    else
    {
        loadIMG("graphics//Spell2//bluefire.png", renderer);
    }
}

void Shooting::HandleMove(const int& x_bor, const int& y_bor)
{
    if (ball_dir == SHOOT_RIGHT)
    {
        rect.x += x_val;
        if (rect.x > x_bor)
        {
            Move = false;
        }
    }
    else if (ball_dir == SHOOT_LEFT)
    {
        rect.x -= x_val;
        if (rect.x < 0)
        {
            Move = false;
        }
    }

    else if (ball_dir == SHOOT_UP)
    {
        rect.y -= y_val;
        if (rect.y < 0)
        {
            Move = false;
        }
    }
    else if (ball_dir == SHOOT_UP_LEFT)
    {
        rect.x -= x_val;
        if (rect.x < 0)
        {
            Move = false;
        }

        rect.y -= y_val;
        if (rect.y < 0)
        {
            Move = false;
        }

    }
    else if (ball_dir == SHOOT_UP_RIGHT)
    {
        rect.x += x_val;
        if (rect.x > x_bor)
        {
            Move = false;
        }

        rect.y -= y_val;
        if (rect.y < 0)
        {
            Move = false;
        }

    }
}
