#pragma once

#include "Game.hpp"
#include "GameObject.hpp"
#include <cmath>

class Shooting : public GameObject
{
public:
    Shooting();
    ~Shooting();

    enum BallDir
    {
        SHOOT_RIGHT = 10,
        SHOOT_LEFT = 11,
        SHOOT_UP = 12,
        SHOOT_UP_RIGHT = 13,
        SHOOT_UP_LEFT = 14,
        SHOOT_DOWN_LEFT = 15,
    };

    //setter
    void setXval(const int& xval) { x_val = xval; }
    void setYval(const int& yval) { y_val = yval; }
    void set_is_move(const bool& isMove) { Move = isMove; }
    void set_ball_dir(const int& ball_dir_) { ball_dir = ball_dir_; }
    void set_magic(const int& mtype) { magic_type = mtype; }

    //getter
    int getX() const { return x_val; }
    int getY() const { return y_val; }
    bool getMove() const { return Move; }
    int get_ball() const { return ball_dir; }
    int get_magic() const { return magic_type; }

    void HandleMove(const int& x_bor, const int& y_bor);
    bool LoadIMG_Magic(SDL_Renderer* renderer);
private:
    int x_val;
    int y_val;

    bool Move;

    int ball_dir;

    int magic_type;
};
