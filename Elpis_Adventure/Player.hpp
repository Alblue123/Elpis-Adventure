#pragma once

#include <vector>
#include "Game.hpp"
#include "GameObject.hpp"
#include "PlayerBar.hpp"
#include "Shooting.hpp"

#define GRAVITY 0.8f
#define MAX_FALL 10
#define PLAYER_SPEED 3
#define JUMP_VAL 10
enum PLAYERACT
{
    RUN_NONE = 0,
    RUN_RIGHT = 1,
    RUN_LEFT = 2,
    ATTACK = 3,
};

class Player : public GameObject
{
public:
    Player();
    ~Player();

    bool loadIMG(std::string path, SDL_Renderer* renderer);
    void setClips();
    void Show(SDL_Renderer* renderer);
    void HandleAction(SDL_Event ev, SDL_Renderer* renderer);
    SDL_Rect getRectFrame();

    void DoPlayer(Map& map_data);
    void CheckMap(Map& map_data);
    void CenterEntity(Map& map_data);

    void setMapXY(const int mapx, const int mapy) { map_x = mapx, map_y = mapy; }

    void UpdatePlayerImage(SDL_Renderer* renderer);
    void PlayerLeftRight();

    void set_ball(std::vector<Shooting*> ball_list_) { ball_list = ball_list_; }
    std::vector<Shooting*> get_ball() const { return ball_list; }
    void HandleBall(SDL_Renderer* renderer);
    void RemoveBall(const int& id);

    void HandleScore();
    int get_score() const { return score; }
    void set_score(const int& score_) { score = score_; }

    void set_come_back_time(const int& cb_time) { come_back_time = cb_time;  }
    void set_healing_status(const bool& healing) { healed = healing; }
    void set_damaged_status(const bool& damaging) { is_damaged = damaging; }
    void set_check_death(const bool& death_) { player_dead = death_; }
    void set_mana(const int& mana_) { mana = mana_; }
    void set_magic(const int& magic_index_) { magic_index = magic_index_; }
    void set_x_pos(const float& x_pos) { xpos = x_pos; }
    void set_y_pos(const float& y_pos) { xpos = y_pos; }
    void set_magi_change(const bool& magi_) { magi_changed = magi_; }


    int GetStatus() const { return status; }

    float Get_x_pos() const { return xpos; }
    float Get_y_pos() const { return ypos; }
    int get_width_frame() const { return width_frame; }
    int get_height_frame() const { return height_frame; }
    bool get_healed() const { return healed; }
    bool get_damaged() const { return is_damaged; }
    bool get_death() const { return player_dead; }
    int get_magic() const { return magic_index; }
    int get_mana() const { return mana; }
    bool get_magi_change() const { return magi_changed; }
    
    

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

    int score;
    int magic_index;

    int jump;
    int speed;

    int mana;

    bool healed;
    bool is_damaged;

    bool player_dead;
    
    bool magi_changed;
};
