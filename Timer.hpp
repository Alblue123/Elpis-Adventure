#pragma once

#include "Game.hpp"

class Timer
{
public:
    Timer();
    ~Timer();

    void start();
    void stop();
    void pause();
    void unpaused();

    int getTicks();

    bool is_started();
    bool is_paused();

private:
    int start_tick;
    int pause_tick;

    bool is_start;
    bool is_pause;

};
