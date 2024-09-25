#ifndef POLYGON_SCRIPTABLE_H
#define POLYGON_SCRIPTABLE_H

#include <sol/sol.hpp>

#include "feature.h"

namespace polygon {

    // Forward Declarations:
    class Context;

    class ScriptFeature : public Feature {
    private:
        // Instance Fields:
        sol::state luaState;
        std::string scriptFilename; 
        sol::function luaOnInitialise;
        sol::function luaOnTick;

    public:
        // Constructor:
        ScriptFeature() {}

        // Methods:
        void LoadFile(const char* filename);
        void OnInitialise(Context& context);
        void OnTick(Context& context, float deltaTime);

    private:
        // Methods:
        void _BindToLua();
    };
}

#endif // !POLYGON_SCRIPTABLE_H
