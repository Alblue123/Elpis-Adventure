#include "Geometry.hpp"

void Geometry::Rectangle(const GeometricFormat& geo_size, const ColorData& c, SDL_Renderer* renderer)
{
	SDL_Rect fill_rect = { geo_size.left, geo_size.top, geo_size.width, geo_size.height };
	SDL_SetRenderDrawColor(renderer, c.red, c.green, c.blue, 255);
	SDL_RenderFillRect(renderer, &fill_rect);
}

void Geometry::RenderOutline(const GeometricFormat& geo_size, const ColorData& c, SDL_Renderer* renderer)
{
	SDL_Rect out_rect = { geo_size.left, geo_size.top, geo_size.width, geo_size.height };
	SDL_SetRenderDrawColor(renderer, c.red, c.green, c.blue, 255);
	SDL_RenderDrawRect(renderer, &out_rect);
}