#ifndef _Timer_h_
#define _Timer_h_

#include <SFML/System/Clock.hpp>

// Simple Timer
class Timer
{
    private:
        sf::Clock clock;
        float timeBuffer;
        bool running;

    public:
        Timer(bool begin = false);

        const float GetElapsedTime() const;

        void Start();
        void Stop();
        void Reset(bool restart = false);

        bool IsRunning();
};

#endif

