#pragma once

#include "Game.hpp"
#include "GameObject.hpp"
#include "Shooting.hpp"

#define ENEMY_FALL 0.8
#define ENEMY_MAX_FALL 10
#define ENEMY_SPEED 3
#define ENEMY_WALK_FRAME 9
#define SLIME_FALL 18

class Enemy : public GameObject
{
public:
	Enemy();
	~Enemy();

	enum MoveType
	{
		STATIC_ENEMY = 40,
		MOVING_ENEMY = 41,
		BOUNCING_ENEMY = 42,
	};

	void LoadMap(std::string name);

	//setter

	void set_x_val(const float& xval) { x_val = xval; }
	void set_y_val(const float& yval) { y_val = yval; }
	void set_posx(const float& xpos) { x_pos = xpos;  }
	void set_posy(const float& ypos) { y_pos = ypos;  }
	void set_mapXY(const int& mp_x, const int& mp_y) { map_x = mp_x, map_y = mp_y; }
	void set_move(const int& t_move) { move_type = t_move; }
	void set_animation(const int& pos_a, const int& pos_b) { animation_a = pos_a, animation_b = pos_b; }
	void set_left(const int& leftip) { input_type.left = leftip; }
	void ShowMove(SDL_Renderer* renderer);
	void set_prjtile_list(const std::vector<Shooting*>& pj_list) { prj_list = pj_list; }

	void setclips();

	//getter
	
	float get_posx() const { return x_pos; }
	float get_posy() const { return y_pos; }
	int get_width() const { return width_frame_; }
	int get_height() const { return height_frame_; }
	std::vector<Shooting*> get_prjtile_list() const { return prj_list; }
	SDL_Rect getRectFrame();
	

	bool loadIMG(std::string path, SDL_Renderer* renderer);
	void Show(SDL_Renderer* renderer);

	void DoEnemy(Map& gMap);
	void CheckMap(Map& map_data);

	void InitEnemy();

	void InitPrj(Shooting* mPrj, SDL_Renderer* renderer);
	void MakePrj(SDL_Renderer* renderer, const int& x_limit, const int& y_limit);
	void ResetProjectile(Shooting* mPrj);

	void set_health(const int& health_) { mHealth = health_; }
	int get_health() const { return mHealth; }
	void DecreaseHealth() { mHealth--; };



private:
	std::vector<Shooting*> prj_list;

	int map_x, map_y;

	float x_pos, y_pos;
	float x_val, y_val;

	int come_back_time;
	bool on_ground_;

	SDL_Rect frame_clip[ENEMY_WALK_FRAME];

	int frame_;
	int width_frame_;
	int height_frame_;
	

	SDL_RendererFlip Flip;

	int move_type;
	Input input_type;
	int animation_a;
	int animation_b;

	int mHealth;

	int mTypes;


};