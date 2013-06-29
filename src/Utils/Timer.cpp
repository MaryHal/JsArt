#include "Timer.h"

Timer::Timer(bool begin)
{
    running = begin;
    timeBuffer = 0.0f;
}

const float Timer::GetElapsedTime() const
{
    if (running)
        return timeBuffer + clock.getElapsedTime().asSeconds();
    return timeBuffer;
}

void Timer::Start()
{
    if (!running)
    {
        running = true;
        clock.restart();
    }
}

void Timer::Stop()
{
    if (running)
    {
        running = false;
        timeBuffer += clock.getElapsedTime().asSeconds();
    }
}

void Timer::Reset(bool restart)
{
    timeBuffer = 0.0f;
    running = restart;
    clock.restart();
}

bool Timer::IsRunning()
{
    return running;
}

