#include "CoreRegistry.h"

std::map<std::string, CoreState*>& CoreRegistry::registry()
{
    static std::map<std::string, CoreState*>* r = new std::map<std::string, CoreState*>();
    return *r;
}

RegisterState::RegisterState(const std::string& identifier, CoreState* state)
{
    CoreRegistry::registerGame(identifier, state);
}

bool CoreRegistry::alreadyExists(const std::string& identifier)
{
    return registry().find(identifier) != registry().end();
}

void CoreRegistry::registerGame(const std::string& identifier, CoreState* entry)
{
    if (alreadyExists(identifier))
        return;

    registry()[identifier] = entry;
}

CoreState* CoreRegistry::getGame(const std::string& identifier)
{
    return alreadyExists(identifier) ? registry()[identifier] : NULL;
}

const std::string& CoreRegistry::getStateName(CoreState* s)
{
    for (std::map<std::string, CoreState*>::iterator iter = registry().begin();
         iter != registry().end();
         ++iter)
    {
        if (iter->second == s)
            return iter->first;
    }

    static std::string str = "<No State Name>";
    return str;
}

int CoreRegistry::getGameCount()
{
    return registry().size();
}
