#pragma once
#include "PhysicsComponent.h"

class GameObject;
//How bullets move
class BulletPhysicsComponent : public PhysicsComponent
{
private:
    float lifetime; //how long the bullet will be active for
public:
    //constructor, parameters: gameObject - owner of this component
    BulletPhysicsComponent(GameObject* gameObject);
    //called every frame, paremeters: frametime - time between frames
    void update(float frametime) override;

};
