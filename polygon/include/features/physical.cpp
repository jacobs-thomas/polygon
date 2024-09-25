#include "physical.h"
#include "../scene.hpp"

void polygon::Physical::OnInitialise(Context& context) {
    b2BodyDef bodyDef;
    bodyDef.position = b2Vec2(possessor->GetGlobalTransform().GetTranslation().x, possessor->GetGlobalTransform().GetTranslation().y);
    bodyDef.type = (b2BodyType)type;

    boxBody =  context.GetBoxWorld().CreateBody(&bodyDef);
}

void polygon::Physical::AddForce(const Vector2f& direction, ForceType type) {
    if (type == ForceType::IMMEDIATE) {
        boxBody->ApplyLinearImpulseToCenter(b2Vec2(direction.x, direction.y), true);
        return;
    }

    boxBody->ApplyForceToCenter(b2Vec2(direction.x, direction.y), true);
}

void polygon::Physical::AddTorque(const float torque) {

    boxBody->ApplyTorque(torque, true);
}

void polygon::Physical::OnTick(Context& scene, const float deltaTime) {

    b2Vec2 translation = boxBody->GetPosition();

    possessor->SetGlobalTranslation(Vector2f(translation.x, translation.y));
}

polygon::Physical::~Physical() {
    b2Free(boxBody);
    boxBody = nullptr;
}