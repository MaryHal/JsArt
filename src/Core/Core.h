#ifndef _Core_h_
#define _Core_h_

#include "CoreState.h"

#include <string>

class ResourceManager;
namespace sf
{
    class RenderWindow;
}

class Core
{
    private:
        static const std::string version;

        // Essentially our application. SFML uses this as the hub for a lot of functionality.
        static sf::RenderWindow* renderer;
        static ResourceManager* resources;

        static CoreState* currentState;
        static CoreState* nextState;
        static bool quit;

    public:
        static void init();
        static void deinit();
        static void run();

        static void changeState(CoreState* s);
        static void setNextState(CoreState* s);

        static void exit();
        static const std::string& getStateName();

        static ResourceManager* getResourceManager();

        static const std::string& getVersion();
};

#endif
