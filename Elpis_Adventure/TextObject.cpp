#include "TextObject.hpp"

TextObject::TextObject()
{
	text_color.r = 255;
	text_color.g = 255;
	text_color.b = 255;

	mTexture = NULL;

	width_ = height_ = 0;
}

TextObject::~TextObject()
{

}

bool TextObject::loadFromRenderedText(TTF_Font* font, SDL_Renderer* renderer)
{
	free();

	SDL_Surface* text_surface = TTF_RenderText_Solid(font, str_val.c_str(), text_color);
	if (text_surface == NULL)
	{
		std::cout << "Unable to render text surface! SDL_ttf Error: " << TTF_GetError() << std::endl;
	}
	else
	{
		mTexture = SDL_CreateTextureFromSurface(renderer, text_surface);
		if (mTexture == NULL)
		{
			std::cout
				<< "Unable to create texture from rendered text! SDL Error: " << SDL_GetError() << std::endl;
		}
		else
		{
			width_ = text_surface->w;
			height_ = text_surface->h;
		}

		SDL_FreeSurface(text_surface);
	}

	return mTexture != NULL;
}

void TextObject::free()
{
	if (mTexture != NULL)
	{
		SDL_DestroyTexture(mTexture);
		mTexture = NULL;
		width_ = 0;
		height_ = 0;
	}
}

void TextObject::setcolor(Uint8 red, Uint8 green, Uint8 blue)
{
	text_color.r = red;
	text_color.g = green;
	text_color.b = blue;
}

void TextObject::setcolor(int type)
{
	if (type == RED_TEXT)
	{
		SDL_Color color = { 255, 0, 0 };
		text_color = color;
	}
	else if (type == BLACK_TEXT)
	{
		SDL_Color color = { 0, 0, 0 };
		text_color = color;
	}
	else
	{
		SDL_Color color = { 255, 255, 255 };
		text_color = color;
	}
}

void TextObject::RenderText(SDL_Renderer* renderer,
							int xpos, int ypos,
							SDL_Rect* clip,
							float angle,
							SDL_Point* center,
							SDL_RendererFlip flip)
{
	SDL_Rect renderQuad = { xpos, ypos, width_, height_ };
	if (clip != NULL)
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}
	SDL_RenderCopyEx(renderer, mTexture, clip, &renderQuad, angle, center, flip);
}

