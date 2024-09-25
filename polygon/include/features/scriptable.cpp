#include "scriptable.h"
#include "physical.h"
#include "renderable.h"

void polygon::ScriptFeature::LoadFile(const char* filename) {
    this->scriptFilename = filename;

    // Initialize Lua
    luaState.open_libraries(sol::lib::base);

    // Load the Lua script
    luaState.script_file(scriptFilename);

    // Bind C++ methods and properties to Lua
    _BindToLua();

    // Get Lua functions for lifecycle events
    luaOnInitialise = luaState["OnInitialise"];
    luaOnTick = luaState["OnTick"];
}

void polygon::ScriptFeature::_BindToLua() {
    // Bind ForceType
    luaState["ForceType"] = luaState.create_table_with(
        "IMMEDIATE", Physical::ForceType::IMMEDIATE,
        "GRADUAL", Physical::ForceType::GRADUAL
    );

    // Bind Vector2f
    luaState.new_usertype<Vector2f>("Vector2f",
        sol::constructors<Vector2f(float, float)>(),
        "x", &Vector2f::x,
        "y", &Vector2f::y
        );

    // Bind Physical class
    luaState.new_usertype<Physical>("Physical",
        sol::base_classes, sol::bases<Feature>(),
        "AddForce", [](Physical& p, sol::table dir, sol::optional<Physical::ForceType> type) {
            if (dir["x"].valid() && dir["y"].valid()) {
                Vector2f direction = { dir["x"], dir["y"] };
                if (type) {
                    p.AddForce(direction, *type);
                }
                else {
                    p.AddForce(direction);  // Default to IMMEDIATE if ForceType is not passed
                }
            }
            else {
                throw std::runtime_error("Invalid direction table");
            }
        },
        "AddTorque", &Physical::AddTorque
            );

    // Bind Node class
    luaState.new_usertype<Node>("Node",
        "AddSpriteRendererFeature", &Node::AddFeature<Renderable>,

        // Capture `this` so the lambda can access `luaState`
        "AddPhysicalFeature", [this](Node& node) -> sol::object {
            std::weak_ptr<Physical> weakPhysical = node.AddFeature<Physical>();
            std::shared_ptr<Physical> physical = weakPhysical.lock();  // Try to lock weak_ptr

            // Check if physical is still valid
            if (physical) {
                return sol::make_object(luaState, physical);  // Return valid object
            }
            else {
                return sol::nil;  // Return nil if weak_ptr is expired
            }
        },

        "GetGlobalTranslation", &Node::GetGlobalTranslation
            );

    // Bind Feature class
    luaState.new_usertype<Feature>("Feature",
        "GetPossessor", [](Feature* f) { return f->possessor; }
    );

    // Bind SpriteRendererFeature class
    luaState.new_usertype<Renderable>("SpriteRendererFeature",
        sol::base_classes, sol::bases<Feature>(),
        "SetSprite", &Renderable::SetSprite,
        "SetShader", &Renderable::SetShader
        );
}

void polygon::ScriptFeature::OnInitialise(Context& context) {
    if (luaOnInitialise.valid()) {
        luaOnInitialise(*possessor);  // Pass the possessor (Node) to the Lua script.
    }
}

void polygon::ScriptFeature::OnTick(Context& context, float deltaTime) {
    if (luaOnTick.valid()) {
        luaOnTick(*possessor, deltaTime);  // Pass the possessor (Node) and deltaTime to Lua.
    }
}