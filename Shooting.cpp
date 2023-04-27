#include "Shooting.hpp"

Shooting::Shooting()
{
    x_val = 0;
    y_val = 0;
    Move = false;

    magic_type = BLUE_FIRE;
    ball_dir = SHOOT_RIGHT;
}

Shooting::~Shooting()
{
 
}

bool Shooting::LoadIMG_Magic(SDL_Renderer* renderer)
{
    bool load = false;
    if (magic_type == WATER_LASER)
    {
        load = loadIMG("graphics//Spell2//waterlaser.png", renderer);
    }
    else if(magic_type == FIRE_BALL)
    {
        load = loadIMG("graphics//Spell2//fireball.png", renderer);
    }
    else
    {
        load = loadIMG("graphics//Spell2//bluefire.png", renderer);
    }

    return load;
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

    else if (ball_dir == SHOOT_DOWN_LEFT)
    {
        rect.x -= x_val;
        rect.y +=  60*cos(rect.x);
        if (rect.x < 0)
        {
            Move = false;
        }

      
       /* rect.y += y_val;
        if (rect.y > y_bor)
        {
            Move = false;
        }*/
    }
    /*else if (ball_dir == SHOOT_UP)
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

    }*/
}
