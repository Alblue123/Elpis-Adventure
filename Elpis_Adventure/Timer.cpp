#include "Timer.hpp"

Timer::Timer()
{
    start_tick = 0;
    pause_tick = 0;

    is_pause = false;
    is_start = false;
}

Timer::~Timer()
{

}

void Timer::start()
{
    is_start = true;
    is_pause = false;
    start_tick = SDL_GetTicks();
}

void Timer::stop()
{
    is_start = false;
    is_pause = false;

}

void Timer::pause()
{
    if (is_start == true && is_pause == false)
    {
        is_pause = true;
        pause_tick = SDL_GetTicks() - start_tick;
    }
}
void Timer::unpaused()
{
    if (is_pause == true)
    {
        is_pause = false;
        start_tick = SDL_GetTicks() - pause_tick;
        pause_tick = 0;
    }
}

int Timer::getTicks()
{
    if (is_start == true)
    {
        if (is_pause == true)
        {
            return pause_tick;
        }
        else
        {
            return SDL_GetTicks() - start_tick;
        }
    }
    return 0;
}

bool Timer::is_started()
{
    return is_start;
}

bool Timer::is_paused()
{
    return is_pause;
}

