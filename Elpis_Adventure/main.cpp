#include "Game.hpp"
#include "GameObject.hpp"
#include "GameMap.hpp"
#include "Player.hpp"
#include "PlayerBar.hpp"
#include "Enemy.hpp"
#include "Boss.hpp"
#include "Explosion.hpp"
#include "TextObject.hpp"
#include "Geometry.hpp"
#include "Sounds.hpp"
#include "Timer.hpp"
#include "Menu.hpp"

GameObject gBackground;
TTF_Font* gFont = NULL;
TTF_Font* mFont = NULL;
Sounds beat;

bool init();
bool loadBackground();
std::vector<Enemy*> Gene_Enemy();
void close();


enum GameState
{
    MainMenu = 0,
    InGame = 1,
    ResetMenu = 2,
};

int main(int argc, char** argv)
{
    //time
    Timer fps_timer;
    Timer game_start;
    game_start.start();

    game_start.pause();

    //initialization
    if (init() == false) return -1;

    if (loadBackground() == false) return -1;

    GameMap game_map;
    game_map.loadMap("map//map1.txt");
    game_map.loadTiles(gRenderer);

    //menu
    Menu gMenu;
    Menu rMenu;

    //player
    Player player;
    player.loadIMG("graphics//player//run.png", gRenderer);
    player.setClips();
    PlayerBar player_bar;
    player_bar.Init(gRenderer);

    //enemy
    std::vector<Enemy*> enemy_list = Gene_Enemy();

    //Boss
    Boss gBoss;
    bool load = gBoss.loadIMG("graphics//Monster//golem.png", gRenderer);
    if (load)
    {
        gBoss.set_clips();
        int xpos = MAX_MAP_X * TILE_SIZE - SCREEN_WIDTH * 0.6;
        gBoss.set_xpos(xpos);
        gBoss.set_ypos(200);
    }
    

    //explosion
    Explosion explo;
    bool exp = explo.loadIMG("graphics//Spell2//explosion.png", gRenderer);
    if (!exp) return -1;
    explo.setClip();

    int num_die = 0;

    //Time Text
    TextObject game_time;
    game_time.setcolor(TextObject::WHITE_TEXT);

    //score text
    TextObject game_score;
    game_score.setcolor(TextObject::WHITE_TEXT);
    int mark = 0;
    int score = 0;

    //mana text
    TextObject player_mana;
    player_mana.setcolor(TextObject::WHITE_TEXT);


    // handle time after boss die
    int timeAfterBoss = 10;

    bool isquit = false;
    GameState game_state = MainMenu;

    while (!isquit)
    {
        switch (game_state)
        {
        case MainMenu:
            {
                int ret_menu = gMenu.ShowMenu(gRenderer, mFont);
                if (ret_menu == 1)
                {
                    isquit = true;
                }
                else
                {
                    isquit = false;
                    //Sounds
                    beat.addSound("audio//Unwelcome_School.wav");
                    beat.playSound();
                    game_state = InGame;
                }
            }
            
            break;
        case InGame:
            {
                fps_timer.start();

                while (SDL_PollEvent(&e) != 0)
                {
                    if (e.type == SDL_QUIT)
                    {
                        isquit = true;
                    }
                    beat.HandleSound(e);
                    player.HandleAction(e, gRenderer);
                }

                SDL_SetRenderDrawColor(gRenderer, 88, 128, 204, 255);
                SDL_RenderClear(gRenderer);

                gBackground.render(gRenderer);


                Map map_data = game_map.getMap();

                if (player.get_mana() > 0)
                {
                    player.HandleBall(gRenderer);
                }
                player.setMapXY(map_data.start_x, map_data.start_y);
                player.DoPlayer(map_data);
                player.Show(gRenderer);

                game_map.setMap(map_data);
                game_map.DrawMap(gRenderer);

                //Draw geometry
                GeometricFormat rect_size(0, 0, SCREEN_WIDTH, 40);
                ColorData color_data(36, 36, 36);
                Geometry::Rectangle(rect_size, color_data, gRenderer);

                GeometricFormat outlineBox(1, 1, SCREEN_WIDTH - 1, 38);
                ColorData color_data2(255, 255, 255);
                Geometry::RenderOutline(outlineBox, color_data2, gRenderer);

                player_bar.Show(gRenderer);


                for (int i = 0; i < enemy_list.size(); ++i)
                {
                    Enemy* mEnemy = enemy_list.at(i);
                    if (mEnemy != NULL)
                    {
                        mEnemy->set_mapXY(map_data.start_x, map_data.start_y);
                        mEnemy->ShowMove(gRenderer);
                        mEnemy->DoEnemy(map_data);
                        mEnemy->Show(gRenderer);
                        //mEnemy->MakePrj(gRenderer, SCREEN_WIDTH, SCREEN_HEIGHT);


                        //collision between player and monsters' magic
                        SDL_Rect pRect = player.getRectFrame();
                        bool mCol1 = false;
                        /*std::vector<Shooting*> eMagic_storage = mEnemy->get_prjtile_list();
                        for (int j = 0; j < eMagic_storage.size(); ++j)
                        {
                            Shooting* mPrjt = eMagic_storage.at(j);
                            if (mPrjt)
                            {
                                mCol1 = SDLGame::CheckCollision(mPrjt->getRect(), pRect);
                                if (mCol1 == true)
                                {
                                    mEnemy->ResetProjectile(mPrjt);
                                    break;
                                }
                            }
                        }*/

                        //collision between player & monster
                        SDL_Rect eRect = mEnemy->getRectFrame();
                        bool mCol2 = SDLGame::CheckCollision(pRect, eRect);


                        if (mCol1 || mCol2)
                        {
                            num_die++;
                            if (num_die <= 3)
                            {
                                player.setRect(0, 0);
                                player.set_come_back_time(60);
                                SDL_Delay(200);

                                player_bar.DecreaseHealth();
                                player_bar.render(gRenderer);
                                continue;
                            }
                            else
                            {
                                game_state = ResetMenu;
                            }
                        }
                    }
                }

                //spikes
                if (player.get_damaged())
                {
                    num_die++;
                    if (num_die <= 3)
                    {
                        player.setRect(0, 0);
                        player.set_come_back_time(60);
                        SDL_Delay(200);

                        player_bar.DecreaseHealth();
                        player.set_damaged_status(false);
                        player_bar.render(gRenderer);
                    }
                    else
                    {
                        game_state = ResetMenu;
                    }
                }
                //healing
                if (player.get_healed())
                {
                    if (num_die <= 3 && num_die > 0)
                    {
                        num_die--;

                        player_bar.IncreaseHealth();
                        player_bar.render(gRenderer);
                        player.set_healing_status(false);
                    }
                }

                int exp_width_frame = explo.get_frame_width();
                int exp_height_frame = explo.get_frame_height();

                //collision between magic and monsters
                if (player.get_mana() > 0)
                {
                    std::vector<Shooting*> magic_storage = player.get_ball();
                    for (int i = 0; i < magic_storage.size(); ++i)
                    {
                        Shooting* mPrj = magic_storage.at(i);
                        if (mPrj != NULL)
                        {
                            for (int j = 0; j < enemy_list.size(); ++j)
                            {
                                Enemy* mEnemy = enemy_list.at(j);
                                if (mEnemy != NULL)
                                {
                                    SDL_Rect eRect;
                                    eRect.x = mEnemy->getRect().x;
                                    eRect.y = mEnemy->getRect().y;
                                    eRect.w = mEnemy->get_width();
                                    eRect.h = mEnemy->get_height();

                                    SDL_Rect mRect = mPrj->getRect();

                                    bool mCol = SDLGame::CheckCollision(mRect, eRect);

                                    if (mCol)
                                    {
                                        if (player.get_magic() == WATER_LASER)
                                        {
                                            if (mEnemy->get_health() == 1) mEnemy->set_health(1);
                                            else
                                            {
                                                mEnemy->set_health(mEnemy->get_health() - 1);
                                            }
                                        }

                                        mEnemy->DecreaseHealth();
                                        for (int ex = 0; ex < 6; ++ex)
                                        {
                                            int xpos = mPrj->getRect().x + exp_width_frame * 0.5;
                                            int ypos = mPrj->getRect().y + exp_height_frame * 0.2;

                                            explo.set_frame(ex);
                                            explo.setRect(xpos, ypos);
                                            explo.Show(gRenderer);
                                        }
                                        player.RemoveBall(i);

                                        if (mEnemy->get_health() <= 0)
                                        {
                                            mark++;
                                            mEnemy->free();
                                            enemy_list.erase(enemy_list.begin() + j);

                                            player.set_mana(player.get_mana() + 10);

                                        }
                                        if (player.get_mana() >= 100)
                                        {
                                            player.set_mana(100);
                                        }

                                    }
                                }
                            }
                            // collision between player bullet with boss
                            SDL_Rect bossRect = gBoss.GetRectFrame();
                            SDL_Rect bRect = mPrj->getRect();
                            bool bCol1 = false;
                            bCol1 = SDLGame::CheckCollision(bossRect, bRect) && (gBoss.GetHealth() > 0)
                                && (mPrj->getMove());
                            if (bCol1)
                            {
                                if (player.get_magic() == WATER_LASER && player.get_magi_change() == true)
                                {
                                    gBoss.set_health(7);
                                    player.set_magi_change(false);
                                }
                                gBoss.DecreaseHealth();
                                for (int ex = 0; ex < 6; ex++)
                                {
                                    int xpos = mPrj->getRect().x + exp_width_frame * 0.5;
                                    int ypos = mPrj->getRect().y + exp_height_frame * 0.2;

                                    explo.set_frame(ex);
                                    explo.setRect(xpos, ypos);
                                    explo.Show(gRenderer);
                                }
                                player.RemoveBall(i);


                                if (gBoss.GetHealth() <= 0)
                                {   // boss die
                                    mark += 10;
                                    gBoss.SetThinkTime(10000);

                                    player.set_mana(100);
                                }
                            }

                        }
                    }
                }


                // after kill boss you will win
                if (gBoss.GetHealth() <= 0)
                {
                    timeAfterBoss--;
                    if (timeAfterBoss <= 0)
                    {
                        if (MessageBox(NULL, L"You Win", L"Info", MB_OK | MB_ICONSTOP) == IDOK)
                        {
                            close();
                            return 0;
                        }
                    }
                }


                //show time
                std::string str_time = "Time: ";
                game_start.unpaused();
                Uint32 time_val = game_start.getTicks() / 1000;
                Uint32 val_time = 180 - time_val;
                if (val_time <= 0)
                {
                    game_state = ResetMenu;
                }
                else
                {
                    std::string str_val = std::to_string(val_time);
                    str_time += str_val;

                    game_time.setText(str_time);
                    game_time.loadFromRenderedText(gFont, gRenderer);
                    game_time.RenderText(gRenderer, SCREEN_WIDTH - 200, 15);
                }

                //Show score
                score = player.get_score();
                std::string score_value = std::to_string(score + mark);
                std::string str_scr = "Score: ";
                str_scr += score_value;
                game_score.setText(str_scr);
                game_score.loadFromRenderedText(gFont, gRenderer);
                game_score.RenderText(gRenderer, SCREEN_WIDTH - 450, 15);

                int mana = player.get_mana();
                std::string mana_value = std::to_string(mana);
                std::string mn_scr = "Mana: ";
                mn_scr += mana_value + "/100";
                player_mana.setText(mn_scr);
                player_mana.loadFromRenderedText(gFont, gRenderer);
                player_mana.RenderText(gRenderer, SCREEN_WIDTH * 0.5 - 250, 15);


                //Show Boss
                int val = MAX_MAP_X * TILE_SIZE - (map_data.start_x + player.getRect().x);
                if (val <= SCREEN_WIDTH)
                {
                    gBoss.SetMapXY(map_data.start_x, map_data.start_y);
                    gBoss.DoBoss(map_data);
                    gBoss.MakeBullet(gRenderer, SCREEN_WIDTH, SCREEN_HEIGHT);
                    gBoss.Show(gRenderer);

                    // collision between boss bullet with player
                    bool bCol = false;
                    SDL_Rect pRect = player.getRectFrame();
                    std::vector<Shooting*> bossBullet = gBoss.get_bullet_list();
                    for (int bo = 0; bo < bossBullet.size(); ++bo)
                    {
                        Shooting* bossbul = bossBullet[bo];
                        if (bossbul != NULL)
                        {
                            SDL_Rect bRect = bossbul->getRect();
                            bCol = SDLGame::CheckCollision(bRect, pRect);
                            if (bCol)
                            {
                                gBoss.ResetProjectile(bossbul);
                                break;
                            }

                        }
                    }

                    // collision between player vs boss
                    bool bCol1 = false;
                    SDL_Rect bossRect = gBoss.GetRectFrame();
                    bCol1 = SDLGame::CheckCollision(pRect, bossRect) && (gBoss.GetHealth() > 0);

                    if (bCol1 || bCol)
                    {
                        num_die++;
                        if (num_die <= 3)
                        {
                            player.setRect(0, 0);
                            player.set_come_back_time(60);
                            SDL_Delay(200);

                            player_bar.DecreaseHealth();
                            player_bar.render(gRenderer);
                            continue;
                        }
                        else
                        {
                            game_state = ResetMenu;
                        }
                    }
                }

                SDL_RenderPresent(gRenderer);

                int real_time = fps_timer.getTicks();
                int time_per_frame = 1000 / FPS; //ms
                if (real_time < time_per_frame)
                {
                    int delay_time = time_per_frame - real_time;
                    if (delay_time >= 0)
                    {
                        SDL_Delay(delay_time);
                    }
                }
            }
            break;
            case ResetMenu:
            {
                SDL_Delay(1000);
                Mix_HaltMusic();
                
                int res_menu = rMenu.ShowResetMenu(gRenderer, mFont);
                if (res_menu == 1)
                {
                    isquit = true;
                }
                else
                {
                    isquit = false;

                    player.free();
                    gBoss.free();
                    
                    SDL_Delay(200);

                    game_start.start();

                    game_start.pause();


                    game_map.loadMap("map//map1.txt");
                    game_map.loadTiles(gRenderer);
                    enemy_list = Gene_Enemy();

                    if (player_bar.get_num() != 0) player_bar.setNum(0);

                    player_bar.Init(gRenderer);

                    player.set_x_pos(0);
                    player.set_y_pos(0);

                    player.set_magic(BLUE_FIRE);
                    player.set_mana(100);

                    num_die = 0;
                    mark = 0;
                    player.set_score(0);

                    timeAfterBoss = 10;

                    bool load = gBoss.loadIMG("graphics//Monster//golem.png", gRenderer);
                    if (load)
                    {
                        gBoss.set_clips();
                        int xpos = MAX_MAP_X * TILE_SIZE - SCREEN_WIDTH * 0.6;
                        gBoss.set_xpos(xpos);
                        gBoss.set_ypos(200);
                    }

                    gBoss.set_health(15);


                    game_start.unpaused();
                    Uint32 time_val = game_start.getTicks() / 1000;
                    Uint32 val_time = 180 - time_val;

                    //Sounds
                    beat.addSound("audio//Unwelcome_School.wav");
                    beat.playSound();
                    game_state = InGame;
                }
                break;
            }
        }
        
    }

    for (int i = 0; i < enemy_list.size(); ++i)
    {
        Enemy* mEnemy = enemy_list.at(i);
        if (mEnemy)
        {
            mEnemy->free();
            mEnemy = NULL;
        }
    }
    enemy_list.clear();

    close();
    return 0;
}

bool init()
{
    bool isRunning = true;
    //Initialize SDL
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        std::cout << "SDL could not initialize! SDL Error: " << SDL_GetError() << std::endl;
        return false;
    }

    //Set texture filtering to linear
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

    //create window
    gWindow = SDL_CreateWindow("Elpis Adventure", SDL_WINDOWPOS_UNDEFINED,
                                SDL_WINDOWPOS_UNDEFINED,
                                SCREEN_WIDTH,
                                SCREEN_HEIGHT,
                                SDL_WINDOW_SHOWN);
    if (gWindow == NULL)
    {
        std::cout << "Window could not be created! SDL Error:" << SDL_GetError() << std::endl;
        isRunning = false;
    }
    else
    {
        gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
        if (gRenderer == NULL)
        {
            std::cout << "Renderer could not be created! SDL Error: " << SDL_GetError() << std::endl;
            isRunning = false;
        }
        else
        {
            //Initialize renderer color
            SDL_SetRenderDrawColor(gRenderer, 88, 128, 204, 255);

            //Initialize PNG loading
            int imgFlags = IMG_INIT_PNG;
            if (!(IMG_Init(imgFlags) & imgFlags))
            {
                std::cout << "SDL_image could not initialize! SDL_image Error:" << IMG_GetError() << std::endl;
                isRunning = false;
            }

            if (TTF_Init() == -1)
            {
                std::cout << "SDL_ttf could not initialize! SDL_ttf Error: " << TTF_GetError() << std::endl;
                isRunning = false;
            }
            else
            {
                gFont = TTF_OpenFont("font//dlxfont_.ttf", 15);
                if (gFont == NULL)
                {
                    std::cout << "Failed to load lazy font! SDL_ttf Error: " << TTF_GetError() << std::endl;
                    isRunning = false;
                }
                mFont = TTF_OpenFont("font//dlxfont_.ttf", 30);
                if (mFont == NULL)
                {
                    std::cout << "Failed to load lazy font! SDL_ttf Error: " << TTF_GetError() << std::endl;
                    isRunning = false;
                }
            }

            //Initialize SDL_mixer
            if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
            {
                std::cout<< "SDL_mixer could not initialize!SDL_mixer Error : " << Mix_GetError() << std::endl;
                isRunning = false;
            }
        }
    }
    return isRunning;

}

bool loadBackground()
{
    bool load = gBackground.loadIMG("graphics//Background1.png", gRenderer);
    if (load == false) return false;
    return true;
}

std::vector<Enemy*> Gene_Enemy()
{
    std::vector<Enemy*> enemy_list;

    Enemy* dynamic_enemies = new Enemy[MAX_ENEMY];

    for (int i = 0; i < MAX_ENEMY-5; ++i)
    {
        Enemy* mEnemy = (dynamic_enemies + i);
        if (mEnemy != NULL)
        {
            mEnemy->loadIMG("graphics//Monster//fire_worm.png", gRenderer);
            mEnemy->setclips();
            mEnemy->InitEnemy();
            mEnemy->set_posx(670.0f + i*560.0f);
            mEnemy->set_posy(480.0f);
            mEnemy->set_move(Enemy::MOVING_ENEMY);
            mEnemy->set_health(3);
            

            int pos1 = mEnemy->get_posx() - 60;
            int pos2 = mEnemy->get_posx() + 60;
            mEnemy->set_animation(pos1, pos2);

            enemy_list.push_back(mEnemy);
        }
    }

    Enemy* dynamic1_enemies = new Enemy[MAX_ENEMY];

    for (int i = 0; i < MAX_ENEMY-5; ++i)
    {
        Enemy* mEnemy = (dynamic1_enemies + i);
        if (mEnemy != NULL)
        {
            mEnemy->loadIMG("graphics//Monster//slime.png", gRenderer);
            mEnemy->setclips();
            mEnemy->InitEnemy();
            mEnemy->set_posx(500.0f + i * 500.0f);
            mEnemy->set_posy(560.0f);
            mEnemy->set_move(Enemy::BOUNCING_ENEMY);
            mEnemy->set_health(2);

            enemy_list.push_back(mEnemy);
        }
    }

    Enemy* enemies = new Enemy[MAX_ENEMY];

    for (int i = 0; i < MAX_ENEMY; ++i)
    {
        Enemy* mEnemy = (enemies + i);
        if (mEnemy != NULL)
        {
            mEnemy->loadIMG("graphics//Monster//brain_eater.png", gRenderer);
            mEnemy->setclips();
            mEnemy->InitEnemy();
            mEnemy->set_left(0);
            mEnemy->set_posx(600.0f + i * 500.0f);
            mEnemy->set_posy(448.0f);
            mEnemy->set_move(Enemy::STATIC_ENEMY);

            enemy_list.push_back(mEnemy);
        }
    }
    return enemy_list;
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
    Mix_Quit();
    IMG_Quit();
    SDL_Quit();
    std::cout << "System cleared" << std::endl;
}
