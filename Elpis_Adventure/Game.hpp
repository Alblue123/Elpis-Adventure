#pragma once

#include <SDL.h>
#include <windows.h>
#include <cstdio>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>

static SDL_Window* gWindow = NULL;
static SDL_Renderer* gRenderer = NULL;
static SDL_Event e;

//Screen
const int FPS = 30;
const int SCREEN_WIDTH = 1024;
const int SCREEN_HEIGHT = 512;
const int gPixelBit = 32;

//color

const int COLOR_KEY_R = 171;
const int COLOR_KEY_G = 173;
const int COLOR_KEY_B = 171;

//map
#define BLANK_TILE 0
#define TILE_SIZE 32
#define MAX_MAP_X 320
#define MAX_MAP_Y 20

//supportive
#define FRUIT 42
#define JUMPY 43
#define HEART 44
#define SPIKE_H 45
#define SPIKE_V 46
#define MUSHROOM 47
#define MANAMANA 48

#define MAX_ENEMY 20
enum Magic
{
    BLUE_FIRE = 30,
    WATER_LASER = 31,
    FIRE_BALL = 32,
};


 struct Input
{
    int left;
    int right;
    int slide;
    int jump;
    int stop;
    int attack;
};

 struct Map
{
    int start_x;
    int start_y;

    int max_x;
    int max_y;

    int tile[MAX_MAP_Y][MAX_MAP_X];

    std::string file_name;
};

 namespace SDLGame
{
     bool CheckCollision(const SDL_Rect& boxA, const SDL_Rect& boxB);

}