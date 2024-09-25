#ifndef POLYGON_RIGIDBODY_HPP
#define POLYGON_RIGIDBODY_HPP


#include <box2d/box2d.h>
#include "../node.hpp"


namespace polygon {

	class Rigidbody : public Node {
    public:
        // Enum:
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
        // Methods:
        virtual void OnInitialise(Scene& scene) {
            
            b2BodyDef bodyDef;
            bodyDef.position = b2Vec2(GetGlobalTransform().GetTranslation().x, GetGlobalTransform().GetTranslation().y);
            bodyDef.type = (b2BodyType)type;

            boxBody = scene.GetWorldID().CreateBody(&bodyDef);
        }

        void AddForce(const Vector2f& direction, ForceType type = ForceType::IMMEDIATE) {

            if (type == ForceType::IMMEDIATE) {
                boxBody->ApplyLinearImpulseToCenter(b2Vec2(direction.x, direction.y), true);
               return;
            }

            boxBody->ApplyForceToCenter(b2Vec2(direction.x, direction.y), true);
        }

        void AddTorque(const float torque) {

            boxBody->ApplyTorque(torque, true);
        }

        virtual void OnTick(Scene& scene, const float deltaTime) override {
            b2Vec2 translation = boxBody->GetPosition();
            //SetGlobalTranslation(Vector2f(translation.x, translation.y));

            // Ensure that the global transform is up-to-date
            GetGlobalTransform();
        }

        virtual void OnFixedTick(Scene& scene, const float deltaTime) { 
        
        }
	};
}


#endif // !POLYGON_RIGIDBODY_HPP