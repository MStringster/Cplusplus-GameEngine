#pragma once
#include "PhysicsComponent.h"

class GameObject;
//player physics component, used for movement
class PlayerPhysicsComponent : public PhysicsComponent
{
private:

public:
    //constructor, parameters: gameObject - owner of this component
    PlayerPhysicsComponent(GameObject* gameObject);
    //called every frame, paremeters: frametime - time between frames
    void update(float frametime) override;
};
