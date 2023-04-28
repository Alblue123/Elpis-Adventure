#include "Explosion.hpp"

Explosion::Explosion()
{
	frame_width = frame_height = 0;
	frame = 0;

    f_lip = SDL_FLIP_NONE;
}

Explosion::~Explosion()
{

}

bool Explosion::loadIMG(std::string path, SDL_Renderer* renderer)
{
    bool load = GameObject::loadIMG(path, renderer);

    if (load == true)
    {
        frame_width = rect.w / EXPLO_FRAME;
        frame_height = rect.h;
    }
    return load;
}

void Explosion::setClip()
{
    if (frame_width > 0 && frame_height > 0)
    {
        for (int i = 0; i < EXPLO_FRAME; ++i)
        {
            frame_clip[i].x = i * frame_width;
            frame_clip[i].y = 0;
            frame_clip[i].w = frame_width;
            frame_clip[i].h = frame_height;
        }
    }
}

void Explosion::Show(SDL_Renderer* renderer)
{
    SDL_Rect* current_clip = &frame_clip[frame];
    SDL_Rect renderQuad = { rect.x, rect.y, frame_width, frame_height };

    if (current_clip != NULL)
    {
        renderQuad.w = current_clip->w;
        renderQuad.h = current_clip->h;
    }

    SDL_RenderCopyEx(renderer, mTexture, current_clip, &renderQuad, 0, NULL, f_lip);
}