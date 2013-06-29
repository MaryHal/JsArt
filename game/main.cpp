#include <Core/Core.h>
#include <Core/CoreRegistry.h>

int main(int argc, const char *argv[])
{
    Core::init();
    Core::changeState(CoreRegistry::getGame("Game"));
    Core::run();
    Core::deinit();

    return 0;
}
