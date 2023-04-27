#pragma once

#include "Game.hpp"
#include "GameObject.hpp"

const int MAX_TILES = 200;

class TileMap : public GameObject
{
public:
    TileMap() {}
    ~TileMap() {}
};

class GameMap
{
public:
    GameMap() {}
    ~GameMap() {}

    void loadMap(std::string name);
    void loadTiles(SDL_Renderer* renderer);
    void DrawMap(SDL_Renderer* renderer);

    Map getMap() { return game_map; }
    void setMap(Map& map_data) { game_map = map_data; }
private:
    Map game_map;
    TileMap tile_map[MAX_TILES];
};

