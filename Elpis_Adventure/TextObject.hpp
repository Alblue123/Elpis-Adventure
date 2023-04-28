#pragma once

#include "Game.hpp"

class TextObject
{
public:
	TextObject();
	~TextObject();

	enum TextColor
	{
		RED_TEXT = 0,
		WHITE_TEXT = 1,
		BLACK_TEXT = 2,
	};

	bool loadFromRenderedText(TTF_Font* font, SDL_Renderer* renderer);
	void free();

	void setcolor(Uint8 red, Uint8 green, Uint8 blue);
	void setcolor(int type);

	void RenderText(SDL_Renderer* renderer,
					int xpos, int ypos,
					SDL_Rect* clip = NULL,
					float angle = 0.0f,
					SDL_Point* center = NULL,
					SDL_RendererFlip flip = SDL_FLIP_NONE);

	int getWidth() const { return width_; }
	int getHeight() const { return height_; }

	void setText(const std::string& text) { str_val = text;  }
	std::string getText() const { return str_val; }
private:
	std::string str_val;
	SDL_Color text_color;
	SDL_Texture* mTexture;

	int width_;
	int height_;
};
