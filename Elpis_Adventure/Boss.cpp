#include "Boss.hpp"

Boss::Boss()
{
    frame_ = 0;

    x_val_ = 0.0;
    y_val_ = 0.0;
    x_pos_ = 0;
    y_pos_ = 0;

    width_frame_ = 0;
    height_frame_ = 0;

    think_time_ = 0;

    map_x_ = 0;
    map_y_ = 0;

    on_ground_ = false;

    health = 15;
}

Boss::~Boss()
{

}

bool Boss::loadIMG(std::string path, SDL_Renderer* renderer)
{
    bool load = GameObject::loadIMG(path, renderer);

    if (load == true)
    {
        width_frame_ = rect.w / FRAME_NUM;
        height_frame_ = rect.h;
    }

    return load;
}

void Boss::set_clips()
{
    //Clip the sprites
    if (width_frame_ > 0 && height_frame_ > 0)
    {
        for (int i = 0; i < FRAME_NUM; ++i)
        {
            frame_clip_[i].x = width_frame_ * i;
            frame_clip_[i].y = 0;
            frame_clip_[i].w = width_frame_;
            frame_clip_[i].h = height_frame_;
        }
    }
}


void Boss::Show(SDL_Renderer* renderer)
{
    if (think_time_ == 0)
    {
        rect.x = x_pos_ - map_x_;
        rect.y = y_pos_ - map_y_;
        frame_++;
        if (frame_ >= FRAME_NUM)
        {
            frame_ = 0;
        }

        SDL_Rect* currentClip = &frame_clip_[frame_];
        SDL_Rect renderQuad = { rect.x, rect.y, width_frame_, height_frame_ };
        if (currentClip != NULL)
        {
            renderQuad.w = currentClip->w;
            renderQuad.h = currentClip->h;
        }

        SDL_RenderCopy(renderer, mTexture , currentClip, &renderQuad);
    }
}

void Boss::DoBoss(Map& g_map)
{
    if (think_time_ == 0)
    {
        x_val_ = 0;
        y_val_ += GRAVITY_SPEED;

        if (y_val_ >= MAX_FALL_SPEED)
        {
            y_val_ = MAX_FALL_SPEED;
        }

        if (input_type.left == 1)
        {
            x_val_ -= BOSS_SPEED;
        }

        else if (input_type.right == 1)
        {
            x_val_ += BOSS_SPEED;
        }

        CheckToMap(g_map);

    }

    if (think_time_ > 0)
    {
        think_time_--;

        if (think_time_ == 0)
        {
            InitBoss();
        }
    }
}

void Boss::InitBoss()
{
    x_val_ = 0;
    y_val_ = 0;

    if (x_pos_ > 128)
    {
        x_pos_ -= 128;
    }
    else
        x_pos_ = 0;
    y_pos_ = 0;
    think_time_ = 0;
    input_type.left = 1;
}

void Boss::CheckToMap(Map& g_map)
{
    int x1 = 0;
    int x2 = 0;
    int y1 = 0;
    int y2 = 0;

    on_ground_ = 0;

    //Check Horizontal
    int height_min = height_frame_;

    x1 = (x_pos_ + x_val_) / TILE_SIZE;
    x2 = (x_pos_ + x_val_ + width_frame_ - 1) / TILE_SIZE;

    y1 = (y_pos_) / TILE_SIZE;
    y2 = (y_pos_ + height_min - 1) / TILE_SIZE;

    // Check x1, x2 with full width of map
    // Check y1, y2 with full heigth of map
    if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y)
    {
        if (x_val_ > 0) // when object is moving by right  ===>
        {
            // Check current position of map. It is not blank_tile.
            if ((g_map.tile[y1][x2] != BLANK_TILE) || (g_map.tile[y2][x2] != BLANK_TILE))
            {
               
                x_pos_ = x2 * TILE_SIZE;
                x_pos_ -= width_frame_ + 1;
                x_val_ = 0; // cannot moving
            }
        }
        else if (x_val_ < 0) // When moving by left    <====
        {
            if ((g_map.tile[y1][x1] != BLANK_TILE) || (g_map.tile[y2][x1] != BLANK_TILE))
            {
                x_pos_ = (x1 + 1) * TILE_SIZE;
                x_val_ = 0;
            }
        }
    }


    // Check vertical
    int width_min = width_frame_;

    x1 = (x_pos_) / TILE_SIZE;
    x2 = (x_pos_ + width_min) / TILE_SIZE;

    y1 = (y_pos_ + y_val_) / TILE_SIZE;
    y2 = (y_pos_ + y_val_ + height_frame_) / TILE_SIZE;

    if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y)
    {
        if (y_val_ > 0)
        {
            //Similar for vertical
            if ((g_map.tile[y2][x1] != BLANK_TILE) || (g_map.tile[y2][x2] != BLANK_TILE))
            {
                y_pos_ = y2 * TILE_SIZE;
                y_pos_ -= height_frame_;

                y_val_ = 0;

                on_ground_ = 1;
            }
        }
        else if (y_val_ < 0)
        {
            if ((g_map.tile[y1][x1] != BLANK_TILE) || (g_map.tile[y1][x2] != BLANK_TILE))
            {
                y_pos_ = (y1 + 1) * TILE_SIZE;

                y_val_ = 0;
            }
        }
    }

    //If there is not collision with map tile. 
    x_pos_ += x_val_;
    y_pos_ += y_val_;

    if (x_pos_ < 0)
    {
        x_pos_ = 0;
    }
    else if (x_pos_ + width_frame_ >= g_map.max_x)
    {
        x_pos_ = g_map.max_x - width_frame_ - 1;
    }

    if (y_pos_ > g_map.max_y)
    {
        think_time_ = 60;
    }
}

void Boss::InitBullet(SDL_Renderer* renderer)
{
    Shooting* mPrj = new Shooting();
    bool load = mPrj->loadIMG("graphics//Spell2//boss.png", renderer);
    if (load)
    {
        mPrj->set_ball_dir(Shooting::SHOOT_DOWN_LEFT);
        mPrj->set_is_move(true);
        mPrj->setRect(rect.x - 20, rect.y - height_frame_ + 65);
        mPrj->setXval(6);
        bullet_list_.push_back(mPrj);
    }
}


void Boss::MakeBullet(SDL_Renderer* renderer, const int& x_limit, const int& y_limit)
{
    if (frame_ == 15)
    {
        InitBullet(renderer);
    }

    for (int i = 0; i < bullet_list_.size(); i++)
    {
        Shooting* mPrj = bullet_list_.at(i);
        if (mPrj != NULL)
        {
            if (mPrj->getMove())
            {
                mPrj->HandleMove(x_limit, y_limit);
                mPrj->render(renderer);
            }
            else
            {
                mPrj->free();
                delete mPrj;
                bullet_list_.erase(bullet_list_.begin() + i);
            }
        }
    }
}

SDL_Rect Boss::GetRectFrame() const
{
    SDL_Rect rectFrame = { rect.x, rect.y, width_frame_, height_frame_ };
    return rectFrame;
}

void Boss:: ResetProjectile(Shooting* mPrj)
{
    mPrj->setRect(rect.x - 20, rect.y - height_frame_ + 65);
    mPrj->setXval(6);
}