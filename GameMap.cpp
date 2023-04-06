#include "GameMap.hpp"

void GameMap::loadMap(std::string name)
{
    FILE* fp = NULL;
    fopen_s(&fp, name.c_str(), "rb"); //open file
    if (fp == NULL)
    {
        return;
    }

    //loading max value
    game_map.max_x = 0;
    game_map.max_y = 0;
    for (int y = 0; y < MAX_MAP_Y; ++y)
    {
        for (int x = 0; x < MAX_MAP_X; ++x)
        {
            fscanf(fp, "%d", &game_map.tile[y][x]);
            int val = game_map.tile[y][x];
            if (val > 0)
            {
                if (x > game_map.max_x)
                {
                    game_map.max_x = x;
                }
                if (y > game_map.max_y)
                {
                    game_map.max_y = y;
                }
            }
        }
    }

    //full map
    game_map.max_x = (game_map.max_x + 1)*TILE_SIZE;
    game_map.max_y = (game_map.max_y + 1)*TILE_SIZE;

    game_map.start_x = 0;
    game_map.start_y = 0;

    game_map.file_name = name.c_str();
    fclose(fp);
}

void GameMap::loadTiles(SDL_Renderer* renderer)
{
    char file_img[200];
    FILE* fp = NULL;

    for (int i = 0; i < MAX_TILES; ++i)
    {
        sprintf_s(file_img, "map/Terrain/%d.png", i);

        fopen_s(&fp, file_img, "rb");
        if (fp == NULL)
        {
            continue; // skip if unvailable
        }
        fclose(fp);

        tile_map[i].loadIMG(file_img, renderer);
    }
}

void GameMap::DrawMap(SDL_Renderer* renderer)
{
    int x1 = 0;
    int x2 = 0;

    int y1 = 0;
    int y2 = 0;

    int map_x = 0;
    int map_y = 0;

    //current dimension
    map_x = game_map.start_x/TILE_SIZE; //tile index
    x1 = (game_map.start_x%TILE_SIZE)*-1;
    x2 = x1 + SCREEN_WIDTH + (x1 == 0 ? 0:TILE_SIZE);

    map_y = game_map.start_y/TILE_SIZE;
    y1= (game_map.start_y%TILE_SIZE)*-1;
    y2 = y1 + SCREEN_HEIGHT + (y1 == 0 ? 0:TILE_SIZE);

    for (int i = y1; i < y2; i+=TILE_SIZE)
    {
        map_x = game_map.start_x/TILE_SIZE;
        for (int j = x1; j < x2; j+=TILE_SIZE)
        {
            int val = game_map.tile[map_y][map_x];
            if (val > 0)
            {
                tile_map[val].setRect(j, i);
                tile_map[val].render(renderer); //render each tile
            }
            map_x++;
        }
        map_y++;
    }

}
