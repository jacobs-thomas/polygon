#ifndef POLYGON_PHYSICAL_H
#define POLYGON_PHYSICAL_H

#include <memory>
#include <box2d/box2d.h>

#include "feature.h"
#include "../type_definitions.hpp"
#include "../transform.h"
#include "../shaders/shader.h"
#include "../texture2D.hpp"
#include "../sprite_renderer.h"
#include "../shaders/shader.h"
#include "../sprite.h"
#include "../nodes/node.hpp"
#include "renderable.h"

namespace polygon {
    class Physical : public Feature {
    public:
        // Enums:
        enum class ForceType {
            IMMEDIATE = 0,
            GRADUAL = 1
        };

        enum class BodyType {
            STATIC_BODY = 0,
            KINEMATIC_BODY = 1,
            DYNAMIC_BODY = 2
        };

    private:
        // Instance Attributes:
        b2Body* boxBody = nullptr;
        BodyType type = BodyType::DYNAMIC_BODY;

    public:
        // Constructor:
        Physical() { }

        // Destructor:
        ~Physical();

        // Methods:
        void OnInitialise(Context& context);
        void AddForce(const Vector2f& direction, ForceType type = ForceType::IMMEDIATE);
        void AddTorque(const float torque);
        void OnTick(Context& scene, const float deltaTime);
    };
}

#endif // !POLYGON_PHYSICAL_H
