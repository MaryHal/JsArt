#ifndef _CoreRegistry_h_
#define _CoreRegistry_h_

#include <map>
#include <string>

#define REGISTER_GAME(name,game)  static RegisterState thisEntry(std::string(name),new game);

class CoreState;

struct RegisterState
{
    public:
    RegisterState(const std::string& identifier, CoreState* state);
};

class CoreRegistry
{
    private:
    static std::map<std::string, CoreState*>& registry();

    public:
    static bool alreadyExists(const std::string& identifier);

    static void registerGame(const std::string& identifier, CoreState* entry);
    static CoreState* getGame(const std::string& identifier);

    static const std::string& getStateName(CoreState* s);

    static int getGameCount();
};

#endif

