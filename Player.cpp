#include "Player.hpp"

Player::Player()
{
    frame = 1;
    x_val = y_val = 0.0f;
    xpos = ypos = 0.0f;

    width_frame = height_frame = 0;

    status = RUN_NONE;

    flip = SDL_FLIP_NONE;

    input_type.left = 0;
    input_type.right = 0;
    input_type.jump = 0;
    input_type.slide = 0;

    on_ground = false;

    map_x = 0;
    map_y = 0;

    come_back_time = 0;

}

Player::~Player()
{

}

bool Player::loadIMG(std::string path, SDL_Renderer* renderer)
{
    bool load = GameObject::loadIMG(path, renderer);

    if (load == true)
    {
        width_frame = rect.w/7;
        height_frame = rect.h;
    }
    return load;
}

void Player::setClips()
{
    if (width_frame > 0 && height_frame > 0)
    {
        for (int i = 0; i < 7; ++i)
        {
            frame_clip[i].x = i*width_frame;
            frame_clip[i].y = 0;
            frame_clip[i].w = width_frame;
            frame_clip[i].h = height_frame;
        }
    }
}

void Player::Show(SDL_Renderer* renderer)
{
    UpdatePlayerImage(renderer);

    if (input_type.left == 1 ||
        input_type.right == 1)
    {
        frame++;
    }
     else frame = 0;

    if (frame >= 7) frame = 0;

    if (come_back_time == 0)
    {
        rect.x = xpos - map_x;
        rect.y = ypos - map_y;

        SDL_Rect* current_clip = &frame_clip[frame];
        SDL_Rect renderQuad = {rect.x, rect.y, width_frame, height_frame};

        SDL_RenderCopyEx(renderer, mTexture, current_clip, &renderQuad, 0, NULL, flip);
        SDL_DestroyTexture(mTexture);
    }
}

void Player::HandleAction(SDL_Event ev, SDL_Renderer* renderer)
{
    if (ev.type == SDL_KEYDOWN)
    {
        switch(ev.key.keysym.sym)
        {
        case SDLK_d:
            status = RUN_RIGHT;
            input_type.right = 1;
            input_type.left = 0;
            break;
        case SDLK_a:
            status = RUN_LEFT;
            input_type.left = 1;
            input_type.right = 0;
            break;
        case SDLK_SPACE:
            input_type.jump = 1;
            break;
        default:
            break;
        }
    }

    if (ev.type == SDL_KEYUP)
    {
        switch(ev.key.keysym.sym)
        {
        case SDLK_d:
            input_type.right = 0;
            break;
        case SDLK_a:
            input_type.left = 0;
            break;
        case SDLK_SPACE:
            input_type.jump = 0;
            break;
        default:
            break;
        }
    }
}

void Player::DoPlayer(Map &map_data)
{
    if (come_back_time == 0)
    {
        x_val = 0.0f;
        y_val += GRAVITY;

        if (y_val >= MAX_FALL)
        {
            y_val = MAX_FALL;
        }

        if (input_type.left == 1)
        {
            x_val -= PLAYER_SPEED;
        }
        else if (input_type.right == 1)
        {
            x_val += PLAYER_SPEED;
        }

        if (input_type.jump == 1)
        {
            if (on_ground == true)
            {
                y_val = -JUMP_VAL;
            }
            on_ground = false;
            input_type.jump = 0;
        }

        CheckMap(map_data);
        CenterEntity(map_data);
    }

    if (come_back_time > 0)
    {
        come_back_time--;
        if (come_back_time == 0)
        {
            on_ground = false;
            if (xpos > 128)
            {
                xpos -= 128;
            } else xpos = 0;
            ypos = 0;
            y_val = 0;
            x_val = 0;
        }
    }
}

void Player::CheckMap(Map &map_data)
{
    int x1 = 0;
    int x2 = 0;

    int y1 = 0;
    int y2 = 0;

    //check horizontal
    int height_min = (height_frame < TILE_SIZE)? height_frame: TILE_SIZE;

    x1 = (xpos + x_val)/TILE_SIZE; //current tile
    x2 = (xpos + x_val + width_frame - 1)/TILE_SIZE;

    y1 = (ypos)/TILE_SIZE;
    y2 = (ypos + height_min - 1)/TILE_SIZE;

    if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y)
    {
        if (x_val > 0) // player moves to right
        {
            if (map_data.tile[y1][x2] != BLANK_TILE || map_data.tile[y2][x2])
            {
                xpos = x2*TILE_SIZE;
                xpos -= width_frame + 1;
                x_val = 0;
            }
        }
        else if (x_val < 0)
        {
            if(map_data.tile[y1][x1] != BLANK_TILE || map_data.tile[y2][x1] != BLANK_TILE)
            {
                xpos = (x1 + 1)*TILE_SIZE;
                x_val = 0;
            }
        }
    }

    //check vertical
    int width_min = (width_frame < TILE_SIZE) ? width_frame: TILE_SIZE;

    x1 = (xpos)/TILE_SIZE;
    x2 = (xpos + width_min)/TILE_SIZE;

    y1 = (ypos + y_val)/TILE_SIZE;
    y2 = (ypos + y_val + height_frame - 1)/TILE_SIZE;

    if (x1 >= 0 && x2 < MAX_MAP_X && y1 >=0 && y2 < MAX_MAP_Y)
    {
        if (y_val > 0) //down
        {
            if (map_data.tile[y2][x1] != BLANK_TILE || map_data.tile[y2][x2] != BLANK_TILE)
            {
                ypos = y2*TILE_SIZE;
                ypos -= height_frame + 1;
                y_val = 0;
                on_ground = true;

                if (status == RUN_NONE)
                {
                    //status = RUN_RIGHT;
                }
            }
        }
        else if (y_val < 0) //up
        {
            if (map_data.tile[y1][x1]  != BLANK_TILE || map_data.tile[y1][x2]  != BLANK_TILE)
            {
                ypos = (y1 + 1)*TILE_SIZE;
                y_val = 0;
            }
        }
    }

    xpos += x_val;
    ypos += y_val;

    if (xpos < 0)
    {
        xpos = 0;
    }
    else if (xpos + width_frame > map_data.max_x)
    {
        xpos = map_data.max_x - width_frame - 1;
    }

    if (ypos > map_data.max_y)
    {
        come_back_time = 30;
    }

}

void Player::CenterEntity(Map &map_data)
{
    map_data.start_x = xpos - (SCREEN_WIDTH/2);
    if (map_data.start_x < 0)
    {
        map_data.start_x = 0;
    }
    else if (map_data.start_x + SCREEN_WIDTH >= map_data.max_x)
    {
        map_data.start_x = map_data.max_x - SCREEN_WIDTH;
    }

    map_data.start_y = ypos - (SCREEN_HEIGHT/2);
    if (map_data.start_y < 0)
    {
        map_data.start_y = 0;
    }
    else if (map_data.start_y + SCREEN_HEIGHT >= map_data.max_y)
    {
        map_data.start_y = map_data.max_y - SCREEN_HEIGHT;
    }
}

void Player::UpdatePlayerImage(SDL_Renderer* renderer)
{
     if (on_ground == true)
    {
        loadIMG("graphics//player//run.png", renderer);
        switch(status)
        {
        case RUN_LEFT:
        {
            flip = SDL_FLIP_HORIZONTAL;
        }
        break;
        case RUN_RIGHT:
        {
            if (flip == SDL_FLIP_HORIZONTAL)
                {
                    flip = SDL_FLIP_NONE;
                }
        }
        break;
        default:
        break;
        }
    }
    else {
        loadIMG("graphics//player//jump.png", renderer);
        switch(status)
        {
        case RUN_LEFT:
        {
            flip = SDL_FLIP_HORIZONTAL;
        }
        break;
        case RUN_RIGHT:
        {
            if (flip == SDL_FLIP_HORIZONTAL)
                {
                    flip = SDL_FLIP_NONE;
                }
        }
        break;
        default:
        break;
        }
    }
}
