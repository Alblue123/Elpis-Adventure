#pragma once

#include <SDL.h>
#include <windows.h>
#include <cstdio>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <vector>
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
#define MAX_MAP_Y 19

 struct Input
 {
     int left;
     int right;
     int slide;
     int jump;
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
