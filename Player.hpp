#pragma once

#include <vector>
#include "Game.hpp"
#include "GameObject.hpp"
#include "Shooting.hpp"

#define GRAVITY 0.8
#define MAX_FALL 10
#define PLAYER_SPEED 3
#define JUMP_VAL 10
enum RunType
{
    RUN_NONE = 0,
    RUN_RIGHT = 1,
    RUN_LEFT = 2,
};

class Player: public GameObject
{
public:
    Player();
    ~Player();

    bool loadIMG(std::string path, SDL_Renderer* renderer);
    void setClips();
    void Show(SDL_Renderer* renderer);
    void HandleAction(SDL_Event ev, SDL_Renderer* renderer);

    void DoPlayer(Map &map_data);
    void CheckMap(Map &map_data);
    void CenterEntity(Map &map_data);

    void setMapXY(const int mapx, const int mapy) {map_x = mapx, map_y = mapy;}

    void UpdatePlayerImage(SDL_Renderer* renderer);
    void PlayerLeftRight();

    void set_ball(std::vector<Shooting*> ball_list_) {ball_list = ball_list_;}
    std::vector<Shooting*> get_ball() const {return ball_list;}
    void SetXYPos(int xp, int yp) {xpos = xp; ypos = yp;}
    void HandleBall(SDL_Renderer* renderer);
private:
    std::vector<Shooting*> ball_list;

    float x_val;
    float y_val;

    float xpos;
    float ypos;

    int width_frame;
    int height_frame;

    SDL_Rect frame_clip[8];
    Input input_type;
    int frame;
    int status;

    SDL_RendererFlip flip;

    int map_x;
    int map_y;

    bool on_ground;
    bool is_slided;

    int come_back_time;

};
