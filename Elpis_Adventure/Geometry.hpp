#pragma once

#include "Game.hpp"

 struct GeometricFormat
{
	GeometricFormat(int left_, int top_, int width_, int height_)
	{ left = left_, top = top_, width = width_, height = height_; }

	int left;
	int top;
	int width;
	int height;
};

 struct ColorData
{
	ColorData(Uint8 r, Uint8 g, Uint8 b) { red = r, green = g, blue = b; }

	Uint8 red;
	Uint8 green;
	Uint8 blue;
};

class Geometry
{
public:
	static void Rectangle(const GeometricFormat& geo_size, const ColorData& c, SDL_Renderer* renderer);
	static void RenderOutline(const GeometricFormat& geo_size, const ColorData& c, SDL_Renderer* renderer);
};