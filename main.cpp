#include "Game.hpp"
#include "GameObject.hpp"
#include "GameMap.hpp"
#include "Player.hpp"
#include "Timer.hpp"

bool init();
bool loadBackground();
void close();

GameObject gBackground;

int main(int argc, char* argv[])
{
    Timer fps_timer;

    if (init() == false) return -1;

    if (loadBackground() == false) return -1;

    GameMap game_map;
    game_map.loadMap("map//map1.txt");
    game_map.loadTiles(gRenderer);

    Player player;
    player.loadIMG("graphics//player//run.png", gRenderer);
    player.setClips();

	bool isquit = false;
	while (!isquit)
    {
        fps_timer.start();

        if (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_QUIT)
            {
                isquit = true;
            }
            player.HandleAction(e, gRenderer);
        }
         SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);
         SDL_RenderClear(gRenderer);

         gBackground.render(gRenderer, NULL);

         Map map_data = game_map.getMap();

         player.setMapXY(map_data.start_x, map_data.start_y);
         player.DoPlayer(map_data);
         player.Show(gRenderer);

         game_map.setMap(map_data);
         game_map.DrawMap(gRenderer);

         int real_time = fps_timer.getTicks();
         int time_per_frame = 1000/FPS; //ms
         if (real_time < time_per_frame)
         {
             int delay_time = time_per_frame - real_time;
             if (delay_time >= 0)
             {
                 SDL_Delay(delay_time);
             }
         }

         SDL_RenderPresent(gRenderer);
    }

    close();
    return 0;
}

bool init()
{
    bool isRunning = true;
    //Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO) < 0 )
	{
		std::cout << "SDL could not initialize! SDL Error: " << SDL_GetError() << std::endl;
		return false;
	}

	     //Set texture filtering to linear
        SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" );

        //create window
        gWindow = SDL_CreateWindow("Elpis Adventure", SDL_WINDOWPOS_UNDEFINED,
                                    SDL_WINDOWPOS_UNDEFINED,
                                    SCREEN_WIDTH,
                                    SCREEN_HEIGHT,
                                    SDL_WINDOW_SHOWN);
            if( gWindow == NULL )
                {
                    std::cout << "Window could not be created! SDL Error:" << SDL_GetError() << std::endl;
                    isRunning = false;
                }
            else
                {
                    gRenderer = SDL_CreateRenderer( gWindow, -1,
                                                   SDL_RENDERER_ACCELERATED);
                    if( gRenderer == NULL )
                    {
                        std::cout<< "Renderer could not be created! SDL Error: " << SDL_GetError() << std::endl;
                        isRunning = false;
                    }
                    else
                    {
                        //Initialize renderer color
                        SDL_SetRenderDrawColor( gRenderer, 255, 255, 255, 255 );

                        //Initialize PNG loading
                        int imgFlags = IMG_INIT_PNG;
                        if( !( IMG_Init( imgFlags ) & imgFlags ) )
                        {
                            std::cout<< "SDL_image could not initialize! SDL_image Error:" << IMG_GetError() << std::endl;
                            isRunning = false;
                        }
                    }
                }
	return isRunning;

}

bool loadBackground()
{
    bool load = gBackground.loadIMG("graphics//background.png", gRenderer);
    if (load == false) return false;
    return true;
}

void close()
{
     //Destroy window
    gBackground.free();

    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    gRenderer = NULL;
    gWindow = NULL;

    //Quit the subsytem
    IMG_Quit();
    SDL_Quit();
    std::cout<< "System cleared" << std::endl;
}
