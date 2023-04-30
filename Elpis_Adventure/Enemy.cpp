#include "Enemy.hpp"

Enemy::Enemy()
{
    map_x = map_y = 0;
	x_pos = y_pos = 0.0f;
	x_val = y_val = 0.0f;

	width_frame_ = height_frame_ = 0;
	frame_ = 0;
   

	on_ground_ = FALSE;
	come_back_time = 0;


	Flip = SDL_FLIP_NONE;

    animation_a = animation_b = 0;
    
    input_type.left = 1;
    move_type = STATIC_ENEMY;

    for (int i = 0; i < ENEMY_WALK_FRAME; ++i)
    {
        frame_clip[i].x = 0;
        frame_clip[i].y = 0;
        frame_clip[i].w = 0;
        frame_clip[i].h = 0;
    }

    mHealth = 1;
}

Enemy::~Enemy()
{

}



bool Enemy::loadIMG(std::string path, SDL_Renderer* renderer) 
{

    bool load = GameObject::loadIMG(path, renderer);
    if (load) {
        width_frame_ = rect.w / ENEMY_WALK_FRAME;
        height_frame_ = rect.h ;
    }
    return load;
}

void Enemy::setclips()
{
    if (width_frame_ > 0 && height_frame_ > 0)
    {
        for (int i = 0; i < ENEMY_WALK_FRAME; ++i)
        {
            frame_clip[i].x = i * width_frame_;
            frame_clip[i].y = 0;
            frame_clip[i].w = width_frame_;
            frame_clip[i].h = height_frame_;
        }
    }
}


void Enemy::Show(SDL_Renderer* renderer)
{
	if (come_back_time == 0)
	{

		rect.x = x_pos - map_x;
		rect.y = y_pos - map_y;
		frame_++;

        if (frame_ >= ENEMY_WALK_FRAME)
        {
            frame_ = 0;
        }

		SDL_Rect* currentClip = &frame_clip[frame_];
		SDL_Rect renderquad = { rect.x, rect.y, width_frame_, height_frame_ };

        if (currentClip != NULL)
        {
            renderquad.w = currentClip->w;
            renderquad.h = currentClip->h;
        }

		SDL_RenderCopyEx(renderer, mTexture, currentClip, &renderquad, 0, NULL, Flip);
	}
}


void Enemy::DoEnemy(Map& gMap)
{
	if (come_back_time == 0)
	{
		x_val = 0.0;
		y_val += ENEMY_FALL;
		if (y_val >= ENEMY_MAX_FALL)
		{
			y_val = ENEMY_MAX_FALL;
		}
        if (input_type.jump == 1)
        {
            if (on_ground_ == true)
            {
                y_val -= SLIME_FALL;
            }
            on_ground_ = false;
            input_type.jump = 0;
        }
        
        if (input_type.left == 1)
        {
            x_val -= ENEMY_SPEED;
        }
        else if (input_type.right == 1)
        {
            x_val += ENEMY_SPEED;
        }

		CheckMap(gMap);
	}
	else if (come_back_time > 0)
	{
		come_back_time--;
		if (come_back_time == 0)
		{
            InitEnemy();
		}
	}
}

void Enemy::InitEnemy()
{
    y_val = 0.0f;
    x_val = 0.0f;
    if (x_pos > 128)
    {
        x_pos -= 128;
        animation_a -= 128;
        animation_b -= 128;
    }
    else
    {
        x_pos = 0;
    }
    y_pos = 0;
    input_type.left = 1;
    come_back_time = 0;
}
void Enemy::CheckMap(Map& map_data)
{
    int x1 = 0;
    int x2 = 0;

    int y1 = 0;
    int y2 = 0;



    //check horizontal
    int height_min = height_frame_;

    x1 = (x_pos + x_val) / TILE_SIZE; //current tile
    x2 = (x_pos + x_val + width_frame_ - 1) / TILE_SIZE;

    y1 = (y_pos) / TILE_SIZE;
    y2 = (y_pos + height_min - 1) / TILE_SIZE;


    if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y)
    {
        if (x_val > 0) // enemy moves to right
        {
                int val1 = map_data.tile[y1][x2];
                int val2 = map_data.tile[y2][x2];
                if ((val1 != BLANK_TILE && val1 != FRUIT && val1 != JUMPY && val1 != HEART
                    && val1 != SPIKE_H && val1 != SPIKE_V && val1 != MANAMANA)
                   ||(val2 != BLANK_TILE && val2 != FRUIT && val2 != JUMPY && val2 != HEART
                      && val2 != SPIKE_H && val2 != SPIKE_V && val2 != MANAMANA))
                {
                    x_pos = x2 * TILE_SIZE;
                    x_pos -= width_frame_ + 1;
                    animation_b = animation_b - 3;
                    
                }
        }
        else if (x_val < 0)
        {
                int val1 = map_data.tile[y1][x1];
                int val2 = map_data.tile[y2][x1];
                if ((val1 != BLANK_TILE && val1 != FRUIT && val1 != JUMPY && val1 != HEART
                    && val1 != SPIKE_H && val1 != SPIKE_V && val1 != MANAMANA)
                   ||(val2 != BLANK_TILE && val2 != FRUIT && val2 != JUMPY && val2 != HEART
                      && val2 != SPIKE_H && val2 != SPIKE_V && val2 != MANAMANA))
                {
                    x_pos = (x1 + 1) * TILE_SIZE;
                    animation_a = animation_a + 3;
                }
        }
    }

    //check vertical
    int width_min = width_frame_;

    x1 = (x_pos) / TILE_SIZE;
    x2 = (x_pos + width_min) / TILE_SIZE;

    y1 = (y_pos + y_val) / TILE_SIZE;
    y2 = (y_pos + y_val + height_frame_ - 1) / TILE_SIZE;

    if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y)
    {
        if (y_val > 0) //down
        {
                int val1 = map_data.tile[y2][x1];
                int val2 = map_data.tile[y2][x2];
                if ((val1 != BLANK_TILE && val1 != FRUIT && val1 != JUMPY && val1 != HEART && val1 != SPIKE_H && val1 != SPIKE_V)
                   ||(val2!= BLANK_TILE && val2 != FRUIT && val2 != JUMPY && val2 != HEART && val2 != SPIKE_H && val2 != SPIKE_V))
                {
                    y_pos = y2 * TILE_SIZE;
                    y_pos -= height_frame_;
                    y_val = 0.0f;
                    
                    on_ground_ = true;

                }
        }
        else if (y_val < 0) //up
        {
                int val1 = map_data.tile[y1][x1];
                int val2 = map_data.tile[y1][x2];
                if ((val1 != BLANK_TILE && val1 != FRUIT && val1 != JUMPY && val1 != HEART && val1 != SPIKE_H && val1 != SPIKE_V)
                   ||(val2 != BLANK_TILE && val2 != FRUIT && val2 != JUMPY && val2 != HEART && val2 != SPIKE_H && val2 != SPIKE_V))
                {
                    y_pos = (y1 + 1) * TILE_SIZE;
                    y_val = 0.0f;
                 
                }
        }
    }

    x_pos += x_val;
    y_pos += y_val;

    if (x_pos < 0.0f)
    {
        x_pos = 0.0f;
    }
    else if (x_pos + width_frame_ > map_data.max_x)
    {
        x_pos = map_data.max_x - width_frame_ - 1;
    }

    if (y_pos > map_data.max_y)
    {
        come_back_time = 60;
    }

}

void Enemy::ShowMove(SDL_Renderer* renderer)
{
    if (move_type == STATIC_ENEMY)
    {
      
        ;
    }
    else if (move_type == BOUNCING_ENEMY)
    {
        if (on_ground_ == true)
        {
            input_type.left = 0;
            input_type.right = 0;
            input_type.jump = 1;
        }
       
    }
    else
    {
        if (on_ground_ == true)
        {
                if (x_pos > animation_b)
                {
                    input_type.left = 1;
                    input_type.right = 0;
                    Flip = SDL_FLIP_NONE;
                }
                else if (x_pos < animation_a)
                {
                    input_type.left = 0;
                    input_type.right = 1;
                    Flip = SDL_FLIP_HORIZONTAL;
                }
        }
      
    }

}

SDL_Rect Enemy::getRectFrame()
{
    SDL_Rect rec = { 0, 0, 0, 0 };
    rec.x = rect.x;
    rec.y = rect.y;
    rec.w = width_frame_/ENEMY_WALK_FRAME;
    rec.h = height_frame_;

    return rec;
}

